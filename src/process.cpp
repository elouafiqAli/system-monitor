#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"
#include "tic.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid): 
    pid_(pid), user_(LinuxParser::User(pid)), command_(LinuxParser::Command(pid))
    {
    start_time= Tic(LinuxParser::UpTime(pid));
    active_tics = Tic(LinuxParser::ActiveJiffies(pid_));
	total_tics = Tic((unsigned long int)(LinuxParser::UpTime()*Tic::hz())-start_time.tic());
      
    cpu_utilization =  1.*active_tics.tic()/(1.*total_tics.tic());
}
int Process::Pid() { return pid_; }


void Process::RefreshCpuUtilization(){
    unsigned long int active = LinuxParser::ActiveJiffies(pid_);
    unsigned long int uptime = (unsigned long int)(LinuxParser::UpTime()*Tic::hz())-start_time.tic();
    if(uptime != total_tics.tic())
        cpu_utilization =  (active_tics.diff(active)/(1.*total_tics.diff(uptime)));
}
// DONE: Return this process's CPU utilization
float Process::CpuUtilization(){ 
    RefreshCpuUtilization();
    return cpu_utilization;
}

string Process::Command() { return command_; }

// DONE: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_); }

string Process::User() { return user_; }

// DONE: Return the age of this process (in seconds)
long int Process::UpTime() const { return start_time.seconds(); }

// TODO: Overload the "less than" comparison operator for Process objects

bool Process::operator<(Process const& a) const { 
    return (cpu_utilization < a.cpu_utilization);
  
}

