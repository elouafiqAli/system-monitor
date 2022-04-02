#include "processor.h"
#include "linux_parser.h"
#include <vector>
#include <string>
#include <unistd.h>
#include <iostream>
// TODO: Return the aggregate CPU utilization
using namespace std;


float Processor::Utilization() { 
    
    
    
    
    unsigned long int prev_total = total_, prev_idle= idle_;
    sleep(1);
    //std::cout<<"lol\n";
    total_ = LinuxParser::Jiffies(); 
    //std::cout<<"lol\n";
    idle_ = LinuxParser::IdleJiffies();
    
    float d_total = 1.0*total_- prev_total;
    float d_idle =  1.0*idle_ - prev_idle; 
    
    return (d_total-d_idle)/d_total; 
}