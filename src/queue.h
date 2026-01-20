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

/*******************************************************************************
 * @brief  Initializes the queue object
 *
 * @details  The caller is responsible for allocating the queue object, and
 *           queue buffer.
 *
 * @param pObj      Pointer to the queue object
 * @param pBuf      Pointer to the queue buffer
 * @param bufSize   Queue buffer size. Must be an integer multiple of datasize
 * @param dataSize  Size of the data type that the queue is handling
 *
 * @returns Queue error flag
 ******************************************************************************/
Queue_Error_e Queue_Init(Queue_t *pObj, void *pBuf, size_t bufSize, size_t dataSize);

/*******************************************************************************
 * @brief  Check if the queue is empty
 *
 * @param pObj  Pointer to the queue object
 *
 * @returns true if empty
 ******************************************************************************/
bool Queue_IsEmpty(Queue_t *pObj);

/*******************************************************************************
 * @brief Check if the queue is full
 *
 * @param pObj  Pointer to the queue object
 *
 * @returns true if full
 ******************************************************************************/
bool Queue_IsFull(Queue_t *pObj);

/*******************************************************************************
 * @brief  Pushes some data type onto the queue
 *
 * @param pObj         Pointer to the queue object
 * @param pDataInVoid  Pointer to the data that will be pushed onto the queue
 *
 * @returns Queue error flag
 ******************************************************************************/
Queue_Error_e Queue_Push(Queue_t *pObj, void *pDataInVoid);

/*******************************************************************************
 * @brief  Pops some data type off the queue
 *
 * @param pObj          Pointer to the queue object
 * @param pDataOutVoid  Pointer to the data that will be popped off the queue
 *
 * @returns Queue error flag
 ******************************************************************************/
Queue_Error_e Queue_Pop(Queue_t *pObj, void *pDataOutVoid);

/*******************************************************************************
 * @brief  Peek at the data on the top of the queue
 *
 * @param pObj          Pointer to the queue object
 * @param pDataOutVoid  Pointer to the peeked data
 *
 * @returns Queue error flag
 ******************************************************************************/
Queue_Error_e Queue_Peek(Queue_t *pObj, void *pDataOutVoid);

#endif /* QUEUE_H_INCLUDED */