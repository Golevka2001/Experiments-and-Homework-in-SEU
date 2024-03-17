"""
PPO & Actor-Critic相关代码
@Author:
@Date: 2023/06/08
"""

import numpy as np
import torch
import torch.nn.functional as F
from torch import nn

device = 'cuda:0'


class ActorCritic(nn.Module):

    def __init__(self, obs_dim, act_dim, hidden_sizes):
        super(ActorCritic, self).__init__()
        self.log_std = nn.Parameter(torch.zeros(act_dim))  # 高斯分布的标准差
        # actor网络 - 输入：状态；输出：动作
        self.actor_fc1_ = nn.Linear(obs_dim, hidden_sizes[0])  # 全连接层
        self.actor_fc2_ = nn.Linear(hidden_sizes[0], hidden_sizes[1])
        self.actor_fc3_ = nn.Linear(hidden_sizes[1], act_dim)
        self.actor_fc3_.weight.data.mul_(0.1)
        self.actor_fc3_.bias.data.mul_(0.0)
        # critic网络 - 输入：状态；输出：动作的价值
        self.critic_fc1_ = nn.Linear(obs_dim, hidden_sizes[0])  # 全连接层
        self.critic_fc2_ = nn.Linear(hidden_sizes[0], hidden_sizes[1])
        self.critic_fc3_ = nn.Linear(hidden_sizes[1], 1)
        self.critic_fc3_.weight.data.mul_(0.1)
        self.critic_fc3_.bias.data.mul_(0.0)
        # 初始化权重
        self.apply(self.init_weights)

    @staticmethod
    def init_weights(m):
        """初始化权重"""
        if isinstance(m, nn.Linear):
            nn.init.xavier_normal_(m.weight, gain=0.1)
            nn.init.constant_(m.bias, 0)

    @staticmethod
    def log_normal_density(x, mean, log_std, std):
        """计算正态分布的log概率密度"""
        var = std.pow(2)
        log_density = -(x - mean).pow(2) / (2 * var) - 0.5 * np.log(2 * np.pi) - log_std
        return log_density.sum(1, keepdim=True)

    def forward(self, obs):
        """前向传播"""
        # actor网络，输出动作的均值
        x = torch.tanh(self.actor_fc1_(obs))  # tanh激活
        x = torch.tanh(self.actor_fc2_(x))
        mean = self.actor_fc3_(x)  # 输出均值
        # 计算标准差，得到动作的分布
        log_std = self.log_std.expand_as(mean)
        std = torch.exp(log_std)
        act = torch.normal(mean, std)
        # critic网络，输出状态的价值估计
        val = torch.tanh(self.critic_fc1_(obs))  # tanh激活
        val = torch.tanh(self.critic_fc2_(val))
        val = self.critic_fc3_(val)  # 输出价值估计
        return val, act, mean

    def evaluate(self, obs, act):
        """评估动作的价值、概率、熵"""
        val, _, mean = self.forward(obs)  # 价值估计
        log_std = self.log_std.expand_as(mean)
        std = torch.exp(log_std)
        log_prob = self.log_normal_density(act, mean, log_std, std)
        dist_entropy = (0.5 + 0.5 * np.log(2 * np.pi)).sum(-1).mean()  # 熵
        return val, log_prob, dist_entropy


def cal_gae(rewd, mask, gamma, lam, val):
    """计算GAE（广义优势估计）

    Args:
        rewd: 奖励值
        mask: 是否终止的标志
        gamma: 折扣因子
        lam: GAE参数
        val: 状态价值估计

    Returns:
        tar_list: 目标值
        adv_list: 优势估计值
    """
    # 转换到cpu
    val = val.detach().squeeze().cpu()
    mask = mask.detach().squeeze().cpu()
    rewd = rewd.detach().squeeze().cpu()
    # 数据量
    step_cnt = rewd.shape[0]
    # 初始化
    tar_list = torch.zeros_like(rewd)
    adv_list = torch.zeros_like(rewd)
    running_tar = 0
    running_adv = 0
    pre_val = 0
    # 倒序遍历，计算每一个step的目标值和优势估计值
    for i in reversed(range(0, step_cnt)):
        running_tar = rewd[i] + mask[i] * gamma * running_tar
        delta = rewd[i] + mask[i] * gamma * pre_val - val[i]
        running_adv = delta + mask[i] * gamma * lam * running_adv
        tar_list[i] = running_tar
        pre_val = val[i]
        adv_list[i] = running_adv
    # 归一化
    adv_list = (adv_list - adv_list.mean()) / adv_list.std()
    return tar_list, adv_list


def ppo_update(policy, mem, optim, k_epochs, batch_size, gamma, lam, clip_param, entropy_coef):
    """更新策略网络

    Args:
        policy: 策略网络
        mem: 经验池
        optim: 优化器
        k_epochs: 更新策略网络的次数
        batch_size: 批次大小
        gamma: 折扣因子
        lam: GAE参数
        clip_param: PPO算法的clip参数
        entropy_coef: 熵的系数

    Returns:
        policy: 更新后的策略网络
    """
    mem = np.asarray(mem, dtype=object)
    obs = torch.FloatTensor(np.vstack(mem[:, 0])).to(device)  # 状态
    act = torch.FloatTensor(np.vstack(mem[:, 1])).to(device)  # 动作
    rewd = torch.FloatTensor(list(mem[:, 2])).to(device)  # 奖励
    mask = torch.FloatTensor(list(mem[:, 3])).to(device)  # 终止标志
    val, _, _ = policy(obs)  # 策略网络输出
    # 计算GAE
    tar_list, adv_list = cal_gae(rewd, mask, gamma, lam, val)
    old_val, old_log_prob, _ = policy.evaluate(obs, act)  # 旧的状态价值、概率、熵
    arr = np.arange(obs.shape[0])
    # 更新策略网络
    for epoch in range(k_epochs):
        np.random.shuffle(arr)  # 乱序
        # 每次使用一个batch的数据进行更新
        for i in range(obs.shape[0] // batch_size):
            batch_idx = torch.LongTensor(arr[batch_size * i:batch_size * (i + 1)])
            # 获取一个batch的采样数据
            obs_sam = obs[batch_idx]
            act_sam = act[batch_idx]
            tar_sam = tar_list[batch_idx].to(device).unsqueeze(1)
            adv_sam = adv_list[batch_idx].to(device).unsqueeze(1)
            log_prob_sam = old_log_prob[batch_idx].detach().to(device)
            val_sam = old_val[batch_idx].detach().to(device)
            # 计算新的价值、概率、熵
            val_new, log_prob_new, dist_entropy = policy.evaluate(obs_sam, act_sam)
            # 剪切比率
            ratio = torch.exp(log_prob_new - log_prob_sam)
            clip_ratio = torch.clamp(ratio, 1.0 - clip_param, 1.0 + clip_param)
            # 计算损失
            surrogate1 = ratio * adv_sam
            surrogate2 = clip_ratio * adv_sam
            policy_loss = -torch.min(surrogate1, surrogate2).mean()
            clip_val = val_sam + torch.clamp(val_new - val_sam, -0.5, 0.5)
            c_loss1 = F.mse_loss(clip_val, tar_sam)
            c_loss2 = F.mse_loss(val_new, tar_sam)
            critic_loss = torch.max(c_loss1, c_loss2).mean()
            loss = policy_loss + 0.5 * critic_loss - entropy_coef * dist_entropy
            # 更新网络
            optim.zero_grad()
            loss.backward()
            optim.step()


# 测试
if __name__ == '__main__':
    obs_dim = 17
    act_dim = 6
    hidden_sizes = [64, 64]
    ac_model = ActorCritic(obs_dim, act_dim, hidden_sizes)

    for _ in range(10):
        obs = np.random.randn(obs_dim)
        act = np.random.randn(act_dim)
        obs = torch.Tensor(obs).unsqueeze(0)
        act = torch.Tensor(act).unsqueeze(0)
        val, log_prob, dist_entropy = ac_model.evaluate(obs, act)

        print('value: ', val.detach().numpy()[0])
        print('log probability: ', log_prob.detach().numpy()[0])
        print('distribution entropy: ', dist_entropy)
