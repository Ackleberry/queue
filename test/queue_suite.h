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

TEST Queue_can_report_empty(void)
{
    /*****************    Arrange    *****************/
    Queue_t q;
    uint8_t buf[2];
    Queue_Init(&q, buf, sizeof(buf));

    /*****************     Act       *****************/
    bool isEmpty = Queue_IsEmpty(&q);

    /*****************    Assert     *****************/
    ASSERT_EQ(true, isEmpty);

    PASS();
}

TEST Queue_can_report_not_empty(void)
{
    /*****************    Arrange    *****************/
    Queue_t q;
    uint8_t buf[2];
    uint8_t dataIn = 5;
    Queue_Init(&q, buf, sizeof(buf));
    Queue_Push(&q, &dataIn, sizeof(dataIn));

    /*****************     Act       *****************/
    bool isEmpty = Queue_IsEmpty(&q);

    /*****************    Assert     *****************/
    ASSERT_EQ(false, isEmpty);

    PASS();
}

TEST Queue_can_report_full_with_homogeneous_data(void)
{
    /*****************    Arrange    *****************/
    Queue_t q;
    uint8_t buf[2];
    uint8_t dataIn = 5;
    Queue_Init(&q, buf, sizeof(buf));
    Queue_Push(&q, &dataIn, sizeof(dataIn));
    Queue_Push(&q, &dataIn, sizeof(dataIn));

    /*****************     Act       *****************/
    bool isFull = Queue_IsFull(&q);

    /*****************    Assert     *****************/
    ASSERT_EQ(true, isFull);

    PASS();
}

TEST Queue_can_report_full_with_heterogeneous_data(void)
{
    /*****************    Arrange    *****************/
    Queue_t q;
    uint8_t buf[7];
    uint32_t dataIn1 = 12345;
    uint16_t dataIn2 = 1234;
    uint8_t  dataIn3 = 123;
    Queue_Init(&q, buf, sizeof(buf));
    Queue_Push(&q, &dataIn1, sizeof(dataIn1));
    Queue_Push(&q, &dataIn2, sizeof(dataIn2));
    Queue_Push(&q, &dataIn3, sizeof(dataIn3));

    /*****************     Act       *****************/
    bool isFull = Queue_IsFull(&q);

    /*****************    Assert     *****************/
    ASSERT_EQ(true, isFull);

    PASS();
}

TEST Queue_reports_not_full_when_empty(void)
{
    /*****************    Arrange    *****************/
    Queue_t q;
    uint8_t buf[2];
    Queue_Init(&q, buf, sizeof(buf));

    /*****************     Act       *****************/
    bool isFull = Queue_IsFull(&q);

    /*****************    Assert     *****************/
    ASSERT_EQ(false, isFull);

    PASS();
}

TEST Queue_can_report_not_full_with_homogeneous_data(void)
{
    /*****************    Arrange    *****************/
    Queue_t q;
    uint8_t buf[3];
    uint8_t dataIn = 5;
    Queue_Init(&q, buf, sizeof(buf));
    Queue_Push(&q, &dataIn, sizeof(dataIn));
    Queue_Push(&q, &dataIn, sizeof(dataIn));

    /*****************     Act       *****************/
    bool isFull = Queue_IsFull(&q);

    /*****************    Assert     *****************/
    ASSERT_EQ(false, isFull);

    PASS();
}

TEST Queue_can_report_not_full_with_heterogeneous_data(void)
{
    /*****************    Arrange    *****************/
    Queue_t q;
    uint8_t buf[7];
    uint32_t dataIn1 = 12345;
    uint16_t dataIn2 = 1234;
    Queue_Init(&q, buf, sizeof(buf));
    Queue_Push(&q, &dataIn1, sizeof(dataIn1));
    Queue_Push(&q, &dataIn2, sizeof(dataIn2));

    /*****************     Act       *****************/
    bool isFull = Queue_IsFull(&q);

    /*****************    Assert     *****************/
    ASSERT_EQ(false, isFull);

    PASS();
}

TEST Queue_pop_fails_if_queue_is_completely_empty(void)
{
    /*****************    Arrange    *****************/
    Queue_t q;
    uint8_t buf[2];
    Queue_Init(&q, buf, sizeof(buf));
    uint8_t dataOut;

    /*****************     Act       *****************/
    Queue_Error_e err = Queue_Pop(&q, &dataOut, sizeof(dataOut));

    /*****************    Assert     *****************/
    ASSERT_EQ(Queue_Error, err);

    PASS();
}

TEST Queue_pop_fails_if_data_is_out_of_memory_bounds(void)
{
    /*****************    Arrange    *****************/
    Queue_t q;
    uint8_t buf[2];
    Queue_Init(&q, buf, sizeof(buf));

    uint8_t dataIn = 5;
    Queue_Push(&q, &dataIn, sizeof(dataIn));

    /*****************     Act       *****************/
    uint32_t dataOut;
    Queue_Error_e err = Queue_Pop(&q, &dataOut, sizeof(dataOut));

    /*****************    Assert     *****************/
    ASSERT_EQ(Queue_Error, err);

    PASS();
}

TEST Queue_push_fails_if_queue_is_completely_full(void)
{
    /*****************    Arrange    *****************/
    Queue_t q;
    uint8_t buf[2];
    Queue_Init(&q, buf, sizeof(buf));
    uint8_t dataIn = 5;

    /* Fill the queue up */
    Queue_Push(&q, &dataIn, sizeof(dataIn));
    Queue_Push(&q, &dataIn, sizeof(dataIn));

    /*****************     Act       *****************/
    Queue_Error_e err = Queue_Push(&q, &dataIn, sizeof(dataIn));

    /*****************    Assert     *****************/
    ASSERT_EQ(Queue_Error, err);

    PASS();
}

TEST Queue_push_does_not_fail_with_heterogeneous_data(void)
{
    /*****************    Arrange    *****************/
    Queue_t q;
    uint8_t buf[13];
    uint64_t dataIn1 = 12345;
    uint32_t dataIn2 = 1234;
    uint8_t dataIn3 = 123;
    Queue_Init(&q, buf, sizeof(buf));

    /* Fill the queue up */
    Queue_Push(&q, &dataIn1, sizeof(dataIn1));
    Queue_Push(&q, &dataIn2, sizeof(dataIn2));

    /*****************     Act       *****************/
    Queue_Error_e err = Queue_Push(&q, &dataIn3, sizeof(dataIn3));

    /*****************    Assert     *****************/
    ASSERT_EQ(Queue_Error_None, err);

    PASS();
}

TEST Queue_push_fails_if_data_is_out_of_memory_bounds(void)
{
    /*****************    Arrange    *****************/
    Queue_t q;
    uint8_t buf[13];
    uint64_t dataIn1 = 12345;
    uint32_t dataIn2 = 1234;
    uint16_t dataIn3 = 123;
    Queue_Init(&q, buf, sizeof(buf));

    /* Fill the queue up */
    Queue_Push(&q, &dataIn1, sizeof(dataIn1));
    Queue_Push(&q, &dataIn2, sizeof(dataIn2));

    /*****************     Act       *****************/
    Queue_Error_e err = Queue_Push(&q, &dataIn3, sizeof(dataIn3));

    /*****************    Assert     *****************/
    ASSERT_EQ(Queue_Error, err);

    PASS();
}

TEST Queue_can_pop_1_byte_data_types(void)
{
    /*****************    Arrange    *****************/
    Queue_t q;
    uint8_t buf[4];
    Queue_Init(&q, buf, sizeof(buf));
    uint8_t dataIn = 201;
    uint8_t dataOut;

    Queue_Push(&q, &dataIn, sizeof(dataIn));

    /*****************     Act       *****************/
    Queue_Error_e err = Queue_Pop(&q, &dataOut, sizeof(dataOut));

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
    Queue_Init(&q, buf, sizeof(buf));
    uint16_t dataIn = 999;
    uint16_t dataOut;

    Queue_Push(&q, &dataIn, sizeof(dataIn));

    /*****************     Act       *****************/
    Queue_Error_e err = Queue_Pop(&q, &dataOut, sizeof(dataOut));

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
    Queue_Init(&q, buf, sizeof(buf));
    uint64_t dataIn = 12345678;
    uint64_t dataOut;

    Queue_Push(&q, &dataIn, sizeof(dataIn));

    /*****************     Act       *****************/
    Queue_Error_e err = Queue_Pop(&q, &dataOut, sizeof(dataOut));

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

    Queue_Init(&q, buf, sizeof(buf));
    Queue_Push(&q, &dataIn, sizeof(dataIn));

    /*****************     Act       *****************/
    err = Queue_Pop(&q, &dataOut, sizeof(dataOut));

    /*****************    Assert     *****************/
    ASSERT_EQ(Queue_Error_None, err);
    ASSERT_MEM_EQ(&dataIn, &dataOut, sizeof(Queue_Struct_t));
    ASSERT_EQ(true, Queue_IsEmpty(&q));

    PASS();
}

TEST Queue_can_pop_heterogeneous_data_types(void)
{
    /*****************    Arrange    *****************/
    uint8_t err = (uint8_t)Queue_Error_None;
    Queue_t q;
    uint8_t buf[4];
    Queue_Init(&q, buf, sizeof(buf));
    uint8_t dataIn1 = 234;
    uint8_t dataOut1;
    uint16_t dataIn2 = 999;
    uint16_t dataOut2;

    Queue_Push(&q, &dataIn1, sizeof(dataIn1));
    Queue_Push(&q, &dataIn2, sizeof(dataIn2));

    /*****************     Act       *****************/
    err |= Queue_Pop(&q, &dataOut1, sizeof(dataOut1));
    err |= Queue_Pop(&q, &dataOut2, sizeof(dataOut2));

    /*****************    Assert     *****************/
    ASSERT_EQ(Queue_Error_None, err);
    ASSERT_EQ(dataIn1, dataOut1);
    ASSERT_EQ(dataIn2, dataOut2);
    ASSERT_EQ(true, Queue_IsEmpty(&q));

    PASS();
}

TEST Queue_can_peek_at_next_element_to_be_popped(void)
{
    /*****************    Arrange    *****************/
    Queue_t q;
    uint16_t buf[4];
    Queue_Init(&q, buf, sizeof(buf));
    uint16_t dataIn[] = { 301, 244, 11, 1 };
    uint16_t peekData;
    uint16_t poppedData;

    Queue_Push(&q, &dataIn[0], sizeof(dataIn[0]));
    Queue_Push(&q, &dataIn[1], sizeof(dataIn[1]));


    /*****************     Act       *****************/
    Queue_Error_e err = Queue_Peek(&q, &peekData, sizeof(peekData));

    /*****************    Assert     *****************/
    Queue_Pop(&q, &poppedData, sizeof(poppedData));
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

    Queue_Init(&q, buf, sizeof(buf));

    /*****************     Act       *****************/

    /* Fill the queue up */
    for (uint16_t i = 0; i < ELEMENTS_IN(dataIn); i++)
    {
        err |= Queue_Push(&q, &dataIn[i], sizeof(dataIn[i]));
    }

    /* Empty the queue */
    for (uint16_t i = 0; i < ELEMENTS_IN(dataOut); i++)
    {
        err |= Queue_Pop(&q, &dataOut[i], sizeof(dataOut[i]));
    }

    /*****************    Assert     *****************/
    ASSERT_EQ(Queue_Error_None, (Queue_Error_e)err);
    ASSERT_MEM_EQ(dataIn, dataOut, ELEMENTS_IN(dataIn));
    ASSERT_EQ(true, Queue_IsEmpty(&q));

    PASS();
}

TEST Queue_can_fill_and_empty_a_large_buffer_with_2_byte_data_types(void)
{
    /*****************    Arrange    *****************/
    Queue_t q;
    int16_t buf[1000];
    int16_t dataIn[1000] =
    {
        [  0] = INT8_MIN,
        [101] = -1,
        [501] = 1,
        [999] = INT8_MAX,
    };
    int16_t dataOut[1000] = { 0 };
    uint8_t err = (uint8_t)Queue_Error_None;

    Queue_Init(&q, buf, sizeof(buf));

    /*****************     Act       *****************/

    /* Fill the queue up */
    for (uint16_t i = 0; i < ELEMENTS_IN(dataIn); i++)
    {
        err |= Queue_Push(&q, &dataIn[i], sizeof(dataIn[i]));
    }

    /* Empty the queue */
    for (uint16_t i = 0; i < ELEMENTS_IN(dataOut); i++)
    {
        err |= Queue_Pop(&q, &dataOut[i], sizeof(dataOut[i]));
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

    Queue_Init(&q, buf, sizeof(buf));

    /*****************     Act       *****************/

    /* Fill the queue up */
    for (uint16_t i = 0; i < ELEMENTS_IN(dataIn); i++)
    {
        err |= Queue_Push(&q, &dataIn[i], sizeof(dataIn[i]));
    }

    /* Empty the queue */
    for (uint16_t i = 0; i < ELEMENTS_IN(dataOut); i++)
    {
        err |= Queue_Pop(&q, &dataOut[i], sizeof(dataOut[i]));
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

    Queue_Init(&q, buf, sizeof(buf));

    /*****************     Act       *****************/

    /* Fill the queue up */
    for (uint16_t i = 0; i < ELEMENTS_IN(dataIn); i++)
    {
        err |= Queue_Push(&q, &dataIn[i], sizeof(dataIn[i]));
    }

    /* Empty the queue */
    for (uint16_t i = 0; i < ELEMENTS_IN(dataOut); i++)
    {
        err |= Queue_Pop(&q, &dataOut[i], sizeof(dataOut[i]));
    }

    /*****************    Assert     *****************/
    ASSERT_EQ(Queue_Error_None, (Queue_Error_e)err);
    ASSERT_MEM_EQ(dataIn, dataOut, ELEMENTS_IN(dataIn));
    ASSERT_EQ(true, Queue_IsEmpty(&q));

    PASS();
}

TEST Queue_can_fill_and_empty_a_large_buffer_with_mixed_data_types(void)
{
    typedef struct _Mixed_Data_t
    {
        uint8_t a;
        uint16_t b;
        uint32_t c;
        uint64_t d;
        uint32_t e;
        uint16_t f;
        uint8_t g;
    } Mixed_Data_t;

    /*****************    Arrange    *****************/
    uint8_t err = (uint8_t)Queue_Error_None;
    Queue_t q;
    int8_t buf[22];
    Queue_Init(&q, buf, sizeof(buf));

    Mixed_Data_t dataIn =
    {
        .a = 0x12,
        .b = 0x3456,
        .c = 0x789012,
        .d = 0x3456789,
        .e = 0x12346,
        .f = 0x7890,
        .g = 0x13,
    };

    /*****************     Act       *****************/

    /* Fill the queue up */
    err |= Queue_Push(&q, &dataIn.a, sizeof(dataIn.a));
    err |= Queue_Push(&q, &dataIn.b, sizeof(dataIn.b));
    err |= Queue_Push(&q, &dataIn.c, sizeof(dataIn.c));
    err |= Queue_Push(&q, &dataIn.d, sizeof(dataIn.d));
    err |= Queue_Push(&q, &dataIn.e, sizeof(dataIn.e));
    err |= Queue_Push(&q, &dataIn.f, sizeof(dataIn.f));
    err |= Queue_Push(&q, &dataIn.g, sizeof(dataIn.g));

    bool isFull = Queue_IsFull(&q);

    /* Empty the queue */
    Mixed_Data_t dataOut = {0};
    err |= Queue_Pop(&q, &dataOut.a, sizeof(dataOut.a));
    err |= Queue_Pop(&q, &dataOut.b, sizeof(dataOut.b));
    err |= Queue_Pop(&q, &dataOut.c, sizeof(dataOut.c));
    err |= Queue_Pop(&q, &dataOut.d, sizeof(dataOut.d));
    err |= Queue_Pop(&q, &dataOut.e, sizeof(dataOut.e));
    err |= Queue_Pop(&q, &dataOut.f, sizeof(dataOut.f));
    err |= Queue_Pop(&q, &dataOut.g, sizeof(dataOut.g));

    /*****************    Assert     *****************/
    ASSERT_EQ(Queue_Error_None, (Queue_Error_e)err);
    ASSERT_EQ(true, isFull);
    ASSERT_MEM_EQ(&dataIn.a, &dataOut.a, sizeof(dataIn.a));
    ASSERT_MEM_EQ(&dataIn.b, &dataOut.b, sizeof(dataIn.b));
    ASSERT_MEM_EQ(&dataIn.c, &dataOut.c, sizeof(dataIn.c));
    ASSERT_MEM_EQ(&dataIn.d, &dataOut.d, sizeof(dataIn.d));
    ASSERT_MEM_EQ(&dataIn.e, &dataOut.e, sizeof(dataIn.e));
    ASSERT_MEM_EQ(&dataIn.f, &dataOut.f, sizeof(dataIn.f));
    ASSERT_MEM_EQ(&dataIn.g, &dataOut.g, sizeof(dataIn.g));
    ASSERT_EQ(true, Queue_IsEmpty(&q));

    PASS();
}

TEST Queue_can_partially_fill_and_empty_multiple_times()
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

    Queue_Init(&q, buf, sizeof(buf));

    /*****************     Act       *****************/
    for (uint16_t i = 0; i < 15; i++)
    {
        err |= Queue_Push(&q, &dataIn[i % sizeof(buf)], sizeof(dataIn[i % sizeof(buf)]));
        err |= Queue_Push(&q, &dataIn[i % sizeof(buf)], sizeof(dataIn[i % sizeof(buf)]));
        err |= Queue_Pop(&q, &dataOut[i % sizeof(buf)], sizeof(dataIn[i % sizeof(buf)]));
        err |= Queue_Pop(&q, &dataOut[i % sizeof(buf)], sizeof(dataIn[i % sizeof(buf)]));

        ASSERT_EQ(Queue_Error_None, (Queue_Error_e)err);
        ASSERT_EQ(false, Queue_IsFull(&q));
        ASSERT_EQ(true, Queue_IsEmpty(&q));
    }

    PASS();
}

SUITE(Queue_Suite)
{
    RUN_TEST(Queue_can_report_empty);
    RUN_TEST(Queue_can_report_not_empty);
    RUN_TEST(Queue_can_report_full_with_homogeneous_data);
    RUN_TEST(Queue_can_report_full_with_heterogeneous_data);
    RUN_TEST(Queue_reports_not_full_when_empty);
    RUN_TEST(Queue_can_report_not_full_with_homogeneous_data);
    RUN_TEST(Queue_can_report_not_full_with_heterogeneous_data);

    RUN_TEST(Queue_pop_fails_if_queue_is_completely_empty);
    RUN_TEST(Queue_pop_fails_if_data_is_out_of_memory_bounds);
    RUN_TEST(Queue_push_fails_if_queue_is_completely_full);
    RUN_TEST(Queue_push_does_not_fail_with_heterogeneous_data);
    RUN_TEST(Queue_push_fails_if_data_is_out_of_memory_bounds);

    RUN_TEST(Queue_can_pop_1_byte_data_types);
    RUN_TEST(Queue_can_pop_2_byte_data_types);
    RUN_TEST(Queue_can_pop_8_byte_data_types);
    RUN_TEST(Queue_can_pop_a_struct_data_type);
    RUN_TEST(Queue_can_pop_heterogeneous_data_types);
    RUN_TEST(Queue_can_peek_at_next_element_to_be_popped);
    RUN_TEST(Queue_can_fill_and_empty_a_large_buffer_with_1_byte_data_types);
    RUN_TEST(Queue_can_fill_and_empty_a_large_buffer_with_2_byte_data_types);
    RUN_TEST(Queue_can_fill_and_empty_a_large_buffer_with_8_byte_data_types);
    RUN_TEST(Queue_can_fill_and_empty_a_large_buffer_with_struct_data_types);
    RUN_TEST(Queue_can_fill_and_empty_a_large_buffer_with_mixed_data_types);
    RUN_TEST(Queue_can_partially_fill_and_empty_multiple_times);
}

#endif /* QUEUE_SUITE_INCLUDED */