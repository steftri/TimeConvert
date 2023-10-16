#ifndef _TIME_CUC_H_
#define _TIME_CUC_H_

#include <inttypes.h>

#include "time_base.h"


/****************************************************************/
/* PUS TC Packet according to                                   */
/*                                                              */
/*  ECSS-E-70-41A - Space Packet Protocol                       */
/*  CCSDS 301.0-B-2 - Time code formats                         */
/*                                                              */
/*  Time base is TAI.                                           */
/*  Recommended epoch: 1958-01-01T00:00 TAI                     */
/*                                                              */
/*  CUC format: description in P-Field (first byte)             */
/*  bit 0: Extension flag                                       */
/*  bit 1-3: 001: Level 1; epoch is 1958-01-01                  */
/*          010: Level 2; epoch is user defined                 */
/*  bit 4-5: number of octets of coarse time -1                 */
/*  bit 6-7 number of octets of fine time                       */
/*                                                              */
/****************************************************************/



const uint8_t CTimeCucMaxSize = 8;
const int64_t CTimeCucEpoch = -(((1970LL-1958LL)*365LL+3LL)*24LL*60LL*60LL);



class TimeCuc : public TimeBase
{
  int64_t ms64_Epoch; // diff against 1958-01-01T00:00 (in sec) 

public:
  typedef enum {L1 = 0x01, L2 = 0x02} ELevel;

  explicit TimeCuc(const int64_t s64_Epoch = 0);
  explicit TimeCuc(const TimeBase *p_Time, const int64_t s64_Epoch = 0);

  void set(const uint8_t *pu8_TimeCucBuffer, const uint8_t u8_BufferSize);
  uint8_t get(uint8_t *pu8_TimeCucBuffer, const uint8_t u8_BufferSize, const uint8_t u8_Format = 0x1E);

  void setEpoch(const int64_t s64_Epoch);
  static uint8_t calcFormat(const ELevel e_Level, const uint8_t u8_CoarseBytes, const uint8_t u8_FineBytes);
};



#endif // _TIME_CUC_H_
