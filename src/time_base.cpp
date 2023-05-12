#ifdef AVR
#include <Arduino.h>
#else
#include <cstdint>
#include <cstring>
#endif

#include "time_base.h"



Time::Time(const uint32_t u32_Sec, const uint32_t u32_SubSec)
{
  mu32_Sec = u32_Sec;
  mu32_SubSec = u32_SubSec;
}



void Time::set(const uint32_t u32_Sec, const uint32_t u32_SubSec)
{
  mu32_Sec = u32_Sec;
  mu32_SubSec = u32_SubSec;
}



uint32_t Time::get(uint32_t *pu32_Sec, uint32_t *pu32_SubSec)
{
  if(pu32_Sec)
    *pu32_Sec = mu32_Sec;
  if(pu32_SubSec)
    *pu32_SubSec = mu32_SubSec;

  return mu32_Sec;
}



bool Time::operator==(const Time &T2)
{
  if(  (this->mu32_Sec==T2.mu32_Sec)
     &&(this->mu32_SubSec==T2.mu32_SubSec))
    return true;
  return false;
}



bool Time::operator<=(const Time &T2)
{
  if(this->mu32_Sec<T2.mu32_Sec)
    return true;
  if(this->mu32_Sec==T2.mu32_Sec && this->mu32_SubSec<=T2.mu32_SubSec)
    return true;
  return false;
}



bool Time::operator<(const Time &T2)
{
  if(this->mu32_Sec<T2.mu32_Sec)
    return true;
  if(this->mu32_Sec==T2.mu32_Sec && this->mu32_SubSec<T2.mu32_SubSec)
    return true;
  return false;
}



bool Time::operator>=(const Time &T2)
{
  if(this->mu32_Sec>T2.mu32_Sec)
    return true;
  if(this->mu32_Sec==T2.mu32_Sec && this->mu32_SubSec>=T2.mu32_SubSec)
    return true;
  return false;
}



bool Time::operator>(const Time &T2)
{
  if(this->mu32_Sec>T2.mu32_Sec)
    return true;
  if(this->mu32_Sec==T2.mu32_Sec && this->mu32_SubSec>T2.mu32_SubSec)
    return true;
  return false;
}


