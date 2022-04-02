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
   if(DEBUG){
    
  } else{ 
      NCursesDisplay::Display(system);
  }
   
}