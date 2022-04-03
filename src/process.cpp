#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

#define EPSILON 0.0001

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid): 
    pid_(pid), user_(LinuxParser::User(pid)), command_(LinuxParser::Command(pid)){
    
}
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const{ 

    float total_time = (1.0*LinuxParser::ActiveJiffies(pid_))/sysconf(_SC_CLK_TCK);;
    float seconds = LinuxParser::UpTime()-UpTime();

    return (1.00*total_time/seconds);
    }

string Process::Command() { return command_; }

// DONE: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_); }

string Process::User() { return user_; }

// DONE: Return the age of this process (in seconds)
long int Process::UpTime() const { return LinuxParser::UpTime(pid_)/sysconf(_SC_CLK_TCK); }

// TODO: Overload the "less than" comparison operator for Process objects

bool Process::operator<(Process const& a) const { 

    return ( (Process::CpuUtilization() - a.CpuUtilization()) < EPSILON) ;
}