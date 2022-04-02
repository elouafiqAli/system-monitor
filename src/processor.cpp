#include "processor.h"
#include "linux_parser.h"
#include <vector>
#include <string>
#include <unistd.h>
#include <iostream>

using namespace std;


float Processor::Utilization() { 

    unsigned long int prev_total = total_, prev_idle= idle_;
    
    total_ = LinuxParser::Jiffies(); 
    idle_ = LinuxParser::IdleJiffies();

    if(total_ == prev_total)
        return last_utilization;
    
    float d_total = 1.0*total_- prev_total;
    float d_idle =  1.0*idle_ - prev_idle; 
    
    last_utilization = (d_total-d_idle)/d_total;
    return last_utilization; 
}