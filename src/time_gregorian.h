#ifndef _TIME_GREGORIAN_H_
#define _TIME_GREGORIAN_H_

#include <inttypes.h>

#include "time_base.h"



class TimeGregorian : public TimeBase
{
private:
  int16_t ms16_TimeZoneInMin;
  
public:
  TimeGregorian(const int16_t s16_TimeZoneInMin = 0);
  TimeGregorian(const TimeBase *p_Time, const int16_t s16_TimeZoneInMin = 0);
  TimeGregorian(const ETimeStandard e_TimeStandard, const int16_t s16_TimeZoneInMin = 0);

  TimeGregorian(const uint16_t u16_Year, const uint8_t u8_Month, const uint8_t u8_Day, const uint8_t u8_Hour = 0, const uint8_t u8_Min = 0, const uint8_t u8_Sec = 0, const int16_t s16_TimeZoneInMin = 0);
  TimeGregorian(const char *pc_Iso8601String);

  static void time2Gregorian(int32_t *ps32_Year, uint8_t *pu8_Month, uint8_t *pu8_Day,
                     uint8_t *pu8_Hour, uint8_t *pu8_Min, uint8_t *pu8_Sec, const int64_t s64_TimeInSec, const int16_t s16_TimeZoneMin = 0);

  static int32_t gregorian2Time(int64_t *ps64_TimeInSec,
                     const int32_t s32_Year, const uint8_t u8_Month, const uint8_t u8_Day,
                     const uint8_t u8_Hour = 0, const uint8_t u8_Min = 0, const uint8_t u8_Sec = 0,
                     const int16_t s16_TimeZoneMin = 0);
 
  static int32_t time2Iso8601(char *pc_Buffer, const uint8_t u8_BufferSize, const uint64_t u64_TimeInSec, const int16_t s16_TimeZoneMin = 0);


  int32_t set(const uint16_t u16_Year, const uint8_t u8_Month, const uint8_t u8_Day,
           const uint8_t u8_Hour = 0, const uint8_t u8_Min = 0, const uint8_t u8_Sec = 0);

  int32_t set(const char *pc_Iso8601String);


  void get(int32_t *ps32_Year, uint8_t *pu8_Month, uint8_t *pu8_Day,
           uint8_t *pu8_Hour = nullptr, uint8_t *pu8_Min = nullptr, uint8_t *pu8_Sec = nullptr);
  void get(const ETimeStandard e_TimeStandard, int32_t *ps32_Year, uint8_t *pu8_Month, uint8_t *pu8_Day,
           uint8_t *pu8_Hour = nullptr, uint8_t *pu8_Min = nullptr, uint8_t *pu8_Sec = nullptr);    
  void get(char *pc_Buffer, const uint8_t u8_BufferSize);
  void get(const ETimeStandard e_TimeStandard, char *pc_Buffer, const uint8_t u8_BufferSize);     
};



#endif // _TIME_GREGORIAN_H_
