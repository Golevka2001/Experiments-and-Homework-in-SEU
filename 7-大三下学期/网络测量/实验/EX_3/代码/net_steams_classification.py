import csv
import os
import sys

import pandas as pd

import numpy as np
from scipy import stats
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder

from MultiClassDTree import *

sys.setrecursionlimit(5000)  # 将最大递归深度设置为5000


def read_csv_file(file_path):
    sequence_list = []
    label_list = []

    # 获取当前CSV field大小限制
    current_limit = csv.field_size_limit()
    csv.field_size_limit(current_limit * 10)

    with open(file_path, 'r') as file:
        data_reader = csv.reader(file)
        next(data_reader)  # 跳过表头

        for row in data_reader:
            # 移除序列字符串中的中括号，将字符串分割为列表，并将其转换为整数列表
            sequence = list(map(int, row[0].strip('[]').split(',')))
            label = row[1].strip()
            sequence_list.append(sequence)
            label_list.append(label)

    # 恢复原来的CSV field大小限制
    csv.field_size_limit(current_limit)

    return sequence_list, label_list


# 定义一个函数，用于提取流的特征
def get_characteristics(flow):
    # c_dict = {'mean': 0, 'median': 0, 'mode': 0, 'variation_ratio': 0, 'quartile_deviation': 0, 'range': 0,
    #           'mean_deviation': 0, 'variance': 0, 'coefficient of variation': 0, 'SK': 0, 'K': 0}

    c_dict = {}

    flow = np.array(flow)
    # 计算各种特征值
    c_dict['mean'] = np.mean(flow)
    c_dict['median'] = np.median(flow)
    c_dict['mode'] = stats.mode(flow, keepdims=True)[0][0]
    c_dict['variation_ratio'] = flow[flow != c_dict['mode']].shape[0] / flow.shape[0]
    c_dict['quartile_deviation'] = np.quantile(flow, 0.75) - np.quantile(flow, 0.25)
    c_dict['range'] = np.max(flow) - np.min(flow)
    c_dict['mean_deviation'] = np.mean(np.abs(flow - np.mean(flow)))
    c_dict['variance'] = np.var(flow)


    if np.mean(flow) == 0:
        c_dict['coefficient of variation'] = 0
    else:
        c_dict['coefficient of variation'] = np.std(flow) / np.mean(flow)

    if np.array_equal(flow - flow[0], np.zeros_like(flow)):
        c_dict['SK'] = 0
        c_dict['K'] = 0
    else:
        c_dict['SK'] = stats.skew(flow)
        c_dict['K'] = stats.kurtosis(flow)

    c_dict['correlation'] = np.corrcoef(flow, flow)[0, 1]  # 相关系数
    c_dict['auto_correlation'] = np.correlate(flow, flow)[0]  # 自相关系数
    c_dict['cross_correlation'] = np.correlate(flow, flow[::-1])[0]  # 互相关系数

    return c_dict


def main():
    file_names_list = ["chat-label.csv", "video-label.csv", "web-label.csv"]
    file_path = os.getcwd()
    n_features = 14
    total_X = np.empty((0, n_features), float)
    total_y = np.empty((0,), int)

    # 定义类别名称
    class_names = ['web', 'video', 'chat']

    # 创建一个LabelEncoder实例，并使用类别名称进行拟合
    label_encoder = LabelEncoder()
    label_encoder.fit(class_names)

    for i in range(len(file_names_list)):
        sequence_list, label_list = read_csv_file(os.path.join(file_path, file_names_list[i]))

        # 初始化特征列表
        features_list = []

        # 计算每个流序列的特征
        for sequence in sequence_list:
            features = get_characteristics(sequence)
            features_list.append(list(features.values()))

        # 将特征列表转换为NumPy数组
        X = np.array(features_list)

        # 将标签列表转换为整数值
        y = label_encoder.transform(label_list)

        # 将当前文件的数据添加到总数据集
        total_X = np.concatenate((total_X, X), axis=0)
        total_y = np.concatenate((total_y, y), axis=0)

    # 打乱数据顺序
    indices = np.arange(total_X.shape[0])
    np.random.shuffle(indices)
    total_X = total_X[indices]
    total_y = total_y[indices]

    # 分割训练集和测试集
    X_train, X_test, y_train, y_test = train_test_split(total_X, total_y, test_size=0.2, random_state=42)

    print("X_train.shape:", X_train.shape)
    print("X_test.shape:", X_test.shape)

    # 初始化准确率计数
    accu_count = 0

    # 使用10折交叉验证
    n_splits = 10
    for i in range(n_splits):
        dict_of_input, fea = build_dict_of_attributes_with_class_values(X_train, y_train)

        # # 创建决策树实例
        build_dict = DecisionTree()

        eta_min_val = round(0.25 * len(total_X))

        # 使用训练数据构建决策树模型
        dec = build_dict.fit(dict_of_input, y_train, fea, eta_min_val)

        # 使用测试数据预测类别标签
        y_pred = build_dict.predict(X_test, dec)

        # 计算预测值的准确率
        right, wrong, accu = accuracy_for_predicted_values(y_test, y_pred)

        # 更新总准确率计数
        accu_count += accu

        # 输出预测值和真实值
        # df = pd.DataFrame({'y_test': y_test, 'y_pred': y_pred})
        # print(df)

        # 输出当前折的准确率
        print("Accuracy is ", accu)

    # 输出10折交叉验证的平均准确率
    print("Accuracy across 10-cross validation for", 0.05, "is", float(accu_count) / n_splits)


if __name__ == '__main__':
    main()
