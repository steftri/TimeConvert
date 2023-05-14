#ifndef _TIME_CUC_H_
#define _TIME_CUC_H_

#include <inttypes.h>

#include "time_base.h"


/****************************************************************/
/* PUS TC Packet according to                                   */
/*                                                              */
/*  ECSS-E-70-41A - Space Packet Protocol                       */
/*                                                              */
/*  Time base is TAI.                                           */
/*                                                              */
/****************************************************************/



const uint8_t CTimeCucSize = 8;


class TimeCuc : public TimeBase
{
public:
  typedef enum
  {
    CUC10 = 0x20,
    CUC11 = 0x21,
    CUC12 = 0x22,
    CUC13 = 0x23,
    CUC20 = 0x24,
    CUC21 = 0x25,
    CUC22 = 0x26,
    CUC23 = 0x27,
    CUC30 = 0x28,
    CUC31 = 0x29,
    CUC32 = 0x2A,
    CUC33 = 0x2B,
    CUC40 = 0x2C,
    CUC41 = 0x2D,
    CUC42 = 0x2E,
    CUC43 = 0x2F
  } EFormat;

  void set(const uint8_t *pu8_TimeCucBuffer, const uint8_t u8_BufferSize);
  void get(uint8_t *pu8_TimeCucBuffer, const uint8_t u8_BufferSize, const TimeCuc::EFormat e_TimeCucFormat = TimeCuc::CUC42);
};



#endif // _TIME_CUC_H_
