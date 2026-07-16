# 核心算法库 (C++ / CUDA / ONNX Runtime)

## 目录结构
```
03_Core_Algorithms/
├── src/                     # 源代码
│   ├── matching_cuda.cu     # 并行立体匹配加速 (CUDA)
│   ├── rectify.cpp          # 极线校正实现
│   ├── triangulate.cpp      # 三角测量
│   ├── pupil_seg.cpp        # 瞳孔分割 (ONNX Runtime)
│   └── pipeline.cpp         # 主流程管线
├── include/                 # DLL 接口定义
│   ├── StereoMatcher.h
│   ├── Triangulate.h
│   └── PupilDetector.h
└── CMakeLists.txt
```

## 多平台适配

| 平台 | 推理库 | CMake 目标 | 状态 |
|------|--------|------------|------|
| CPU 通用 | ONNX Runtime | `binocular_cpu` | ✅ |
| Intel 核显 | OpenVINO | `binocular_ov` | ✅ ~120ms |
| AMD 核显 | DirectML | `binocular_dml` | 🔄 优化中 |
| RK3588 NPU | RKNN | `binocular_rk3588` | ✅ ~80ms |

## 依赖
- OpenCV ≥ 4.5
- ONNX Runtime / DirectML / OpenVINO / RKNN (按平台选择)
- CUDA Toolkit (若启用 CUDA 加速)

> 源代码由开发者上传
