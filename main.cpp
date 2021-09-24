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
  std::cout << LinuxParser::User(120) << std::endl;
  return 0;
}

std::string LinuxParser::User(int pid) {

  std::string Uid;

  // Get the Uid from StatusFile.
  std::ifstream StatusFile(LinuxParser::kProcDirectory + std::to_string(pid) +
                           LinuxParser::kStatusFilename);
  if (StatusFile.is_open()) {
    std::string key, line, value;
    while (std::getline(StatusFile, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream statusStream(line);
      while (statusStream >> key >> value) {
        if (key == "Uid") Uid = value;
      }
    }
  }

  // Get the userName from /etc/passwd
  std::ifstream pwdFile(LinuxParser::kPasswordPath);
  if (pwdFile.is_open()) {
    std::string userName, x, line, value;
    while (std::getline(pwdFile, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream pwdStream(line);
      while (pwdStream >> userName >> x >> value) {
        if (value == Uid) return userName;
      }
    }
  }
  return " ";
}
