#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "tic.h"
class Processor {
 public:
  float Utilization();  
  
 private:
    Tic total_tics{0};
    Tic active_tics{0};
};

#endif