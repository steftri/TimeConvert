#ifndef _TIME_UNIX_H_
#define _TIME_UNIX_H_

#include <inttypes.h>
#include <time.h>

#include "time_base.h"



class UnixTimestamp : public TimeBase
{
public:
  UnixTimestamp(const time_t SecSince1970 = 0);

  void set(const time_t SecSince1970);
  time_t get(time_t *SecSince1970 = nullptr);

  bool isValid(void);
};



#endif // _TIME_CUC_H_
