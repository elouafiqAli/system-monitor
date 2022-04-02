#ifndef PROCESSOR_H
#define PROCESSOR_H


class KernelJiffies{
public:
  unsigned long int kUser{0};
  unsigned long int kNice{0};
  unsigned long int kSystem{0};
  unsigned long int kIdle{0};
  unsigned long int kIOwait{0};
  unsigned long int kIRQ{0};
  unsigned long int kSoftIRQ{0};
  unsigned long int kSteal{0};
  unsigned long int kGuest{0};
  unsigned long int kGuestNice{0};
  unsigned long int kNonIdle() const;
  unsigned long int kTotal() const;
  
};

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  KernelJiffies Tic() const { return tic;}
  KernelJiffies Toc() const;
  // TODO: Declare any necessary private members
 private:
    KernelJiffies tic;
    
    
};

#endif