import gym
from os import path
from matplotlib import pyplot as plt

from agent import Agent

# hyper-parameters:
sarsa = False
save_q_table = True
max_training_episodes = 0
max_steps = 200
discount_factor = 0.9
learning_rate = 0.01
epsilon = 0.9
epsilon_decay = 0.995
epsilon_min = 0.01
file_path = '.\\q_table-{}.csv'.format("SARSA" if sarsa else "Q-learning")

# environment:
env = gym.make('CliffWalking-v0', render_mode=None)
env.reset()

# agent:
agent = Agent(env, discount_factor, learning_rate, epsilon, epsilon_decay, epsilon_min)


def train(sarsa=True):
    if max_training_episodes <= 0:
        return
    # training:
    rewd_list = [0] * max_training_episodes
    ma_rewd_list = [0] * max_training_episodes
    for episode in range(max_training_episodes):
        obs = env.reset()
        step_cnt = 1
        if sarsa:
            # SARSA:
            # select action:
            act = int(agent.select_action(str(obs)))
        while step_cnt <= max_steps:
            if not sarsa:
                # Q-learning:
                # select action:
                act = int(agent.select_action(str(obs)))
            # take action:
            nxt_obs, rewd, term, trun, _ = env.step(act)
            done = term or trun
            rewd_list[episode] += rewd
            step_cnt += 1
            # learn (action will be updated in SARSA):
            act = agent.learn(sarsa, str(obs), act, rewd, str(nxt_obs), done)
            if done or step_cnt > max_steps:
                if episode % 100 == 0:
                    print('episode: {}, steps: {}, score: {}'.format(episode, step_cnt, rewd_list[episode]))
                break
            # update state:
            obs = nxt_obs
        # moving average:
        if episode == 0:
            ma_rewd_list[episode] = rewd_list[episode]
        else:
            ma_rewd_list[episode] = ma_rewd_list[episode - 1] * 0.9 + rewd_list[episode] * 0.1
    env.close()
    # plot:
    plt.plot(rewd_list, label='reward')
    plt.plot(ma_rewd_list, label='ma_reward')
    plt.plot([-13] * max_training_episodes, label='goal')
    plt.ylim(-200, 0)
    plt.xlabel('episode')
    plt.ylabel('score')
    plt.title(
        'CliffWalking-v0 - {} - ε={:.2f}(*{:.2f})'.format("SARSA" if sarsa else "Q-learning", epsilon, epsilon_decay))
    plt.legend()
    plt.show()
    # save Q table:
    if save_q_table:
        print('training finished! average score: {}'.format(sum(rewd_list) / len(rewd_list)))
        agent.save_q_table(file_path)


def test():
    # test:
    # modify parameters:
    agent.eps_ = 0
    max_steps = 20
    # modify render mode:
    env = gym.make('CliffWalking-v0', render_mode='human')
    obs = env.reset()
    step_cnt = 1
    rewd_sum = 0
    while step_cnt <= max_steps:
        # select action:
        act = int(agent.select_action(str(obs)))
        # take action:
        nxt_obs, rewd, term, trun, _ = env.step(act)
        done = term or trun
        rewd_sum += rewd
        step_cnt += 1
        if done or step_cnt > max_steps:
            print('steps: {}, score: {}'.format(step_cnt, rewd_sum))
            break
        # update state:
        obs = nxt_obs
    env.close()


if __name__ == '__main__':
    # load Q table:
    if path.exists(file_path):
        agent.load_q_table(file_path)

    # train:
    train(sarsa)

    # test:
    test()
