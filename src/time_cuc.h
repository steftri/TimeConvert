#ifndef _TIME_CUC_H_
#define _TIME_CUC_H_

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

typedef enum
{
  TimeCUC10 = 0x20,
  TimeCUC11 = 0x21,
  TimeCUC12 = 0x22,
  TimeCUC13 = 0x23,
  TimeCUC20 = 0x24,
  TimeCUC21 = 0x25,
  TimeCUC22 = 0x26,
  TimeCUC23 = 0x27,
  TimeCUC30 = 0x28,
  TimeCUC31 = 0x29,
  TimeCUC32 = 0x2A,
  TimeCUC33 = 0x2B,
  TimeCUC40 = 0x2C,
  TimeCUC41 = 0x2D,
  TimeCUC42 = 0x2E,
  TimeCUC43 = 0x2F
} ETimeCucFormat;



class TimeCuc : public Time
{
public:
  void set(const uint8_t *pu8_TimeCucBuffer, const uint8_t u8_BufferSize);
  void get(uint8_t *pu8_TimeCucBuffer, const uint8_t u8_BufferSize, const ETimeCucFormat e_TimeCucFormat = TimeCUC42);
};



#endif // _TIME_CUC_H_
