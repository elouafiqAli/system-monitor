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
  if(DEBUG){
    assert(LinuxParser::Uid(20) == "0" );
    assert(LinuxParser::User(20)== "root");
    std::cout<< LinuxParser::Command(20) <<std::endl;
   
  } else{ 
      NCursesDisplay::Display(system);
  }
   
}