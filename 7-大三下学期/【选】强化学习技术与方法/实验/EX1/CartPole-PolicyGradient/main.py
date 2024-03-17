import gym
import matplotlib.pyplot as plt
import numpy as np

from policy_network import PolicyNetwork
from sampler import Sampler


def train(environment, policy_network, sampler, max_training_times, max_episode, threshold_score):
    environment.reset()
    ret_sum = 0
    x_axis = np.arange(0, max_training_times, 1)
    y_axis = []
    for i in range(max_training_times):
        # sample:
        obs_tr, act_tr, ret_tr = sampler.sample(max_episode)
        # train the policy network using the sampled episodes:
        loss = policy_network.train_step(obs_tr, act_tr, ret_tr)
        # test and record the performance:
        if i == 0:
            ret_sum = test(environment, policy_network, 1)[0]
        else:
            ret_sum = 0.9 * ret_sum + 0.1 * test(environment, policy_network, 1)[0]
        print('training times: %d \t loss: %f \t score: %d' % ((i + 1), loss, ret_sum))
        y_axis.append(ret_sum)
        # end of training:
        if ret_sum > threshold_score:
            x_axis = np.arange(0, i + 1, 1)  # x_axis of the plot(training times)
            environment.reset()
            break
    # save the model:
    # policy_network.save_model('./model/cur_best_cartpole')
    # plot:
    plt.plot(x_axis, y_axis)
    plt.xlim(0, max_training_times)
    plt.ylim(0, threshold_score)
    plt.xlabel('training times')
    plt.ylabel('score')
    plt.show()


def test(environment, policy_network, test_times) -> list:
    ret_seq = list(np.zeros(test_times))
    for i in range(test_times):
        obs, _ = environment.reset()
        while True:
            st = np.reshape(obs, [1, policy_network.feat_dim_])
            act = policy_network.greedy_action(st)  # take action according to the policy network
            obs, rewd, term, trun, info = environment.step(act)
            ret_seq[i] += rewd
            # end of an episode:
            if term or trun:
                break
    return ret_seq


if __name__ == '__main__':
    # hyper parameters:
    max_training_times = 10
    max_episodes = 10
    learning_rate = 0.01
    discounted_factor = 0.98
    threshold_score = 500
    seed = np.random.randint(0, 1000)

    # # train:
    # env_train = gym.make('CartPole-v1', render_mode=None)
    # env_train.action_space.seed(seed)
    # env_train.reset(seed=seed)
    # policy_network = PolicyNetwork(env_train, learning_rate)
    # policy_network.restore_model('./model/cur_best_cartpole')
    # sampler = Sampler(env_train, policy_network, discounted_factor)
    # train(env_train, policy_network, sampler, max_training_times, max_episodes, threshold_score)
    # env_train.close()

    # test:
    env_test = gym.make('CartPole-v1', render_mode='human')
    env_test.action_space.seed(seed)
    observation, _ = env_test.reset(seed=seed)
    policy_network = PolicyNetwork(env_test, learning_rate)
    policy_network.restore_model('./model/cur_best_cartpole')
    score = 0
    cnt = 0
    while True:
        cnt += 1
        state = np.reshape(observation, [1, policy_network.feat_dim_])
        action = policy_network.greedy_action(state)
        observation, reward, terminated, truncated, _ = env_test.step(action)
        score += reward
        print('step: %d \t action: %d \t score: %d' % (cnt, action, score))
        if terminated or truncated:
            env_test.close()
            break
