/**
 * @brief 双目测距核心算法 DLL 接口定义
 *
 * 暴露给上位机（C++/C#/Python 等）调用的 C 风格接口。
 * Windows 导出 __declspec(dllexport)，Linux 导出默认符号。
 */

#pragma once
#ifndef STEREO_API_H
#define STEREO_API_H

#ifdef _WIN32
    #define STEREO_API __declspec(dllexport)
#else
    #define STEREO_API __attribute__((visibility("default")))
#endif

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========== 数据结构 ========== */

/** @brief 相机标定参数 */
typedef struct {
    double Kl_data[9];      // 左相机内参 3x3
    double Kr_data[9];      // 右相机内参 3x3
    double dist_l[5];       // 左畸变系数
    double dist_r[5];       // 右畸变系数
    double R_data[9];       // 旋转矩阵 3x3
    double T_data[3];       // 平移向量 3x1
    int    image_width;     // 图像宽度
    int    image_height;    // 图像高度
} StereoCalibParams;

/** @brief 瞳孔检测结果 */
typedef struct {
    double left_x;          // 左瞳孔 X (像素)
    double left_y;          // 左瞳孔 Y (像素)
    double right_x;         // 右瞳孔 X (像素)
    double right_y;         // 右瞳孔 Y (像素)
    float  confidence;      // 置信度 [0, 1]
} PupilResult;

/** @brief 测距结果 */
typedef struct {
    double pos_x;           // 空间 X (mm)
    double pos_y;           // 空间 Y (mm)
    double pos_z;           // 空间 Z (mm)
    double dist_left;       // 距左相机 (mm)
    double dist_right;      // 距右相机 (mm)
    double baseline;        // 基线长度 (mm)
    float  elapsed_ms;      // 处理耗时 (ms)
} RangeResult;

/* ========== 接口函数 ========== */

/**
 * @brief 初始化双目测距引擎
 * @param params 标定参数
 * @param model_path 瞳孔识别模型路径
 * @return 句柄指针（失败返回 NULL）
 */
STEREO_API void* Stereo_Init(const StereoCalibParams* params, const char* model_path);

/**
 * @brief 处理单帧图像
 * @param handle 引擎句柄
 * @param left_img 左图数据 (BGR, contiguous)
 * @param right_img 右图数据 (BGR, contiguous)
 * @param result [out] 测距结果
 * @return 0=成功, -1=失败
 */
STEREO_API int Stereo_ProcessFrame(void* handle,
                                   const unsigned char* left_img,
                                   const unsigned char* right_img,
                                   RangeResult* result);

/**
 * @brief 获取瞳孔像素坐标
 * @param handle 引擎句柄
 * @param left_img 左图数据
 * @param right_img 右图数据
 * @param pupil [out] 瞳孔坐标
 * @return 0=成功, -1=失败
 */
STEREO_API int Stereo_GetPupilPos(void* handle,
                                  const unsigned char* left_img,
                                  const unsigned char* right_img,
                                  PupilResult* pupil);

/**
 * @brief 释放引擎资源
 * @param handle 引擎句柄
 */
STEREO_API void Stereo_Release(void* handle);

#ifdef __cplusplus
}
#endif

#endif /* STEREO_API_H */
