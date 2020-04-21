/*
 * queue.h
 *
 *  Created on: Apr 20, 2020
 *      Author: Katherine
 *
 *      https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_8/Serial-Demo/inc/queue.h
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdint.h>
#include <MKL25Z4.h>

#define Q_MAX_SIZE (256)

typedef struct {
  unsigned int Head; // Index of oldest data element
  unsigned int Tail; // Index of next free space
  unsigned int Size; // Number of elements in use
  uint8_t Data[Q_MAX_SIZE];
} volatile Q_T;


extern int Q_Empty(Q_T * q);
extern int Q_Full(Q_T * q);
extern int Q_Size(Q_T * q);
extern int Q_Enqueue(Q_T * q, uint8_t d);
extern uint8_t Q_Dequeue(Q_T * q);
extern void Q_Init(Q_T * q);

#endif /* QUEUE_H_ */
