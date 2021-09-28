#include "format.h"

using std::string;
using std::stringstream;
using std::to_string;

string format(int num) {
  stringstream Ss;
  if (num < 10) Ss << "0";
  Ss << num;
  return Ss.str();
}

// DONE: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
  const long mnt = (seconds / 60) % 60;
  const long hrs = seconds / 3600;
  const long sec = seconds % 60;

  std::stringstream stream;
  stream << format(hrs) << ":" << format(mnt) << ":" << format(sec);
  return stream.str();
}