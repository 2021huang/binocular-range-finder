# 极线几何推导

## 1. 对极几何基本约束

设空间点 $P$ 在世界坐标系下的齐次坐标为 $\tilde{P} = [X, Y, Z, 1]^T$，其在左、右相机图像平面上的投影点分别为 $p_l$ 和 $p_r$。

左相机投影：

$$
p_l = K_l [I \mid 0] \tilde{P}
$$

右相机投影：

$$
p_r = K_r [R \mid T] \tilde{P}
$$

其中 $K_l, K_r \in \mathbb{R}^{3 \times 3}$ 为左右相机的内参矩阵，$R \in \mathbb{R}^{3 \times 3}$ 为旋转矩阵，$T \in \mathbb{R}^3$ 为平移向量。

## 2. 本质矩阵与基础矩阵

本质矩阵 $E$ 描述了两个相机之间的对极几何关系（归一化图像坐标下）：

$$
E = [T]_{\times} R
$$

其中 $[T]_{\times}$ 是平移向量 $T$ 的反对称矩阵：

$$
[T]_{\times} = \begin{bmatrix}
0 & -T_z & T_y \\
T_z & 0 & -T_x \\
-T_y & T_x & 0
\end{bmatrix}
$$

基础矩阵 $F$ 描述了像素坐标系下的对极几何关系：

$$
F = K_r^{-T} E K_l^{-1}
$$

对极约束：

$$
p_r^T F p_l = 0
$$

## 3. 极线方程

给定左图像点 $p_l$，其在右图像中对应的极线方程为：

$$
l_r = F p_l
$$

即右图像中的极线为 $l_r^T p_r = 0$。

同理，右图像点 $p_r$ 在左图像中的极线为：

$$
l_l = F^T p_r
$$

## 4. 极点

左图像中的极点 $e_l$ 是所有右图像极线在左图像中的交点，满足：

$$
F e_l = 0
$$

右图像中的极点 $e_r$ 满足：

$$
e_r^T F = 0
$$

极点在图像平面上是左右相机光心连线与图像平面的交点。

## 5. 三角测量原理

已知匹配点对 $(p_l, p_r)$ 和投影矩阵 $P_l, P_r$，可通过三角测量恢复三维点坐标。

将投影方程写为齐次形式：

$$
p_l = P_l \tilde{P}, \quad p_r = P_r \tilde{P}
$$

对于左相机，$p_l = (u_l, v_l, 1)^T$，有：

$$
u_l = \frac{P_l^{1T} \tilde{P}}{P_l^{3T} \tilde{P}}, \quad
v_l = \frac{P_l^{2T} \tilde{P}}{P_l^{3T} \tilde{P}}
$$

其中 $P_l^{iT}$ 表示 $P_l$ 的第 $i$ 行。整理得：

$$
(u_l P_l^{3T} - P_l^{1T}) \tilde{P} = 0 \\
(v_l P_l^{2T} - P_l^{2T}) \tilde{P} = 0
$$

同理对右相机。将四个方程联立，构成 $A\tilde{P} = 0$，使用 SVD 分解求解，取最小奇异值对应的右奇异向量即为三维齐次坐标 $\tilde{P}$。

---

## 参考

- Hartley, R., & Zisserman, A. (2003). *Multiple View Geometry in Computer Vision*. Cambridge University Press.
- OpenCV: `cv::triangulatePoints` 实现
