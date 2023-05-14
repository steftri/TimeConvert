#include "time_unix_timestamp.h"



#define TIME_T_MIN 0
#define TIME_T_MAX 0xffffffffULL


UnixTimestamp::UnixTimestamp(time_t SecSince1970)
 : Time(UTC)
{
  set(SecSince1970);
}



void UnixTimestamp::set(const time_t SecSince1970)
{
  Time::set(static_cast<uint64_t>(SecSince1970));
  return;
}



time_t UnixTimestamp::get(time_t *p_SecSince1970)
{
  time_t SecSince1970;
  SecSince1970 = static_cast<time_t>(Time::get());
  if(p_SecSince1970)
    *p_SecSince1970 = SecSince1970;
  return SecSince1970;
}


bool UnixTimestamp::isValid(void)
{
  int64_t s64_Time;

  if(!Time::isValid())
    return false;

  s64_Time = Time::get();
  if((s64_Time<TIME_T_MIN) || (s64_Time>TIME_T_MAX))
    return false;

  return true;
}