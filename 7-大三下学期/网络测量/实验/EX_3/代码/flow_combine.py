import codecs

import dpkt
import numpy as np
import pandas as pd
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
    timestamps = None
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
        self.trans_layer_proto = trans_layer_proto
        self.packets = list()
        self.packets.append(packet)
        self.timestamps = list()
        self.timestamps.append(timestamp)
        self.length = length
        self.pkt_size_seq = list()
        self.pkt_size_seq.append(pkt_size)

    def append_packet(self, packet, timestamp, pktsize):
        self.packets.append(packet)
        self.timestamps.append(timestamp)
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
    if not isinstance(eth.data, dpkt.ip.IP):
        print('Non IP Packet type not supported %s\n' % eth.data.__class__.__name__)
    #  ip数据包
    ip_packet = eth.data

    return ip_packet


def pcap_read(pcap_file):
    pcap = dpkt.pcap.Reader(open(pcap_file, "rb"))
    pkt_list = pcap.readpkts()
    pkt_result = []
    tms_result = []
    for (ts, pkt) in pkt_list:
        try:
            ip_packet = get_IP_packet(pkt)
            trans_packet = ip_packet.data  # 传输层的数据
            data = trans_packet.data  # 应用层数据
            pkt_result.append(pkt)
            tms_result.append(ts)
        except Exception as e:
            print(e)
            continue
    return tms_result, pkt_result


def flow_combine(ip_pkt_list, ip_tms_list):
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
        src_ip = inet_to_str(pkt.src)
        dst_ip = inet_to_str(pkt.dst)
        if pkt.p == dpkt.ip.IP_PROTO_TCP:  # TCP数据包
            tcp_packet = pkt.tcp
            src_port = tcp_packet.sport
            dst_port = tcp_packet.dport
            trans_layer_proto = dpkt.ip.IP_PROTO_TCP
            pkt_size = tcp_packet.__len__()
            if src_ip > dst_ip:
                pkt_size = - pkt_size
        elif pkt.p == dpkt.ip.IP_PROTO_UDP:  # UDP数据包
            udp_packet = pkt.udp
            src_port = udp_packet.sport
            dst_port = udp_packet.dport
            trans_layer_proto = dpkt.ip.IP_PROTO_UDP
            pkt_size = udp_packet.__len__()
            if src_ip > dst_ip:
                pkt_size = - pkt_size
        if len(flow_list) == 0:  # 初次
            flow = Flow(src_ip, dst_ip, src_mac, dst_mac, src_port, dst_port, trans_layer_proto, eth, tms, length,
                        pkt_size)
            flow_list.append(flow)
        else:
            flow_is_exist = False
            # 本实验中考虑双向流
            for flow_unit in flow_list:
                if ((
                            flow_unit.src_ip == src_ip and flow_unit.dst_ip == dst_ip and flow_unit.src_port == src_port and flow_unit.dst_port == dst_port) or (
                            flow_unit.src_ip == dst_ip and flow_unit.dst_ip == src_ip and flow_unit.src_port == dst_port and flow_unit.dst_port == src_port)) and flow_unit.trans_layer_proto == trans_layer_proto:
                    flow_is_exist = True
                    flow_unit.append_packet(eth, tms, pkt_size)
                    flow_unit.length = flow_unit.length + 1
                    break
            if flow_is_exist == False:
                #  插入新流
                flow = Flow(src_ip, dst_ip, src_mac, dst_mac, src_port, dst_port, trans_layer_proto, eth, tms, length,
                            pkt_size)
                flow_list.append(flow)

    return flow_list


# 提取五元组和对应的报文长度序列
def extractFlow(flow_list):
    session_list = []

    for idx in range(len(flow_list)):
        ''' 
            补全此处代码
            此处需要提取每条流的五元组和对应的报文长度序列
            session_list的每一行对应一条流，第一列是五元组组成的列表，第二列是报文长度序列组成的列表
        '''
        five_tup = [flow_list[idx].src_ip, flow_list[idx].dst_ip, flow_list[idx].src_port, flow_list[idx].dst_port,
                    flow_list[idx].trans_layer_proto]
        session_list.append([five_tup, flow_list[idx].pkt_size_seq])

    return session_list


# 将提取出的流信息写入csv文件
def data_write_csv(file_write_path, datas, flag):
    file_csv = codecs.open(file_write_path, 'a+', 'utf-8')
    farray = np.array(datas, dtype=object)
    df = pd.DataFrame(data=farray)
    if flag == True:
        df.columns = ['five_tup', 'flow_pktlen']
        df.to_csv(file_csv, index=False)
    else:
        df.to_csv(file_csv, header=None, index=False)
    print("文件保存成功")


if __name__ == "__main__":
    cwd = os.getcwd()
    path = os.path.join(cwd, 'data/')

    for root, dirs, _ in os.walk(path):
        for dir in dirs:
            data_path = os.path.join(root, dir)
            file_list = os.listdir(data_path)
            flag = True  # 用来判断是不是当前文件夹下第一个文件，是的话则添加表头，否则不重复添加
            for file in file_list:
                tms, pkt = pcap_read(os.path.join(data_path, file))
                print(os.path.join(data_path, file))
                flow = flow_combine(pkt, tms)
                session_list = extractFlow(flow)
                data_write_csv(dir + ".csv", session_list, flag)
                flag = False
