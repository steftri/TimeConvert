#include <stdio.h>
#include <ctype.h>

#include "time_gregorian.h"


#define MAX_ISO8601_STR_LENGTH 30   // 9999999-12-31T12:00:22.000000



TimeGregorian::TimeGregorian(const int16_t s16_TimeZoneInMin) 
 : TimeBase(UTC)
 , ms16_TimeZoneInMin{s16_TimeZoneInMin}
{
}



TimeGregorian::TimeGregorian(const TimeBase *p_Time, const int16_t s16_TimeZoneInMin)
 : TimeBase(p_Time)
 , ms16_TimeZoneInMin{s16_TimeZoneInMin} 
{
}



TimeGregorian::TimeGregorian(const ETimeStandard e_TimeStandard, const int16_t s16_TimeZoneInMin) 
 : TimeBase(e_TimeStandard)
 , ms16_TimeZoneInMin{s16_TimeZoneInMin}
{
}



TimeGregorian::TimeGregorian(const uint16_t u16_Year, const uint8_t u8_Month, const uint8_t u8_Day, const uint8_t u8_Hour, const uint8_t u8_Min, const uint8_t u8_Sec, const int16_t s16_TimeZoneInMin)
  : TimeBase(UTC)
  , ms16_TimeZoneInMin{s16_TimeZoneInMin}
{
  set(u16_Year, u8_Month, u8_Day, u8_Hour, u8_Min, u8_Sec);
}    



TimeGregorian::TimeGregorian(const char *pc_Iso8601String)
  : TimeBase(UTC)
  , ms16_TimeZoneInMin{0}
{
  set(pc_Iso8601String);
}




void TimeGregorian::time2Gregorian(int32_t *ps32_Year, uint8_t *pu8_Month, uint8_t *pu8_Day,
      uint8_t *pu8_Hour, uint8_t *pu8_Min, uint8_t *pu8_Sec, const int64_t s64_TimeInSec, const int16_t s16_TimeZoneMin)
{
  
  const uint32_t SEC_PER_DAY        =  86400ul; /*  24* 60 * 60 */
  const uint32_t DAYS_PER_YEAR      =    365ul; /* kein Schaltjahr */
  const uint32_t DAYS_PER_4_YEARS   =   1461ul; /*   4*365 +   1 */
  const uint32_t DAYS_PER_100_YEARS =  36524ul; /* 100*365 +  25 - 1 */
  const uint32_t DAYS_PER_400_YEARS = 146097ul; /* 400*365 + 100 - 4 + 1 */
  const uint32_t DAY_AD_1970_01_01  = 719468ul; /* Tagnummer bezogen auf den 1. Maerz des Jahres "Null" */

  uint32_t u32_DaysAD;
  uint32_t u32_SecOfDay;
  uint32_t u32_Temp;
  
  int32_t s32_Year;
  uint8_t u8_Month;
  uint8_t u8_Day;

  u32_DaysAD = DAY_AD_1970_01_01 + (s64_TimeInSec+s16_TimeZoneMin*60LL)/ SEC_PER_DAY;
  u32_SecOfDay = (s64_TimeInSec+s16_TimeZoneMin*60LL) % SEC_PER_DAY;
  
  /* Schaltjahrregel des Gregorianischen Kalenders: jedes durch 100 teilbare Jahr ist kein Schaltjahr, es sei denn, es ist durch 400 teilbar. */
  u32_Temp = 4 * (u32_DaysAD + DAYS_PER_100_YEARS + 1) / DAYS_PER_400_YEARS - 1;
  s32_Year = 100 * u32_Temp;
  u32_DaysAD -= DAYS_PER_100_YEARS * u32_Temp + u32_Temp / 4;
  
  /* Schaltjahrregel des Julianischen Kalenders:
  Jedes durch 4 teilbare Jahr ist ein Schaltjahr. */
  u32_Temp = 4 * (u32_DaysAD + DAYS_PER_YEAR + 1) / DAYS_PER_4_YEARS - 1;
  s32_Year += u32_Temp;
  u32_DaysAD -= DAYS_PER_YEAR * u32_Temp + u32_Temp / 4;

  /* u32_DaysAD enthaelt jetzt nur noch die Tage des errechneten Jahres bezogen auf den 1. Maerz. */
  u8_Month = (5 * u32_DaysAD + 2) / 153;
  u8_Day = u32_DaysAD - (u8_Month * 153 + 2) / 5 + 1;
  /*  153 = 31+30+31+30+31 Tage fuer die 5 Monate von Maerz bis Juli
      153 = 31+30+31+30+31 Tage fuer die 5 Monate von August bis Dezember
            31+28          Tage fuer Januar und Februar (siehe unten)
      +2: Justierung der Rundung
      +1: Der erste Tag im Monat ist 1 (und nicht 0).
  */

  u8_Month += 3; /* vom Jahr, das am 1. Maerz beginnt auf unser normales Jahr umrechnen: */
  if(u8_Month > 12)
  {  /* Monate 13 und 14 entsprechen 1 (Januar) und 2 (Februar) des naechsten Jahres */
     u8_Month -= 12;
     s32_Year++;
  }

  if(ps32_Year)
    *ps32_Year = s32_Year;
  
  if(pu8_Month)
    *pu8_Month = u8_Month;
  
  if(pu8_Day)
    *pu8_Day = u8_Day;
  
  if(pu8_Hour)
    *pu8_Hour = u32_SecOfDay / 3600;
  
  if(pu8_Min)
    *pu8_Min = u32_SecOfDay % 3600 / 60;
  
  if(pu8_Sec)
    *pu8_Sec = u32_SecOfDay % 60;
}



  
int32_t TimeGregorian::gregorian2Time(int64_t *ps64_TimeInSec,
                                const int32_t s32_Year, const uint8_t u8_Month, const uint8_t u8_Day,
                                const uint8_t u8_Hour, const uint8_t u8_Min, const uint8_t u8_Sec,
                                const int16_t s16_TimeZoneMin)
{
  int64_t s64_TimeInSec;
  const uint16_t u16_DayOfYear[12] = /* Anzahl der Tage seit Jahresanfang ohne Tage des aktuellen Monats und ohne Schalttag */
    {0,31,59,90,120,151,181,212,243,273,304,334};
  uint16_t u16_LeapYears;
  int32_t s32_DaysSince1970;

  if(s32_Year<0 || s32_Year>9999 || u8_Month==0 || u8_Month>12 || u8_Day==0 || u8_Day>31 || u8_Hour>24 || u8_Min>60 || u8_Sec>70)
    return -1;

  /* for algorithm, see https://de.wikipedia.org/wiki/Unixzeit */
  
  u16_LeapYears = ((s32_Year-1)-1968)/4    /* Anzahl der Schaltjahre seit 1970 (ohne das evtl. laufende Schaltjahr) */
                - ((s32_Year-1)-1900)/100
                + ((s32_Year-1)-1600)/400;

  s32_DaysSince1970 = (s32_Year-1970)*365L + u16_LeapYears
                    + u16_DayOfYear[u8_Month-1] + u8_Day-1;

  if( (u8_Month>2) && (s32_Year%4==0 && (s32_Year%100!=0 || s32_Year%400==0)) )
    s32_DaysSince1970 += 1; /* +Schalttag, wenn jahr Schaltjahr ist */
  
  s64_TimeInSec = (u8_Sec + 60 * ( u8_Min + 60 * (u8_Hour + 24*static_cast<int64_t>(s32_DaysSince1970)) - s16_TimeZoneMin ) );
  
  if(ps64_TimeInSec)
    *ps64_TimeInSec = s64_TimeInSec;

  return 0;
}




int32_t TimeGregorian::time2Iso8601(char *pc_Buffer, const uint8_t u8_BufferSize, const uint64_t u64_TimeInSec, const int16_t s16_TimeZoneMin)
{
  int32_t s32_Year;
  uint8_t u8_Month, u8_Day;
  uint8_t u8_Hour, u8_Min, u8_Sec;
  
  if((NULL==pc_Buffer) || (0==u8_BufferSize))
    return -1;
  
  time2Gregorian(&s32_Year, &u8_Month, &u8_Day, &u8_Hour, &u8_Min, &u8_Sec, u64_TimeInSec, s16_TimeZoneMin);

  if(s32_Year<0)
    s32_Year=0;
  if(s32_Year>9999)
    s32_Year=9999;

  if(u8_BufferSize>=20)
    sprintf(pc_Buffer, "%04d-%02d-%02dT%02d:%02d:%02d", static_cast<uint16_t>(s32_Year), u8_Month, u8_Day, u8_Hour, u8_Min, u8_Sec);
  else if(u8_BufferSize>=11)
    sprintf(pc_Buffer, "%04d-%02d-%02d", static_cast<uint16_t>(s32_Year), u8_Month, u8_Day);
  else
    return -1;
  
  return 0;
}



int32_t TimeGregorian::set(const uint16_t u16_Year, const uint8_t u8_Month, const uint8_t u8_Day,
         const uint8_t u8_Hour, const uint8_t u8_Min, const uint8_t u8_Sec)
{
  int64_t s64_TimeInSec = 0;
  int32_t rc=0;

  if(0==(rc=gregorian2Time(&s64_TimeInSec, u16_Year, u8_Month, u8_Day, u8_Hour, u8_Min, u8_Sec, ms16_TimeZoneInMin)))
    TimeBase::set(s64_TimeInSec);

  return rc;
}



int32_t TimeGregorian::set(const char *pc_Iso8601String)
{
  int32_t s32_Year = 0;
  bool b_Negative = false;
  uint8_t u8_Month = 0, u8_Day = 0, u8_Hour = 0, u8_Min = 0, u8_Sec = 0;
  uint8_t u8_StringPtr = 0; 

  while(u8_StringPtr<MAX_ISO8601_STR_LENGTH && pc_Iso8601String[u8_StringPtr] && isspace(pc_Iso8601String[u8_StringPtr]))
    u8_StringPtr++;
  if(pc_Iso8601String[u8_StringPtr] == '-')
  {
    b_Negative=true;
    u8_StringPtr++;
  }
  // YYYY-MM-DD
  while(u8_StringPtr<MAX_ISO8601_STR_LENGTH && pc_Iso8601String[u8_StringPtr] && isdigit(pc_Iso8601String[u8_StringPtr]))
    s32_Year = s32_Year*10+(pc_Iso8601String[u8_StringPtr++]-'0');
  if(b_Negative)
    s32_Year = -s32_Year;
  if(pc_Iso8601String[u8_StringPtr++]!='-')
    return -1;
  while(u8_StringPtr<MAX_ISO8601_STR_LENGTH && pc_Iso8601String[u8_StringPtr] && isdigit(pc_Iso8601String[u8_StringPtr]))
    u8_Month = u8_Month*10+(pc_Iso8601String[u8_StringPtr++]-'0');
  if(pc_Iso8601String[u8_StringPtr++]!='-')
    return -1;
  while(u8_StringPtr<MAX_ISO8601_STR_LENGTH && pc_Iso8601String[u8_StringPtr] && isdigit(pc_Iso8601String[u8_StringPtr]))
    u8_Day = u8_Day*10+(pc_Iso8601String[u8_StringPtr++]-'0');    

  if(pc_Iso8601String[u8_StringPtr]=='T' || isspace(pc_Iso8601String[u8_StringPtr]))
  {
    // HH:MM[:SS]
    u8_StringPtr++;
    while(u8_StringPtr<MAX_ISO8601_STR_LENGTH && pc_Iso8601String[u8_StringPtr] && isdigit(pc_Iso8601String[u8_StringPtr]))
      u8_Hour = u8_Hour*10+(pc_Iso8601String[u8_StringPtr++]-'0'); 
    if(pc_Iso8601String[u8_StringPtr++]!=':')
      return -1;
    while(u8_StringPtr<MAX_ISO8601_STR_LENGTH && pc_Iso8601String[u8_StringPtr] && isdigit(pc_Iso8601String[u8_StringPtr]))
      u8_Min = u8_Min*10+(pc_Iso8601String[u8_StringPtr++]-'0');    
    if(pc_Iso8601String[u8_StringPtr++]==':')
    {
      while(u8_StringPtr<MAX_ISO8601_STR_LENGTH && pc_Iso8601String[u8_StringPtr] && isdigit(pc_Iso8601String[u8_StringPtr]))
        u8_Sec = u8_Sec*10+(pc_Iso8601String[u8_StringPtr++]-'0'); 
    }
  }
  return set(s32_Year, u8_Month, u8_Day, u8_Hour, u8_Min, u8_Sec);
}




void TimeGregorian::get(int32_t *ps32_Year, uint8_t *pu8_Month, uint8_t *pu8_Day,
         uint8_t *pu8_Hour, uint8_t *pu8_Min, uint8_t *pu8_Sec)
{
  time2Gregorian(ps32_Year, pu8_Month, pu8_Day, pu8_Hour, pu8_Min, pu8_Sec, TimeBase::get(), ms16_TimeZoneInMin);
}


void TimeGregorian::get(ETimeStandard e_TimeStandard, int32_t *ps32_Year, uint8_t *pu8_Month, uint8_t *pu8_Day,
         uint8_t *pu8_Hour, uint8_t *pu8_Min, uint8_t *pu8_Sec)
{
  time2Gregorian(ps32_Year, pu8_Month, pu8_Day, pu8_Hour, pu8_Min, pu8_Sec, TimeBase::get(e_TimeStandard), ms16_TimeZoneInMin);
}



void TimeGregorian::get(char *pc_Buffer, const uint8_t u8_BufferSize)
{
  time2Iso8601(pc_Buffer, u8_BufferSize, TimeBase::get(), ms16_TimeZoneInMin);
}


void TimeGregorian::get(ETimeStandard e_TimeStandard, char *pc_Buffer, const uint8_t u8_BufferSize)
{
  time2Iso8601(pc_Buffer, u8_BufferSize, TimeBase::get(e_TimeStandard), ms16_TimeZoneInMin);
} 
