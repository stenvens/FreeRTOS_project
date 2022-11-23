#ifndef __BUFF_H__
#define __BUFF_H__
#include "stdint.h"

#ifndef NULL
	#define NULL 0  
#endif

#define RING_BUFF_SIZE		64
typedef struct _Buffer8
{
	uint8_t Buff[RING_BUFF_SIZE];
	uint8_t WritePt;
	uint8_t ReadPt;
}RING_BUFF;

uint8_t Buff8IsFull(RING_BUFF* buf);
uint8_t Buff8IsEmpty(RING_BUFF* buf);
uint8_t Buff8GetSize(RING_BUFF* buf);
uint8_t Buff8GetFreeSize(RING_BUFF* buf);
void Buff8Write(RING_BUFF* buf, uint8_t value);
int8_t RING_BUFFRead(RING_BUFF *buf,uint8_t *dat);
void Buff8Init(RING_BUFF* buf);

#endif
