#include "time_base.h"



TimeBase::TimeBase(ETimeBase e_TimeBase)
  : me_TimeBase{e_TimeBase}
  , mu64_Sec{0}
  , mu32_SubSec{0}
  , mb_Valid{true}
{
}


void TimeBase::set(const uint64_t u64_Sec, const uint32_t u32_SubSec)
{
  mu64_Sec = u64_Sec;
  mu32_SubSec = u32_SubSec;
  mb_Valid = true;
}



uint64_t TimeBase::get(uint64_t *pu64_Sec, uint32_t *pu32_SubSec)
{
  if(pu64_Sec)
    *pu64_Sec = mu64_Sec;
  if(pu32_SubSec)
    *pu32_SubSec = mu32_SubSec;

  return mu64_Sec;
}



bool TimeBase::isValid(void)
{
  return mb_Valid;
}



void TimeBase::setInvalid(void)
{
  mb_Valid=false;
}  



bool TimeBase::operator==(const TimeBase &T2)
{
  if(  (this->mu64_Sec==T2.mu64_Sec)
     &&(this->mu32_SubSec==T2.mu32_SubSec))
    return true;
  return false;
}



bool TimeBase::operator<=(const TimeBase &T2)
{
  if(this->mu64_Sec<T2.mu64_Sec)
    return true;
  if(this->mu64_Sec==T2.mu64_Sec && this->mu32_SubSec<=T2.mu32_SubSec)
    return true;
  return false;
}



bool TimeBase::operator<(const TimeBase &T2)
{
  if(this->mu64_Sec<T2.mu64_Sec)
    return true;
  if(this->mu64_Sec==T2.mu64_Sec && this->mu32_SubSec<T2.mu32_SubSec)
    return true;
  return false;
}



bool TimeBase::operator>=(const TimeBase &T2)
{
  if(this->mu64_Sec>T2.mu64_Sec)
    return true;
  if(this->mu64_Sec==T2.mu64_Sec && this->mu32_SubSec>=T2.mu32_SubSec)
    return true;
  return false;
}



bool TimeBase::operator>(const TimeBase &T2)
{
  if(this->mu64_Sec>T2.mu64_Sec)
    return true;
  if(this->mu64_Sec==T2.mu64_Sec && this->mu32_SubSec>T2.mu32_SubSec)
    return true;
  return false;
}


