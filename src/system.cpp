

#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// DONE: Return the system's CPU
Processor& System::Cpu() { return this->cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() {
  set<int> setOfid;
  for (Process px : this->processes_) setOfid.insert(px.Pid());

  vector<int> vecOfid = LinuxParser::Pids();
  for (int id : vecOfid) {
    if (setOfid.find(id) == setOfid.end())
      this->processes_.emplace_back(Process(id));
  }

  for (Process pro : this->processes_) pro.CpuUtilization();

  return this->processes_;
}

// DONE: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// DONE: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// DONE: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// DONE: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// DONE: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// DONE: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }