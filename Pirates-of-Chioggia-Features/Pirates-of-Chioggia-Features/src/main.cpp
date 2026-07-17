// author: Babak Behkamkia (2154295)


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <opencv2/opencv.hpp>
#include "dataset.h"
#include "features.h"
#include "csv_writer.h"

int main()
{
    std::vector<std::string> classNames;
    classNames.push_back("Bare Soil");
    classNames.push_back("Stone");
    classNames.push_back("Vegetation");

    std::map<std::string, std::vector<std::string>> classPaths = loadImagePaths();

    std::vector<Sample> allSamples;
    for (int label = 0; label < (int)classNames.size(); ++label) {
        const std::vector<std::string>& paths = classPaths[classNames[label]];
        for (int i = 0; i < (int)paths.size(); ++i) {
            Sample s;
            s.path  = paths[i];
            s.label = label;
            allSamples.push_back(s);
        }
    }
    std::cout << "Total images: " << allSamples.size() << "\n";

    std::vector<std::vector<float>> allFeatures;

    for (int i = 0; i < (int)allSamples.size(); ++i) {
        allFeatures.push_back(extractFeatures(allSamples[i].path));
    }

    writeCSV("../dataset/features.csv", allSamples, allFeatures, classNames);
    std::cout << "Features are saved in the dataset folder.";

    return 0;
}