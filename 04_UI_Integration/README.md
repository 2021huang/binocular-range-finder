# 上位机接口 (C++ DLL 接口)

## 概述

核心算法编译为动态链接库（DLL/SO），通过统一的 C 风格接口暴露给上位机程序调用。

上位机支持的调用方式：
- **C++**：直接链接 DLL，调用头文件中声明的函数
- **C# / WPF**：通过 `DllImport` P/Invoke 调用
- **Python**：通过 `ctypes` / `cffi` 调用
- **LabVIEW / MATLAB**：通过节点调用 DLL

## DLL 文件清单

| 平台 | DLL 名称 | 说明 |
|------|----------|------|
| CPU | `binocular_cpu.dll` | ONNX Runtime CPU 版本 |
| AMD 核显 | `binocular_dml.dll` | DirectML 加速版本 |
| Intel 核显 | `binocular_ov.dll` | OpenVINO 加速版本 |
| ARM64 | `libbinocular_rk3588.so` | RK3588 NPU 版本 |

## 接口定义

详见 [`03_Core_Algorithms/include/StereoApi.h`](../03_Core_Algorithms/include/StereoApi.h)

```c
// 接口概览
void*  Stereo_Init(const StereoCalibParams* params, const char* model_path);
int    Stereo_ProcessFrame(void* handle, const unsigned char* left_img,
                           const unsigned char* right_img, RangeResult* result);
int    Stereo_GetPupilPos(void* handle, const unsigned char* left_img,
                          const unsigned char* right_img, PupilResult* pupil);
void   Stereo_Release(void* handle);
```

## 上位机 P/Invoke 示例（C#）

```csharp
[DllImport("binocular_core.dll", CallingConvention = CallingConvention.Cdecl)]
public static extern IntPtr Stereo_Init(ref StereoCalibParams params, string modelPath);

[DllImport("binocular_core.dll", CallingConvention = CallingConvention.Cdecl)]
public static extern int Stereo_ProcessFrame(IntPtr handle, byte[] leftImg,
                                              byte[] rightImg, ref RangeResult result);

[DllImport("binocular_core.dll", CallingConvention = CallingConvention.Cdecl)]
public static extern void Stereo_Release(IntPtr handle);
```

> 代码由开发者上传
