// author: Babak Behkamkia (2154295)
// ref: https://en.cppreference.com/cpp/filesystem/directory_iterator
//      https://www.w3schools.com/cpp/cpp_iterators.asp

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <filesystem>
#include "dataset.h"

std::map<std::string, std::vector<std::string>> loadImagePaths()
{
    std::map<std::string, std::string> classFolders;
    classFolders["Bare Soil"] = "../dataset/Bare soil/";
    classFolders["Stone"] = "../dataset/Stones/";
    classFolders["Vegetation"] = "../dataset/Vegetation/";

    std::map<std::string, std::vector<std::string>> result;

    std::vector<std::string> classNames = {"Bare Soil", "Stone", "Vegetation"};
    for (int i = 0; i < (int)classNames.size(); ++i)
    {
        std::string cls = classNames[i];
        std::string folder = classFolders[cls];

        if (!std::filesystem::exists(folder)) {
            std::cerr << "WARNING: could not find folder: " << folder << "\n";
            continue;
        }

        std::vector<std::string> paths;
        std::filesystem::directory_iterator entry(folder);
        std::filesystem::directory_iterator end;

        while (entry != end)
        {
            std::string filePath = entry->path().string();

            std::string ext = entry->path().extension().string();

            for (int j = 0; j < (int)ext.size(); ++j)
                ext[j] = tolower(ext[j]);

            if (ext == ".png" || ext == ".jpg" || ext == ".jpeg")
                paths.push_back(filePath);

            ++entry;
        }

        std::sort(paths.begin(), paths.end());
        std::cout << "  " << cls << ": " << paths.size() << " images\n";
        result[cls] = paths;

    }

    return result;
}