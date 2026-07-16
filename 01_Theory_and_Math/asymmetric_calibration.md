# 非对称双目（异构相机）相对坐标系建立方案

## 1. 问题描述

实际应用中，左右相机可能型号不同（异构相机），内参不同，且光轴不平行。此时需要精确标定外参 $R, T$ 来描述两个相机的相对位姿。

## 2. 标定参数定义

### 左相机内参

$$
K_l = \begin{bmatrix}
f_{x_l} & 0 & c_{x_l} \\
0 & f_{y_l} & c_{y_l} \\
0 & 0 & 1
\end{bmatrix}
$$

### 右相机内参

$$
K_r = \begin{bmatrix}
f_{x_r} & 0 & c_{x_r} \\
0 & f_{y_r} & c_{y_r} \\
0 & 0 & 1
\end{bmatrix}
$$

### 外参

右相机相对于左相机的位姿：

$$
R = \begin{bmatrix}
r_{11} & r_{12} & r_{13} \\
r_{21} & r_{22} & r_{23} \\
r_{31} & r_{32} & r_{33}
\end{bmatrix}, \quad
T = \begin{bmatrix} t_x \\ t_y \\ t_z \end{bmatrix}
$$

## 3. 投影矩阵

左相机（世界坐标系建立在左相机光心）：

$$
P_l = K_l [I \mid 0] \in \mathbb{R}^{3 \times 4}
$$

右相机：

$$
P_r = K_r [R \mid T] \in \mathbb{R}^{3 \times 4}
$$

## 4. 三角测量通用公式

### 4.1 投影矩阵法

使用 `cv::triangulatePoints(P1, P2, pts1, pts2, pts4D)`：

输入 $P_l, P_r$ 和匹配点对 $(p_l, p_r)$，输出齐次坐标 $\tilde{P} = (X, Y, Z, W)^T$。

归一化得到三维笛卡尔坐标：

$$
x = \frac{X}{W}, \quad y = \frac{Y}{W}, \quad z = \frac{Z}{W}
$$

### 4.2 齐次线性方程组法

直接求解 $A\tilde{P} = 0$，其中：

$$
A = \begin{bmatrix}
u_l P_l^{3T} - P_l^{1T} \\
v_l P_l^{2T} - P_l^{2T} \\
u_r P_r^{3T} - P_r^{1T} \\
v_r P_r^{2T} - P_r^{2T}
\end{bmatrix} \in \mathbb{R}^{4 \times 4}
$$

## 5. 坐标归一化处理

根据标志位 $n_{\text{normflag}}$ 选择不同的处理方式：

### 方式一：未归一化（$n_{\text{normflag}} = 1$）

直接使用原始像素坐标 $(u, v)$。

投影矩阵：

$$
P_l = K_l [I \mid 0], \quad P_r = K_r [R \mid T]
$$

### 方式二：图像中心归一化（$n_{\text{normflag}} = 2$）

使用内参将像素坐标归一化：

$$
x = \frac{u - c_x}{f_x}, \quad y = \frac{v - c_y}{f_y}
$$

此时投影矩阵退化为位姿矩阵：

$$
P_l = [I \mid 0], \quad P_r = [R \mid T]
$$

## 6. 右相机光心位置

左相机光心为原点 $O_l = (0, 0, 0)^T$。

右相机光心 $O_r$ 由 $R O_r + T = 0$ 解得：

$$
O_r = -R^{-1} T = -R^T T
$$

## 7. 关键距离计算

### 基线长度

$$
b = \|O_r\|_2 = \sqrt{O_{r_x}^2 + O_{r_y}^2 + O_{r_z}^2}
$$

### 目标到左相机距离

$$
d_{l} = \sqrt{x^2 + y^2 + z^2}
$$

### 目标到右相机距离

$$
d_{r} = \sqrt{(x - O_{r_x})^2 + (y - O_{r_y})^2 + (z - O_{r_z})^2}
$$

### 目标到基线的垂直距离

设向量 $\vec{l}_t = (x, y, z)^T$，$\vec{l}_r = O_r$。

夹角余弦：

$$
\cos\theta = \frac{\vec{l}_t \cdot \vec{l}_r}{d_l \cdot b}
$$

夹角正弦：

$$
\sin\theta = \sqrt{1 - \cos^2\theta}
$$

垂直距离：

$$
d_{\perp} = d_l \cdot \sin\theta
$$

## 8. 坐标系转换到双目中心坐标系

### 8.1 平移

原点平移到两相机中点的向量：

$$
T_{\text{new}} = -\frac{O_r}{2}
$$

### 8.2 旋转

计算两相机光轴夹角的一半：

$$
\frac{\beta}{2} = \frac{\arccos(R_{33})}{2}
$$

计算基线向量与 $X$ 轴单位向量的夹角：

$$
\cos\alpha = \frac{O_{r_x}}{b}
$$

构建新旋转矩阵 $R_{\text{new}}$，结合平移向量 $T_{\text{new}}$，将原始目标点 $P_t$ 映射到新坐标系：

$$
P_w = R_{\text{new}} (P_t + T_{\text{new}})
$$

最终坐标 $(P_{w_x}, P_{w_y}, P_{w_z})$ 满足：
- $X$ 轴沿双目连线向左为正
- $Y$ 轴垂直 $X$ 轴向下为正
- $Z$ 轴指向眼睛为正

---

## 参考

- Hartley & Zisserman (2003), Chapter 12 — 三角测量
- OpenCV: `cv::triangulatePoints`, `cv::solve`, `cv::Rodrigues`
