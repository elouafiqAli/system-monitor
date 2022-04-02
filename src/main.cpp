#include "ncurses_display.h"
#include "system.h"
#include "linux_parser.h"
#include <iostream>
#include <cassert>
#include <unistd.h>
#include <string>
#include <vector>

#define DEBUG false
int main() {
  System system;
   if(!DEBUG){
    NCursesDisplay::Display(system);
  } else{
    for(int i = 0; i< 99 ; i++){
    std::cout << "CPU :"    <<system.Cpu().Utilization() <<std::endl;
    std::cout << "idle : "  <<(system.Cpu().Tic().kIdle + system.Cpu().Toc().kUser)
    << " Non Idle: " <<system.Cpu().Toc().kNonIdle() << std::endl;
    }
   
      
  }
   
}