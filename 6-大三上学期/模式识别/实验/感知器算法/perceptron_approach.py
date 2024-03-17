"""Perceptron Approach
@File: perceptron_approach.py
@Author:
"""

import numpy as np
import matplotlib.pyplot as plt
# from mpl_toolkits import mplot3d


class PerceptronApproach:

    def __init__(self, omega1_: list, omega2_: list, W_: np.matrix,
                 c_: float) -> None:
        ''' initialize '''
        self.o1 = omega1_
        self.o2 = omega2_
        self.W = list()
        self.W.append(W_)
        self.c = c_
        self.sample_list = list()  # store processed samples
        self.cnt = 0  # max index of W

    def solve(self) -> str:
        ''' solve the whole problem '''

        # augmented vectors & normalize:
        for sample in self.o1:
            temp = self._augment(sample)
            self.sample_list.append(self._normalize(1, temp))
        for sample in self.o2:
            temp = self._augment(sample)
            self.sample_list.append(self._normalize(2, temp))

        # iterate and adjust weight vectors:
        while True:
            if self._iterate():
                break

        # print weight vectors:
        for i in range(len(self.W)):
            print('W%d: ' % (i + 1), self.W[i].T, 'T')

        # return discriminant function:
        return self._d_func(self.W[self.cnt])

    def _augment(self, sample_: np.matrix) -> np.matrix:
        ''' get augmented vector of a sample '''
        shape = sample_.shape[1]
        return np.r_[sample_, np.ones(shape, int).reshape(1, shape)]

    def _normalize(self, class_: int, sample_: np.matrix) -> np.matrix:
        ''' normalize the sample, *(-1) if in ω2 '''
        if class_ == 2:
            sample_ = sample_ * (-1)
        return sample_

    def _iterate(self) -> bool:
        ''' calculate and adjust the weight vector '''
        flag = True
        for sample in self.sample_list:
            if self.W[self.cnt].T * sample > 0:
                self.W.append(self.W[self.cnt])
            else:
                self.W.append(self.W[self.cnt] + sample * self.c)
                flag = False
            self.cnt += 1
        return flag

    def _d_func(self, W_: np.matrix) -> str:
        ''' get discriminant function '''
        d = 'd(X) = '
        for i in range(W_.shape[0]):
            if W_[i] != 0:
                d += '%.1f * x%d + ' % (W_[i], i + 1)
        d = d[:-8]  # remove last " * xi + "
        return d


omega1 = [
    np.mat([0, 0, 0]).T,
    np.mat([1, 0, 0]).T,
    np.mat([1, 0, 1]).T,
    np.mat([1, 1, 0]).T
]
omega2 = [
    np.mat([0, 0, 1]).T,
    np.mat([0, 1, 1]).T,
    np.mat([0, 1, 0]).T,
    np.mat([1, 1, 1]).T
]
W = np.mat([-1, -2, -2, 0]).T
c = 1
''' solve '''
test = PerceptronApproach(omega1, omega2, W, c)
print(test.solve())
''' plot '''
fig = plt.figure()
plot = plt.axes(projection='3d')
plot.set_xlabel('x1')
plot.set_ylabel('x2')
plot.set_zlabel('x3')
# plane - discriminant function:
x1 = np.outer(np.linspace(0, 1, 20), np.ones(20))
x2 = x1.copy().T
x3 = (3 * x1 - 2 * x2 + 1) / 3
plot.plot_surface(x1, x2, x3, cmap='binary')
# scatters - samples:
x1_o1 = list()
x2_o1 = list()
x3_o1 = list()
x1_o2 = list()
x2_o2 = list()
x3_o2 = list()
for sample in omega1:
    x1_o1.append(sample[0])
    x2_o1.append(sample[1])
    x3_o1.append(sample[2])
for sample in omega2:
    x1_o2.append(sample[0])
    x2_o2.append(sample[1])
    x3_o2.append(sample[2])
plot.scatter3D(x1_o1, x2_o1, x3_o1, s=50, c='r', label='ω1')
plot.scatter3D(x1_o2, x2_o2, x3_o2, s=50, c='g', label='ω2')
# plot:
plt.legend()
plt.show()
