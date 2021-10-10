/*******************************************************************************
 * @file  queue.c
 *
 * @brief Queue implementation
 *
 * @author Brooks Anderson <bilbrobaggins@gmail.com>
 ******************************************************************************/

/*============================================================================*
 *                              I N C L U D E S                               *
 *============================================================================*/
#include "queue.h"

/*============================================================================*
 *                      P U B L I C    F U N C T I O N S                      *
 *============================================================================*/

void Queue_Init(Queue_t *pObj, void *pBuf, size_t bufSize, size_t dataSize)
{
    pObj->bufSize = bufSize;
    pObj->front = SIZE_MAX;
    pObj->rear = 0;
    pObj->pBuf = pBuf;
    pObj->dataSize = dataSize;
}

bool Queue_IsEmpty(Queue_t *pObj)
{
    return (pObj->front == SIZE_MAX);
}

bool Queue_IsFull(Queue_t *pObj)
{
    return (pObj->rear == pObj->front);
}

Queue_Error_e Queue_Push(Queue_t *pObj, void *pDataIn)
{
    Queue_Error_e err = Queue_Error_None;
    uint8_t *pData = (uint8_t *)pDataIn;

    /* Push the data into the queue one byte at a time */
    for (size_t idx = 0; idx < pObj->dataSize; idx++)
    {
        if (Queue_IsFull(pObj))
        {
            err = Queue_Error;
            break;
        }

        if (pObj->front == SIZE_MAX)
        {
            pObj->front = pObj->rear;
        }

        pObj->pBuf[pObj->rear] = pData[idx];
        pObj->rear = (pObj->rear + 1) % pObj->bufSize;
    }

    return err;
}

Queue_Error_e Queue_Pop(Queue_t *pObj, void *pDataOut)
{
    Queue_Error_e err = Queue_Error_None;
    uint8_t *pData = (uint8_t *)pDataOut;

    /* Pop the data off the queue one byte at a time */
    for (size_t idx = 0; idx < pObj->dataSize; idx++)
    {
        if (Queue_IsEmpty(pObj))
        {
            err = Queue_Error;
            break;
        }

        pData[idx] = pObj->pBuf[pObj->front];
        pObj->front = (pObj->front + 1) % pObj->bufSize;

        if (pObj->front == pObj->rear)
        {
            pObj->front = SIZE_MAX;
        }
    }

    return err;
}

Queue_Error_e Queue_Peek(Queue_t *pObj, void *pDataOut)
{
    Queue_Error_e err = Queue_Error_None;
    size_t front = pObj->front;
    size_t rear = pObj->rear;

    err = Queue_Pop(pObj, pDataOut);

    pObj->front = front;
    pObj->rear = rear;
    return err;
}