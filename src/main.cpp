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
    std::cout << LinuxParser::UpTime(20) <<std::endl;
 
  } else{ 
      NCursesDisplay::Display(system);
  }
   
}