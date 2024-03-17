"""K-Means Clustering Algorithm
@File: k_means_algorithm.py
@Author:
"""

import numpy as np
import matplotlib.pyplot as plt

# initialize:
# samples:
X = np.array([[0, 0], [3, 8], [2, 2], [1, 1], [5, 3], [4, 8], [6, 3], [5, 4],
              [6, 4], [7, 5]],
             dtype=np.int8)
# number of clusters:
K = 4
# centroids:
Z = np.zeros((K, 2), dtype=np.float16)
# cluster list:
S = [[] for i in range(K)]
# distance matrix:
# D[i,j] means the distance between X[i] and Z[j]
D = np.zeros((len(X), K), dtype=np.float16)
# iteration counter:
cnt = 0

# randomly choose K samples as initial centroids:
Z = np.array([X[i] for i in np.random.randint(0, len(X), K)], dtype=np.float16)
# display initial centroids:
print('\nInitial centroids:')
for i in range(K):
    print('  Z[%d] =' % (i + 1), Z[i])

# iterate:
while True:
    cnt += 1
    print('\nRound %d:' % cnt)
    # clear cluster list:
    S = [[] for i in range(K)]
    # calculate the distance between each sample and each centroid:
    for i in range(len(X)):
        for j in range(K):
            D[i, j] = np.linalg.norm(X[i] - Z[j])
    # find the minimum distance D[i,j], add X[i] to S[j]:
    for i in range(len(X)):
        S[np.argmin(D[i])].append(X[i])
    # display new clusters:
    for i in range(K):
        print('  S[%d] =' % (i + 1))
        for j in range(len(S[i])):
            print('    ', S[i][j])
    # calculate the new centroids, and check if the centroids are changed, \
    # stop if all unchanged:
    flag = True
    for i in range(K):
        new_Z = np.mean(S[i], axis=0, dtype=np.float16)
        # display new centroids:
        print('  Z[%d] =' % (i + 1), new_Z)
        if not np.array_equal(Z[i], new_Z):
            Z[i] = new_Z
            flag = False
    if flag:
        break

# plot:
plt.figure()
plt.title('Result of K-Means Clustering Algorithm')
plt.xlabel('x')
plt.ylabel('y')
for i in range(K):
    plt.scatter([S[i][j][0] for j in range(len(S[i]))],
                [S[i][j][1] for j in range(len(S[i]))],
                label='S[%d]' % (i + 1))
for i in range(K):
    plt.scatter(Z[i][0], Z[i][1], label='Z[%d]' % (i + 1), marker='x')
plt.grid()
plt.legend()
plt.show()
