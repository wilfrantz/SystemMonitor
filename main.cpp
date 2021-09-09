#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <unistd.h>

// NOTE: Use as sanbox will delete later.
long UpTime();

int main() {
  std::ifstream MemFile("/proc/meminfo");
  float data, memory = 0.0f, MemTotal = 0.0f, MemFree = 0.0f, MemAvail = 0.0f;
  std::string key, size, line;
  const std::string keys[5] = {"MemTotal:", "MemFree:"};

  std::unordered_map<std::string, float> FileMap;

  if (MemFile.is_open()) {
    std::cout << "Reading: /proc/meminfo in:" << std::endl;
    while (std::getline(MemFile, line)) {
      while (MemFile >> key >> data >> size) FileMap[key] = data;
      //  FileMap.insert(std::make_pair(key, data));
    }
  }

  if (!FileMap.empty()) {
    std::cout << "the map size is " << FileMap.size() << "\n\n";
    for (const auto &elem : FileMap) {
      if (elem.first == keys[0]) MemTotal = elem.second;
      if (elem.first == keys[1]) MemFree = elem.second;
    }
  } else {
    std::cout << "The Map is empty, there was an error." << std::endl;
    exit(1);
  }
  std::cout << "MemTotal is " << MemTotal << "\n"
            << "MemFree is " << MemFree << "\n\n";

  std::cout << "Memory is " << MemTotal - MemFree << "\n";

  std::cout << "The system uptime is: " << UpTime() << std::endl;

  MemFile.close();
  return 0;
}

long UpTime() {
  std::string line, sysTime;
  std::ifstream TimeFile("/proc/uptime");
  if (TimeFile.is_open()) {
    while (std::getline(TimeFile, line)) {
      std::istringstream linestream(line);
      linestream >> sysTime;
    }
  }

  TimeFile.close();
  return std::stol(sysTime);
}