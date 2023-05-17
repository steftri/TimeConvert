#ifndef _TIME_BASE_H_
#define _TIME_BASE_H_

#include <inttypes.h>


#define MAX_LEAP_SECONDS   64

class TimeLeapSec   // singleton
{
  struct 
  {
    uint32_t u32_Time;
    int8_t   s8_Diff;
  } ma_LeapSeconds[MAX_LEAP_SECONDS];
  uint8_t mu8_NumberOfEntries;

public: 
  static TimeLeapSec *getObject(void);

  void clear(void);
  int32_t addEntry(const uint32_t u32_Time, const int8_t s8_Diff);
  int32_t calcLeapSecondsTAI(int64_t s64_Sec);
  int32_t calcLeapSecondsUTC(int64_t s64_Sec);

private:
  TimeLeapSec(void);
};





class TimeBase
{
public:
  typedef enum 
  {
    TT,   // Terrestrial Time, based on SI second
    TAI,  // Temps Atomique International, messured by atomic clocks; TAI = TT + ~32.184s  
    GPS,  // GPS-Time, UCT = TAI - 19s
    UTC   // Universal Time Coordinated, UTC = TAI - leap seconds     
  } ETimeStandard;

protected:
  ETimeStandard me_TimeStandard;
  int64_t   ms64_Sec;
  uint32_t  mu32_SubSec;
  bool      mb_Valid;
  
public:
  TimeBase(TimeBase *p_Time);
  TimeBase(ETimeStandard e_TimeStandard = TAI, const int64_t s64_Sec = 0, const uint32_t u32_SubSec = 0);

  void clearAllLeapSecs(void);
  int32_t addLeapSec(const uint32_t u32_UtcSecSince1970, const int8_t s8_Diff);
  
  void set(TimeBase *p_Time);
  void set(const int64_t s64_Sec, const uint32_t u32_SubSec = 0);
  int64_t get(int64_t *ps64_Sec = nullptr, uint32_t *pu32_SubSec = nullptr);
  int64_t get(ETimeStandard e_TimeStandard, int64_t *ps64_Sec = nullptr, uint32_t *pu32_SubSec = nullptr);

  bool isValid(void);
  void setInvalid(void);    
  
  bool operator==(TimeBase &T2);
  bool operator<=(TimeBase &T2);
  bool operator<(TimeBase &T2);
  bool operator>=(TimeBase &T2);
  bool operator>(TimeBase &T2);
};



#endif // _TIME_BASE_H_
