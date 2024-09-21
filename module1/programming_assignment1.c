/**
 * @file programming_assignment1.c
 * @author Thomas Carrassi
 * @brief Question 1
 *
 * In this programming assignment you will implement one or more of the integer multiplication algorithms described in lecture.
 * To get the most out of this assignment, your program should restrict itself to multiplying only pairs of single-digit numbers.
 * You can implement the grade-school algorithm if you want, but to get the most out of the assignment you'll want to implement recursive integer multiplication and/or Karatsuba's algorithm.
 * So: what's the product of the following two 64-digit numbers?
 * 3141592653589793238462643383279502884197169399375105820974944592
 * 2718281828459045235360287471352662497757247093699959574966967627
 *
 * [TIP: before submitting, first test the correctness of your program on some small test cases of your own devising. Then post your best test cases to the discussion forums to help your fellow students!]
 * [Food for thought: the number of digits in each input number is a _power of 2.  Does this make your life easier?  Does it depend on which algorithm you're implementing?]
 * The numeric answer should be typed in the space below.  So if your answer is 1198233847, then just type 1198233847 in the space provided without any space / commas / any other punctuation marks.
 * (We do not require you to submit your code, so feel free to use any programming language you want --- just type the final numeric answer in the following space.)
 * @version 0.1
 * @date 2024-09-17
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <stdio.h>
#include "assignment1_lib.h"
#include "test.h"

#define _TEST_

int main()
{
    printf("HELL0\n\n");

#ifndef _TEST_
    karatsuba_string_t a, b, r;

    get_input(&a);
    get_input(&b);

    karatsuba_init(&r);

    //sub(&a, &b, &r);
    multiply(&a, &b, &r);
    format(&r);

    printf("\n\n>> Result: %s\n\n", r.value);
#else
    printf("HELL0\n\n");
    run_tests();
#endif
    return 0;
}
