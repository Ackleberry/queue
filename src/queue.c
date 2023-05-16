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

void Queue_Init(Queue_t *pObj, void *pBuf, size_t bufSize)
{
    pObj->bufSize = bufSize;
    pObj->front = SIZE_MAX;
    pObj->rear = 0;
    pObj->pBuf = pBuf;
}

bool Queue_IsEmpty(Queue_t *pObj)
{
    return (pObj->front == SIZE_MAX);
}

bool Queue_IsFull(Queue_t *pObj)
{
    return (pObj->rear == pObj->front);
}

Queue_Error_e Queue_Push(Queue_t *pObj, void *pDataInVoid, size_t dataSize)
{
    Queue_Error_e err = Queue_Error_None;
    uint8_t *pDataIn = (uint8_t *)pDataInVoid;

    if (Queue_IsFull(pObj))
    {
        err = Queue_Error;
    }
    else
    {
        if (Queue_IsEmpty(pObj))
        {
            pObj->front = pObj->rear; /* Unstash front cursor */
        }

        size_t origRear = pObj->rear; /* Save rear incase of error */

        /* Push the data into the queue one byte at a time */
        for (size_t byte = 0; byte < dataSize; byte++)
        {
            pObj->pBuf[pObj->rear] = pDataIn[byte];

            /* Increment cursor around buffer */
            pObj->rear++;
            if (pObj->rear >= pObj->bufSize)
            {
                pObj->rear = 0;
            }

            /* Error if all bytes were not pushed */
            if (Queue_IsFull(pObj) && (byte != (dataSize - 1)))
            {
                err = Queue_Error;
                pObj->rear = origRear;
                break;
            }
        }
    }

    return err;
}

Queue_Error_e Queue_Pop(Queue_t *pObj, void *pDataOutVoid, size_t dataSize)
{
    Queue_Error_e err = Queue_Error_None;
    uint8_t *pDataOut = (uint8_t *)pDataOutVoid;

    if (Queue_IsEmpty(pObj))
    {
        err = Queue_Error;
    }
    else
    {
        size_t origFront = pObj->front; /* Save front incase of error */

        /* Pop the data off the queue one byte at a time */
        for (size_t byte = 0; byte < dataSize; byte++)
        {
            pDataOut[byte] = pObj->pBuf[pObj->front];

            /* Increment cursor around buffer */
            pObj->front++;
            if (pObj->front >= pObj->bufSize)
            {
                pObj->front = 0;
            }

            /* If cursors are equal then we are empty. Stash the front cursor */
            if (pObj->front == pObj->rear)
            {
                pObj->front = SIZE_MAX;
            }

            /* Error if all bytes were not popped */
            if (Queue_IsEmpty(pObj) && (byte != (dataSize - 1)))
            {
                err = Queue_Error;
                pObj->front = origFront;
                break;
            }
        }
    }

    return err;
}

Queue_Error_e Queue_Peek(Queue_t *pObj, void *pDataOutVoid, size_t dataSize)
{
    Queue_Error_e err = Queue_Error_None;
    size_t front = pObj->front;
    size_t rear = pObj->rear;

    err = Queue_Pop(pObj, pDataOutVoid, dataSize);

    pObj->front = front;
    pObj->rear = rear;
    return err;
}