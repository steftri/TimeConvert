#include "time_cuc.h"



TimeCuc::TimeCuc(const int64_t s64_Epoch)
 : TimeBase(TAI, CTimeCucEpoch+s64_Epoch)
 , ms64_Epoch{s64_Epoch}
{
}



TimeCuc::TimeCuc(const TimeBase *p_Time, const int64_t s64_Epoch)
 : TimeBase(p_Time)
 , ms64_Epoch{s64_Epoch}
{
}



void TimeCuc::set(const uint8_t *pu8_TimeCucBuffer, const uint8_t u8_BufferSize)
{
  uint8_t u8_Level;
  uint8_t u8_CoarseTime;
  uint8_t u8_FineTime;
  uint32_t u32_Sec;
  uint32_t u32_SubSec;
  int64_t s64_Sec;
  
  if((nullptr==pu8_TimeCucBuffer) || (u8_BufferSize<2))
    return;

  if(0x00!=(pu8_TimeCucBuffer[0]&0x80))  // first bit must be 0
    return;  // format not supported
  
  u8_Level = (pu8_TimeCucBuffer[0]>>4)&0x7;
  if((u8_Level!=1) && (u8_Level!=2))
    return; // level is not supported

  u8_CoarseTime = ((pu8_TimeCucBuffer[0]>>2)&0x3)+1;
  u8_FineTime = pu8_TimeCucBuffer[0]&0x3;
  
  if(u8_BufferSize < 1+u8_CoarseTime+u8_FineTime)
    return; // buffer size is too small to hold valid time
  
  u32_Sec = 0;
  u32_SubSec = 0;
  for(uint8_t i=0; i<u8_CoarseTime; i++)
    u32_Sec = (u32_Sec<<8) | pu8_TimeCucBuffer[1+i];
  for(uint8_t i=0; i<u8_FineTime; i++)
    u32_SubSec |= ((uint32_t)(pu8_TimeCucBuffer[1+u8_CoarseTime+i])<<(8*(3-i)));
  
  if(u8_Level == 2) // user-defined epoch?
    s64_Sec=static_cast<int64_t>(u32_Sec)+CTimeCucEpoch+ms64_Epoch;
  else 
    s64_Sec=static_cast<int64_t>(u32_Sec)+CTimeCucEpoch;  

  TimeBase::set(s64_Sec, u32_SubSec);
  
  return;
}



uint8_t TimeCuc::get(uint8_t *pu8_TimeCucBuffer, const uint8_t u8_BufferSize, const uint8_t u8_Format)
{
  uint8_t u8_Level;  
  uint8_t u8_CoarseTime;
  uint8_t u8_FineTime;
  int64_t s64_Sec;
  uint32_t u32_SubSec;

  if((nullptr==pu8_TimeCucBuffer) || (u8_BufferSize<2))
    return 0;

  if(0x00!=(u8_Format&0x80))  // first bit must be 0
    return 0;  // format not supported

  u8_Level = (u8_Format>>4)&0x7;
  if((u8_Level!=0x01) && (u8_Level!=0x02))
    return 0; // level is not supported

  u8_CoarseTime = ((u8_Format>>2)&0x3)+1;
  u8_FineTime = (u8_Format)&0x3;
  
  if(u8_BufferSize < 1+u8_CoarseTime+u8_FineTime)
    return 0; // buffer size is too small to hold valid time

  // first, get time in Sec and SubSec
  TimeBase::get(&s64_Sec, &u32_SubSec);

  if(u8_Level == 2) // user-defined epoch? 
    s64_Sec=s64_Sec-CTimeCucEpoch-ms64_Epoch;
  else 
    s64_Sec=s64_Sec-CTimeCucEpoch;

  pu8_TimeCucBuffer[0]=u8_Format;
  for(uint8_t i=0; i<u8_CoarseTime; i++)
    pu8_TimeCucBuffer[1+i] = (uint8_t)(s64_Sec>>(8*(u8_CoarseTime-i-1)));
  for(uint8_t i=0; i<u8_FineTime; i++)
    pu8_TimeCucBuffer[1+u8_CoarseTime+i] = (uint8_t)(u32_SubSec>>(8*(3-i)));
  
  return 1+u8_CoarseTime+u8_FineTime;
}


void TimeCuc::setEpoch(const int64_t s64_Epoch)
{
  ms64_Epoch=s64_Epoch;
}


uint8_t TimeCuc::calcFormat(const ELevel e_Level, const uint8_t u8_CoarseBytes, const uint8_t u8_FineBytes)
{
  return (static_cast<uint8_t>(e_Level)<<4)|(((u8_CoarseBytes-1)&0x3)<<2)|(u8_FineBytes&0x3);
}

