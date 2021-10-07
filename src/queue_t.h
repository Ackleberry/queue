/*******************************************************************************
 * @file  queue_t.h
 *
 * @brief Queue public function declarations
 *
 * @author Brooks Anderson <bilbrobaggins@gmail.com>
 ******************************************************************************/
#ifndef QUEUE_T_H_INCLUDED
#define QUEUE_T_H_INCLUDED

/*============================================================================*
 *                              I N C L U D E S                               *
 *============================================================================*/
#include <stddef.h>
#include <stdint.h>

/*============================================================================*
 *                                D E F I N E S                               *
 *============================================================================*/

/*============================================================================*
 *                           E N U M E R A T I O N S                          *
 *============================================================================*/

typedef enum _Queue_Error_e
{
    Queue_Error_None = 0,
    Queue_Error      = 1,
} Queue_Error_e;

/*============================================================================*
 *                             S T R U C T U R E S                            *
 *============================================================================*/

typedef struct _Queue_t
{
    size_t   front;    /*!< Buffer index to the front of the queue */
    size_t   rear;     /*!< Buffer index to the rear of the queue */
    uint8_t *pBuf;     /*!< Pointer to the queue buffer */
    size_t   bufSize;  /*!< Size of the queue buffer */
    size_t   dataSize; /*!< Size of the data type to be stored in the queue */
} Queue_t;

#endif /* QUEUE_T_H_INCLUDED */