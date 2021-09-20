#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <unistd.h>
#include "include/linux_parser.h"

// NOTE: Use as sanbox will delete later.
using std::stol;

int main() {
  using namespace LinuxParser;
  Jiffies();

  // std:: cout << "Jiffies is: " << data << std::endl;

}

long LinuxParser::Jiffies() {
  long jiffies = 0;
  std::string line, key, data;
  std::ifstream jif_file(LinuxParser::kProcDirectory +
                         LinuxParser::kTimerListFilename);

  if (jif_file.is_open()) {
    while (std::getline(jif_file, line)) {
      std::istringstream stream(line);
      while (stream >> key >> data)
        if (key == "jiffies") std::cout << key << " " << data << std::endl;
    }
  }

  // jif_file.close();

  return 0.0;
  // return std::stol(data);
}
