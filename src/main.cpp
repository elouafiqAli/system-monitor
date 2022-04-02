#include "ncurses_display.h"
#include "system.h"
#include "linux_parser.h"
#include <iostream>
#include <cassert>
#include <string>
#include <vector>

#define DEBUG false
int main() {
  System system;
  if(DEBUG){
    std::vector <int> pids = LinuxParser::Pids();
    for (int pid : pids){
      Process pro(pid);
      std::cout<< std::to_string(pid)+" " +pro.User()<<std::endl;
      std::cout<< "RAM : "+pro.Ram()<<std::endl;
    }
 
  } else{ 
      NCursesDisplay::Display(system);
  }
   
}