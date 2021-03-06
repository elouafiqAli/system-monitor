#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>
#include "linux_parser.h"
#include <iomanip>
#include <sstream>
using std::stof;
using std::string;
using std::to_string;
using std::vector;
using std::stol;
using std::to_string;
// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

float LinuxParser::MemoryUtilization() {
  int MemTotal{1}, MemFree{0};
  string line, key, value;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);

  if(filestream.is_open()){
    while(std::getline(filestream,line)){
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == kMemTotal) {
          MemTotal = std::stoi(value);
        }
        if (key == kMemFree){
          MemFree = std::stoi(value);
          return ((float)(MemTotal-MemFree))/MemTotal;
        }
      }
    }
  }
  
  return 0.0;

} 

long LinuxParser::UpTime() { 
  long uptime{0};
  string line, uptime_s, idletime_s;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime_s >> idletime_s;
    uptime = std::stold(uptime_s);
  }
  
  return uptime; 
}

long LinuxParser::Jiffies() { 
  
  vector<string> set = LinuxParser::CpuUtilization();
  //std::cout<< set.at(LinuxParser::CPUStates::kGuestNice_);
  set.erase(set.begin());
  return (stol(set.at(LinuxParser::CPUStates::kUser_))
         +stol(set.at(LinuxParser::CPUStates::kNice_))
         +stol(set.at(LinuxParser::CPUStates::kSystem_))
         +stol(set.at(LinuxParser::CPUStates::kIdle_))
         +stol(set.at(LinuxParser::CPUStates::kIOwait_))
         +stol(set.at(LinuxParser::CPUStates::kIRQ_))
         +stol(set.at(LinuxParser::CPUStates::kSoftIRQ_))
         +stol(set.at(LinuxParser::CPUStates::kSteal_)));
  
}

// DONE: Read and return the number of active jiffies for a PID

long LinuxParser::ActiveJiffies(int pid) { 
  vector<string> set = LinuxParser::LineTokenizer(
    to_string(pid),kProcDirectory+to_string(pid)+kStatFilename, ' ');
  
  long active_jiffies = stol(set.at(ProcessStates::utime));
  active_jiffies += stol(set.at(ProcessStates::stime));
  active_jiffies += stol(set.at(ProcessStates::cstime));
  active_jiffies += stol(set.at(ProcessStates::cutime));

  return active_jiffies;
 }


long LinuxParser::ActiveJiffies() { 
  return ( LinuxParser::Jiffies() - LinuxParser::IdleJiffies());
 }

long LinuxParser::IdleJiffies() { 
  vector<string> set = LinuxParser::CpuUtilization();
  return ( +stol(set.at(LinuxParser::CPUStates::kIdle_))
         +stol(set.at(LinuxParser::CPUStates::kIOwait_)));
 }


vector<string> LinuxParser::LineTokenizer(string keyword, string path, char space_) { 
    vector<string> Utilization;
    string line, key, value;
    std::ifstream filestream(path);
    
    if (filestream.is_open()) {
      while (std::getline(filestream, line)) {
        // goes line by line
        std::istringstream linestream(line);
        std::getline(linestream, value,space_);
        // checks if keyword at the head of the line
        if (value == keyword) {
          // loops over the line and skips the keyword
          while (std::getline(linestream, value,space_)) {
            Utilization.push_back(value);
         }
          //exits when it ends
          return Utilization;
        }else{
          while (std::getline(linestream, value,space_)) {
            if(value == keyword){
              std::getline(linestream, value,space_);
              std::getline(linestream, value,space_);
              Utilization.push_back(value);
              return Utilization;
            }
         }
        }
        // else it skips the line for the next line
       
      }
    }
    return Utilization;
  }

vector<string> LinuxParser::CpuUtilization() { 
  return LinuxParser::LineTokenizer(kCPUword, kProcDirectory+kStatFilename, ' ');
}


int LinuxParser::TotalProcesses() { 
  string line, key, value;
  std::ifstream filestream(kProcDirectory+kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          return std::stoi(value);
        }
      }
    }
  }
  return PROCESS_READING_ERROR;
}


int LinuxParser::RunningProcesses() { 
  string line, key, value;
    std::ifstream filestream(kProcDirectory+kStatFilename);
    if (filestream.is_open()) {
      while (std::getline(filestream, line)) {
        std::istringstream linestream(line);
        while (linestream >> key >> value) {
          if (key == "procs_running") {
            return std::stoi(value);
          }
        }
      }
    }
    return PROCESS_READING_ERROR;
}

string LinuxParser::Command(int pid) { 
   string line; 
   std::ifstream filestream(kProcDirectory+to_string(pid)+kCmdlineFilename);
   if (filestream.is_open())  std::getline(filestream, line);
  return line;
 }


string LinuxParser::Ram(int pid) { 
  return LineTokenizer(kVMSize, kProcDirectory+to_string(pid)+kStatusFilename, '\t').at(0); 
  
  }


string LinuxParser::Uid(int pid) { 
  return LineTokenizer(kUID, kProcDirectory+to_string(pid)+kStatusFilename, '\t').at(0);
}

string LinuxParser::User(int pid) { 
  return LineTokenizer(Uid(pid), kPasswordPath, ':').at(0);
}

long LinuxParser::UpTime(int pid) { 

  vector<string> set = LinuxParser::LineTokenizer(to_string(pid),kProcDirectory+to_string(pid)+kStatFilename, ' ');
  long uptime_cycles =  stol(set.at(ProcessStates::uptime));
 
  return uptime_cycles; 
  }

