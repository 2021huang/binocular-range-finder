# 双目测距知识库 / Stereo Vision Knowledge Base

> **Doc as Code** — 理论推导、原型验证、核心算法、上位机工程强绑定

## 📋 概述

面向医疗设备（眼底相机、生物测量仪、Smart OCT、3500项目）的**双目立体视觉测距**系统知识库。

### 应用设备

| 设备 | 平台 | 耗时 | 状态 |
|------|------|------|------|
| 眼底相机 | Intel 核显 | ~120ms | ✅ |
| 生物测量仪 | AMD R5 7430U | 250~330ms → 目标66ms | 🔴 紧急优化 |
| Smart OCT | NPU3588 | ~80ms | ✅ |
| 3500项目 | Intel/AMD | 待定 | 🟡 |

---

## 📂 目录结构

```
stereo_vision_kb/
├── 01_Theory_and_Math/         # 理论与数学推导 (Markdown + LaTeX)
├── 02_Prototypes/              # 算法原型验证 (MATLAB)
├── 03_Core_Algorithms/         # 核心算法库 (C++ / CUDA / ONNX)
│   ├── src/                    # 四平台推理部署代码
│   ├── include/                # DLL 接口定义 (StereoApi.h)
│   └── README.md               # 算法原理 + 流程图
├── 04_UI_Integration/          # 上位机接口 (C++ DLL → C#/Python)
├── 05_Datasets/                # 标定板图像与测试数据 (Git LFS)
├── 06_Config_Params/           # 参数与配置文件 (YAML)
└── README.md                   # 本文件
```

---

## 🚀 快速导航

| 目录 | 内容 | 入口 |
|------|------|------|
| 理论 | 极线几何、坐标系变换、三角测量 | [`01_Theory_and_Math/`](01_Theory_and_Math/) |
| 原型 | MATLAB 标定/深度图脚本 | [`02_Prototypes/`](02_Prototypes/) |
| 算法 | C++ 核心算法 + DLL 接口 (四平台) | [`03_Core_Algorithms/`](03_Core_Algorithms/) |
| 接口 | 上位机 DLL 调用规范 | [`04_UI_Integration/`](04_UI_Integration/) |
| 数据 | 标定原图、人眼数据集 (LFS) | [`05_Datasets/`](05_Datasets/) |
| 配置 | 内外参 YAML、样机记录 | [`06_Config_Params/`](06_Config_Params/) |

---

## 🔧 优化方向

- [ ] **知识蒸馏** — Teacher-Student 结构压缩模型
- [ ] **模型剪枝** — PyTorch 结构化剪枝
- [ ] **FP16 推理** — 半精度浮点加速
- [ ] **模型量化** — FP32 → INT8/FP8
- [ ] **AMD 核显加速** — DirectML 目标 66ms (15 FPS)

---

## 🔄 核心流程

```
┌──────────┐   ┌──────────┐   ┌───────────┐   ┌──────────┐   ┌──────────┐
│ ① 双目标定 │ → │ ② 图像校正 │ → │ ③ 瞳孔识别  │ → │ ④ 三角测量 │ → │ ⑤ 坐标变换 │
│ 内外参获取 │   │ 去畸变   │   │ 语义分割  │   │ 空间测距 │   │ 输出Pt   │
└──────────┘   └──────────┘   └───────────┘   └──────────┘   └──────────┘
```

---

## 📚 Doc as Code 规范

- 数学模型全部使用 **Markdown + LaTeX** 编写
- Commit 采用 **Conventional Commits** 规范
- 二进制/图像文件使用 **Git LFS** 管理
- 分支策略：`main` (唯一真相源) + `feature/*` (预研分支) + PR 讨论沉淀

---

## 👤 维护者

huangliang200801@163.com
