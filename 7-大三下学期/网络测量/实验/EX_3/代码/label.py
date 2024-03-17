import os

import numpy as np
import pandas as pd


def process_csv_file(file_name):
    file_path = os.path.join(os.getcwd(), file_name)
    pd_data = pd.read_csv(file_path + ".csv")

    flow_data = []
    for flow_idx in range(pd_data.shape[0]):
        five_tup = eval(pd_data['five_tup'][flow_idx])
        if five_tup[4] == 6:
            flow_pktlen = eval(pd_data['flow_pktlen'][flow_idx])
            flow_data.append([flow_pktlen, file_name])

    return flow_data


def process_data(file_names):
    new_data = []
    for name in file_names:
        flow_data = process_csv_file(name)
        flow_data = list(filter(None, flow_data))

        result_file_path = os.path.join(os.getcwd(), name + '-label.csv')
        farray = np.array(flow_data, dtype=object)

        df = pd.DataFrame(data=farray, columns=['flow_pktlen', 'label'])
        df.to_csv(result_file_path, index=False)
        print(f"{name}-label.csv 文件保存成功！")

        new_data.append(flow_data)

    return new_data


file_names = ["chat", "video", "web"]
new_data = process_data(file_names)
