#include <math.h>
#include "time_julian_date.h"




TimeJulianDate::TimeJulianDate(const TimeBase *p_Time) 
 : TimeBase(p_Time)
{
}


TimeJulianDate::TimeJulianDate(const float f_MJD)
 : TimeBase(TAI)
{
  setMJD(f_MJD);
}


TimeJulianDate::TimeJulianDate(const ETimeStandard e_TimeStandard, const float f_MJD)
 : TimeBase(e_TimeStandard)
{
  setMJD(f_MJD);
}


void TimeJulianDate::setMJD(const float f_MJD)
{
  int64_t s64_Sec;
  uint32_t u32_SubSec;

  double f64_IntPart;
  double f64_FractPart;

  f64_FractPart = modf((static_cast<double>(f_MJD)-40587.0)*86400.0, &f64_IntPart);

  s64_Sec = static_cast<int64_t>(f64_IntPart);
  u32_SubSec = static_cast<uint32_t>(f64_FractPart/0x100000000);

  TimeBase::set(s64_Sec, u32_SubSec);

  return;
}




float TimeJulianDate::getMJD(void)
{
  int64_t s64_Sec;
  uint32_t u32_SubSec;
  double f64_MJD = 0.0;

  TimeBase::get(&s64_Sec, &u32_SubSec);

  f64_MJD = static_cast<double>(s64_Sec)/86400.0 + static_cast<double>(u32_SubSec)/174319837642752.0 + 40587.0;

  return static_cast<float>(f64_MJD);
}



float TimeJulianDate::getMJD(const ETimeStandard e_TimeStandard)
{
  int64_t s64_Sec;
  uint32_t u32_SubSec;
  float f32_MJD = 0.0;

  TimeBase::get(e_TimeStandard, &s64_Sec, &u32_SubSec);

  return f32_MJD;
}