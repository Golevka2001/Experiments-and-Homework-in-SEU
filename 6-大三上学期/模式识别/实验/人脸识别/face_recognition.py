"""Face Recognition Based on ORL Database (PCA & K-L)
@File: face_recognition.py
@Author:
"""

import os
import time

import numpy as np
from PIL import Image

faces_dir = './faces/'  # path of faces
train_num_each = 7  # number of training images per person
K = 100  # number of eigenvalues
# R = 10  # number of rounds to cross validation

# needn't change:
faces_dir = os.path.join(os.path.abspath(os.path.dirname(__file__)), faces_dir)
test_num_each = 10 - train_num_each  # number of test images per person
train_num = 40 * train_num_each  # number of training images
test_num = 40 * test_num_each  # number of test images


def read_faces(
        faces_dir: str
) -> tuple[np.ndarray, np.ndarray, np.ndarray, np.ndarray]:
    """Read faces of 40 people, each person has 10 images, \
        7 for training and 3 for testing

    Args:
        faces_dir (str): directory of faces

    Returns:
        tuple[np.ndarray, np.ndarray, np.ndarray, np.ndarray]: \
            training faces, shape (10304, 280), \
            test faces, shape (10304, 120), \
            training image indices, \
            test image indices
    """
    train_idx_list = np.random.choice(10, train_num_each, replace=False) + 1
    train_idx_list.sort()
    test_idx_list = np.setdiff1d(np.arange(1, 11), train_idx_list)
    print('training images:', train_idx_list)
    print('test images:', test_idx_list)
    train_set = []
    test_set = []
    for i in range(1, 41):
        for j in range(1, 11):
            filename = os.path.join(faces_dir, 's' + str(i), str(j) + '.pgm')
            img = Image.open(filename)
            vec = np.array(img).flatten()
            if j in train_idx_list:
                train_set.append(vec)
            else:
                test_set.append(vec)
    train_set = np.array(train_set).squeeze().T
    test_set = np.array(test_set).squeeze().T
    return train_set, test_set, train_idx_list, test_idx_list


def calc_mean_face(train_set: np.ndarray) -> np.ndarray:
    """Calculate mean face

    Args:
        train_set (np.ndarray): training faces, shape (10304, 280)

    Returns:
        np.ndarray: mean face, shape (10304, 1)
    """
    mean_face = np.mean(train_set, axis=1).reshape(-1, 1)
    # Image.fromarray(mean_face.reshape(112, 92)).show()
    return mean_face


def calc_eigen_vals(train_set: np.ndarray, mean_face: np.ndarray,
                    K: int) -> np.ndarray:
    """Calculate and get K largest eigenvalues

    Args:
        train_set (np.ndarray): training faces, shape (10304, 280)
        mean_face (np.ndarray): mean face, shape (10304, 1)
        K (int): number of eigenvalues

    Returns:
        np.ndarray: transformation matrix (10304, K)
    """
    # covariance matrix:
    C = train_set - mean_face  # zero-centered
    cov = np.dot(C.T, C)  # cov = np.cov(C)
    eig_vals, eig_vecs = np.linalg.eig(cov)
    eig_vecs = np.dot(C, eig_vecs)  # eig_vecs = np.dot(C.T, eig_vecs)
    # sort and get K largest eigen values
    sort_idx = np.argsort(-eig_vals)[:K]
    # construct transformation matrix:
    return eig_vecs.T[sort_idx]


def calc_proj_vecs(train_set: np.ndarray, mean_face: np.ndarray,
                   tf_mat: np.ndarray) -> np.ndarray:
    """Calculate projection vectors

    Args:
        train_set (np.ndarray): training faces, shape (10304, 280)
        mean_face (np.ndarray): mean face, shape (10304, 1)
        tf_mat (np.ndarray): transformation matrix (10304, K)

    Returns:
        np.ndarray: projection vectors, shape (K, 280)
    """
    return np.dot(tf_mat, train_set - mean_face)


if __name__ == '__main__':
    train_set, test_set, train_idx_list, test_idx_list = read_faces(faces_dir)
    mean_face = calc_mean_face(train_set)
    tf_mat = calc_eigen_vals(train_set, mean_face, K)
    proj_vecs = calc_proj_vecs(train_set, mean_face, tf_mat)

    # test:
    # randomly choose a test image:
    test_idx = np.random.randint(0, test_num)
    print('\ntest image: s%d/%d.pgm' %
          (test_idx // test_num_each + 1,
           test_idx_list[test_idx % test_num_each]))
    test_vec = test_set[:, test_idx, np.newaxis]
    # project test image to eigen space:
    test_proj = np.dot(tf_mat, test_vec - mean_face)
    # calculate distance between test image and training images:
    dists = np.linalg.norm(proj_vecs - test_proj, axis=0)
    min_idx = np.argmin(dists)
    print('match image: s%d/%d.pgm' %
          (min_idx // train_num_each + 1,
           train_idx_list[min_idx % train_num_each]))
    # display two images: test and match
    test_vec = test_vec.reshape(112, 92)
    match_vec = train_set[:, min_idx, np.newaxis].reshape(112, 92)
    contrast = np.hstack((test_vec, np.zeros([112, 3]), match_vec))
    Image.fromarray(contrast).show()
