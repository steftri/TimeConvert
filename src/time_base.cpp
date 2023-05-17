#include "time_base.h"

#define TIME_DIFF_1900_1970   2208988800UL



// leap seconds list is from https://www.ietf.org/timezones/data/leap-seconds.list

TimeLeapSec::TimeLeapSec(void)
 : ma_LeapSeconds{
    {2272060800UL-TIME_DIFF_1900_1970, 10}, //  # 1 Jan 1972 UTC
    {2287785600UL-TIME_DIFF_1900_1970, 11}, //	# 1 Jul 1972 UTC
    {2303683200UL-TIME_DIFF_1900_1970, 12}, //	# 1 Jan 1973 UTC
    {2335219200UL-TIME_DIFF_1900_1970, 13}, //	# 1 Jan 1974 UTC
    {2366755200UL-TIME_DIFF_1900_1970, 14}, //	# 1 Jan 1975 UTC
    {2398291200UL-TIME_DIFF_1900_1970, 15}, //	# 1 Jan 1976 UTC
    {2429913600UL-TIME_DIFF_1900_1970, 16}, //	# 1 Jan 1977 UTC
    {2461449600UL-TIME_DIFF_1900_1970, 17}, //	# 1 Jan 1978 UTC
    {2492985600UL-TIME_DIFF_1900_1970, 18}, //	# 1 Jan 1979 UTC
    {2524521600UL-TIME_DIFF_1900_1970, 19}, //	# 1 Jan 1980 UTC
    {2571782400UL-TIME_DIFF_1900_1970, 20}, //	# 1 Jul 1981 UTC
    {2603318400UL-TIME_DIFF_1900_1970, 21}, //	# 1 Jul 1982 UTC
    {2634854400UL-TIME_DIFF_1900_1970, 22}, //	# 1 Jul 1983 UTC
    {2698012800UL-TIME_DIFF_1900_1970, 23}, //	# 1 Jul 1985 UTC
    {2776982400UL-TIME_DIFF_1900_1970, 24}, //	# 1 Jan 1988 UTC
    {2840140800UL-TIME_DIFF_1900_1970, 25}, //	# 1 Jan 1990 UTC
    {2871676800UL-TIME_DIFF_1900_1970, 26}, //	# 1 Jan 1991 UTC
    {2918937600UL-TIME_DIFF_1900_1970, 27}, //	# 1 Jul 1992 UTC
    {2950473600UL-TIME_DIFF_1900_1970, 28}, //	# 1 Jul 1993 UTC
    {2982009600UL-TIME_DIFF_1900_1970, 29}, //	# 1 Jul 1994 UTC
    {3029443200UL-TIME_DIFF_1900_1970, 30}, //	# 1 Jan 1996 UTC
    {3076704000UL-TIME_DIFF_1900_1970, 31}, //	# 1 Jul 1997 UTC
    {3124137600UL-TIME_DIFF_1900_1970, 32}, //	# 1 Jan 1999 UTC
    {3345062400UL-TIME_DIFF_1900_1970, 33}, //	# 1 Jan 2006 UTC
    {3439756800UL-TIME_DIFF_1900_1970, 34}, //	# 1 Jan 2009 UTC
    {3550089600UL-TIME_DIFF_1900_1970, 35}, //	# 1 Jul 2012 UTC
    {3644697600UL-TIME_DIFF_1900_1970, 36}, //	# 1 Jul 2015 UTC
    {3692217600UL-TIME_DIFF_1900_1970, 37}, //	# 1 Jan 2017 UTC
    }
 , mu8_NumberOfEntries{28}    
{
}


TimeLeapSec *TimeLeapSec::get(void) 
{
  static TimeLeapSec myTimeLeapSecSingleton; 
  return &myTimeLeapSecSingleton; 
}



void TimeLeapSec::clear(void)
{
  mu8_NumberOfEntries = 0;
}


int32_t TimeLeapSec::addEntry(const uint32_t u32_Time, const int8_t s8_Diff)
{
  if(mu8_NumberOfEntries>=MAX_LEAP_SECONDS)
    return -1;

  if(mu8_NumberOfEntries>0 && (ma_LeapSeconds[mu8_NumberOfEntries].u32_Time>=u32_Time))
    return -1;  // new time is smaller than already inserted timestamp, but timestamps must be chronological

  ma_LeapSeconds[mu8_NumberOfEntries].u32_Time=u32_Time;
  ma_LeapSeconds[mu8_NumberOfEntries].s8_Diff=s8_Diff;
  mu8_NumberOfEntries++;

  return 0;
}



int32_t TimeLeapSec::calcLeapSecondsTAI(int64_t s64_Sec)
{
  int32_t s32_Diff = 0;

  for(uint8_t i=0; i<mu8_NumberOfEntries; i++)
  {
    if(static_cast<int64_t>(static_cast<uint64_t>(ma_LeapSeconds[i].u32_Time))+s32_Diff>s64_Sec)   // this leap second is not reached
      break;
    s32_Diff=ma_LeapSeconds[i].s8_Diff;  
  }

  return s32_Diff;
}



int32_t TimeLeapSec::calcLeapSecondsUTC(int64_t s64_Sec)
{
  int32_t s32_Diff = 0;

  for(uint8_t i=0; i<mu8_NumberOfEntries; i++)
  {
    if(static_cast<int64_t>(static_cast<uint64_t>(ma_LeapSeconds[i].u32_Time))>s64_Sec)   // this leap second is not reached
      break;
    s32_Diff=ma_LeapSeconds[i].s8_Diff;  
  }

  return s32_Diff;
}




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



void TimeBase::clearAllLeapSecs(void)
{
  TimeLeapSec::get()->clear();
}



int32_t TimeBase::addLeapSec(const uint32_t u32_UtcSecSince1970, const int8_t s8_Diff)
{
  return TimeLeapSec::get()->addEntry(u32_UtcSecSince1970, s8_Diff);
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
      case UTC: s16_SecDiff+=TimeLeapSec::get()->calcLeapSecondsUTC(ms64_Sec); break;
      default: break;
    }
    switch(e_TimeStandard)
    {
      case TT: s16_SecDiff-=32; s32_SubSecDiff-=(0x100000000LL*184/1000); break; // -32.184s
      case TAI: break;
      case GPS: s16_SecDiff-=19; break; // -19s
      case UTC: s16_SecDiff-=TimeLeapSec::get()->calcLeapSecondsTAI(ms64_Sec); break;
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



bool TimeBase::operator==(TimeBase &T2)
{
  int64_t  s64_Sec;
  uint32_t u32_SubSec;

  T2.get(me_TimeStandard, &s64_Sec, &u32_SubSec);

  if((ms64_Sec==s64_Sec) && (mu32_SubSec==u32_SubSec))
    return true;

  return false;
}



bool TimeBase::operator<=(TimeBase &T2)
{
  int64_t  s64_Sec;
  uint32_t u32_SubSec;

  T2.get(me_TimeStandard, &s64_Sec, &u32_SubSec);

  if(ms64_Sec<s64_Sec)
    return true;
  if(ms64_Sec==s64_Sec && mu32_SubSec<=u32_SubSec)
    return true;
  return false;
}



bool TimeBase::operator<(TimeBase &T2)
{
  int64_t  s64_Sec;
  uint32_t u32_SubSec;

  T2.get(me_TimeStandard, &s64_Sec, &u32_SubSec);  

  if(ms64_Sec<s64_Sec)
    return true;
  if(ms64_Sec==s64_Sec && mu32_SubSec<u32_SubSec)
    return true;
  return false;
}



bool TimeBase::operator>=(TimeBase &T2)
{
  int64_t  s64_Sec;
  uint32_t u32_SubSec;

  T2.get(me_TimeStandard, &s64_Sec, &u32_SubSec);

  if(ms64_Sec>s64_Sec)
    return true;
  if(ms64_Sec==s64_Sec && mu32_SubSec>=u32_SubSec)
    return true;
  return false;
}



bool TimeBase::operator>(TimeBase &T2)
{
  int64_t  s64_Sec;
  uint32_t u32_SubSec;

  T2.get(me_TimeStandard, &s64_Sec, &u32_SubSec);

  if(ms64_Sec>s64_Sec)
    return true;
  if(ms64_Sec==s64_Sec && mu32_SubSec>u32_SubSec)
    return true;

  return false;
}


