// author: Babak Behkamkia (2154295)

#pragma once
#include <string>
#include <vector>
#include <map>

struct Sample {
    std::string path;
    int label;
};

std::map<std::string, std::vector<std::string>> loadImagePaths();