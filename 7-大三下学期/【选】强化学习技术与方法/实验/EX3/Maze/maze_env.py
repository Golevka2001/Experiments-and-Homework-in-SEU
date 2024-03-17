## 实现深入浅出强化学习：原理入门中Page 35的迷宫构建
# 首先，导入库文件（包括gym模块和gym中的渲染模块）
import gym
import time
import random, copy
from gym.envs.classic_control import rendering

UP, DOWN, LEFT, RIGHT = 0, 1, 2, 3


# 我们生成一个类，该类继承 gym.Env. 同时，可以添加元数据，改变渲染环境时的参数
class MazeEnv(gym.Env):
    # 如果你不想改参数，下面可以不用写
    metadata = {
        'render.modes': ['human', 'rgb_array'],
        'video.frames_per_second': 2
    }

    # 我们在初始函数中定义一个 viewer ，即画板
    def __init__(self):
        self.viewer = rendering.Viewer(700, 700)  # 600x400 是画板的长和框

        self.shape = [5, 5]  #

        self.state_space = self.get_state_space()  # 其中key为状态编号，其值为坐标
        self.n_state = len(self.state_space)
        self.action_space = [0, 1, 2, 3]
        self.n_action = len(self.action_space)
        self.state = None  # 当前状态
        self.trap_space = {}
        self.terminate_space = {}
        self.treasure_space = {}
        self.treasure_space[(3, 5)] = (550, 350)
        self.transition = {}
        self.get_transition()  # 获得转移函数

    def reset(self):
        # 随机生成一个状态
        self.state = random.choice(list(self.state_space))
        conflict_pos = [(1, 4), (2, 4), (3, 1), (3, 2), (3, 5), (5, 3), (5, 4), (5, 5)]
        if self.state in conflict_pos:
            self.state = self.reset()
        return self.state

    def step(self, action):
        # 系统当前状态
        state = copy.deepcopy(self.state)
        if state in self.terminate_space:
            return state, 0, True

        key = (state[0], state[1], action)

        if key in self.transition:
            next_state = self.transition[key]
        else:
            next_state = state
        self.state = next_state

        done = False

        # next_index = (next_state[0], next_state[1])
        if next_state in self.terminate_space:
            done = True

        if next_state in self.trap_space:
            r = -1
        elif next_state in self.treasure_space:
            r = 1
        else:
            r = 0

        return next_state, r, done

    # 继承Env render函数
    def render(self, mode='human', close=False):
        # 清空画板
        self.viewer.geoms = []

        # 下面就可以定义你要绘画的元素了，6*6的网格
        # 绘画横向线段
        grid_length = 6
        for j in range(0, grid_length):
            line = rendering.Line((100, j * 100 + 100), (600, j * 100 + 100))
            line.set_color(0, 0, 0)
            self.viewer.add_geom(line)

        # 绘画纵向线段
        for i in range(0, grid_length):
            line = rendering.Line((i * 100 + 100, 100), (i * 100 + 100, 600))
            line.set_color(0, 0, 0)
            self.viewer.add_geom(line)

        # 创建第1个陷阱
        trap_1 = rendering.make_circle(50)
        circletrans = rendering.Transform(translation=(450, 550))
        trap_1.add_attr(circletrans)
        trap_1.set_color(0, 0, 0)
        self.viewer.add_geom(trap_1)
        self.trap_space[(1, 4)] = (450, 550)

        # 创建第2个陷阱
        trap_2 = rendering.make_circle(50)
        circletrans = rendering.Transform(translation=(450, 450))
        trap_2.add_attr(circletrans)
        trap_2.set_color(0, 0, 0)
        self.viewer.add_geom(trap_2)
        self.trap_space[(2, 4)] = (450, 450)

        # 创建第3个陷阱
        trap_3 = rendering.make_circle(50)
        circletrans = rendering.Transform(translation=(150, 350))
        trap_3.add_attr(circletrans)
        trap_3.set_color(0, 0, 0)
        self.viewer.add_geom(trap_3)
        self.trap_space[(3, 1)] = (150, 350)

        # 创建第4个陷阱
        trap_4 = rendering.make_circle(50)
        circletrans = rendering.Transform(translation=(250, 350))
        trap_4.add_attr(circletrans)
        trap_4.set_color(0, 0, 0)
        self.viewer.add_geom(trap_4)
        self.trap_space[(3, 2)] = (250, 350)

        # 创建第5个陷阱
        trap_5 = rendering.make_circle(50)
        circletrans = rendering.Transform(translation=(350, 150))
        trap_5.add_attr(circletrans)
        trap_5.set_color(0, 0, 0)
        self.viewer.add_geom(trap_5)
        self.trap_space[(5, 3)] = (350, 150)

        # 创建第6个陷阱
        trap_6 = rendering.make_circle(50)
        circletrans = rendering.Transform(translation=(450, 150))
        trap_6.add_attr(circletrans)
        trap_6.set_color(0, 0, 0)
        self.viewer.add_geom(trap_6)
        self.trap_space[(5, 4)] = (450, 150)

        # 创建第7个陷阱
        trap_7 = rendering.make_circle(50)
        circletrans = rendering.Transform(translation=(550, 150))
        trap_7.add_attr(circletrans)
        trap_7.set_color(0, 0, 0)
        self.viewer.add_geom(trap_7)
        self.trap_space[(5, 5)] = (550, 150)

        # 创建宝藏
        treasure = rendering.make_circle(50)
        circletrans = rendering.Transform(translation=(550, 350))
        treasure.add_attr(circletrans)
        treasure.set_color(0, 255, 0)
        self.viewer.add_geom(treasure)

        # 创建机器人
        robot = rendering.make_circle(50)
        robotrans = rendering.Transform()
        robot.add_attr(robotrans)
        robot.set_color(255, 0, 0)
        self.viewer.add_geom(robot)

        self.terminate_space = copy.deepcopy(self.trap_space)
        self.terminate_space[(3, 5)] = (550, 350)

        robotrans.set_translation(self.state_space[self.state][0], self.state_space[self.state][1])

        return self.viewer.render(return_rgb_array=mode == 'rgb_array')

    def get_state_space(self):
        # 从左到右从上到下，依次使用在网格中的坐标标号
        states = {}
        # n = 0
        # for y in range(550, 100, -100):
        #     for x in range(150, 600, 100):
        #         states[n] = (x, y)
        #         n += 1
        # ------------以下代码使用网格坐标来表示转态-----------------
        i = 1
        for y in range(550, 100, -100):
            j = 1
            for x in range(150, 600, 100):
                states[(i, j)] = (x, y)
                j += 1
            i += 1
        return states

    def get_transition(self):
        self.transition[(1, 1, DOWN)] = (2, 1); self.transition[(1, 1, RIGHT)] = (1, 2)
        self.transition[(1, 2, DOWN)] = (2, 2); self.transition[(1, 2, LEFT)] = (1, 1); self.transition[(1, 2, RIGHT)] = (1, 3)
        self.transition[(1, 3, DOWN)] = (2, 3); self.transition[(1, 3, LEFT)] = (1, 2); self.transition[(1, 3, RIGHT)] = (1, 4)
        self.transition[(1, 5, DOWN)] = (2, 5); self.transition[(1, 5, LEFT)] = (1, 4)

        self.transition[(2, 1, UP)] = (1, 1); self.transition[(2, 1, DOWN)] = (3, 1); self.transition[(2, 1, RIGHT)] = (2, 2)
        self.transition[(2, 2, UP)] = (1, 2); self.transition[(2, 2, DOWN)] = (3, 2); self.transition[(2, 2, LEFT)] = (2, 1); self.transition[(2, 2, RIGHT)] = (2, 3)
        self.transition[(2, 3, UP)] = (1, 3); self.transition[(2, 3, DOWN)] = (3, 3); self.transition[(2, 3, LEFT)] = (2, 2); self.transition[(2, 3, RIGHT)] = (2, 4)
        self.transition[(2, 5, UP)] = (1, 5); self.transition[(2, 5, DOWN)] = (3, 5); self.transition[(2, 5, LEFT)] = (2, 4)

        self.transition[(3, 3, UP)] = (2, 3); self.transition[(3, 3, DOWN)] = (4, 3); self.transition[(3, 3, LEFT)] = (3, 2); self.transition[(3, 3, RIGHT)] = (3, 4)
        self.transition[(3, 4, UP)] = (2, 4); self.transition[(3, 4, DOWN)] = (4, 4); self.transition[(3, 4, LEFT)] = (3, 3); self.transition[(3, 4, RIGHT)] = (3, 5)

        self.transition[(4, 1, UP)] = (3, 1); self.transition[(4, 1, DOWN)] = (5, 1); self.transition[(4, 1, RIGHT)] = (4, 2)
        self.transition[(4, 2, UP)] = (3, 2); self.transition[(4, 2, DOWN)] = (5, 2); self.transition[(4, 2, LEFT)] = (4, 1); self.transition[(4, 2, RIGHT)] = (4, 3)
        self.transition[(4, 3, UP)] = (3, 3); self.transition[(4, 3, DOWN)] = (5, 3); self.transition[(4, 3, LEFT)] = (4, 2); self.transition[(4, 3, RIGHT)] = (4, 4)
        self.transition[(4, 4, UP)] = (3, 4); self.transition[(4, 4, DOWN)] = (5, 4); self.transition[(4, 4, LEFT)] = (4, 3); self.transition[(4, 4, RIGHT)] = (4, 5)
        self.transition[(4, 5, UP)] = (3, 5); self.transition[(4, 5, DOWN)] = (5, 5); self.transition[(4, 5, LEFT)] = (4, 4)

        self.transition[(5, 1, UP)] = (4, 1); self.transition[(5, 1, RIGHT)] = (5, 2)
        self.transition[(5, 2, UP)] = (4, 2); self.transition[(5, 2, LEFT)] = (5, 1); self.transition[(5, 2, RIGHT)] = (5, 3)

    def get_action_name(self, a):
        action2name = {UP: 'U', DOWN: 'D', LEFT: 'L', RIGHT: 'R'}
        return action2name[a]

    def close(self):
        if self.viewer:
            self.viewer.close()

        self.viewer = None
