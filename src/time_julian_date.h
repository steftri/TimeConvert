#ifndef _TIME_JULIAN_DATE_H_
#define _TIME_JULIAN_DATE_H_

#include <inttypes.h>

#include "time_base.h"



class TimeJulianDate : public TimeBase
{
public:
  TimeJulianDate(const TimeBase *p_Time);

  TimeJulianDate(const float f_MJD = 0.0);
  TimeJulianDate(const ETimeStandard e_TimeStandard, const float f_MJD = 0.0);

  void setMJD(const float f_MJD = 0.0);

  float getMJD(void);
  float getMJD(const ETimeStandard e_TimeStandard);
};



#endif // _TIME_CUC_H_
