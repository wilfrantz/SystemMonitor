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
