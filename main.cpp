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
  std::cout << LinuxParser::Uid(2364) << std::endl;
  return 0;
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
std::string LinuxParser::Uid(int pid) {
  std::string Uid, line, key;
  std::ifstream UidFile(LinuxParser::kProcDirectory + std::to_string(pid) +
                        LinuxParser::kStatusFilename);
  if (UidFile.is_open()) {
    while (std::getline(UidFile, line)) {
      std::istringstream UidStream(line);
      while (UidStream >> key >> Uid)
        if (key == "Uid:") return Uid;
    }

  }
    return " ";
}