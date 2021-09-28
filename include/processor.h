#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include <vector>

#include "LinuxParser.h"

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
  int _pid;
  float _cup;
  std::string _user, cmd;
};

#endif