#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  // TODO: Declare any necessary private members
 private:
    unsigned long int total_{1};
    unsigned long int idle_{0};
    float last_utilization{0.0};
    
};

#endif