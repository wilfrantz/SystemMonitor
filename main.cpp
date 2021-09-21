#include <unistd.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "include/linux_parser.h"

// NOTE: Use as sanbox will delete later.

int main() {
  std::vector<std::string> data = LinuxParser::CpuUtilization();

  for (int i = 0; i < data.size(); i++) std::cout << data[i] << " " << std::endl;
}

std::vector<std::string> LinuxParser::CpuUtilization() {
  std::vector<std::string> CpuUse;

  std::ifstream cpuFile(LinuxParser::kProcDirectory +
                        LinuxParser::kStatFilename);
  if (cpuFile.is_open()) {
    std::string line, key, data;
    while (std::getline(cpuFile, line)) {
      std::istringstream cpuStream(line);
      while (cpuStream >> key) {
        if (key == "cpu") {
          for (int i = 0; i < LinuxParser::CPUStates::kGuestNice_; i++) {
            std::string data;
            cpuStream >> data;
            CpuUse.push_back(data);
          }
        }
      }
    }
  }
  return CpuUse;
}