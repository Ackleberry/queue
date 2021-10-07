/*******************************************************************************
 * @file  queue.h
 *
 * @brief Queue public function declarations
 *
 * @author Brooks Anderson <bilbrobaggins@gmail.com>
 ******************************************************************************/

#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

/*============================================================================*
 *                              I N C L U D E S                               *
 *============================================================================*/
#include <stddef.h>
#include <stdbool.h>

#include "queue_t.h"

/*============================================================================*
 *                 F U N C T I O N    D E C L A R A T I O N S                 *
 *============================================================================*/

void Queue_Init(Queue_t *pObj, void *pBuf, size_t bufSize, size_t dataSize);

bool Queue_IsEmpty(Queue_t *pObj);

bool Queue_IsFull(Queue_t *pObj);

Queue_Error_e Queue_Push(Queue_t *pObj, void *pDataIn);

Queue_Error_e Queue_Pop(Queue_t *pObj, void *pDataOut);

Queue_Error_e Queue_Peek(Queue_t *pObj, void *pDataOut);

#endif /* QUEUE_H_INCLUDED */