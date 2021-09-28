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
using std::stol;
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

// DONE: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  float data, MemTotal = 0.0f, MemFree = 0.0f;
  std::string key, size, line;
  std::unordered_map<string, float> FileMap;
  const std::string keys[3] = {"MemTotal:", "MemFree:"};

  std::ifstream MemFile(LinuxParser::kProcDirectory +
                        LinuxParser::kMeminfoFilename);

  // Read the file and store the data in FileMap
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
  return stol(sysTime);
}

// DONE: Read and return the number of jiffies for the system
// NOTE: Unable to read the file on local machine due to file permission.
long LinuxParser::Jiffies() {
  std::string line, key, data;
  std::ifstream jif_file(LinuxParser::kProcDirectory +
                         LinuxParser::kTimerListFilename);
  if (jif_file.is_open()) {
    while (std::getline(jif_file, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> data) {
        if (key == "jiffies") {
          jif_file.close();
          return stol(data);
        }
      }
    }
  }

  return (-1);
}

// DONE: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) {
  std::string line, data;
  std::vector<string> activeJiffies;

  std::ifstream jif_file(LinuxParser::kProcDirectory + std::to_string(pid) +
                         LinuxParser::kStatFilename);
  if (jif_file.is_open()) {
    while (std::getline(jif_file, line)) {
      std::istringstream jifStream(line);
      while (jifStream >> data) activeJiffies.push_back(data);
    }
  }
  return std::stol(activeJiffies[13] + activeJiffies[14]);
}

// DONE: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {
  std::vector<string> CpuUse = LinuxParser::CpuUtilization();

  return std::stol(CpuUse[LinuxParser::CPUStates::kUser_]) +
         std::stol(CpuUse[LinuxParser::CPUStates::kNice_]) +
         std::stol(CpuUse[LinuxParser::CPUStates::kSystem_]) +
         std::stol(CpuUse[LinuxParser::CPUStates::kIRQ_]) +
         std::stol(CpuUse[LinuxParser::CPUStates::kSoftIRQ_]) +
         std::stol(CpuUse[LinuxParser::CPUStates::kSteal_]);
}

// DONE: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {
  std::vector<string> CpuUse = LinuxParser::CpuUtilization();

  // NOTE: Idle_Jiffies = CPUStates::KIdle_ +CPUStates::KIOwait_
  return std::stol(CpuUse[LinuxParser::CPUStates::kIdle_]) +
         std::stol(CpuUse[LinuxParser::CPUStates::kIOwait_]);
}

// DONE: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  std::vector<string> CpuUse;

  std::ifstream cpuFile(LinuxParser::kProcDirectory +
                        LinuxParser::kStatFilename);
  if (cpuFile.is_open()) {
    std::string line, key, data;
    while (std::getline(cpuFile, line)) {
      std::istringstream cpuStream(line);
      while (cpuStream >> key) {
        if (key == "cpu") {
          for (int i = 0; i < LinuxParser::CPUStates::kGuestNice_; i++) {
            std::string data;
            cpuStream >> data;
            CpuUse.push_back(data);
          }
        }
      }
    }
  }
  return CpuUse;
}

// DONE: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  std::string line, process, key;

  std::ifstream memFile(LinuxParser::kProcDirectory +
                        LinuxParser::kStatFilename);

  if (memFile.is_open()) {
    while (std::getline(memFile, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> process)
        if (key == "process") return std::stoi(process);
    }
  }
  return (-1);
}

// DONE: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  std::string line, key;
  int Running_Processes = 0;
  std::ifstream ProcessFile(LinuxParser::kProcDirectory +
                            LinuxParser::kStatFilename);
  if (ProcessFile.is_open()) {
    while (std::getline(ProcessFile, line)) {
      std::istringstream Prostream(line);
      while (Prostream >> key >> Running_Processes)
        if (key == "procs_running") return Running_Processes;
    }
  }

  return (-1);
}

// DONE: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  std::string line, cmd;
  std::ifstream cmdline(LinuxParser::kProcDirectory + std::to_string(pid) +
                        LinuxParser::kCmdlineFilename);
  if (cmdline.is_open())
    while (std::getline(cmdline, line)) cmd = line;

  return cmd;
}

// DONE: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
std::string LinuxParser::Ram(int pid) {
  std::string line, key, ram;
  std::ifstream ramFile(LinuxParser::kProcDirectory + std::to_string(pid) +
                        LinuxParser::kStatusFilename);
  if (ramFile.is_open()) {
    while (std::getline(ramFile, line)) {
      std::istringstream ramStream(line);
      while (ramStream >> key >> ram)
        if (key == "Mems_allowed:") return ram;
    }
  }

  return " ";
}

// DONE: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
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

// DONE: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
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

// DONE: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
  std::string line;
  std::ifstream UpFile(LinuxParser::kProcDirectory + std::to_string(pid) +
                       LinuxParser::kStatFilename);

  if (UpFile.is_open()) std::getline(UpFile, line);

  return stol(line) / sysconf(_SC_CLK_TCK);
}