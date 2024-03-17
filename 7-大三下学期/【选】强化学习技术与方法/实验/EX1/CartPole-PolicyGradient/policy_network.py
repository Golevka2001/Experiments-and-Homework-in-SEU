import numpy as np
import tensorflow as tf

tf.compat.v1.disable_eager_execution()


class PolicyNetwork:
    def __init__(self, environment, learning_rate=0.01, model_path=None) -> None:
        # parameters:
        self.l_rate_ = learning_rate
        self.feat_dim_ = environment.observation_space.shape[0]  # dimension of input features
        self.act_dim_ = environment.action_space.n  # dimension of action space

        # layers of policy network:
        # input layer:
        self.obs_ = tf.compat.v1.placeholder(tf.float32, shape=[None, self.feat_dim_])
        # hidden layer 1:
        self.full_con_layer = tf.compat.v1.layers.dense(inputs=self.obs_, units=20, activation=tf.nn.relu,
                                                        kernel_initializer=tf.compat.v1.random_normal_initializer(
                                                            mean=0,
                                                            stddev=0.1),
                                                        bias_initializer=tf.compat.v1.constant_initializer(0.1))
        # hidden layer 2:
        self.all_act_ = tf.compat.v1.layers.dense(inputs=self.full_con_layer, units=self.act_dim_, activation=None,
                                                  kernel_initializer=tf.compat.v1.random_normal_initializer(mean=0,
                                                                                                            stddev=0.1),
                                                  bias_initializer=tf.compat.v1.constant_initializer(0.1))
        # output layer(softmax):
        self.all_act_prob_ = tf.nn.softmax(self.all_act_)  # use softmax to convert to probability of each action

        # label and reward:
        self.cur_act_ = tf.compat.v1.placeholder(tf.int32, [None, ])
        self.cur_rewd_ = tf.compat.v1.placeholder(tf.float32, [None, ])

        # loss functions:
        self.neg_log_prob_ = tf.nn.sparse_softmax_cross_entropy_with_logits(logits=self.all_act_, labels=self.cur_act_)
        self.loss_ = tf.reduce_mean(input_tensor=self.neg_log_prob_ * self.cur_rewd_)

        # optimizer:
        self.optmz_ = tf.compat.v1.train.AdamOptimizer(self.l_rate_).minimize(self.loss_)

        # session:
        self.sess_ = tf.compat.v1.Session()
        self.sess_.run(tf.compat.v1.global_variables_initializer())  # initialize

        # store and restore model:
        self.saver = tf.compat.v1.train.Saver()
        if model_path is not None:
            self.restore_model(model_path)

    def train_step(self, state_batch, label_batch, reward_batch) -> tuple:
        loss, _, _ = self.sess_.run([self.loss_, self.optmz_, self.neg_log_prob_],
                                    feed_dict={self.obs_: state_batch, self.cur_act_: label_batch,
                                               self.cur_rewd_: reward_batch})
        return loss

    def gen_action(self, state):
        prob = self.sess_.run(self.all_act_prob_,
                              feed_dict={self.obs_: state})  # get the probability of each action
        act = np.random.choice(range(prob.shape[1]), p=prob.ravel())
        # print("action",action)
        return act

    def greedy_action(self, state):
        prob = self.sess_.run(self.all_act_prob_,
                              feed_dict={self.obs_: state})  # get the probability of each action
        act = np.argmax(prob, 1)
        # print("greedy action", action)
        return act[0]

    def save_model(self, model_path):
        self.saver.save(self.sess_, model_path)

    def restore_model(self, model_path):
        self.saver.restore(self.sess_, model_path)
