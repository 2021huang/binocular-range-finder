#pragma once
#ifndef STEREO_MATCHER_H
#define STEREO_MATCHER_H

#include <opencv2/opencv.hpp>

namespace stereo {

struct MatchResult {
    cv::Mat disparity;
    cv::Mat depth_map;
    double elapsed_ms;
};

class StereoMatcher {
public:
    virtual ~StereoMatcher() = default;
    virtual MatchResult compute(const cv::Mat& left, const cv::Mat& right) = 0;
};

}  // namespace stereo

#endif
