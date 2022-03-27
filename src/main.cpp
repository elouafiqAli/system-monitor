#include "ncurses_display.h"
#include "system.h"
#include <iostream>
int main() {
  System system;
  //std::cout << system.UpTime() <<std::endl;
  NCursesDisplay::Display(system);
}