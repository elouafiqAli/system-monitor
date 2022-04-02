#include "ncurses_display.h"
#include "system.h"
#include "linux_parser.h"
#include <iostream>
#include <cassert>
#include <unistd.h>
#include <string>
#include <vector>

#define DEBUG true
int main() {
  System system;
  std::vector<int> pids = LinuxParser::Pids();
  if(DEBUG){
    for(auto pid : pids){
      std::cout << pid << " - uuid :"<<LinuxParser::Uid(pid) <<" - user : " <<LinuxParser::User(pid) << std::endl;
    } 
    
  } else{ 
      NCursesDisplay::Display(system);
  }
   
}