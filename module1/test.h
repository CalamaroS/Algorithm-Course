#ifndef __M1_TEST_H__
#define __M1_TEST_H__

#include "assignment1_lib.h"


typedef void(karatsuba_testfoo_t)(karatsuba_string_t *, karatsuba_string_t *, karatsuba_string_t *);
typedef struct karatsuba_test_s
{
    karatsuba_string_t *data1;
    karatsuba_string_t *data2;
    karatsuba_testfoo_t *foo;
    karatsuba_string_t expected;
    karatsuba_string_t actual;
} karatsuba_test_t;


void run_tests(void);
void test_execute(karatsuba_test_t *);


#endif // __M1_TEST_H__
