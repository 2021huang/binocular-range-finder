#pragma once
#ifndef TRIANGULATE_H
#define TRIANGULATE_H

#include <opencv2/opencv.hpp>

namespace stereo {

struct TriangulateResult {
    cv::Point3f position_3d;
    double distance_left;
    double distance_right;
    double baseline;
};

class Triangulator {
public:
    TriangulateResult compute(
        const cv::Point2f& p_left,
        const cv::Point2f& p_right,
        const cv::Mat& P_left,
        const cv::Mat& P_right
    );
};

}  // namespace stereo

#endif
