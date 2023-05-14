#ifndef _TIME_BASE_H_
#define _TIME_BASE_H_

#include <inttypes.h>

class TimeBase
{
public:
  typedef enum 
  {
    TT,   // Terrestrial Time, based on SI second
    TAI,  // Temps Atomique International, messured by atomic clocks; TAI = TT + ~32.184s  
    GPS,  // GPS-Time, UCT = TAI - 19s
    UTC   // Universal Time Coordinated, UTC = TAI - leap seconds     
  } ETimeBase;

protected:
  ETimeBase me_TimeBase;
  uint64_t  mu64_Sec;
  uint32_t  mu32_SubSec;
  bool      mb_Valid;
  
public:
  TimeBase(ETimeBase e_TimeBase = TAI);
  
  void set(const uint64_t u64_Sec, const uint32_t u32_SubSec = 0);
  uint64_t get(uint64_t *pu64_Sec = nullptr, uint32_t *pu32_SubSec = nullptr);

  bool isValid(void);
  void setInvalid(void);    
  
  bool operator==(const TimeBase &T2);
  bool operator<=(const TimeBase &T2);
  bool operator<(const TimeBase &T2);
  bool operator>=(const TimeBase &T2);
  bool operator>(const TimeBase &T2);
};



#endif // _TIME_BASE_H_
