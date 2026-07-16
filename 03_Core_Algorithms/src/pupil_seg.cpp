/**
 * @brief 瞳孔语义分割推理
 *
 * 使用 ONNX Runtime 加载 PupilCheck_sim0.onnx / PupilCheck_sim1.onnx
 * 推理库按平台选择:
 *   - CPU: Microsoft.ML.OnnxRuntime
 *   - AMD: Microsoft.ML.OnnxRuntime.DirectML
 *   - Intel: OpenVINO
 *   - RK3588: RKNN
 *
 * TODO: 源代码由开发者上传
 */
#include "StereoApi.h"
