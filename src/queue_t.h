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

/**
 * @brief Error flag
**/
typedef enum _Queue_Error_e
{
    Queue_Error_None = 0,
    Queue_Error      = 1,
} Queue_Error_e;

/*============================================================================*
 *                             S T R U C T U R E S                            *
 *============================================================================*/

/**
 * @brief  Queue Object
 *
 * @note   This object should never be directly manipulated by the caller.
**/
typedef struct _Queue_t
{
    size_t   front;    /*!< Front (read) buffer cursor */
    size_t   rear;     /*!< Rear (write) buffer cursor */
    uint8_t *pBuf;     /*!< Pointer to the queue buffer */
    size_t   bufSize;  /*!< Size of the queue buffer */
} Queue_t;

#endif /* QUEUE_T_H_INCLUDED */