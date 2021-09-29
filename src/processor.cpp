#include "processor.h"

Processor::Processor()
    : _pIdle(LinuxParser::IdleJiffies()),
      _pNonIdle(LinuxParser::ActiveJiffies()),
      _pTotal(_pIdle + _pNonIdle) {}

// DONE: Return the aggregate CPU utilization
float Processor::Utilization() {
  long cActive = LinuxParser::ActiveJiffies();
  long cIdle = LinuxParser::IdleJiffies();
  long cTotal = cActive + cIdle;

  long idle_ = cIdle - _pIdle;
  long total_ = cTotal - _pTotal;

  _pIdle = cIdle;
  _pNonIdle = cActive;
  _pTotal = cTotal;

  long cpu = total_ == 0 ? 0.0 : (total_ - idle_) / total_;

  return cpu;
}