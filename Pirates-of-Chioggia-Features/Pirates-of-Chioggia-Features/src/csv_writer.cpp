// author: Babak Behkamkia (2154295)
// ref: https://www.gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp/


#include "csv_writer.h"
#include <fstream>
#include <iostream>

void writeCSV(const std::string& outputPath, 
              const std::vector<Sample>& samples, 
              const std::vector<std::vector<float>>& features, 
              const std::vector<std::string>& classNames)
{
    std::ofstream file(outputPath);

    // Header
    file << "image,class";
    for (int i = 0; i < 209; ++i)
        file << ",feat_" << i;
    file << "\n";

    // Rows
    for (int i = 0; i < (int)samples.size(); ++i) {
        file << samples[i].path << "," << classNames[samples[i].label];
        for (int j = 0; j < (int)features[i].size(); ++j)
            file << "," << features[i][j];
        file << "\n";
    }
}