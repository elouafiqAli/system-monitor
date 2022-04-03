#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include "processor.h"
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
  float CpuUtilization() const;                  
  std::string Ram();                       
  long int UpTime() const;                       
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  // TODO: Declare any necessary private members
 private:
    long int pid_{20};
    std::string user_{"root"};
    std::string command_{"pwd"};

};

#endif