// author: Babak Behkamkia (2154295)

#include <string>
#include <vector>
#include "dataset.h"

void writeCSV(const std::string& outputPath,
              const std::vector<Sample>& samples,
              const std::vector<std::vector<float>>& features,
              const std::vector<std::string>& classNames);