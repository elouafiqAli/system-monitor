#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  // TODO: Declare any necessary private members
 private:
    unsigned long int total_{0};
    unsigned long int idle_{0};
    unsigned long int active_{0};
    
};

#endif