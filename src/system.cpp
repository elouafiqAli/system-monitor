#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;
using std::sort;
using std::reverse;

Processor& System::Cpu() { return cpu_; }

// DONE: Return a container composed of the system's processes
void System::RefreshProcesses(){
    std::vector <Process> processes = {};
    std::vector <int> pids = LinuxParser::Pids();
    for(int pid : pids) processes.push_back(Process(pid));

    sort(processes.begin(),processes.end());
    reverse(processes.begin(),processes.end());
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
