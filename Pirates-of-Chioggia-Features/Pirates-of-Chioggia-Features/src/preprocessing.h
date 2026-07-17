// author: Babak Behkamkia (2154295)

#include <opencv2/opencv.hpp>

cv::Mat applyGaussianBlur(const cv::Mat& rgb);
cv::Mat applyCLAHE(const cv::Mat& rgb);
void preprocess(const cv::Mat& rgb, cv::Mat& rgbOut, cv::Mat& grayOut);