#ifndef _UTILS_HPP
#define _UTILS_HPP


#define DEBUG_BUILD



#ifdef DEBUG_BUILD
    #define DEBUG(x) Serial.println(x)
#else
    #define DEBUG(x) void(x)
#endif


#endif