from collections import Counter

from numpy import *

feature = []

# Multiclass classifier decision tree using ID3 algorithm

# normalize the entire dataset prior to learning using min-max normalization
"""
    这段代码定义了一个名为 normalize 的函数，该函数对输入的矩阵（二维数组）进行最小-最大归一化处理。
    归一化后的数据将具有相同的尺度范围，这通常在机器学习任务中是有益的，因为它可以避免特征之间尺度差异影响模型的性能。
"""


def normalize(matrix):
    # 在函数开始时，首先将输入矩阵转换为 NumPy 数组，并确保其数据类型为浮点数。
    a = np.array(matrix)
    print(a.shape)
    a = a.astype(float)

    # print(a)
    # print("Before normalizing")

    # x_normalized = (x - min(x)) / (max(x) - min(x))
    # 其中 `x` 是输入特征值，`min(x)` 和 `max(x)` 分别是该特征的最小值和最大值。

    b = np.apply_along_axis(lambda x: (x - np.min(x)) / float(np.max(x) - np.min(x)), 0, a)

    return b


# reading from the file using numpy genfromtxt
def load_csv(file):
    data = genfromtxt(file, delimiter=',', dtype=str)

    return data


# method to randomly shuffle the array
def random_numpy_array(ar):
    np.random.shuffle(ar)
    arr = ar
    return arr


def generate_set(X):
    # Extract labels (class names) from the last column of the dataset
    Y = X[:, -1]
    j = Y.reshape(len(Y), 1)

    # Extract features from the dataset, excluding the last column
    new_X = X[:, :-1]

    # Normalize the features and concatenate with the original labels (class names)
    normalized_X = normalize(new_X)
    normalized_final_X = np.concatenate((normalized_X, j), axis=1)
    X = normalized_final_X

    # Calculate the number of rows (samples) in the dataset and the size of the test set (10% of total samples)
    size_of_rows = X.shape[0]
    num_test = round(0.1 * (X.shape[0]))

    # Initialize loop to generate 10 sets of training and test data
    start = 0
    end = num_test
    test_attri_list = []
    test_class_names_list = []
    training_attri_list = []
    training_class_names_list = []
    for i in range(10):
        # Extract test set and training set based on start and end indices
        X_test = X[start:end, :]
        tmp1 = X[:start, :]
        tmp2 = X[end:, :]
        X_training = np.concatenate((tmp1, tmp2), axis=0)

        # Extract labels (class names) for test and training sets
        y_test = X_test[:, -1].flatten()
        y_training = X_training[:, -1].flatten()

        # Remove label column from test and training sets and convert datatype to float
        X_test = X_test[:, :-1].astype(np.float)
        X_training = X_training[:, :-1].astype(np.float)

        # Append test and training sets to their respective lists
        test_attri_list.append(X_test)
        test_class_names_list.append(y_test)
        training_attri_list.append(X_training)
        training_class_names_list.append(y_training)

        # Update start and end indices for the next test set
        start = end
        end = end + num_test

    # Return the lists of test and training sets
    return test_attri_list, test_class_names_list, training_attri_list, training_class_names_list


'''
    这段代码定义了一个名为 entropy 的函数，用于计算输入向量 y 中的熵。
    熵是一种衡量数据集中信息的不确定性或复杂性的度量。在此代码中，熵计算用于评估分类问题中类别标签的不确定性。

    以下是代码的工作原理：

    初始化一个名为 class_freq 的字典，用于存储类别标签的频率。
    遍历输入向量 y 中的每个元素，计算每个类别标签的频率，并将其存储在 class_freq 字典中。
    初始化一个名为 attribute_entropy 的变量，用于存储计算得到的熵值。
    遍历字典 class_freq 中的每个频率值，计算该类别标签在数据集中出现的概率，然后将其乘以该概率的以 2 为底的对数的负值。将这个结果累加到 attribute_entropy 中。
    返回计算得到的熵值 attribute_entropy。

    熵值在决策树算法（如 ID3 算法）中具有重要作用，因为它可以帮助确定哪个属性最适合用于分割数据集。
    较低的熵值表示数据集中的类别较为纯净，而较高的熵值表示数据集中的类别混合。
    通过选择具有最大信息增益（即熵的减少）的属性来分割数据集，决策树算法可以有效地构建分类模型。
'''


def entropy(y):
    # Initialize a dictionary to store class frequencies
    class_freq = {}

    # Calculate class frequencies
    for i in y:
        if i in class_freq:
            class_freq[i] += 1
        else:
            class_freq[i] = 1

    # Calculate attribute entropy
    attribute_entropy = 0.0
    for freq in class_freq.values():
        probability = freq / float(len(y))
        attribute_entropy += -probability * math.log(probability, 2)

    return attribute_entropy


'''
    accuracy_for_predicted_values 函数计算了预测值的准确性，即正确预测的数量占总预测数量的比例。
'''


def accuracy_for_predicted_values(test_class_names1, l):
    # Initialize counters for true and false predictions
    true_count = 0
    false_count = 0

    # Compare each element in the test_class_names1 and l lists
    for i in range(len(test_class_names1)):
        if test_class_names1[i] == l[i]:
            true_count += 1
        else:
            false_count += 1

    # Calculate accuracy as the ratio of true predictions to the total number of predictions
    accuracy = float(true_count) / len(l)

    return true_count, false_count, accuracy


'''
    build_dict_of_attributes_with_class_values 函数构建了一个字典，字典的键是类别标签，值是属于该类别的特征。
    这个结构可以在决策树算法中使用，以便于在每个节点根据最佳特征对数据进行分割。
'''


def build_dict_of_attributes_with_class_values(X, y):
    # Initialize a dictionary to store attributes with their corresponding class values
    dict_of_attri_class_values = {}

    # Initialize a list to store feature indices
    feature_list = []

    # Iterate through each feature in the input matrix X
    for i in range(X.shape[1]):
        feature = i
        feature_values = X[:, i]

        # Initialize a list to store attribute values with their corresponding class labels
        attribute_list = []
        count = 0

        # Iterate through each value in the current feature
        for value in feature_values:
            attribute_value = [value, y[count]]
            attribute_list.append(attribute_value)
            count += 1

        # Add the attribute list to the dictionary with the feature index as the key
        dict_of_attri_class_values[feature] = attribute_list

        # Append the feature index to the feature_list
        feature_list.append(feature)

    return dict_of_attri_class_values, feature_list


def return_features(Y):
    return feature


'''
    Node 类用于表示决策树中的节点。
    每个节点包含一个值（特征索引或类别标签），左右子节点的引用，一个阈值（用于分割数据）和一个布尔值，表示节点是否是叶子节点。
    类还提供了一些方法，以便在构建和遍历决策树时访问节点的属性。
'''


class Node(object):
    def __init__(self, val, lchild, rchild, theta, leaf):
        self.root_value = val
        self.root_left = lchild
        self.root_right = rchild
        self.theta = theta
        self.leaf = leaf

    # Method to identify if the node is a leaf
    def is_leaf(self):
        return self.leaf

    # Method to return the threshold value
    def ret_theta(self):
        return self.theta

    # Method to return the root value
    def ret_root_value(self):
        return self.root_value

    # Method to return the left child
    def ret_llist(self):
        return self.root_left

    # Method to return the right child
    def ret_rlist(self):
        return self.root_right

    # Represent the Node object as a string
    def __repr__(self):
        return "(%r, %r, %r, %r)" % (self.root_value, self.root_left, self.root_right, self.theta)


# Decision tree object
class DecisionTree(object):
    fea_list = []

    def __init__(self):
        self.root_node = None

    # Fit the decision tree
    '''
        fit 方法负责构建决策树。
        它接收一个包含所有特征和类别信息的字典（dict_of_everything）、类别值（cl_val）、特征列表（features）和最小熵阈值（eta_min_val）。
        方法首先将特征列表设置为全局变量，以便在构建决策树时使用。
        然后，它调用 create_decision_tree 方法来构建决策树，并返回树的根节点。
    '''

    def fit(self, dict_of_everything, cl_val, features, eta_min_val):
        global feature_list
        feature_list = features

        # Create the decision tree and return the root node
        root_node = self.create_decision_tree(dict_of_everything, cl_val, eta_min_val)
        return root_node

    '''
    cal_major_class_values 方法用于计算并返回主要的类别值。
    它接收一个包含类别值的列表，然后使用 Counter 类来计算每个类别值的频率。
    接着，它找到频率最高的类别值并返回。这个方法在决策树构建过程中用于确定叶子节点的类别值。
    '''

    # Method to return the major class value
    def cal_major_class_values(self, class_values):
        # Calculate the frequency of each class value
        data = Counter(class_values)

        # Find the most common class value and return it
        major_class_value = data.most_common(1)[0][0]
        return major_class_value

    # 计算每个特征的最佳阈值方法
    '''
    cal_best_theta_value 方法通过最大化信息增益来计算给定特征的最佳阈值。
    它需要两个参数：ke，表示特征索引；attri_list，是包含特征值及其对应类别值的元组列表。
    该方法返回最大信息增益、最佳阈值以及阈值两侧数据点的索引。
    '''

    def cal_best_theta_value(self, ke, attri_list):
        data = []
        class_values = []

        # 分离特征值和类别值
        for i in attri_list:
            data.append(i[0])
            class_values.append(i[1])

        entropy_of_par_attr = entropy(class_values)
        max_info_gain = 0
        theta = 0
        best_index_left_list = []
        best_index_right_list = []
        class_labels_list_after_split = []

        # 对数据进行排序以找到最佳阈值
        data.sort()

        # 遍历特征值
        for i in range(len(data) - 1):
            cur_theta = float(data[i] + data[i + 1]) / 2

            index_less_than_theta_list = []
            values_less_than_theta_list = []
            index_greater_than_theta_list = []
            values_greater_than_theta_list = []

            '''
            补全此部分代码，实现以下逻辑功能：
                1. 根据当前阈值划分数据
                2. 计算每个划分的熵
                3. 计算当前阈值的信息增益, 如果需要，更新最佳阈值
            '''
            # 1. 根据当前阈值划分数据
            for idx, val in enumerate(attri_list):
                if val[0] < cur_theta:
                    index_less_than_theta_list.append(idx)
                    values_less_than_theta_list.append(val[1])
                else:
                    index_greater_than_theta_list.append(idx)
                    values_greater_than_theta_list.append(val[1])
            # 2. 计算每个划分的熵
            entropy_less_than_theta = entropy(values_less_than_theta_list)
            entropy_greater_than_theta = entropy(values_greater_than_theta_list)
            # 3. 计算当前阈值的信息增益, 如果需要，更新最佳阈值
            cur_info_gain = entropy_of_par_attr - (
                    entropy_less_than_theta * (len(index_less_than_theta_list) / float(len(attri_list)))) - (
                                    entropy_greater_than_theta * (
                                    len(index_greater_than_theta_list) / float(len(attri_list))))
            # print('第{}条数据：阈值：{}，信息增益：{}（最大信息增益：{}），{}更新'
            #       .format(i, cur_theta.__round__(2), cur_info_gain.__round__(2), max_info_gain.__round__(2),
            #               ('' if cur_info_gain > max_info_gain else '不')))
            if cur_info_gain > max_info_gain:
                # 更新最大信息增益、最佳阈值、阈值两侧数据点的索引、阈值两侧数据点的类别值
                max_info_gain = cur_info_gain
                theta = cur_theta
                best_index_left_list = index_less_than_theta_list
                best_index_right_list = index_greater_than_theta_list
                class_labels_list_after_split = values_less_than_theta_list + values_greater_than_theta_list

        return max_info_gain, theta, best_index_left_list, best_index_right_list, class_labels_list_after_split

    # 从所有特征中选择最佳特征的方法
    '''
    best_feature 方法从所有特征中选择最佳特征，通过最大化信息增益来实现。
    它需要一个参数：dict_rep，表示特征的字典表示。
    该方法返回一个包含最佳特征索引、最佳阈值、最佳左侧索引列表、最佳右侧索引列表和分割后的类别标签列表的列表。
    '''

    def best_feature(self, dict_rep):
        key_value = None
        best_info_gain = -1
        best_theta = 0
        best_index_left_list = []
        best_index_right_list = []
        best_class_labels_after_split = []

        # 遍历所有特征
        for ke in dict_rep.keys():
            # 计算当前特征的最佳阈值、信息增益等信息
            info_gain, theta, index_left_list, index_right_list, class_labels_after_split \
                = self.cal_best_theta_value(ke, dict_rep[ke])

            # 如果当前特征的信息增益大于当前最佳信息增益，更新最佳特征和相关信息
            if info_gain > best_info_gain:
                best_info_gain = info_gain
                best_theta = theta
                key_value = ke
                best_index_left_list = index_left_list
                best_index_right_list = index_right_list
                best_class_labels_after_split = class_labels_after_split

        # 将结果信息存储在一个列表中
        result_list = [
            key_value,
            best_theta,
            best_index_left_list,
            best_index_right_list,
            best_class_labels_after_split
        ]

        return result_list

    # 根据给定的索引列表划分数据字典的方法
    '''
    get_remainder_dict 方法根据给定的索引列表从原始数据字典中移除相应的数据点，并返回一个新的字典，表示剩余的数据集。
    它需要两个参数：
        dict_of_everything，表示包含所有数据的原始字典；
        index_split，表示需要从原始字典中移除的数据点的索引列表。
    该方法返回两个值：一个是分割后的数据字典，另一个是分割后数据集中所有类别标签值的列表。
    '''

    def get_remainder_dict(self, dict_of_everything, index_split):
        splited_dict = {}

        # 遍历所有特征
        for ke in dict_of_everything.keys():
            modified_list = []

            # 遍历特征的数据列表
            for i, v in enumerate(dict_of_everything[ke]):
                # 如果当前索引不在给定的索引列表中，将其添加到修改后的列表中
                if i not in index_split:
                    modified_list.append(v)

            # 将修改后的列表添加到分割后的字典中
            splited_dict[ke] = modified_list

        # 提取所有类别标签值（属于分割后的数据集）
        val_list = [v[1] for modified_list in splited_dict.values() for v in modified_list]

        return splited_dict, val_list

    # 创建决策树的方法
    '''
    create_decision_tree 方法使用递归方法创建决策树。
    它需要三个参数：
        dict_of_everything，表示包含所有数据的原始字典；
        class_val，表示当前数据集的类别标签列表；
        eta_min_val，表示类别标签数量的阈值，当类别标签数量小于此阈值时，将创建一个叶子节点。
    该方法返回一个表示决策树的根节点。
    在递归过程中，它将根据最佳特征和阈值将数据集划分为左子树和右子树，然后继续创建子树。
    '''

    def create_decision_tree(self, dict_of_everything, class_val, eta_min_val):
        # 如果所有类别标签相同，创建一个叶子节点并返回
        if len(set(class_val)) == 1:
            root_node = Node(class_val[0], None, None, 0, True)
            return root_node

        # 如果类别标签数量小于阈值，创建一个叶子节点，类别为数量最多的类别，并返回
        elif len(class_val) < eta_min_val:
            majority_val = self.cal_major_class_values(class_val)
            root_node = Node(majority_val, None, None, 0, True)
            return root_node

        else:
            # 计算最佳特征、阈值等信息
            best_features_list = self.best_feature(dict_of_everything)
            node_name = best_features_list[0]
            theta = best_features_list[1]
            index_left_split = best_features_list[2]
            index_right_split = best_features_list[3]

            # 根据索引列表划分数据字典
            left_dict, class_val1 = self.get_remainder_dict(dict_of_everything, index_left_split)
            right_dict, class_val2 = self.get_remainder_dict(dict_of_everything, index_right_split)

            # 递归地创建左子树和右子树
            leftchild = self.create_decision_tree(left_dict, class_val1, eta_min_val)
            rightchild = self.create_decision_tree(right_dict, class_val2, eta_min_val)

            # 创建根节点并返回
            root_node = Node(node_name, rightchild, leftchild, theta, False)
            return root_node

    # method to the labels for the test data
    def predict(self, X, root):
        predicted_list = []
        for row in X:
            y_pred = self.classify(row, root)
            predicted_list.append(y_pred)
        return predicted_list

    '''
    classify 方法使用给定的决策树对输入行进行分类。
    它需要两个参数：row，表示要分类的数据行；root，表示决策树的根节点。该方法返回分类结果，即输入行所属的类别标签。
    在分类过程中，方法从根节点开始，根据每个节点的特征值和阈值决定沿着左子树还是右子树进行分类，直到到达叶子节点。
    '''

    # 使用决策树对给定数据行进行分类的方法
    def classify(self, row, root):
        # 将输入行转换为字典，以便根据特征索引获取特征值
        dict_test = {k: j for k, j in enumerate(row)}

        # 从决策树的根节点开始
        current_node = root

        # 循环直到到达叶子节点
        while not current_node.leaf:
            # 检查当前节点的特征值是否小于等于阈值
            if dict_test[current_node.root_value] <= current_node.theta:
                # 如果是，则转到左子节点
                current_node = current_node.root_left
            else:
                # 否则，转到右子节点
                current_node = current_node.root_right

        # 当到达叶子节点时，返回其类别标签作为分类结果
        return current_node.root_value


'''
    main 函数接受两个参数：
        num_arr，表示包含所有数据的 NumPy 数组；
        eta_min，表示用于创建决策树的阈值比例。
    函数首先计算用于决策树创建的类别标签数量阈值 eta_min_val，然后随机打乱数组并将数据划分为测试集和训练集。
    接着，使用 10 折交叉验证方法，对于每一折，根据训练数据构建决策树模型，然后使用测试数据预测类别标签并计算预测值的准确率。
    最后，输出 10 折交叉验证的平均准确率。
'''


def main(num_arr, eta_min):
    # 计算eta_min_val，它是用于决策树创建的阈值
    eta_min_val = round(eta_min * num_arr.shape[0])

    # 随机打乱数组，以便将数据划分为测试集和训练集
    random_arr1 = random_numpy_array(num_arr)

    # 将数据划分为测试特征、测试类别、训练特征和训练类别
    test_attri_list, test_class_names_list, training_attri_list, training_class_names_list = generate_set(random_arr1)

    # 初始化准确率计数
    accu_count = 0

    # 使用10折交叉验证
    for i in range(10):
        # 使用类别标签和相应特征值构建输入字典
        dict_of_input, fea = build_dict_of_attributes_with_class_values(training_attri_list[i],
                                                                        training_class_names_list[i])

        # 创建决策树实例
        build_dict = DecisionTree()

        # 使用训练数据构建决策树模型
        dec = build_dict.fit(dict_of_input, training_class_names_list[i], fea, eta_min_val)

        # 使用测试数据预测类别标签
        l = build_dict.predict(test_attri_list[i], dec)

        # 计算预测值的准确率
        right, wrong, accu = accuracy_for_predicted_values(test_class_names_list[i], l)

        # 更新总准确率计数
        accu_count += accu

        # 输出当前折的准确率
        print("Accuracy is ", accu)

    # 输出10折交叉验证的平均准确率
    print("Accuracy across 10-cross validation for", eta_min, "is", float(accu_count) / 10)


if __name__ == "__main__":
    if len(sys.argv) == 2:
        # 从命令行参数获取数据文件名
        newfile = sys.argv[1]

        # 加载数据文件并进行预处理
        num_arr = load_csv(newfile)

        # 定义阈值比例列表
        eta_min_list = [0.05, 0.10, 0.15, 0.20, 0.25]

        # 对每个阈值比例运行分类器进行10折交叉验证
        for eta_min in eta_min_list:
            main(num_arr, eta_min)
