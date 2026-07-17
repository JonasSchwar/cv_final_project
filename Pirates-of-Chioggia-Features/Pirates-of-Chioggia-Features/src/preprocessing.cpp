// author: Babak Behkamkia (2154295)
// ref: https://docs.opencv.org/4.13.0/d4/d86/group__imgproc__filter.html
//      https://docs.opencv.org/4.13.0/d6/db6/classcv_1_1CLAHE.html
//      https://stackoverflow.com/questions/24341114/simple-illumination-correction-in-images-opencv-c


#include <opencv2/opencv.hpp>
#include "preprocessing.h"


cv::Mat applyGaussianBlur(const cv::Mat& rgb)
{
    cv::Mat blurred;
    cv::GaussianBlur(rgb, blurred, cv::Size(5, 5), 1.0);
    return blurred;
}

cv::Mat applyCLAHE(const cv::Mat& rgb)
{
    cv::Mat lab;
    cv::cvtColor(rgb, lab, cv::COLOR_RGB2Lab);

    std::vector<cv::Mat> channels(3);
    cv::split(lab, channels);

    cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE(2.0, cv::Size(8, 8));
    clahe->apply(channels[0], channels[0]);

    cv::merge(channels, lab);
    cv::Mat result;
    cv::cvtColor(lab, result, cv::COLOR_Lab2RGB);
    return result;
}

void preprocess(const cv::Mat& rgb, cv::Mat& rgbOut, cv::Mat& grayOut)
{
    cv::Mat blurred = applyGaussianBlur(rgb);
    rgbOut = applyCLAHE(blurred);
    cv::cvtColor(rgbOut, grayOut, cv::COLOR_RGB2GRAY);
}
