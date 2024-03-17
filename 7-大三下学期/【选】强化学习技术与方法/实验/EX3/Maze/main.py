import time
from os import path

import matplotlib.pyplot as plt

from agent import Agent
from maze_env import MazeEnv

# hyper-parameters:
save_q_table = True
max_training_episodes = 600
max_test_episodes = 0
max_steps = 100
discount_factor = 0.9
learning_rate = 0.01
epsilon = 0.9
epsilon_decay = 0.995
epsilon_min = 0.01
penalty = -0.01
file_path = '.\\q_table.csv'

# environment:
env = MazeEnv()
env.reset()

# agent:
agent = Agent(env, discount_factor, learning_rate, epsilon, epsilon_decay, epsilon_min)


def train():
    if max_training_episodes <= 0:
        return
    # training:
    rewd_list = [0] * max_training_episodes
    ma_rewd_list = [0] * max_training_episodes
    for episode in range(max_training_episodes):
        obs = env.reset()
        step_cnt = 1
        while step_cnt <= max_steps:
            env.render()
            # select action:
            act = int(agent.select_action(str(obs)))
            # take action:
            nxt_obs, rewd, done = env.step(act)
            if rewd != 1:
                rewd = penalty
            rewd_list[episode] += rewd
            step_cnt += 1
            # learn:
            agent.learn(str(obs), act, rewd, str(nxt_obs), done)
            if done or step_cnt > max_steps:
                print('episode: {}, steps: {}, score: {}'.format(episode, step_cnt, rewd_list[episode]))
                break
            # update state:
            obs = nxt_obs
        # moving average:
        if episode == 0:
            ma_rewd_list[episode] = rewd_list[episode]
        else:
            ma_rewd_list[episode] = ma_rewd_list[episode - 1] * 0.9 + rewd_list[episode] * 0.1
    # plot:
    plt.plot(rewd_list, label='reward')
    plt.plot(ma_rewd_list, label='ma_reward')
    plt.plot([1] * max_training_episodes, label='goal')
    plt.ylim(-0.3, 1.1)
    plt.xlabel('episode')
    plt.ylabel('reward')
    plt.title('Maze - Q-learning')
    plt.legend()
    plt.show()
    # save Q table:
    if save_q_table:
        print('training finished! average score: {}'.format(sum(rewd_list) / len(rewd_list)))
        agent.save_q_table(file_path)


def test():
    # test:
    if max_test_episodes <= 0:
        return
    # modify parameters:
    agent.eps_ = 0
    rewd_list = [0] * max_test_episodes
    ma_rewd_list = [0] * max_test_episodes
    for episode in range(max_test_episodes):
        obs = env.reset()
        step_cnt = 1
        while step_cnt <= max_steps:
            env.render()
            # select action:
            act = int(agent.select_action(str(obs)))
            # take action:
            nxt_obs, rewd, done = env.step(act)
            if rewd != 1:
                rewd = penalty
            rewd_list[episode] += rewd
            step_cnt += 1
            if done or step_cnt > max_steps:
                print('episode: {}, steps: {}, score: {}'.format(episode, step_cnt, rewd_list[episode]))
                break
            # update state:
            obs = nxt_obs
            # time.sleep(0.05)
        if episode == 0:
            ma_rewd_list[episode] = rewd_list[episode]
        else:
            ma_rewd_list[episode] = ma_rewd_list[episode - 1] * 0.9 + rewd_list[episode] * 0.1
    # plot:
    plt.plot(rewd_list, label='reward')
    plt.plot(ma_rewd_list, label='ma_reward')
    plt.plot([1] * max_test_episodes, label='goal')
    plt.ylim(-0.3, 1.1)
    plt.xlabel('episode')
    plt.ylabel('reward')
    plt.title('Maze - Q-learning')
    plt.legend()
    plt.show()


if __name__ == '__main__':
    # load Q table:
    if path.exists(file_path):
        agent.load_q_table(file_path)

    # train:
    train()

    # test:
    time.sleep(1)
    test()

    env.close()
