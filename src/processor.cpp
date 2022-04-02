#include "processor.h"
#include "linux_parser.h"
#include <vector>
#include <string>
#include <unistd.h>
// TODO: Return the aggregate CPU utilization
using namespace std;


KernelJiffies Processor::Toc() const{
    KernelJiffies tic;
    vector<string> utils =  LinuxParser::CpuUtilization();

    tic.kUser = stoi(utils.at(LinuxParser::CPUStates::kUser_));
    tic.kNice = stoi(utils.at(LinuxParser::CPUStates::kNice_));
    tic.kSystem = stoi(utils.at(LinuxParser::CPUStates::kSystem_));
    tic.kIdle = stoi(utils.at(LinuxParser::CPUStates::kIdle_));
    tic.kIOwait = stoi(utils.at(LinuxParser::CPUStates::kIOwait_));
    tic.kIRQ = stoi(utils.at(LinuxParser::CPUStates::kIRQ_));
    tic.kSoftIRQ = stoi(utils.at(LinuxParser::CPUStates::kSoftIRQ_));
    tic.kSteal = stoi(utils.at(LinuxParser::CPUStates::kSteal_));
    tic.kGuest = stoi(utils.at(LinuxParser::CPUStates::kGuest_));
    tic.kGuestNice = stoi(utils.at(LinuxParser::CPUStates::kGuestNice_));

    return tic;
}

unsigned long int KernelJiffies::kNonIdle() const{
    return  (kUser + kNice + kSystem + kIRQ + kSoftIRQ + kSteal);
};

unsigned long int KernelJiffies::kTotal() const{
    return KernelJiffies::kNonIdle() + kIdle + kIOwait;;
}

float Processor::Utilization() { 
    if(tic.kUser == 0){
        tic = Processor::Toc();
        return 0.0;
    }
    sleep(0.5);
    KernelJiffies prev_tic = tic;
    tic = Processor::Toc();
    
    float d_total = (float)tic.kTotal() - (float)prev_tic.kTotal();
    float d_idle = tic.kIdle + tic.kIOwait - prev_tic.kIdle - prev_tic.kIOwait;
    
    return (d_total-d_idle)/d_total; 
}