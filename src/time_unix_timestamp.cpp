#include "time_unix_timestamp.h"



#define TIME_T_MIN 0
#define TIME_T_MAX 0xffffffffUL


UnixTimestamp::UnixTimestamp(time_t SecSince1970)
 : TimeBase(UTC)
{
  set(SecSince1970);
}



void UnixTimestamp::set(const time_t SecSince1970)
{
  TimeBase::set(static_cast<int64_t>(SecSince1970));

  return;
}



time_t UnixTimestamp::get(time_t *p_SecSince1970)
{
  time_t SecSince1970;

  SecSince1970 = static_cast<time_t>(TimeBase::get());

  if(p_SecSince1970)
    *p_SecSince1970 = SecSince1970;

  return SecSince1970;
}


bool UnixTimestamp::isValid(void)
{
  int64_t s64_Time;

  if(!TimeBase::isValid())
    return false;

  s64_Time = TimeBase::get();
  if((s64_Time<TIME_T_MIN) || (s64_Time>TIME_T_MAX))
    return false;

  return true;
}
