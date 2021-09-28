#ifndef PROCESSOR_H
#define PROCESSOR_H


#include "linux_parser.h"

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  Processor();

  // TODO: Declare any necessary private members
 private:
  int _pid;
  long _pIdle;
  long _pNonIdle;
  long _pTotal;
};

#endif