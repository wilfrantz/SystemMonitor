#include "processor.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  long cActive = LinuxParser::activeJiffies();
  long cIddle = LinuxParser::IdleJiffies();
  long cTotal = cActive + cIddle;

  long cpu = cTotal == 0 ? return cpu : return (cTotal - cIddle) / cTotal;

  return 0.0;
}