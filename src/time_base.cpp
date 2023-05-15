#include "time_base.h"



TimeBase::TimeBase(TimeBase *p_Time)
{
  if(p_Time)
  {
    me_TimeStandard = p_Time->me_TimeStandard;
    ms64_Sec = p_Time->ms64_Sec;
    mu32_SubSec = p_Time->mu32_SubSec;
    mb_Valid = p_Time->mb_Valid;    
  } 
}


TimeBase::TimeBase(ETimeStandard e_TimeStandard, const int64_t s64_Sec, const uint32_t u32_SubSec)
  : me_TimeStandard{e_TimeStandard}
  , ms64_Sec{s64_Sec}
  , mu32_SubSec{u32_SubSec}
  , mb_Valid{true}
{
}



void TimeBase::set(TimeBase *p_Time)
{
  me_TimeStandard = p_Time->me_TimeStandard;
  ms64_Sec = p_Time->ms64_Sec;
  mu32_SubSec = p_Time->mu32_SubSec;
  mb_Valid = p_Time->mb_Valid;
}



void TimeBase::set(const int64_t s64_Sec, const uint32_t u32_SubSec)
{
  ms64_Sec = s64_Sec;
  mu32_SubSec = u32_SubSec;
  mb_Valid = true;
}



int64_t TimeBase::get(int64_t *ps64_Sec, uint32_t *pu32_SubSec)
{
  if(ps64_Sec)
    *ps64_Sec = ms64_Sec;
  if(pu32_SubSec)
    *pu32_SubSec = mu32_SubSec;

  return ms64_Sec;
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
  if(  (this->ms64_Sec==T2.ms64_Sec)
     &&(this->mu32_SubSec==T2.mu32_SubSec))
    return true;
  return false;
}



bool TimeBase::operator<=(const TimeBase &T2)
{
  if(this->ms64_Sec<T2.ms64_Sec)
    return true;
  if(this->ms64_Sec==T2.ms64_Sec && this->mu32_SubSec<=T2.mu32_SubSec)
    return true;
  return false;
}



bool TimeBase::operator<(const TimeBase &T2)
{
  if(this->ms64_Sec<T2.ms64_Sec)
    return true;
  if(this->ms64_Sec==T2.ms64_Sec && this->mu32_SubSec<T2.mu32_SubSec)
    return true;
  return false;
}



bool TimeBase::operator>=(const TimeBase &T2)
{
  if(this->ms64_Sec>T2.ms64_Sec)
    return true;
  if(this->ms64_Sec==T2.ms64_Sec && this->mu32_SubSec>=T2.mu32_SubSec)
    return true;
  return false;
}



bool TimeBase::operator>(const TimeBase &T2)
{
  if(this->ms64_Sec>T2.ms64_Sec)
    return true;
  if(this->ms64_Sec==T2.ms64_Sec && this->mu32_SubSec>T2.mu32_SubSec)
    return true;
  return false;
}


