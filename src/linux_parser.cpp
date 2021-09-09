#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using std::cout;
using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

//Done: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  float data, MemTotal = 0.0f, MemFree = 0.0f;
  std::string key, size, line;
  const std::string keys[3] = {"MemTotal:", "MemFree:"};

  std::unordered_map<string, float> FileMap;

  std::ifstream MemFile(LinuxParser::kProcDirectory +
                        LinuxParser::kMeminfoFilename);

  // Read the file and store the data in an unordered_map
  if (MemFile.is_open()) {
    while (std::getline(MemFile, line)) {
      while (MemFile >> key >> data >> size) FileMap[key] = data;
    }
  }

  // NOTE: Needs to find out why it won't take the first element "MemTotal".
  // Go through the map, compare the elements, retrieve Memtotal and MemFree .
  if (!FileMap.empty()) {
    for (auto& it : keys) {
      for (const auto& elem : FileMap) {
        if (elem.first == keys[0]) MemTotal = elem.second;
        if (elem.first == keys[1]) MemFree = elem.second;
      }
    }
  } else {
    cout << "Error: Map is empty." << std::endl;
    exit(1);
  }

  MemFile.close();

  return MemTotal - MemFree;
}

// Done: Read and return the system uptime
long LinuxParser::UpTime() {
  std::string line, sysTime;

  std::ifstream TimeFile(LinuxParser::kProcDirectory +
                         LinuxParser::kUptimeFilename);
  if (TimeFile.is_open()) {
    while (std::getline(TimeFile, line)) {
      std::istringstream linestream(line);
      linestream >> sysTime;
    }
  }

  TimeFile.close();
  return stol(sysTime);
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid [[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { return 0; }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { return 0; }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid [[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid [[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid [[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid [[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid [[maybe_unused]]) { return 0; }
