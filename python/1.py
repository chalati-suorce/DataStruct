import matplotlib.pyplot as plt
import numpy as np

# 设置图片清晰度
plt.rcParams['figure.dpi'] = 300

# 创建一个图形对象
fig, ax = plt.subplots()

# 绘制雪王的头部（圆形）
head_center = (0, 0)
head_radius = 1
circle = plt.Circle(head_center, head_radius, color='yellow', ec='black', lw=2)
ax.add_artist(circle)

# 绘制雪王的皇冠
# 皇冠底部弧线
theta = np.linspace(0, np.pi, 100)
x_crown_base = head_radius * np.cos(theta)
y_crown_base = head_radius * np.sin(theta) + head_center[1] + head_radius
ax.plot(x_crown_base, y_crown_base, color='black', lw=2)

# 皇冠的三个尖
spike_heights = [1.5, 2, 1.5]
spike_positions = [-0.6, 0, 0.6]
for spike_height, spike_position in zip(spike_heights, spike_positions):
    spike_x = [spike_position - 0.1, spike_position, spike_position + 0.1]
    spike_y = [head_radius + head_center[1], head_radius + head_center[1] + spike_height, head_radius + head_center[1]]
    ax.plot(spike_x, spike_y, color='black', lw=2)

# 绘制雪王的眼睛
eye_radius = 0.15
left_eye_center = (-0.4, 0.2)
right_eye_center = (0.4, 0.2)
left_eye = plt.Circle(left_eye_center, eye_radius, color='black')
right_eye = plt.Circle(right_eye_center, eye_radius, color='black')
ax.add_artist(left_eye)
ax.add_artist(right_eye)

# 绘制雪王的嘴巴
mouth_x = np.linspace(-0.3, 0.3, 100)
mouth_y = -0.2 - 0.1 * (mouth_x ** 2)
ax.plot(mouth_x, mouth_y, color='black', lw=2)

# 绘制雪王的身体（椭圆）
body_width = 1.2
body_height = 1.5
body_center = (0, -1.2)
ellipse = plt.Ellipse(body_center, body_width, body_height, color='yellow', ec='black', lw=2)
ax.add_artist(ellipse)

# 绘制雪王的手臂
arm_start = [(-0.6, -0.5), (0.6, -0.5)]
arm_end = [(-1.2, -1), (1.2, -1)]
for start, end in zip(arm_start, arm_end):
    ax.plot([start[0], end[0]], [start[1], end[1]], color='black', lw=2)

# 绘制雪王的腿
leg_start = [(-0.3, -2), (0.3, -2)]
leg_end = [(-0.3, -2.5), (0.3, -2.5)]
for start, end in zip(leg_start, leg_end):
    ax.plot([start[0], end[0]], [start[1], end[1]], color='black', lw=2)

# 设置坐标轴比例相等
ax.set_aspect('equal')

# 隐藏坐标轴
ax.axis('off')

# 显示图形
plt.show()
