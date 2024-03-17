"""
PPO-HalfCheetah测试部分
@Author:
@Date: 2023/06/08
"""

import gym
import torch
from torch.optim import Adam

from actor_critic import ActorCritic

# 超参数
device = 'cuda:0'
hidden_sizes = [128, 128]  # 隐藏层维度（两个隐藏层）
learning_rate = 3e-4  # 学习率

# 环境
env = gym.make('HalfCheetah-v2', render_mode=None)
# 状态空间和动作空间的维度
obs_dim = env.observation_space.shape[0]
act_dim = env.action_space.shape[0]

# 智能体
ac_policy = ActorCritic(obs_dim, act_dim, hidden_sizes).to(device)  # 演员-评论家策略
optim = Adam(ac_policy.parameters(), lr=learning_rate)  # 优化器

# 加载模型参数
ac_policy.load_state_dict(torch.load('./ac_policy.pth'))

# 测试
for i in range(10):
    obs, _ = env.reset()
    done = False
    rewd_sum = 0
    step_cnt = 0
    while not done:
        step_cnt += 1
        # 选择动作
        _, act, _ = ac_policy(torch.FloatTensor(obs).to(device))
        act = act.detach().cpu().numpy()
        # 与环境交互
        obs_nxt, rewd, term, trun, _ = env.step(act)
        done = term or trun
        rewd_sum += rewd
        if done:
            break
        # 更新状态
        obs = obs_nxt
    # 打印结果
    print(f'Episode: {i}, Reward: {rewd_sum}')

env.close()
