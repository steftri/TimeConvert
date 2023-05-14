#include "time_base.h"



Time::Time(const uint64_t u64_Sec, const uint32_t u32_SubSec)
  : me_TimeBase{TAI}
  , mu64_Sec{u64_Sec}
  , mu32_SubSec{u32_SubSec}
  , mb_Valid{true}
{
}


Time::Time(ETimeBase e_TimeBase, const uint64_t u64_Sec, const uint32_t u32_SubSec)
  : me_TimeBase{e_TimeBase}
  , mu64_Sec{u64_Sec}
  , mu32_SubSec{u32_SubSec}
  , mb_Valid{true}
{
}


void Time::set(const uint64_t u64_Sec, const uint32_t u32_SubSec)
{
  mu64_Sec = u64_Sec;
  mu32_SubSec = u32_SubSec;
  mb_Valid = true;
}



uint64_t Time::get(uint64_t *pu64_Sec, uint32_t *pu32_SubSec)
{
  if(pu64_Sec)
    *pu64_Sec = mu64_Sec;
  if(pu32_SubSec)
    *pu32_SubSec = mu32_SubSec;

  return mu64_Sec;
}



bool Time::isValid(void)
{
  return mb_Valid;
}



void Time::setInvalid(void)
{
  mb_Valid=false;
}  



bool Time::operator==(const Time &T2)
{
  if(  (this->mu64_Sec==T2.mu64_Sec)
     &&(this->mu32_SubSec==T2.mu32_SubSec))
    return true;
  return false;
}



bool Time::operator<=(const Time &T2)
{
  if(this->mu64_Sec<T2.mu64_Sec)
    return true;
  if(this->mu64_Sec==T2.mu64_Sec && this->mu32_SubSec<=T2.mu32_SubSec)
    return true;
  return false;
}



bool Time::operator<(const Time &T2)
{
  if(this->mu64_Sec<T2.mu64_Sec)
    return true;
  if(this->mu64_Sec==T2.mu64_Sec && this->mu32_SubSec<T2.mu32_SubSec)
    return true;
  return false;
}



bool Time::operator>=(const Time &T2)
{
  if(this->mu64_Sec>T2.mu64_Sec)
    return true;
  if(this->mu64_Sec==T2.mu64_Sec && this->mu32_SubSec>=T2.mu32_SubSec)
    return true;
  return false;
}



bool Time::operator>(const Time &T2)
{
  if(this->mu64_Sec>T2.mu64_Sec)
    return true;
  if(this->mu64_Sec==T2.mu64_Sec && this->mu32_SubSec>T2.mu32_SubSec)
    return true;
  return false;
}


