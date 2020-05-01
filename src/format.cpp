#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    long hours = (seconds/3600);
    long min = (seconds%3600)/60 ;
    long sec = (seconds%3600)%60 ;

    std::string HH,MM,SS ;
    HH = hours <= 9 ? "0"+std::to_string(hours):std::to_string(hours); // this case for adding the leading zero
    MM = min <= 9 ? "0"+std:: to_string(min):std:: to_string(min); // just for formating style 
    SS = sec <= 9 ? "0"+std:: to_string(sec):std:: to_string(sec); 
    return HH+":"+MM+":"+SS ;



 
 }