"""
实验二：组流
"""

import dpkt
import numpy as np
# import sys
from dpkt.compat import compat_ord
from scapy.all import *


class Flow(object):
    src_ip = None
    dst_ip = None
    src_mac = None
    dst_mac = None
    src_port = None
    dst_port = None
    trans_layer_proto = None
    time_stamps = None
    packets = None
    length = 0
    pkt_size_seq = None

    def __init__(self, src_ip, dst_ip, src_mac, dst_mac, src_port, dst_port, trans_layer_proto, packet, timestamp,
                 length, pkt_size):
        self.src_ip = src_ip
        self.dst_ip = dst_ip
        self.src_mac = src_mac
        self.dst_mac = dst_mac
        self.src_port = src_port
        self.dst_port = dst_port
        self.var = 0
        self.trans_layer_proto = trans_layer_proto
        self.packets = list()
        self.packets.append(packet)
        self.time_stamps = list()
        self.time_stamps.append(timestamp)
        self.length = length
        self.pkt_size_seq = list()
        self.pkt_size_seq.append(pkt_size)

    def append_packet(self, packet, timestamp, pktsize):
        self.packets.append(packet)
        self.time_stamps.append(timestamp)
        self.pkt_size_seq.append(pktsize)


def mac_addr(address):
    # 将MAC地址转换为可读/可打印的字符串
    return ':'.join('%02x' % compat_ord(b) for b in address)


def inet_to_str(inet):
    # 将inet对象转换为字符串
    # 先尝试ipv4再尝试ipv6
    try:
        return socket.inet_ntop(socket.AF_INET, inet)
    except ValueError:
        return socket.inet_ntop(socket.AF_INET6, inet)


def get_IP_packet(pkt):
    # pkt：全部数据
    eth = dpkt.ethernet.Ethernet(pkt)
    # 确保以太网帧包含一个IP包
    # print('src mac address:', mac_addr(eth.src))
    # print('dst mac address:', mac_addr(eth.dst))

    if not isinstance(eth.data, dpkt.ip.IP):
        print('Non IP Packet type not supported %s\n' % eth.data.__class__.__name__)
    #  ip数据包
    ip_packet = eth.data
    # src_ip = ip_packet.src
    # dst_ip = ip_packet.dst
    # print('src IP address:', inet_to_str(ip_packet.src) )
    # print('dst IP address:', inet_to_str(ip_packet.dst))

    return ip_packet


def pcap_read(pcap_file):
    pcap = dpkt.pcap.Reader(open(pcap_file, "rb"))
    pkt_list = pcap.readpkts()
    pkt_result = []
    tms_result = []
    for (ts, pkt) in pkt_list:
        try:
            """
            ip_packet = get_IP_packet(pkt)
            print("该Pcap数据包IP层数据包长度：", ip_packet.len)
            print("该Pcap数据包存活时间：", ip_packet.ttl)
            trans_packet = ip_packet.data  # 传输层的数据
            data = trans_packet.data  # 应用层数据
            print("该Pcap数据包应用层数据：", data)
            """
            pkt_result.append(pkt)
            tms_result.append(ts)
        except Exception as e:
            print(e)
            continue
    return tms_result, pkt_result


def flow_combine(ip_pkt_list, ip_tms_list, flow_definition):
    flow_list = []
    src_port = None
    dst_port = None
    length = 1
    trans_layer_proto = None
    src_mac = None
    dst_mac = None
    for (pkt_stream, tms) in zip(ip_pkt_list, ip_tms_list):
        eth = dpkt.ethernet.Ethernet(pkt_stream)
        src_mac = mac_addr(eth.src)
        dst_mac = mac_addr(eth.dst)
        pkt = eth.data
        src_ip = pkt.src
        dst_ip = pkt.dst
        pkt_size = pkt.__len__()
        if pkt.p == dpkt.ip.IP_PROTO_TCP:  # TCP数据包
            tcp_packet = pkt.tcp
            src_port = tcp_packet.sport
            dst_port = tcp_packet.dport
            trans_layer_proto = dpkt.ip.IP_PROTO_TCP

        elif pkt.p == dpkt.ip.IP_PROTO_UDP:  # UDP数据包
            udp_packet = pkt.udp
            src_port = udp_packet.sport
            dst_port = udp_packet.dport
            trans_layer_proto = dpkt.ip.IP_PROTO_UDP
        if len(flow_list) == 0:  # 初次
            flow = Flow(src_ip, dst_ip, src_mac, dst_mac, src_port, dst_port, trans_layer_proto, eth, tms, length,
                        pkt_size)
            flow_list.append(flow)
        else:
            flow_is_exist = False
            if flow_definition == 1:  # 单向流
                for flow_unit in flow_list:
                    # 根据五元组判断是否同流
                    if ((flow_unit.src_ip, flow_unit.dst_ip, flow_unit.src_port, flow_unit.dst_port,
                         flow_unit.trans_layer_proto) == (src_ip, dst_ip, src_port, dst_port, trans_layer_proto)):
                        # 同流则将该数据包加入
                        flow_unit.append_packet(pkt, tms, pkt_size)
                        flow_unit.length += 1
                        flow_is_exist = True
                        break
            elif flow_definition == 2:  # 双向流
                for flow_unit in flow_list:
                    # 双向流还应添加源、目的相反的判断逻辑
                    same_flow = (((flow_unit.src_ip, flow_unit.dst_ip, flow_unit.src_port,
                                   flow_unit.dst_port, flow_unit.trans_layer_proto) == (
                                      src_ip, dst_ip, src_port, dst_port, trans_layer_proto)) or (
                                         (flow_unit.src_ip, flow_unit.dst_ip, flow_unit.src_port, flow_unit.dst_port,
                                          flow_unit.trans_layer_proto) == (
                                             dst_ip, src_ip, dst_port, src_port, trans_layer_proto)))
                    if same_flow:
                        # 同流则将该数据包加入
                        flow_unit.append_packet(pkt, tms, pkt_size)
                        flow_unit.length += 1
                        flow_is_exist = True
                        break
            if not flow_is_exist:
                flow = Flow(src_ip, dst_ip, src_mac, dst_mac, src_port, dst_port, trans_layer_proto, eth, tms, length,
                            pkt_size)
                flow_list.append(flow)

    return flow_list


def var_set_calc(flow_list):
    var_set = []
    for flow in flow_list:
        flow.var = np.var(flow.pkt_size_seq)
        var_set.append(flow.var)
    return var_set


def print_flow_list(flow_list):
    print('流总数：', len(flow_list))
    idx = 0
    for flow in flow_list:
        idx += 1
        if flow.trans_layer_proto == dpkt.ip.IP_PROTO_TCP:
            protocol = 'TCP'
        else:
            protocol = 'UDP'
        print('第', idx, '条流：')
        print('  - [{}, {}, {}, {}, {}]'.format(inet_to_str(flow.src_ip), inet_to_str(flow.dst_ip), flow.src_port,
                                                flow.dst_port, protocol))
        print('  - 源MAC地址：', flow.src_mac)
        print('  - 目的MAC地址：', flow.dst_mac)
        print('  - 报文长度序列：', flow.pkt_size_seq)
        print('  - 报文长度方差：', flow.var)


def hist_log_plot(x, plotspot, title):
    logbins = np.append([0], np.power(10, np.arange(0, int(np.log10(max(x))) + 1, 0.5)))
    plt.subplot(plotspot)
    plt.hist(x, bins=logbins)
    plt.xscale('log')
    plt.title(title)
    plt.xlabel("报文长度方差")
    plt.ylabel("流数量")


if __name__ == "__main__":
    plt.rcParams['font.sans-serif'] = ['SimHei']

    pcap_name = "test.pcap"
    tms1, pkt1 = pcap_read(pcap_name)

    # 单向流
    flow_list_one_way = flow_combine(pkt1, tms1, 1)  # 组流
    var_set_one_way = var_set_calc(flow_list_one_way)  # 计算方差
    print_flow_list(flow_list_one_way)  # 打印流信息
    hist_log_plot(var_set_one_way, 221, "方差分布-单向流")  # 绘制流方差分布图

    # 双向流
    flow_list_two_way = flow_combine(pkt1, tms1, 2)  # 组流
    var_set_two_way = var_set_calc(flow_list_two_way)  # 计算方差
    print_flow_list(flow_list_two_way)  # 打印流信息
    hist_log_plot(var_set_two_way, 222, "方差分布-双向流")  # 绘制流方差分布图

    # 绘图
    plt.show()

