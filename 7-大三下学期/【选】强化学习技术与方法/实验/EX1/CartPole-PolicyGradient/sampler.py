import numpy as np


class Sampler:
    def __init__(self, environment, policy_network, discount_factor=0.98) -> None:
        self.env_ = environment
        self.p_net_ = policy_network
        self.gamma_ = discount_factor

    def sample(self, max_episode=10) -> tuple:
        """Sample function.

        Args:
            max_episode: number of episodes to sample

        Returns:
            batch_obs: observations of all episodes
            batch_act: actions of all episodes
            batch_ret: discounted returns of all episodes
        """
        obs_batch = []
        act_batch = []
        ret_batch = []
        for _ in range(max_episode):
            # initialize:
            obs, _ = self.env_.reset()
            rewd_seq = []  # reward of each step at current episode
            # take actions according to current policy, and store data:
            while True:
                st = np.reshape(obs, [1, self.p_net_.feat_dim_])  # list -> np.array
                act = self.p_net_.gen_action(st)  # generate an action
                obs_new, rewd, term, trun, info = self.env_.step(act)  # take action
                # store:
                obs_batch.append(obs)
                act_batch.append(act)
                rewd_seq.append(rewd)
                # end of an episode:
                if term or trun:
                    # calculate discounted return:
                    rewd_sum = 0
                    ret_seq = np.zeros_like(rewd_seq)
                    for t in reversed(range(len(rewd_seq))):
                        rewd_sum = rewd_sum * self.gamma_ + rewd_seq[t]
                        ret_seq[t] = rewd_sum
                    # normalize:
                    ret_seq -= np.mean(ret_seq)
                    ret_seq /= np.std(ret_seq)
                    # store:
                    for t in range(len(rewd_seq)):
                        ret_batch.append(ret_seq[t])
                    self.env_.reset()
                    break
                # not end, next step:
                obs = obs_new
        # reshape:
        obs_batch = np.reshape(obs_batch, [len(obs_batch), self.p_net_.feat_dim_])
        act_batch = np.reshape(act_batch, [len(ret_batch), ])
        ret_batch = np.reshape(ret_batch, [len(ret_batch), ])
        return obs_batch, act_batch, ret_batch
