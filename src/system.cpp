#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <iostream>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

Processor& System::Cpu() { return cpu_; }

// DONE: Return a container composed of the system's processes
void System::RefreshProcesses(){
    std::vector <Process> processes = {};
    std::vector <int> pids = LinuxParser::Pids();
    for(int pid : pids){
        Process p(pid);  
        processes.push_back(p);
    }
    processes_ = processes;
}
vector<Process>& System::Processes() { 
    RefreshProcesses();
    return processes_; 
}


std::string System::Kernel() { return LinuxParser::Kernel(); }


float System::MemoryUtilization() {  return LinuxParser::MemoryUtilization(); }


std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }


int System::RunningProcesses() { return LinuxParser::RunningProcesses();; }


int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }


long int System::UpTime() { return LinuxParser::UpTime(); }