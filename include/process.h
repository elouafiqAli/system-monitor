#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include "tic.h"
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/

class Process {
 public:
  Process(int pid);
  int Pid();                               
  std::string User();                      
  std::string Command();                    
  float CpuUtilization();                  
  std::string Ram();                       
  long int UpTime() const;                       
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp
  // TODO: Declare any necessary private members
 private:

    long int pid_{20};
    std::string user_{"root"};
    std::string command_{"pwd"};
    
    Tic active_tics{0};
    Tic total_tics{1};
    Tic start_time{0};
    
    void RefreshCpuUtilization();
    float cpu_utilization{0.0};
};

#endif