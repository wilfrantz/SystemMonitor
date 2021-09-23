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
  std::cout << LinuxParser::UpTime(2364) << std::endl;
  return 0;
}

long LinuxParser::UpTime(int pid) {
  std::string line;
  std::ifstream UpFile(LinuxParser::kProcDirectory + std::to_string(pid) +
                       LinuxParser::kStatFilename);

  if (UpFile.is_open()) std::getline(UpFile, line);

  return stol(line) / sysconf(_SC_CLK_TCK);
}

/*
long LinuxParser::UpTimes(int pid) {
  std::string line;
  std::ifstream UpFile(LinuxParser::kProcDirectory + std::to_string(pid) +
                       LinuxParser::kStatFilename);

  if (UpFile.is_open()) {
    while (std::getline(UpFile, line)) {
      std::cout << "here: " << line << std::endl;
      int pos = line.find(pid);
      std::cout << "There: " << std::stol(line) / sysconf(_SC_CLK_TCK)<< std::endl;
      std::istringstream upstream(line);
      std::string data;
      exit (0);
      std::istringstream upstream(line);
      // for (int i = 0; i < 52; i++) upstream >> data;
      // std::cout << "here: " << data << std::endl;
      exit (0);
    }
  }
    // return stol(data) / sysconf(_SC_CLK_TCK);
    return 0;
}
*/