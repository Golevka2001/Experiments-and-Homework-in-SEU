import random
from collections import deque

import numpy as np
import tensorflow as tf
from matplotlib import pyplot as plt
from tensorflow.python.keras import Sequential
from tensorflow.python.keras.layers import InputLayer, Dense
from tensorflow.python.keras.models import load_model
from tensorflow.python.keras.optimizers import adam_v2


class Agent:
    def __init__(self, environment, seed, target_score, discount_factor=0.98, memory_capacity=65536, batch_size=32,
                 learning_rate=0.001,                 updating_rate=10,
                 epsilon=1.0, epsilon_decay=0.995,
                 epsilon_min=0.01) -> None:
        self.env_ = environment
        self.seed_ = seed
        self.tar_score_ = target_score
        self.gamma_ = discount_factor
        # replay memory:
        self.rep_mem_ = deque(maxlen=memory_capacity)
        self.bat_size_ = batch_size
        # learning rate:
        self.l_rate_ = learning_rate
        # target model updating rate:
        self.upd_rate_ = updating_rate
        # epsilon:
        self.eps_ = epsilon
        self.eps_dc_ = epsilon_decay
        self.eps_min_ = epsilon_min
        # dimension of input and output:
        self.st_dim_ = self.env_.observation_space.shape[0]
        self.act_dim_ = self.env_.action_space.n
        # model:
        self.model_ = self.__create_model()
        self.tar_model_ = self.__create_model()

    def __create_model(self) -> tf.keras.Sequential:
        """Create a neural network model for the agent.

        Returns:
            tf.keras.Sequential: the neural network model.
        """
        model = Sequential([
            InputLayer((self.st_dim_,)),
            Dense(256, activation='relu'),
            Dense(256, activation='relu'),
            Dense(self.act_dim_)
        ])
        model.compile(loss='mse', optimizer=adam_v2.Adam(self.l_rate_))
        return model

    def __memorize(self, state, action, reward, next_state, done) -> None:
        """Store the transition in the replay memory.

        Args:
            state (np.ndarray): the current state of the environment.
            action (int): the action taken by the agent.
            reward (float): the reward received by the agent.
            next_state (np.ndarray): the next state of the environment.
            done (int): whether the episode is finished.
        """
        self.rep_mem_.append((state, action, reward, next_state, done))

    def __replay(self) -> None:
        """Replay the experience in the replay memory."""
        # sample a minibatch from replay memory:
        minibatch = random.sample(self.rep_mem_, self.bat_size_)
        st_bat, act_bat, rewd_bat, st_nxt_bat, done_bat = map(np.asarray, zip(*minibatch))
        # update q-value:
        q_pred = self.model_(st_bat)
        q_pred_copy = np.copy(q_pred)
        tar_val = self.tar_model_(st_nxt_bat)
        tar_val_max = tf.math.reduce_max(tar_val, axis=1, keepdims=True)
        for i in range(self.bat_size_):
            q_pred_copy[i][act_bat[i]] = rewd_bat[i] + (1 - done_bat[i]) * self.gamma_ * tar_val_max[i]
        # train the model:
        self.model_.fit(st_bat, q_pred_copy, batch_size=self.bat_size_, verbose=0)

    def train(self, max_training_episodes, max_steps) -> None:
        """Train the agent for 'max_training_episodes' episodes.

        Args:
            max_training_episodes (int): maximum number of episodes for training.
            max_steps (int): maximum number of steps for each episode, \
                penalty will be given if the episode is not finished.
        """
        score_seq, avg_score_seq = [], []  # for plotting
        for i in range(max_training_episodes):
            st, _ = self.env_.reset(seed=self.seed_)
            score = 0
            for j in range(max_steps):
                # select an action
                act = self.select_action(st)
                # execute the action, get reward and next state:
                st_nxt, rewd, term, trun, _ = self.env_.step(act)
                done = 1 if term or trun else 0
                score += rewd
                # store the transition:
                self.__memorize(st, act, rewd, st_nxt, done)
                # update state:
                st = st_nxt
                # experience replay:
                if len(self.rep_mem_) >= self.bat_size_:
                    self.__replay()
                # update target model:
                if i % self.upd_rate_ == 0:
                    self.tar_model_.set_weights(self.model_.get_weights())
                # end of episode:
                if term or trun:
                    print(
                        'episode {}/{} \t score: {:.2f}({} steps)'.format(i + 1, max_training_episodes, score,
                                                                          j + 1))
                    break
            # plot:
            score_seq.append(score)
            avg_score = np.mean(score_seq)
            avg_score_seq.append(avg_score)
            if i % (max_training_episodes / 10) == 0 or i == max_training_episodes - 1:
                plt.plot(score_seq, label='score', color='blue')
                plt.plot(avg_score_seq, label='average score', color='red')
                plt.plot([self.tar_score_] * (i + 1), label='target score', color='green')
                plt.xlabel('episode')
                plt.legend()
                plt.show()
                self.save_model('temp'.format(i))
        # save model:
        self.save_model('final')

    def select_action(self, state) -> int:
        """Select an action for the agent.

        Args:
            state (np.ndarray): the current state of the environment.
        """
        # update epsilon:
        if self.eps_ > self.eps_min_:
            self.eps_ *= self.eps_dc_
        # with probability epsilon, select a random action:
        if np.random.rand() < self.eps_:
            return random.choice(range(self.act_dim_))
        # otherwise, select the action with the highest q-value:
        st = np.array([state])
        act = self.model_(st)
        return tf.math.argmax(act, axis=1).numpy()[0]

    def save_model(self, name) -> None:
        """Save the model."""
        model_path = './model/model-{}'.format(name)
        weights_path = './model/weights-{}'.format(name)
        self.model_.save_weights(weights_path)
        self.model_.save(model_path)
        print('model saved to {}'.format(model_path))

    def load_model(self, name) -> None:
        """Load the model."""
        model_path = './model/model-{}'.format(name)
        weights_path = './model/weights-{}'.format(name)
        self.model_ = load_model(model_path)
        self.model_.load_weights(weights_path)
        print('model loaded from {}'.format(model_path))

    def switch_environment(self, environment):
        """Training environment -> Testing environment."""
        self.env_ = environment
