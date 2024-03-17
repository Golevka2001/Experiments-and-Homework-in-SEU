import random
import keyboard

import gym
import tensorflow as tf

from agent import Agent

gpu = tf.config.list_physical_devices(device_type='GPU')
tf.config.set_visible_devices(devices=gpu[0], device_type='GPU')
# tf.config.experimental.set_memory_growth(device=gpu[0], enable=True)


if __name__ == '__main__':
    # hyper parameters:
    # train = True
    train = False
    test = True
    # test = False
    max_training_episodes = 100
    testing_episodes = 5
    max_steps = 1000
    target_score = 0
    discount_factor = 0.95
    memory_capacity = 4096
    batch_size = 128
    learning_rate = 0.001
    updating_rate = 5
    epsilon = 1
    epsilon_decay = 0.998
    epsilon_min = 0.01
    seed = random.randint(0, 1000)
    # seed = 0

    # environment:
    env = gym.make('LunarLander-v2', render_mode=None)
    env.action_space.seed(seed)
    env.reset(seed=seed)

    # agent:
    agent = Agent(env, seed, target_score, discount_factor, memory_capacity, batch_size, learning_rate,
                  updating_rate, epsilon, epsilon_decay, epsilon_min)
    agent.load_model('final')

    # train:
    if train:
        agent.train(max_training_episodes, max_steps)
    env.close()

    # test:
    if test:
        env_test = gym.make('LunarLander-v2', render_mode='human')
        env_test.action_space.seed(seed)
        env_test.reset(seed=seed)
        agent.eps_ = 0
        agent.switch_environment(env_test)
        score_sum = 0
        for i in range(testing_episodes):
            # test:
            score, step_cnt = 0, 0
            st, _ = env_test.reset()
            while True:
                step_cnt += 1
                # use keyboard to control the agent:
                if keyboard.is_pressed('w'):
                    act = 2
                elif keyboard.is_pressed('a'):
                    act = 3
                elif keyboard.is_pressed('d'):
                    act = 1
                else:
                    act = 0
                # act = agent.select_action(st)
                st, rewd, term, trun, _ = env_test.step(act)
                score += rewd
                if term or trun:
                    break
            score_sum += score
            print('score: {:.2f}({} steps)'.format(score, step_cnt))
        print('average score: {:.2f}'.format(score_sum / testing_episodes))
        env_test.close()
