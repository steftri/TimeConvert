#ifndef _TIME_GREGORIAN_H_
#define _TIME_GREGORIAN_H_

#include <inttypes.h>

#include "time_base.h"



class TimeGregorian : public TimeBase
{
private:
//  static int8_t ms8_UtcLeapSec;
  static uint64_t mu64_EpochOffset;  // default epoch is 1970-01-01 00:00:00 UTC (Unixtime)
  int16_t ms16_TimeZoneInMin;
  
public:
  TimeGregorian(const int16_t s16_TimeZoneInMin = 0);
  TimeGregorian(const ETimeBase e_TimeBase, const int16_t s16_TimeZoneInMin = 0);
  TimeGregorian(const uint16_t u16_Year, const uint8_t u8_Month, const uint8_t u8_Day, const uint8_t u8_Hour = 0, const uint8_t u8_Min = 0, const uint8_t u8_Sec = 0, const int16_t s16_TimeZoneInMin = 0);

  static void time2Gregorian(uint16_t *pu16_Year, uint8_t *pu8_Month, uint8_t *pu8_Day,
                     uint8_t *pu8_Hour, uint8_t *pu8_Min, uint8_t *pu8_Sec, const uint64_t u64_TimeInSec, const int16_t s16_TimeZoneMin = 0);

  static uint64_t gregorian2Time(uint64_t *pu64_TimeInSec,
                     const uint16_t u16_Year, const uint8_t u8_Month, const uint8_t u8_Day,
                     const uint8_t u8_Hour, const uint8_t u8_Min, const uint8_t u8_Sec,
                     const int16_t s16_TimeZoneMin = 0);
  
  static int32_t setEpoch(const uint16_t u16_Year = 1970, const uint8_t u8_Month = 1, const uint8_t u8_Day = 1,
                       const uint8_t u8_Hour = 0, const uint8_t u8_Min = 0, const uint8_t u8_Sec = 0);
 
  static int32_t time2Iso8601(char *pc_Buffer, const uint8_t u8_BufferSize, const uint64_t u64_TimeInSec, const int16_t s16_TimeZoneMin = 0);

  void set(const uint16_t u16_Year, const uint8_t u8_Month, const uint8_t u8_Day,
           const uint8_t u8_Hour, const uint8_t u8_Min, const uint8_t u8_Sec = 0);
  
  void get(uint16_t *pu16_Year, uint8_t *pu8_Month, uint8_t *pu8_Day,
           uint8_t *pu8_Hour, uint8_t *pu8_Min, uint8_t *pu8_Sec = NULL);
  
private:
  static uint64_t _gregorian2UnixTime(uint64_t *pu64_TimeInSec,
                     const uint16_t u16_Year, const uint8_t u8_Month, const uint8_t u8_Day,
                     const uint8_t u8_Hour, const uint8_t u8_Min, const uint8_t u8_Sec,
                     const int16_t s16_TimeZoneMin = 0);
};



#endif // _TIME_GREGORIAN_H_
