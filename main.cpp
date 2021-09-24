#include <unistd.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "include/linux_parser.h"

// NOTE: Sanbox, will delete later.

int main() {
  std::cout << LinuxParser::Command(3018) << std::endl;
  return 0;
}

std::string LinuxParser::Command(int pid) {
  std::string line, cmd;
  std::ifstream cmdline(LinuxParser::kProcDirectory + std::to_string(pid) +
                        LinuxParser::kCmdlineFilename);
  if (cmdline.is_open()) {
    std::cout << "File is opened" << std::endl; // NOTE: Remove me!
    while (std::getline(cmdline, line)) return cmd = line;
  }

  return "Empty";
}
