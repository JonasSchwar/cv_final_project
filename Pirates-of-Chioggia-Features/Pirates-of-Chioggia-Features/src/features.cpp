// author: Babak Behkamkia (2154295)
// ref: https://docs.opencv.org/4.13.0/d6/dc7/group__imgproc__hist.html
//      https://docs.opencv.org/4.13.0/d4/d86/group__imgproc__filter.html
//      https://docs.opencv.org/4.13.0/dd/d1a/group__imgproc__feature.html

#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath>
#include "features.h"
#include "preprocessing.h"

std::vector<float> colorFeatures(const cv::Mat& rgb, int nBins)
{
    cv::Mat hsvImage, labImage;
    cv::cvtColor(rgb, hsvImage, cv::COLOR_RGB2HSV);
    cv::cvtColor(rgb, labImage, cv::COLOR_RGB2Lab);

    std::vector<float> feats;

    std::vector<cv::Mat> hsvChannels(3);
    std::vector<cv::Mat> labChannels(3);
    cv::split(hsvImage, hsvChannels);
    cv::split(labImage, labChannels);

    std::vector<cv::Mat> allChannels;
    for (int i = 0; i < 3; ++i) {
        allChannels.push_back(hsvChannels[i]);
    }
    for (int i = 0; i < 3; ++i) {
        allChannels.push_back(labChannels[i]);
    }

    for (int c = 0; c < (int)allChannels.size(); ++c)
    {
        float range[] = {0, 256};
        const float* ranges = {range};
        cv::Mat hist;
        cv::calcHist(&allChannels[c], 1, 0, cv::Mat(), hist, 1, &nBins, &ranges);

        float totalPixels = (float)(allChannels[c].rows * allChannels[c].cols);
        for (int b = 0; b < nBins; ++b)
            feats.push_back(hist.at<float>(b) / totalPixels);
    }

    return feats;
}

std::vector<float> gradientFeatures(const cv::Mat& gray)
{
    // Sobel
    cv::Mat sx, sy;
    cv::Sobel(gray, sx, CV_64F, 1, 0, 3);
    cv::Sobel(gray, sy, CV_64F, 0, 1, 3);
    cv::Mat sobelMag;
    cv::magnitude(sx, sy, sobelMag);

    cv::Scalar sobelMean, sobelStd;
    cv::meanStdDev(sobelMag, sobelMean, sobelStd);

    // Laplacian
    cv::Mat lap;
    cv::Laplacian(gray, lap, CV_64F);
    cv::Scalar lapMean, lapStd;
    cv::meanStdDev(lap, lapMean, lapStd);
    float lapVar = (float)(lapStd[0] * lapStd[0]);

    return {
        (float)sobelMean[0],
        (float)sobelStd[0],
        lapVar
    }; 
}

std::vector<float> extractFeatures(const std::string& imagePath)
{
    cv::Mat bgr = cv::imread(imagePath);
    cv::Mat rgb;
    cv::cvtColor(bgr, rgb, cv::COLOR_BGR2RGB);

    cv::Mat rgbProc, grayProc;
    preprocess(rgb, rgbProc, grayProc);

    std::vector<float> colorFeats = colorFeatures(rgbProc, 32); 
    std::vector<float> gradientFeats  = gradientFeatures(grayProc); 

    std::vector<float> allFeatures;
    for (int i = 0; i < (int)colorFeats.size(); ++i)
        allFeatures.push_back(colorFeats[i]);
    for (int i = 0; i < (int)gradientFeats.size(); ++i)
        allFeatures.push_back(gradientFeats[i]);

    return allFeatures;  
}