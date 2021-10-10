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

/*******************************************************************************
 * @brief  Initializes the queue object
 *
 * @details  The caller is responsible for allocating the queue object, and
 *           queue buffer.
 *
 * @param pObj      Pointer to the queue object
 * @param pBuf      Pointer to the queue buffer
 * @param bufSize   Size of the buffer, must be an integer multiple of datasize
 * @param dataSize  Size of the data type that the queue is handling
 *
 * @return none
 ******************************************************************************/
void Queue_Init(Queue_t *pObj, void *pBuf, size_t bufSize, size_t dataSize)
{
    pObj->bufSize = bufSize;
    pObj->front = SIZE_MAX;
    pObj->rear = 0;
    pObj->pBuf = pBuf;
    pObj->dataSize = dataSize;
}

/*******************************************************************************
 * @brief  Check if the queue is empty
 *
 * @details  Queue top is considered empty when set to largest `size_t` value,
 *           SIZE_MAX. The first added element "rolls" the top over from
 *           SIZE_MAX to 0.
 *
 * @param pObj  Pointer to the queue object
 *
 * @returns true if empty
 ******************************************************************************/
bool Queue_IsEmpty(Queue_t *pObj)
{
    return (pObj->front == SIZE_MAX);
}

/*******************************************************************************
 * @brief Check if the queue is full
 *
 * @details  Queue top is considered full when set to one less than the buffer
 *           size.
 *
 * @param pObj  Pointer to the queue object
 *
 * @returns true if full
 ******************************************************************************/
bool Queue_IsFull(Queue_t *pObj)
{
    return (pObj->rear == pObj->front);
}

/*******************************************************************************
 * @brief  Pushes some data type onto the queue
 *
 * @param pObj     Pointer to the queue object
 * @param pDataIn  Pointer to the data that will be pushed onto the queue
 *
 * @returns Queue error flag
 ******************************************************************************/
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

/*******************************************************************************
 * @brief  Pops some data type off the queue
 *
 * @param pObj      Pointer to the queue object
 * @param pDataOut  Pointer to the data that will be popped off the queue
 *
 * @returns Queue error flag
 ******************************************************************************/
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

/*******************************************************************************
 * @brief  Peek at the data on the top of the queue
 *
 * @param  pObj      Pointer to the queue object
 * @param  pDataOut  Pointer to the peeked data
 *
 * @returns Queue error flag
 ******************************************************************************/
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