import numpy as np
import pandas as pd


class Agent:
    def __init__(self, environment, discount_factor=0.98, learning_rate=0.001, epsilon=1.0, epsilon_decay=0.995,
                 epsilon_min=0.01):
        self.env_ = environment
        self.obs_dim_ = self.env_.observation_space.n
        self.act_dim_ = self.env_.action_space.n
        self.gamma_ = discount_factor
        self.l_rate_ = learning_rate
        self.eps_ = epsilon
        self.eps_dc_ = epsilon_decay
        self.eps_min_ = epsilon_min

        self.q_tab_ = pd.DataFrame(columns=np.arange(self.act_dim_), dtype=np.float16)

    def select_action(self, observation):
        self.append_q_table(observation)
        # update epsilon:
        self.eps_ = max(self.eps_min_, self.eps_ * self.eps_dc_)
        # select action:
        if np.random.random() < self.eps_:
            # random action:
            act = np.random.randint(self.act_dim_)
        else:
            # best action:
            cur_line = self.q_tab_.loc[observation, :]
            # some actions may have the same value, randomly choose on in these actions:
            act = np.random.choice(cur_line[cur_line == np.max(cur_line)].index)
        return act

    def learn(self, sarsa, observation, action, reward, next_observation, done):
        self.append_q_table(next_observation)
        # update Q table:
        q_pred = self.q_tab_.loc[observation, action]
        nxt_act = 0
        if done:
            q_tar = reward
        else:
            if sarsa:
                # SARSA:
                nxt_act = int(self.select_action(next_observation))
                q_tar = reward + self.gamma_ * self.q_tab_.loc[next_observation, nxt_act]
            else:
                # Q-learning:
                q_tar = reward + self.gamma_ * self.q_tab_.loc[next_observation, :].max()
        self.q_tab_.loc[observation, action] += self.l_rate_ * (q_tar - q_pred)
        return nxt_act

    def append_q_table(self, observation):
        # append new state to Q table:
        if observation not in self.q_tab_.index:
            self.q_tab_ = pd.concat(
                [self.q_tab_, pd.DataFrame([[0] * self.act_dim_], index=[observation], dtype=np.float64,
                                           columns=self.q_tab_.columns)])

    def save_q_table(self, file_path):
        self.q_tab_.to_csv(file_path)
        print('Q-table saved to "{}"'.format(file_path))

    def load_q_table(self, file_path):
        print('loading Q-table from "{}"'.format(file_path))
        self.q_tab_ = pd.read_csv(file_path, index_col=0, header=0, names=[None, 0, 1, 2, 3])
        print('Q-table loaded!')
