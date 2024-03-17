"""
PPO-HalfCheetah训练部分
@Author:
@Date: 2023/06/08
"""

from collections import deque

import gym
import seaborn as sns
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import torch
from torch.optim import Adam

from actor_critic import ActorCritic, ppo_update

# 超参数
device = 'cuda:0'
render = False
hidden_sizes = [128, 128]  # 隐藏层维度（两个隐藏层）
learning_rate = 3e-4  # 学习率
k_epochs = 10  # 每次更新actor-critic策略的迭代次数
batch_size = 64  # 更新时的数据批次大小
gamma = 0.99  # 折扣因子
lam = 0.98  # GAE参数，调节长期和短期效应的比例
clip_param = 0.2  # PPO算法中的clip参数
entropy_coefficient = 0.01  # PPO算法中的熵系数
max_train_epoch = 30  # 最大训练轮数
max_sample_size = 2048  # 每轮最大采样步数
max_steps_per_episode = 512  # 每个episode最大步数（HalfCheetah内置的最大步数为1000）

# # 设置日志
# logger = logging.getLogger(__name__)
# logger.setLevel(level=logging.INFO)
# handler = logging.FileHandler('log.txt')
# handler.setLevel(logging.INFO)
# formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')
# handler.setFormatter(formatter)
# console = logging.StreamHandler()
# console.setLevel(logging.INFO)
# logger.addHandler(handler)
# logger.addHandler(console)

# 环境
if render:
    mode = 'human'
else:
    mode = 'None'
env = gym.make('HalfCheetah-v2', render_mode=mode)
# 状态空间和动作空间的维度
obs_dim = env.observation_space.shape[0]
act_dim = env.action_space.shape[0]

# 智能体
ac_policy = ActorCritic(obs_dim, act_dim, hidden_sizes).to(device)  # 演员-评论家策略
optim = Adam(ac_policy.parameters(), lr=learning_rate)  # 优化器

# 记录reward和running average reward的文件
rewd_file = open('reward.csv', 'w')
ra_rewd_file = open('running_average_reward.csv', 'w')

# 训练-PPO算法
rewd_list = []  # 记录每个epoch的reward
for i in range(max_train_epoch):
    mem = deque()  # 经验池
    episode_cnt = 0
    step_cnt = 0
    temp_rewd_list = []
    # 在一个epoch中采样max_sample_step个样本
    while len(mem) < max_sample_size:
        episode_cnt += 1
        obs, _ = env.reset()
        rewd_sum = 0
        # 进行一个episode的采样
        for _ in range(max_steps_per_episode):
            step_cnt += 1
            # 选择动作
            val, act, mean = ac_policy(torch.FloatTensor(obs).to(device))
            act = act.detach().cpu().numpy()
            # 与环境交互
            obs_nxt, rewd, term, trun, _ = env.step(act)
            done = term or trun
            # 存储经验
            if done:
                mask = 0
            else:
                mask = 1
            mem.append([obs, act, rewd, mask])
            rewd_sum += rewd
            obs = obs_nxt
            if done:
                break
        temp_rewd_list.append(rewd_sum)
    # 计算reward
    rewd_list.append(temp_rewd_list)
    # 将reward保存到csv文件中
    df_rewd = pd.DataFrame(rewd_list, index=None)
    df_rewd.to_csv('reward.csv')
    # # 记录日志
    # logger.info(f'epoch: {i} | episode: {episode_cnt}, step: {step_cnt}, reward: {rewd_list[i]}')
    # 一轮采样结束后，打印信息，更新actor-critic策略
    print(f'epoch: {i} | episode: {episode_cnt}, step: {step_cnt}, average reward: {np.mean(rewd_list[i])}')
    ppo_update(ac_policy, mem, optim, k_epochs, batch_size, gamma, lam, clip_param, entropy_coefficient)
    # 每隔10轮保存一次模型
    if i % 10 == 0:
        torch.save(ac_policy.state_dict(), 'ac_policy.pth')

# 训练完成绘制图像
# 读取数据
rewd = pd.read_csv('reward.csv', header=0, index_col=0)
rewd = rewd.T
df = pd.DataFrame(rewd).melt(var_name='epoch', value_name='reward')
df['label'] = 'PPO'

# 绘制图像
plt.figure(figsize=(20, 10))
sns.lineplot(x="epoch", y="reward", data=df)
plt.title("Reward - Epoch (HalfCheetah-v2, PPO)")
plt.xlabel("Epoch")
plt.ylabel("Reward")
plt.show()

env.close()
