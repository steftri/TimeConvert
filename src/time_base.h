#ifndef _TIME_BASE_H_
#define _TIME_BASE_H_



class Time
{
protected:
  uint32_t mu32_Sec;
  uint32_t mu32_SubSec;
  
public:
  
  Time(const uint32_t u32_Sec = 0, const uint32_t u32_SubSec = 0);
  
  void set(const uint32_t u32_Sec, const uint32_t u32_SubSec = 0);
  uint32_t get(uint32_t *pu32_Sec = NULL, uint32_t *pu32_SubSec = NULL);
  
  bool operator==(const Time &T2);
  bool operator<=(const Time &T2);
  bool operator<(const Time &T2);
  bool operator>=(const Time &T2);
  bool operator>(const Time &T2);
};



#endif // _TIME_BASE_H_
