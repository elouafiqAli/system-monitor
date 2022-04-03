#include <string>

#include "format.h"

using std::string;

// DONE: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
  int HH = seconds/3600;
  int MM = seconds/60-HH*60;
  int SS = seconds - 60*MM - 3600*HH;
  
  string HH_MM_SS;
  HH/10 > 0 ? HH_MM_SS.append(std::to_string(HH)+":") : HH_MM_SS.append((HH ? ("0"+std::to_string(HH)+":") : "00:"));
  MM/10 > 0 ? HH_MM_SS.append(std::to_string(MM)+":") : HH_MM_SS.append((MM ? ("0"+std::to_string(MM)+":") : "00:"));
  SS/10 > 0 ? HH_MM_SS.append(std::to_string(SS)) : HH_MM_SS.append("0"+std::to_string(SS));
  
  return HH_MM_SS; 
}