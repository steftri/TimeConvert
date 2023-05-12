#ifndef _TIME_GREGORIAN_H_
#define _TIME_GREGORIAN_H_

#include "time_base.h"



class TimeGregorian : public Time
{
private:
//  static int8_t ms8_UtcLeapSec;
  static uint32_t mu32_EpochOffset;  // default epoch is 1970-01-01 00:00:00 UTC (Unixtime)
  int16_t ms16_TimeZoneInMin;
  
public:
  TimeGregorian(const int16_t s16_TimeZoneInMin = 0);
  
  static void time2Gregorian(uint16_t *pu16_Year, uint8_t *pu8_Month, uint8_t *pu8_Day,
                     uint8_t *pu8_Hour, uint8_t *pu8_Min, uint8_t *pu8_Sec, const uint32_t u32_TimeInSec, const int16_t s16_TimeZoneMin = 0);

  static uint32_t gregorian2Time(uint32_t *pu32_TimeInSec,
                     const uint16_t u16_Year, const uint8_t u8_Month, const uint8_t u8_Day,
                     const uint8_t u8_Hour, const uint8_t u8_Min, const uint8_t u8_Sec,
                     const int16_t s16_TimeZoneMin = 0);
  
  static int32_t setEpoch(const uint16_t u16_Year = 1970, const uint8_t u8_Month = 1, const uint8_t u8_Day = 1,
                       const uint8_t u8_Hour = 0, const uint8_t u8_Min = 0, const uint8_t u8_Sec = 0);
 
  static int32_t time2Iso8601(char *pc_Buffer, const uint8_t u8_BufferSize, const uint32_t u32_TimeInSec, const int16_t s16_TimeZoneMin = 0);

  void set(const uint16_t u16_Year, const uint8_t u8_Month, const uint8_t u8_Day,
           const uint8_t u8_Hour, const uint8_t u8_Min, const uint8_t u8_Sec = 0);
  
  void get(uint16_t *pu16_Year, uint8_t *pu8_Month, uint8_t *pu8_Day,
           uint8_t *pu8_Hour, uint8_t *pu8_Min, uint8_t *pu8_Sec = NULL);
  
private:
  static uint32_t _gregorian2UnixTime(uint32_t *pu32_TimeInSec,
                     const uint16_t u16_Year, const uint8_t u8_Month, const uint8_t u8_Day,
                     const uint8_t u8_Hour, const uint8_t u8_Min, const uint8_t u8_Sec,
                     const int16_t s16_TimeZoneMin = 0);
};



#endif // _TIME_GREGORIAN_H_
