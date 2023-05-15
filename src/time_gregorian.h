#ifndef _TIME_GREGORIAN_H_
#define _TIME_GREGORIAN_H_

#include <inttypes.h>

#include "time_base.h"



class TimeGregorian : public TimeBase
{
private:
//  static int8_t ms8_UtcLeapSec;
  int16_t ms16_TimeZoneInMin;
  
public:
  TimeGregorian(const int16_t s16_TimeZoneInMin = 0);
  TimeGregorian(const ETimeStandard e_TimeStandard, const int16_t s16_TimeZoneInMin = 0);
  TimeGregorian(const uint16_t u16_Year, const uint8_t u8_Month, const uint8_t u8_Day, const uint8_t u8_Hour = 0, const uint8_t u8_Min = 0, const uint8_t u8_Sec = 0, const int16_t s16_TimeZoneInMin = 0);

  static void time2Gregorian(uint16_t *pu16_Year, uint8_t *pu8_Month, uint8_t *pu8_Day,
                     uint8_t *pu8_Hour, uint8_t *pu8_Min, uint8_t *pu8_Sec, const int64_t s64_TimeInSec, const int16_t s16_TimeZoneMin = 0);

  static int64_t gregorian2Time(int64_t *ps64_TimeInSec,
                     const uint16_t u16_Year, const uint8_t u8_Month, const uint8_t u8_Day,
                     const uint8_t u8_Hour, const uint8_t u8_Min, const uint8_t u8_Sec,
                     const int16_t s16_TimeZoneMin = 0);
 
  static int32_t time2Iso8601(char *pc_Buffer, const uint8_t u8_BufferSize, const uint64_t u64_TimeInSec, const int16_t s16_TimeZoneMin = 0);

  void set(const uint16_t u16_Year, const uint8_t u8_Month, const uint8_t u8_Day,
           const uint8_t u8_Hour = 0, const uint8_t u8_Min = 0, const uint8_t u8_Sec = 0);
  
  void get(uint16_t *pu16_Year, uint8_t *pu8_Month, uint8_t *pu8_Day,
           uint8_t *pu8_Hour = nullptr, uint8_t *pu8_Min = nullptr, uint8_t *pu8_Sec = nullptr);
};



#endif // _TIME_GREGORIAN_H_
