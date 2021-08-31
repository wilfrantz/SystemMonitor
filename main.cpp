#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

// NOTE: Used as playground will delete later.

int main() {
  std::ifstream file("/proc/meminfo");
  long int data;
  std::string key;
  std::unordered_map<std::string, int> FileMap;

  if (file.is_open()) {
    std::cout << "Reading: /proc/meminfo in:" << std::endl;
    while (file >> key >> data) FileMap[key] = data;
  }

  if (!FileMap.empty()) {
    std::cout << "the map size is " << FileMap.size() << std::endl;
    for (const auto &elem : FileMap) std::cout << elem.second << std::endl;
  } else {
    std::cout << "The Map is empty, there was an error." << std::endl;
    exit(1);
  }

  file.close();
  return 0;
}
