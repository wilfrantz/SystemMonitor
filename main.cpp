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
  long data = LinuxParser::Jiffies();

  std::cout << "from main " << data << std::endl;
}

long LinuxParser::Jiffies() {
 std::string line, key, data;
  std::ifstream jif_file(LinuxParser::kProcDirectory +
                         LinuxParser::kTimerListFilename);

  if (jif_file.is_open()) {
    std::cout<<"File is open." << std::endl;
    while (std::getline(jif_file, line)) jif_file >> key >> data;
    return stol(data);
  }else{
    std::cout<<"File was not processed!"<< std::endl;
  }

  jif_file.close();
  return (-1); 
}