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

Queue_Error_e Queue_Push(Queue_t *pObj, void *pDataInVoid)
{
    Queue_Error_e err = Queue_Error_None;
    uint8_t *pDataIn = (uint8_t *)pDataInVoid;

    /* Push the data into the queue one byte at a time */
    for (size_t byte = 0; byte < pObj->dataSize; byte++)
    {
        if (Queue_IsFull(pObj))
        {
            err = Queue_Error;
            break;
        }

        if (Queue_IsEmpty(pObj))
        {
            pObj->front = pObj->rear;
        }

        pObj->pBuf[pObj->rear] = pDataIn[byte];

        /* Increment cursor around buffer */
        pObj->rear++;
        if (pObj->rear >= pObj->bufSize)
        {
            pObj->rear = 0;
        }
    }

    return err;
}

Queue_Error_e Queue_Pop(Queue_t *pObj, void *pDataOutVoid)
{
    Queue_Error_e err = Queue_Error_None;
    uint8_t *pDataOut = (uint8_t *)pDataOutVoid;

    /* Pop the data off the queue one byte at a time */
    for (size_t byte = 0; byte < pObj->dataSize; byte++)
    {
        if (Queue_IsEmpty(pObj))
        {
            err = Queue_Error;
            break;
        }

        pDataOut[byte] = pObj->pBuf[pObj->front];

        /* Increment cursor around buffer */
        pObj->front++;
        if (pObj->front >= pObj->bufSize)
        {
            pObj->front = 0;
        }

        if (Queue_IsFull(pObj))
        {
            pObj->front = SIZE_MAX;
        }
    }

    return err;
}

Queue_Error_e Queue_Peek(Queue_t *pObj, void *pDataOutVoid)
{
    Queue_Error_e err = Queue_Error_None;
    size_t front = pObj->front;
    size_t rear = pObj->rear;

    err = Queue_Pop(pObj, pDataOutVoid);

    pObj->front = front;
    pObj->rear = rear;
    return err;
}