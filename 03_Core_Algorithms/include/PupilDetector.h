#pragma once
#ifndef PUPIL_DETECTOR_H
#define PUPIL_DETECTOR_H

#include <opencv2/opencv.hpp>
#include <memory>

namespace stereo {

struct PupilResult {
    cv::Point2f center;
    float confidence;
    cv::Mat segmentation_mask;
};

class PupilDetector {
public:
    virtual ~PupilDetector() = default;
    virtual PupilResult detect(const cv::Mat& image) = 0;
};

}  // namespace stereo

#endif
