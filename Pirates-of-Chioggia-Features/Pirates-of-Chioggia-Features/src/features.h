// author: Babak Behkamkia (2154295)


#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

std::vector<float> colorFeatures(const cv::Mat& rgb, int nBins);
std::vector<float> gradientFeatures(const cv::Mat& gray);
std::vector<float> extractFeatures(const std::string& imagePath);