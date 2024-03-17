# mainly used in Windows system
import ipaddress
from optparse import OptionParser
from random import randint

from scapy.all import *


def ICMP_Ping(addr, ttl):
    # achieve the Ping using ICMP
    # 构造ICMP Ping数据包，ttl从参数传入
    pkt = IP(dst=addr, ttl=ttl, id=randint(0, 65535)) / ICMP(id=randint(0, 65535), seq=randint(0, 65535))
    reply = sr1(pkt, timeout=1, verbose=False)
    # 打印结果
    if reply is not None:
        reply.show()


# python .\ICMP_Ping.py --mode ping -a 10.208.64.0/24 -i 30
if __name__ == "__main__":
    parser = OptionParser()
    parser.add_option("--mode", dest="mode", help="选择模式<ping>")
    parser.add_option("-a", "--addr", dest="addr", help="指定一个IP地址或范围")
    parser.add_option("-i", "--TTL", dest="TTL", help="指定生存时间", default=30)
    (options, args) = parser.parse_args()  # options: {'mode': 'ping', 'addr': '**.**.**.**'}
    print("By:ICMP_Ping in Active Measurement Experiment.")

    if options.mode == "ping":
        net = ipaddress.ip_network(str(options.addr))
        TTL_number = int(options.TTL)
        for item in net:
            # 调用ICMP_Ping函数实现功能
            t = threading.Thread(target=ICMP_Ping, args=(str(item), TTL_number))
            t.start()
    else:
        print("Please understand the input of ICMP_Ping.py")
        parser.print_help()
