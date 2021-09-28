#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "LinuxParser.h"

using std::string;
using std::to_string;
using std::vector;

// DONE: Return this process's ID
int Process::Pid() {return this->_pid;}

// DONE: Return this process's CPU utilization
float Process::CpuUtilization() { return this->_cpu; }

// DONE: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(this->_pid);}

// DONE: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(this->_pid); }

// DONE: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(this->_pid); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() {
  return LinuxParser::UpTime(this->_pid) - (starttime_ - hertz_);
}

// DONE: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { return LinuxParser::CpuUtilization < a._cpu; }