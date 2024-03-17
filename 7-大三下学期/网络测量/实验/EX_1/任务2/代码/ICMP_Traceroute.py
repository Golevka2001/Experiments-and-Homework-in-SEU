# mainly used in Windows system
from optparse import OptionParser
from random import randint

import networkx as nx
from scapy.all import *


class Traceroute:
    def __init__(self, dst, max_ttl):
        self.dst = dst
        self.max_ttl = max_ttl

    @staticmethod
    def visualization(ip_list):
        # achieve the IP visualization
        graph = nx.Graph()
        for i in range(len(ip_list) - 1):
            graph.add_edge('[{}] {}'.format(i, ip_list[i]), '[{}] {}'.format(i + 1, ip_list[i + 1]))
        nx.draw(graph, with_labels=True, font_weight='bold')
        plt.show()

    def tracert_icmp(self, ttl):
        # achieve the ICMP Tracert
        try:
            # 构造ICMP Ping数据包，ttl从参数传入
            pkt = IP(dst=self.dst, ttl=ttl, id=randint(0, 65535)) / ICMP(id=randint(0, 65535), seq=randint(0, 65535))
            # 记录发送、接收时间
            send_t = time.time()
            reply = sr1(pkt, timeout=5, verbose=False)
            recv_t = time.time()
            # 根据Tracert，未到达目标主机返回(1, 地址, 消耗时间);到达目标主机返回(2, 地址, 消耗时间)
            ret_val = 0
            if reply.type == 11:  # 11表示TTL超时
                ret_val = 1
            elif reply.type == 0:  # 0表示Ping成功
                ret_val = 2
            return ret_val, str(reply.src), recv_t - send_t
        # 测试失败返回None
        except Exception as e:
            if re.match('.*NoneType.*', str(e)):
                return None

    def tracert(self):
        ip_list = []
        for ttl in range(1, self.max_ttl):
            result = self.tracert_icmp(ttl)
            if result is None:  # 测试失败，打印‘*’
                ip_list.append('*')  # 存储每一跳的地址用于绘图
                print('{} | {}\t| {}'.format(ttl, '*', 'Time Out'))
            else:  # 未抵达目标主机，打印这一跳和消耗的时间；抵达目标主机，打印这一跳和消耗的时间，并跳出循环
                ip_list.append(result[1])  # 存储每一跳的地址用于绘图
                time_result = '%4.2f' % result[2]
                print('{} | {} ms\t| {}'.format(ttl, time_result, result[1]))
                if result[0] == 2:
                    break
            time.sleep(1)
        # traceroute结束后，调用可视化函数
        self.visualization(ip_list)
        # 使用scapy的traceroute函数及内置的可视化函数对比
        ans, unans = traceroute(self.dst, maxttl=self.max_ttl)
        ans.graph(target='> graph.svg', type='svg')


# python .\ICMP_Traceroute.py --mode trace -a seu.edu.cn -M 30
if __name__ == '__main__':
    parser = OptionParser()
    parser.add_option('--mode', dest='mode', help='选择模式<trace>')
    parser.add_option('-a', '--addr', dest='addr', help='指定一个IP地址或范围')
    parser.add_option('-M', '--Max_TTL', dest='Max_TTL', help='指定trace时的最大生存时间', default=30)
    (options, args) = parser.parse_args()  # options: {'mode': 'trace', 'addr': '**.**.**.**'}
    print('By:ICMP_Traceroute in Active Measurement Experiment.')

    if options.mode == 'trace':
        max_ttl = int(options.Max_TTL)
        t_obj = Traceroute(str(options.addr), max_ttl)
        t_obj.tracert()
    else:
        print('Please understand the input of ICMP_Traceroute.py')
        parser.print_help()
