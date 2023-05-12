#ifdef AVR
#include <Arduino.h>
#else
#include <cstdint>
#include <cstring>
#endif

#include "time_cuc.h"




void TimeCuc::set(const uint8_t *pu8_TimeCucBuffer, const uint8_t u8_BufferSize)
{
  uint8_t u8_CoarseTime;
  uint8_t u8_FineTime;
  uint32_t u32_Sec;
  uint32_t u32_SubSec;
  
  if((NULL==pu8_TimeCucBuffer) || (u8_BufferSize<2))
    return;

  if(0x20!=(pu8_TimeCucBuffer[0]&0xF0))  // first nibble must be 0x20
    return;  // format not supported
  
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
  
  Time::set(u32_Sec, u32_SubSec);
  
  return;
}



void TimeCuc::get(uint8_t *pu8_TimeCucBuffer, const uint8_t u8_BufferSize, const ETimeCucFormat e_TimeCucFormat)
{
  uint8_t u8_CoarseTime;
  uint8_t u8_FineTime;
  uint32_t u32_Sec;
  uint32_t u32_SubSec;

  if((NULL==pu8_TimeCucBuffer) || (u8_BufferSize<2))
    return;

  if(0x20!=((uint8_t)e_TimeCucFormat&0xF0))  // first nibble must be 0x20
    return;  // format not supported
  
  u8_CoarseTime = ((((uint8_t)e_TimeCucFormat)>>2)&0x3)+1;
  u8_FineTime = ((uint8_t)e_TimeCucFormat)&0x3;
  
  if(u8_BufferSize < 1+u8_CoarseTime+u8_FineTime)
    return; // buffer size is too small to hold valid time

  // first, get time in Sec and SubSec
  Time::get(&u32_Sec, &u32_SubSec);

  pu8_TimeCucBuffer[0]=(uint8_t)e_TimeCucFormat;
  for(uint8_t i=0; i<u8_CoarseTime; i++)
    pu8_TimeCucBuffer[1+i] = (uint8_t)(u32_Sec>>(8*(u8_CoarseTime-i-1)));
  for(uint8_t i=0; i<u8_FineTime; i++)
    pu8_TimeCucBuffer[1+u8_CoarseTime+i] = (uint8_t)(u32_SubSec>>(8*(3-i)));
  
  return;
}


