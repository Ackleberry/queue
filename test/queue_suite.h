#ifndef QUEUE_SUITE_INCLUDED
#define QUEUE_SUITE_INCLUDED

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "greatest.h"
#include "queue_test_helper.h"
#include "queue.h"

/* Declare a local suite. */
SUITE(Queue_Suite);

TEST Queue_init_fails_if_buffer_is_not_an_integer_multiple_of_data_size(void)
{
    /*****************    Arrange    *****************/
    Queue_t q;
    uint8_t buf[6];
    
    /*****************     Act       *****************/
    Queue_Error_e err = Queue_Init(&q, buf, sizeof(buf), 4);

    /*****************    Assert     *****************/
    ASSERT_EQ(Queue_Error, err);

    PASS();
}

TEST Queue_init_fails_if_buffer_is_size_max(void)
{
    /*****************    Arrange    *****************/
    Queue_t q;
    uint8_t buf[2];
    
    /*****************     Act       *****************/
    Queue_Error_e err = Queue_Init(&q, buf, SIZE_MAX, sizeof(buf[0]));

    /*****************    Assert     *****************/
    ASSERT_EQ(Queue_Error, err);

    PASS(); 
}

TEST Queue_can_report_empty(void)
{
    /*****************    Arrange    *****************/
    Queue_t q;
    uint8_t buf[2];
    Queue_Error_e err = Queue_Init(&q, buf, sizeof(buf), sizeof(buf[0]));

    /*****************     Act       *****************/
    bool isEmpty = Queue_IsEmpty(&q);

    /*****************    Assert     *****************/
    ASSERT_EQ(Queue_Error_None, err);
    ASSERT_EQ(true, isEmpty);

    PASS();
}

TEST Queue_can_report_not_empty(void)
{
    /*****************    Arrange    *****************/
    Queue_t q;
    uint8_t buf[2];
    uint8_t dataIn = 5;
    Queue_Init(&q, buf, sizeof(buf), sizeof(buf[0]));
    Queue_Push(&q, &dataIn);

    /*****************     Act       *****************/
    bool isEmpty = Queue_IsEmpty(&q);

    /*****************    Assert     *****************/
    ASSERT_EQ(false, isEmpty);

    PASS();
}

TEST Queue_can_report_full(void)
{
    /*****************    Arrange    *****************/
    Queue_t q;
    uint8_t buf[2];
    uint8_t dataIn = 5;
    Queue_Init(&q, buf, sizeof(buf), sizeof(buf[0]));
    Queue_Push(&q, &dataIn);
    Queue_Push(&q, &dataIn);

    /*****************     Act       *****************/
    bool isFull = Queue_IsFull(&q);

    /*****************    Assert     *****************/
    ASSERT_EQ(true, isFull);

    PASS();
}

TEST Queue_can_report_not_full(void)
{
    /*****************    Arrange    *****************/
    Queue_t q;
    uint8_t buf[2];
    Queue_Init(&q, buf, sizeof(buf), sizeof(buf[0]));

    /*****************     Act       *****************/
    bool isFull = Queue_IsFull(&q);

    /*****************    Assert     *****************/
    ASSERT_EQ(false, isFull);

    PASS();
}

TEST Queue_pop_fails_if_underflow(void)
{
    /*****************    Arrange    *****************/
    Queue_t q;
    uint8_t buf[2];
    Queue_Init(&q, buf, sizeof(buf), sizeof(buf[0]));
    uint8_t dataOut;

    /*****************     Act       *****************/
    Queue_Error_e err = Queue_Pop(&q, &dataOut);

    /*****************    Assert     *****************/
    ASSERT_EQ(Queue_Error, err);

    PASS();
}

TEST Queue_push_fails_if_overflow(void)
{
    /*****************    Arrange    *****************/
    Queue_t q;
    uint8_t buf[2];
    Queue_Init(&q, buf, sizeof(buf), sizeof(buf[0]));
    uint8_t dataIn = 5;

    /* Fill the queue up */
    Queue_Push(&q, &dataIn);
    Queue_Push(&q, &dataIn);

    /*****************     Act       *****************/
    Queue_Error_e err = Queue_Push(&q, &dataIn);

    /*****************    Assert     *****************/
    ASSERT_EQ(Queue_Error, err);

    PASS();
}

TEST Queue_can_pop_1_byte_data_types(void)
{
    /*****************    Arrange    *****************/
    Queue_t q;
    uint8_t buf[4];
    Queue_Init(&q, buf, sizeof(buf), sizeof(buf[0]));
    uint8_t dataIn = 201;
    uint8_t dataOut;

    Queue_Push(&q, &dataIn);

    /*****************     Act       *****************/
    Queue_Error_e err = Queue_Pop(&q, &dataOut);

    /*****************    Assert     *****************/
    ASSERT_EQ(Queue_Error_None, err);
    ASSERT_EQ(dataIn, dataOut);
    ASSERT_EQ(true, Queue_IsEmpty(&q));

    PASS();
}

TEST Queue_can_pop_2_byte_data_types(void)
{
    /*****************    Arrange    *****************/
    Queue_t q;
    uint16_t buf[4];
    Queue_Init(&q, buf, sizeof(buf), sizeof(buf[0]));
    uint16_t dataIn = 999;
    uint16_t dataOut;

    Queue_Push(&q, &dataIn);

    /*****************     Act       *****************/
    Queue_Error_e err = Queue_Pop(&q, &dataOut);

    /*****************    Assert     *****************/
    ASSERT_EQ(Queue_Error_None, err);
    ASSERT_EQ(dataIn, dataOut);
    ASSERT_EQ(true, Queue_IsEmpty(&q));

    PASS();
}

TEST Queue_can_pop_8_byte_data_types(void)
{
    /*****************    Arrange    *****************/
    Queue_t q;
    uint64_t buf[4];
    Queue_Init(&q, buf, sizeof(buf), sizeof(buf[0]));
    uint64_t dataIn = 12345678;
    uint64_t dataOut;

    Queue_Push(&q, &dataIn);

    /*****************     Act       *****************/
    Queue_Error_e err = Queue_Pop(&q, &dataOut);

    /*****************    Assert     *****************/
    ASSERT_EQ(Queue_Error_None, err);
    ASSERT_EQ(dataIn, dataOut);
    ASSERT_EQ(true, Queue_IsEmpty(&q));
    PASS();
}

TEST Queue_can_pop_a_struct_data_type()
{
    /*****************    Arrange    *****************/
    typedef struct _Queue_Struct_t
    {
        uint8_t a;
        uint16_t b;
        uint32_t c;
        uint8_t d;
        uint32_t e;
    } Queue_Struct_t;

    Queue_t q;
    Queue_Struct_t buf[2];
    Queue_Struct_t dataIn = { .a = 5, .b = 54, .c = 1000, .d = 254, .e = 9999 };
    Queue_Struct_t dataOut;
    Queue_Error_e err = (uint8_t)Queue_Error_None;

    Queue_Init(&q, buf, sizeof(buf), sizeof(buf[0]));
    Queue_Push(&q, &dataIn);

    /*****************     Act       *****************/
    err = Queue_Pop(&q, &dataOut);

    /*****************    Assert     *****************/
    ASSERT_EQ(Queue_Error_None, err);
    ASSERT_MEM_EQ(&dataIn, &dataOut, sizeof(Queue_Struct_t));
    ASSERT_EQ(true, Queue_IsEmpty(&q));

    PASS();
}

TEST Queue_can_peek_at_next_element_to_be_popped(void)
{
    /*****************    Arrange    *****************/
    Queue_t q;
    uint16_t buf[4];
    Queue_Init(&q, buf, sizeof(buf), sizeof(buf[0]));
    uint16_t dataIn[] = { 301, 244, 11, 1 };
    uint16_t peekData;
    uint16_t poppedData;

    Queue_Push(&q, &dataIn[0]);
    Queue_Push(&q, &dataIn[1]);


    /*****************     Act       *****************/
    Queue_Error_e err = Queue_Peek(&q, &peekData);

    /*****************    Assert     *****************/
    Queue_Pop(&q, &poppedData);
    ASSERT_EQ(Queue_Error_None, err);
    ASSERT_EQ(dataIn[0], peekData);
    ASSERT_EQ(peekData, poppedData);
    PASS();
}

TEST Queue_can_fill_and_empty_a_large_buffer_with_1_byte_data_types(void)
{
    /*****************    Arrange    *****************/
    Queue_t q;
    int8_t buf[1000];
    int8_t dataIn[1000] =
    {
        [  0] = INT8_MIN,
        [101] = -1,
        [501] = 1,
        [999] = INT8_MAX,
    };
    int8_t dataOut[1000] = { 0 };
    uint8_t err = (uint8_t)Queue_Error_None;

    Queue_Init(&q, buf, sizeof(buf), sizeof(dataIn[0]));

    /*****************     Act       *****************/

    /* Fill the queue up */
    for (uint16_t i = 0; i < ELEMENTS_IN(dataIn); i++)
    {
        err |= Queue_Push(&q, &dataIn[i]);
    }

    /* Empty the queue */
    for (uint16_t i = 0; i < ELEMENTS_IN(dataOut); i++)
    {
        err |= Queue_Pop(&q, &dataOut[i]);
    }

    /*****************    Assert     *****************/
    ASSERT_EQ(Queue_Error_None, (Queue_Error_e)err);
    ASSERT_MEM_EQ(dataIn, dataOut, ELEMENTS_IN(dataIn));
    ASSERT_EQ(true, Queue_IsEmpty(&q));

    PASS();
}

TEST Queue_can_fill_and_empty_a_large_buffer_with_8_byte_data_types(void)
{
    /*****************    Arrange    *****************/
    Queue_t q;
    int64_t buf[1000];
    int64_t dataIn[1000] =
    {
        [  0] = INT64_MIN,
        [101] = -1,
        [501] = 1,
        [999] = INT64_MAX,
    };
    int64_t dataOut[1000] = { 0 };
    uint8_t err = (uint8_t)Queue_Error_None;

    Queue_Init(&q, buf, sizeof(buf), sizeof(dataIn[0]));

    /*****************     Act       *****************/

    /* Fill the queue up */
    for (uint16_t i = 0; i < ELEMENTS_IN(dataIn); i++)
    {
        err |= Queue_Push(&q, &dataIn[i]);
    }

    /* Empty the queue */
    for (uint16_t i = 0; i < ELEMENTS_IN(dataOut); i++)
    {
        err |= Queue_Pop(&q, &dataOut[i]);
    }

    /*****************    Assert     *****************/
    ASSERT_EQ(Queue_Error_None, (Queue_Error_e)err);
    ASSERT_MEM_EQ(dataIn, dataOut, ELEMENTS_IN(dataIn));
    ASSERT_EQ(true, Queue_IsEmpty(&q));

    PASS();
}

TEST Queue_can_fill_and_empty_a_large_buffer_with_struct_data_types(void)
{
    typedef struct _Queue_Struct_t
    {
        uint8_t a;
        int16_t b;
        uint32_t c;
        int8_t d;
        uint32_t e;
    } Queue_Struct_t;

    /*****************    Arrange    *****************/
    Queue_t q;
    Queue_Struct_t buf[1000];
    Queue_Struct_t dataIn[1000] =
    {
        [  1] = { .a = UINT8_MAX, .b = INT16_MAX, .c = -1, .d = INT8_MIN, .e = 1  },
        [101] = { .a = INT8_MAX,  .b = INT16_MIN, .c = 0,  .d = INT8_MAX, .e = -1 },
        [501] = { .a = UINT8_MAX, .b = INT16_MAX, .c = -1, .d = INT8_MIN, .e = 1  },
        [999] = { .a = INT8_MAX,  .b = INT16_MIN, .c = 0,  .d = INT8_MAX, .e = -1 },
    };
    Queue_Struct_t dataOut[1000];
    uint8_t err = (uint8_t)Queue_Error_None;

    Queue_Init(&q, buf, sizeof(buf), sizeof(Queue_Struct_t));

    /*****************     Act       *****************/

    /* Fill the queue up */
    for (uint16_t i = 0; i < ELEMENTS_IN(dataIn); i++)
    {
        err |= Queue_Push(&q, &dataIn[i]);
    }

    /* Empty the queue */
    for (uint16_t i = 0; i < ELEMENTS_IN(dataOut); i++)
    {
        err |= Queue_Pop(&q, &dataOut[i]);
    }

    /*****************    Assert     *****************/
    ASSERT_EQ(Queue_Error_None, (Queue_Error_e)err);
    ASSERT_MEM_EQ(dataIn, dataOut, ELEMENTS_IN(dataIn));
    ASSERT_EQ(true, Queue_IsEmpty(&q));

    PASS();
}

TEST Queue_can_partially_fill_and_empty_1_byte_data_multiple_times()
{
    /*****************    Arrange    *****************/
    Queue_t q;
    int8_t buf[5];
    int8_t dataIn[5] =
    {
        [0] = -7,
        [1] = 121,
        [2] = -121,
        [3] = 7,
        [4] = INT8_MAX,
    };
    int8_t dataOut[5] = { 0 };
    uint8_t err = (uint8_t)Queue_Error_None;

    Queue_Init(&q, buf, sizeof(buf), sizeof(dataIn[0]));

    /*****************     Act       *****************/
    for (uint64_t i = 0; i < 100000; i++)
    {
        err |= Queue_Push(&q, &dataIn[i % ELEMENTS_IN(buf)]);
        err |= Queue_Push(&q, &dataIn[i % ELEMENTS_IN(buf)]);
        err |= Queue_Pop(&q, &dataOut[i % ELEMENTS_IN(buf)]);
        err |= Queue_Pop(&q, &dataOut[i % ELEMENTS_IN(buf)]);

        ASSERT_EQ(Queue_Error_None, (Queue_Error_e)err);
        ASSERT_EQ(false, Queue_IsFull(&q));
        ASSERT_EQ(true, Queue_IsEmpty(&q));
    }

    PASS();
}

TEST Queue_can_partially_fill_and_empty_8_byte_data_multiple_times()
{
    /*****************    Arrange    *****************/
    Queue_t q;
    int64_t buf[5];
    int64_t dataIn[5] =
    {
        [0] = -7,
        [1] = 121,
        [2] = -121,
        [3] = 7,
        [4] = INT64_MAX,
    };

    int64_t dataOut[5] = { 0 };
    uint8_t err = (uint8_t)Queue_Error_None;

    Queue_Init(&q, buf, sizeof(buf), sizeof(dataIn[0]));

    /*****************     Act       *****************/
    for (uint64_t i = 0; i < 100000; i++)
    {
        err |= Queue_Push(&q, &dataIn[i % ELEMENTS_IN(buf)]);
        err |= Queue_Push(&q, &dataIn[i % ELEMENTS_IN(buf)]);
        err |= Queue_Pop(&q, &dataOut[i % ELEMENTS_IN(buf)]);
        err |= Queue_Pop(&q, &dataOut[i % ELEMENTS_IN(buf)]);

        ASSERT_EQ(Queue_Error_None, (Queue_Error_e)err);
        ASSERT_EQ(false, Queue_IsFull(&q));
        ASSERT_EQ(true, Queue_IsEmpty(&q));
    }

    PASS();
}

SUITE(Queue_Suite)
{
    /* Unit Tests */
    RUN_TEST(Queue_init_fails_if_buffer_is_not_an_integer_multiple_of_data_size);
    RUN_TEST(Queue_init_fails_if_buffer_is_size_max);
    RUN_TEST(Queue_can_report_empty);
    RUN_TEST(Queue_can_report_not_empty);
    RUN_TEST(Queue_can_report_full);
    RUN_TEST(Queue_can_report_not_full);
    RUN_TEST(Queue_pop_fails_if_underflow);
    RUN_TEST(Queue_push_fails_if_overflow);
    RUN_TEST(Queue_can_pop_1_byte_data_types);
    RUN_TEST(Queue_can_pop_2_byte_data_types);
    RUN_TEST(Queue_can_pop_8_byte_data_types);
    RUN_TEST(Queue_can_pop_a_struct_data_type);
    RUN_TEST(Queue_can_peek_at_next_element_to_be_popped);

    /* Integration Tests */
    RUN_TEST(Queue_can_fill_and_empty_a_large_buffer_with_1_byte_data_types);
    RUN_TEST(Queue_can_fill_and_empty_a_large_buffer_with_8_byte_data_types);
    RUN_TEST(Queue_can_fill_and_empty_a_large_buffer_with_struct_data_types);
    RUN_TEST(Queue_can_partially_fill_and_empty_1_byte_data_multiple_times);
    RUN_TEST(Queue_can_partially_fill_and_empty_8_byte_data_multiple_times);
}

#endif /* QUEUE_SUITE_INCLUDED */