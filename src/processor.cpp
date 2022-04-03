#include "processor.h"
#include "linux_parser.h"
#include <vector>
#include <string>
#include <unistd.h>
#include <iostream>

using namespace std;

float Processor::Utilization() { 

    unsigned long int jiffies = LinuxParser::Jiffies(); 
    unsigned long int active_jiffies = LinuxParser::ActiveJiffies();
    if(jiffies != total_tics.tic())
        utilization = active_tics.diff(active_jiffies)/(1.*total_tics.diff(jiffies));
    else 
        return utilization;

}