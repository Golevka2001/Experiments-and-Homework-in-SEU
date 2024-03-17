import math

from sklearn.ensemble import RandomForestClassifier


class Domain:
    def __init__(self, name, label, length, num_cnt, entropy):
        self.name_ = name
        self.label_ = label
        self.length_ = length
        self.num_cnt_ = num_cnt
        self.entropy_ = entropy

    def get_feat(self):
        return [self.length_, self.num_cnt_, self.entropy_]

    def is_dga(self):
        return self.label_ == 'dga'


def count_num(s):
    """统计字符串中数字的数量"""
    return sum(1 for c in s if c.isdigit())


def calc_entropy(s):
    """计算字符串的信息熵"""
    letter_counts = [0] * 26
    cnt = 0
    s = s.lower()
    for c in s:
        if c.isalpha():
            letter_counts[ord(c) - ord('a')] += 1
            cnt += 1
    h = sum(-p * math.log(p, 2) for p in (1.0 * n / cnt for n in letter_counts) if p > 0)
    return h


def preprocess(filename, domain_list):
    with open(filename) as f:
        for line in f:
            line = line.strip()
            # 跳过以#开头或为空的行
            if line.startswith('#') or not line:
                continue
            tokens = line.split(',')
            name = tokens[0]
            label = tokens[1] if len(tokens) > 1 else '?'
            length = len(name)
            num_cnt = count_num(name)
            entropy = calc_entropy(name)
            domain_list.append(Domain(name, label, length, num_cnt, entropy))


if __name__ == '__main__':
    domain_list_train = []  # 训练集
    domain_list_test = []  # 测试集
    feat_mat = []  # 特征矩阵
    label_list = []  # 标签列表

    # 处理训练集文件，并将特征矩阵和标签列表添加到对应的列表中
    preprocess('.\\DGA\\train.txt', domain_list_train)
    for item in domain_list_train:
        feat_mat.append(item.get_feat())
        label_list.append(item.is_dga())

    # 随机森林
    clf = RandomForestClassifier(random_state=0)
    clf.fit(feat_mat, label_list)

    # 处理测试集文件，预测域名是否为DGA，并将结果写入result.txt
    preprocess('.\\DGA\\test.txt', domain_list_test)
    with open('result.txt', 'w') as f:
        for item in domain_list_test:
            # f.write('[{}]\t{}\n'.format('dga' if clf.predict([item.get_feat()])[0] == 1 else 'not', item.name_))
            f.write('{},{}\n'.format(item.name_, 'dga' if clf.predict([item.get_feat()])[0] == 1 else 'notdga'))
