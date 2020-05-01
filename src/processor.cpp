#include "processor.h"
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    long static prevTotal =0;long static prevIdle =0;
    long deltaTotal,deltaIdle , Total,Idle ; 
    float Utilization ; 
    std::vector<std::string> data  = LinuxParser::CpuUtilization() ;
    /** I've used this method "calling CpuUt function" insted of calling jiffies ,activejiff
     * and idle jiff to avoid reading cpu data in multiple time 
     * this method insure to read the cpu method in same time insted of reading the cpu stat file 
     * three time  "time for every stat"
     **/

    Total =  std::stol(data[LinuxParser::CPUStates::kUser_])+std::stol(data[LinuxParser::CPUStates::kNice_])+std::stol(data[LinuxParser::CPUStates::kSystem_])+std::stol(data[LinuxParser::CPUStates::kIRQ_])+std::stol(data[LinuxParser::CPUStates::kSoftIRQ_])+std::stol(data[LinuxParser::CPUStates::kSteal_])+std::stol(data[LinuxParser::CPUStates::kIdle_])+std::stol(data[LinuxParser::CPUStates::kIOwait_]);
    Idle =  std::stol(data[LinuxParser::CPUStates::kIdle_])+std::stol(data[LinuxParser::CPUStates::kIOwait_]);
    deltaIdle = Idle - prevIdle ;
    deltaTotal = Total - prevTotal;
    Utilization = ((float)(deltaTotal-deltaIdle)/(float)deltaTotal);

    prevTotal = Total ;
    prevIdle = Idle ; 
    
    return  Utilization ; 


 }