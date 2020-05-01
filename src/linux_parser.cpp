#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

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
  string os, version,kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version>>kernel;
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

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {  
float MemTotal , MemFree ;
string line,key,value ;
std::ifstream filestream(kProcDirectory +kMeminfoFilename);
    if(filestream.is_open()){
      while(std::getline(filestream,line)){
          std::istringstream linestream(line);
          linestream >> key >> value ;
          if(key == "MemTotal:")
            MemTotal = stof(value); // in this line we found mem total and we change its value to float using std stof .
          else if (key == "MemFree:")
            MemFree = stof(value);

      }

      }
return (MemTotal-MemFree) / MemTotal ; // using htop method for total used mem 

 }

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { long int upTime ;  
  string line,value;
  std::ifstream filestream(kProcDirectory+kUptimeFilename);
  if(filestream.is_open()){
    std::getline(filestream,line);
    std::istringstream linestream(line);
     

    linestream  >> value ; 
    upTime  = std::stol(value);
    

  }


return upTime ;  }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {  vector<string>data ;
 string key,line,value ; 
  
  std::ifstream filestream(kProcDirectory+kStatFilename);
  if(filestream.is_open()){
    while(std::getline(filestream,line))
    {
      std::istringstream linestream(line);
      linestream >> key  ;
      if(key == "cpu")
        {
          for (int  i = 0; i < 10; i++)
          {
            linestream >> value ;
            data.push_back(value);
          }
          return data ;
        }
    }
  }

return data ; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {   string key,value,line ; 
  int totalProcesses  ;
  std::ifstream filestream(kProcDirectory+kStatFilename);
  if(filestream.is_open()){
    while(std::getline(filestream,line))
    {
      std::istringstream linestream(line);
      linestream >> key >> value ;
      if(key == "processes")
        {
          totalProcesses = std::stoi(value);
          return totalProcesses ;
        }
    }
  }

return totalProcesses ;}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
   string key,value,line ; 
     int totalRunning  ;
  std::ifstream filestream(kProcDirectory+kStatFilename);
  if(filestream.is_open()){
    while(std::getline(filestream,line))
    {
      std::istringstream linestream(line);
      linestream >> key >> value ;
      if(key == "procs_running")
        {
          totalRunning = std::stoi(value);
          return totalRunning ;
        }
    }
  }

return totalRunning ; }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {   
  string command ; 
  std::ifstream filestream(kProcDirectory+to_string(pid)+kCmdlineFilename) ;
  if(filestream.is_open()){
  
  std::getline(filestream,command);
  }

  return command ; }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {   string key, line ;
  int  ram =0 ;
  std::ifstream filestream(kProcDirectory+to_string(pid)+kStatusFilename);
  if(filestream.is_open()){
    while (std::getline(filestream,line))
    {
     std::istringstream linestream(line);
     linestream>>key ; 
     if(key == "VmSize:"){
       linestream>>ram  ; 
       break;
     }
    }
  }
  
  ram /= 1024 ;
  
  return to_string(ram);}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {    string key,value , line ;
  std::ifstream filestream(kProcDirectory+to_string(pid)+kStatusFilename);
  if(filestream.is_open()){
    while (std::getline(filestream,line))
    {
     std::istringstream linestream(line);
     linestream>>key ; 
     if(key == "Uid::"){
       linestream>>value  ; 
       return value;
     }
    }
  }
  return value;}
string LinuxParser::User(int pid) { 
  string Uid ,key,value,line,x ;
  Uid = LinuxParser::Uid(pid);
  std::ifstream filestream(kPasswordPath);
  if(filestream.is_open()){
    while (std::getline(filestream,line))
    {
      std::replace(line.begin(),line.end(),':',' ');
      std::istringstream linestream(line);
      linestream>>value>>x>>key ;
      if(key == Uid){
        return value ;
      }

    }
  }
  return value ;
 }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
  string value ,line ;
  long time ;
  std::ifstream filestream(kProcDirectory+to_string(pid)+kStatFilename);
  if(filestream.is_open()){
      std::getline(filestream,line);
      std::istringstream linestream(line);
      for (int i = 0; i < 22; i++)
      {
        linestream >> value ;
      }
      time = std::stol(value)/sysconf(_SC_CLK_TCK);



  }

  return LinuxParser::UpTime()-time ;
  // return up time for the process which is OS uptime - start time of the process

 }