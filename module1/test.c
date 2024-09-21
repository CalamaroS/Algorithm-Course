
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "test.h"


#define TEST_DATA_NUMBER 10
#define TEST_NUMBER 3
#define DEFAULT_SIZE 32

karatsuba_string_t test_data[TEST_DATA_NUMBER] = {
    {
        .value = "12",
        .digits = 2,
    },
    {
        .value = "10",
        .digits = 2,
    },
    {
        .value = "100",
        .digits = 3,
    },
    {
        .value = "1000",
        .digits = 4,
    },
    {
        .value = "99",
        .digits = 2,
    },
    {
        .value = "956",
        .digits = 3,
    },
    {
        .value = "87",
        .digits = 2,
    },
    {
        .value = "1234",
        .digits = 4,
    },
    {
        .value = "5678",
        .digits = 4,
    },
    {
        .value = "876",
        .digits = 3,
    }};

karatsuba_test_t tests[TEST_NUMBER] = {
    {
        .data1 = &test_data[0],
        .data2 = &test_data[1],
        .foo = add,
        .expected = {
            .value = "22",
            .digits = 2,
        },
        .actual = {
            .value = "",
            .digits = 0,
        },
    },
    {
        .data1 = &test_data[0],
        .data2 = &test_data[1],
        .foo = sub,
        .expected = {
            .value = "2",
            .digits = 1,
        },
        .actual = {
            .value = "",
            .digits = 0,
        },
    },
    {
        .data1 = &test_data[0],
        .data2 = &test_data[1],
        .foo = multiply,
        .expected = {
            .value = "120",
            .digits = 3,
        },
        .actual = {
            .value = "",
            .digits = 0,
        },
    },
    };

void strrev(char* str, size_t strlen){
    size_t i, j;
    char tmp;

    i = 0;
    j = strlen-1;

    while (i<j){
        tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
        i++;
        j--;
    }

}

void test_execute(karatsuba_test_t *test)
{
    printf("EXE \n");

    // Execute
    test->actual.value = malloc(DEFAULT_SIZE * sizeof(unsigned char));
    printf("EXE1 \n");

    char *tmp1 = malloc(strlen(test->data1->value) * sizeof(unsigned char));
    char *tmp2 = malloc(strlen(test->data2->value) * sizeof(unsigned char));

    strcpy(tmp1, test->data1->value);
    strcpy(tmp2, test->data2->value);
    printf("EXE1.5 \n");

    strrev(tmp1, strlen(tmp1));
    strrev(tmp2, strlen(tmp2));
    printf("EXE1.99 \n");

    test->data1->value = tmp1;
    test->data2->value = tmp2;

    printf("EXE2 \n");

    test->foo(test->data1, test->data2, &test->actual);
    printf("EXE3 \n");

    inplace_reverse(test->actual.value);

    printf("RES \n");

    // Compute result
    int res = strcmp(test->actual.value, test->expected.value);
    res = res || !(test->actual.digits == test->expected.digits);

    printf("PRINT \n");
    // print results
    if (res)
        printf("\n> FAIL - e: %s, %d - a %s, %d", test->expected.value, test->expected.digits, test->actual.value, test->actual.digits);

    else
        printf("\n> PASS - e: %s, %d - a %s, %d", test->expected.value, test->expected.digits, test->actual.value, test->actual.digits);
}

void run_tests()
{
    printf("HELLO \n");
    for (int t=0; t<TEST_NUMBER; t++){
        test_execute(&tests[t]);
        printf("\n");
    }
}
