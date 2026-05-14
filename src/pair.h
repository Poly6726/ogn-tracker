/*

    WORK IN PROGRESS, don't use now!

    

*/

#ifndef PAIR_H_INLCUDED
#define PAIR_H_INLCUDED

#include <stdio.h>
#include <stdint.h>

class PAIR_RxMsg // receiver for the PAIR messages
{ public:
   static const uint8_t MaxBytes = 65; // max. number of bytes
   static const uint8_t Sync   = 0xFE; // MAV sync byte

   uint16_t Check;
   uint8_t  Byte[MaxBytes];
   uint8_t  Idx;

  public:
   void Clear(void) { Idx=0; CheckInit(Check); }

   uint8_t getLen   (void) const { return Byte[1]; }  // Payload length (not whole packet length)
   uint8_t getSeq   (void) const { return Byte[2]; }  // Sequence (increments with every new message)
   uint8_t getSysID (void) const { return Byte[3]; }  // System-ID
   uint8_t getCompID(void) const { return Byte[4]; }  // Component-ID
   uint8_t getMsgID (void) const { return Byte[5]; }  // Message-ID
   void  *getPayload(void) const { return (void *)(Byte+6); }   // message (pointer to) Payload

   void Print(bool Ext=1) const
   { printf("PAIR[%2d:%2d] [%02X] %02X:%02X %3d:", Idx, getLen(), getSeq(), getSysID(), getCompID(), getMsgID() );
     if( (getMsgID()==MAV_ID_STATUSTEXT) && isComplete() )
     { printf("(%d) %s\n", Byte[6], Byte+7); }
     else
     { for(uint8_t i=6; i<Idx; i++)
         printf(" %02X", Byte[i]);
       printf(" %04X (%c)\n", Check, isComplete()?'+':'-');
       if(Ext)
       {      if(getMsgID()==MAV_ID_HEARTBEAT              ) { ((const MAV_HEARTBEAT               *)getPayload())->Print(); }
         else if(getMsgID()==MAV_ID_SYS_STATUS             ) { ((const MAV_SYS_STATUS              *)getPayload())->Print(); }
         else if(getMsgID()==MAV_ID_SYSTEM_TIME            ) { ((const MAV_SYSTEM_TIME             *)getPayload())->Print(); }
         else if(getMsgID()==MAV_ID_SCALED_PRESSURE        ) { ((const MAV_SCALED_PRESSURE         *)getPayload())->Print(); }
         else if(getMsgID()==MAV_ID_GPS_RAW_INT            ) { ((const MAV_GPS_RAW_INT             *)getPayload())->Print(); }
         else if(getMsgID()==MAV_ID_GLOBAL_POSITION_INT    ) { ((const MAV_GLOBAL_POSITION_INT     *)getPayload())->Print(); }
         else if(getMsgID()==MAV_ID_ADSB_VEHICLE           ) { ((const MAV_ADSB_VEHICLE            *)getPayload())->Print(); }
         else if(getMsgID()==MAV_ID_PARAM_VALUE            ) { ((const MAV_PARAM_VALUE             *)getPayload())->Print(); }
       }
     }
   }

   uint8_t ProcessByte(uint8_t RxByte)                       // process a single byte: add to the message or reject
   { // printf("Process[%2d] 0x%02X\n", Idx, RxByte);
     if(Idx==0)                                              // the very first byte: we only accept SYNC
     { if(RxByte==Sync) { Byte[Idx++]=RxByte; return 1; }
                   else {                     return 0; }
     }
     if(Idx==1)                                              // second byte: payload length
     { Byte[Idx++]=RxByte; CheckPass(Check, RxByte); return 1; }
     if(Idx>=MaxBytes) { Clear(); return 0; }                // take following bytes
     Byte[Idx++]=RxByte; if(Idx<(getLen()+7)) CheckPass(Check, RxByte);
     if(Idx==(getLen()+8))
     { CheckPass(Check, mavlink_message_crcs[getMsgID()]);
       // printf("[%2d]", Idx); for(uint8_t i=0; i<Idx; i++) printf(" %02X", Byte[i]); printf(" %04X\n", Check);
       if( ((Check&0xFF)!=Byte[Idx-2]) || ((Check>>8)!=Byte[Idx-1]) ) { Clear(); return 0; }
     }
     return 1; }

   uint8_t isComplete(void) const { return Idx==(getLen()+8); }

   void static CheckInit(uint16_t &Check) { Check=0xFFFF; }
   void static CheckPass(uint16_t &Check, uint8_t Byte)
   { uint8_t Tmp = Byte ^ (uint8_t)(Check&0xFF);
     Tmp ^= (Tmp<<4);
     Check = (Check>>8) ^ ((uint16_t)Tmp<<8) ^ ((uint16_t)Tmp<<3) ^ (Tmp>>4);
     // printf("CheckPass: 0x%02X => 0x%04X\n", Byte, Check);
   }

   static uint8_t Send(uint8_t Len, uint8_t Seq, uint8_t SysID, uint8_t CompID, uint8_t MsgID, const uint8_t *Payload, void (*SendByte)(char) )
   { uint16_t Check; CheckInit(Check);
     (*SendByte)(Sync);
     (*SendByte)(Len);    CheckPass(Check, Len);
     (*SendByte)(Seq);    CheckPass(Check, Seq);
     (*SendByte)(SysID);  CheckPass(Check, SysID);
     (*SendByte)(CompID); CheckPass(Check, CompID);
     (*SendByte)(MsgID);  CheckPass(Check, MsgID);
     for(uint8_t Idx=0; Idx<Len; Idx++)
     { (*SendByte)(Payload[Idx]); CheckPass(Check, Payload[Idx]); }
     CheckPass(Check, mavlink_message_crcs[MsgID]);
     (*SendByte)(Check&0xFF); (*SendByte)(Check>>8);
     return 8+Len; }

    uint8_t Send(void (*SendByte)(char)) const
    { return Send(Byte[1], Byte[2], Byte[3], Byte[4], Byte[5], Byte+6, SendByte); }

} ;


#endif
