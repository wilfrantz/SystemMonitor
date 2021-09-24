#include <unistd.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "include/linux_parser.h"

// NOTE: Sanbox will delete later.

int main() {
  std::cout << LinuxParser::Ram(120) << std::endl;
  return 0;
}

std::string LinuxParser::Ram(int pid) {
  std::string line, key, ram;
  std::ifstream ramFile(LinuxParser::kProcDirectory + std::to_string(pid) +
                        LinuxParser::kStatusFilename);
  if (ramFile.is_open()) {
    while (std::getline(ramFile, line)) {
      std::istringstream ramStream(line);
      while (ramStream >> key >> ram)
        if (key == "Mems_allowed:") return ram;
    }
  }

  return " ";
}
