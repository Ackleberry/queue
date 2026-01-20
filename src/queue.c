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

Queue_Error_e Queue_Init(Queue_t *pObj, void *pBuf, size_t bufSize, size_t dataSize)
{
    if (bufSize % dataSize != 0 || bufSize == SIZE_MAX) {
        return Queue_Error;
    }
    pObj->bufSize = bufSize;
    pObj->front = SIZE_MAX;
    pObj->rear = 0;
    pObj->pBuf = pBuf;
    pObj->dataSize = dataSize;

    return Queue_Error_None;
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
    if (Queue_IsFull(pObj))
    {
        return Queue_Error;
    }

    /* If empty, unstash front cursor */
    if (pObj->front == SIZE_MAX)
    {
        pObj->front = pObj->rear;
    }

    /* Push the data into the queue */
    for (size_t byte = 0; byte < pObj->dataSize; byte++)
    {
        pObj->pBuf[pObj->rear++] = ((uint8_t *)pDataInVoid)[byte];
    }

    /* Increment cursor around buffer */
    if (pObj->rear == pObj->bufSize)
    {
        pObj->rear = 0;
    }

    return Queue_Error_None;
}

Queue_Error_e Queue_Pop(Queue_t *pObj, void *pDataOutVoid)
{
    if (Queue_IsEmpty(pObj))
    {
        return Queue_Error;
    }

    /* Pop the data off the queue */
    for (size_t byte = 0; byte < pObj->dataSize; byte++)
    {
        ((uint8_t *)pDataOutVoid)[byte] = pObj->pBuf[pObj->front++];
    }

    /* Increment cursor around buffer */
    if (pObj->front == pObj->bufSize)
    {
        pObj->front = 0;
    }

    /* If empty, stash front cursor */
    if (pObj->front == pObj->rear)
    {
        pObj->front = SIZE_MAX;
    }

    return Queue_Error_None;
}

Queue_Error_e Queue_Peek(Queue_t *pObj, void *pDataOutVoid)
{
    if (Queue_IsEmpty(pObj))
    {
        return Queue_Error;
    }

    /* Copy the data out but don't update object state */
    size_t front = pObj->front;
    for (size_t byte = 0; byte < pObj->dataSize; byte++)
    {
        ((uint8_t *)pDataOutVoid)[byte] = pObj->pBuf[front++];
    }

    return Queue_Error_None;
}