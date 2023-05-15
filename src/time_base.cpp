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



int16_t TimeBase::_calcLeapSec(void)
{
  return 37;
} 



/*
    TT,   // Terrestrial Time, based on SI second
    TAI,  // Temps Atomique International, messured by atomic clocks; TAI = TT + ~32.184s  
    GPS,  // GPS-Time, GPS = TAI - 19s
    UTC   // Universal Time Coordinated, UTC = TAI - leap seconds */
int64_t TimeBase::get(ETimeStandard e_TimeStandard, int64_t *ps64_Sec, uint32_t *pu32_SubSec)
{
  int16_t  s16_SecDiff = 0;
  int32_t  s32_SubSecDiff = 0;
  int64_t  s64_Sec=ms64_Sec;
  uint32_t u32_SubSec=mu32_SubSec;

  if(e_TimeStandard!=me_TimeStandard)
  {
    switch(me_TimeStandard)
    {
      case TT: s16_SecDiff+=32; s32_SubSecDiff+=(0x100000000LL*184/1000); break; // +32.184s
      case TAI: break;
      case GPS: s16_SecDiff+=19; break; // +19s
      case UTC: s16_SecDiff+=_calcLeapSec(); break;
      default: break;
    }
    switch(e_TimeStandard)
    {
      case TT: s16_SecDiff-=32; s32_SubSecDiff-=(0x100000000LL*184/1000); break; // -32.184s
      case TAI: break;
      case GPS: s16_SecDiff-=19; break; // -19s
      case UTC: s16_SecDiff-=_calcLeapSec(); break;
      default: break;
    }

    s64_Sec = ms64_Sec+s16_SecDiff;
    u32_SubSec = mu32_SubSec+static_cast<uint32_t>(s32_SubSecDiff);
    if(s32_SubSecDiff>0 && (u32_SubSec<mu32_SubSec))  // SubSec overflow
      s64_Sec++;
    if(s32_SubSecDiff<0 && (u32_SubSec>mu32_SubSec))  // Subsec underflow
      s64_Sec--;
  }

  if(ps64_Sec)
    *ps64_Sec = s64_Sec;
  if(pu32_SubSec)
    *pu32_SubSec = u32_SubSec;

  return s64_Sec;  
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


