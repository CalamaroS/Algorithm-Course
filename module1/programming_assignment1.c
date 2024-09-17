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
 * [Food for thought: the number of digits in each input number is a power of 2.  Does this make your life easier?  Does it depend on which algorithm you're implementing?]
 * The numeric answer should be typed in the space below.  So if your answer is 1198233847, then just type 1198233847 in the space provided without any space / commas / any other punctuation marks.
 * (We do not require you to submit your code, so feel free to use any programming language you want --- just type the final numeric answer in the following space.)
 * @version 0.1
 * @date 2024-09-17
 *
 * @copyright Copyright (c) 2024
 *
 */


#include <stdint.h>
#include <stddef.h>
#include <string.h>


void multiply(karatsuba_string_t*, karatsuba_string_t*, karatsuba_string_t*);

void add(karatsuba_string_t*, karatsuba_string_t*, karatsuba_string_t*);

int value(karatsuba_string_t*);

void multiply(karatsuba_string_t* x, karatsuba_string_t* y, karatsuba_string_t* res){
    karatsuba_string_t a = {
        .head = x->head,
        .digits = x->digits >> 1,
    };
    karatsuba_string_t b = {
        .head = x->head + (x->digits >> 1),
        .digits = x->digits >> 1,
    };
    karatsuba_string_t c = {
        .head = y->head,
        .digits = y->digits >> 1,
    };
    karatsuba_string_t d = {
        .head = y->head + (x->digits >> 1),
        .digits = y->digits >> 1,
    };




    if (x->digits == 2 && y->digits == 2){
        int ac = value(&a) * value(&c) - value(&d) * value(&d)
    }
}


int main(){


    return 0;
}

typedef struct karatsuba_string_s{
    char *head;
    int digits;
} karatsuba_string_t;

unsigned int karatsuba_int(unsigned int a, unsigned int b, unsigned int c, unsigned int d){
    unsigned int ac = a*c;
    unsigned int bd = b*d;
    unsigned int step3 = (a+b) * (c+d);
    return step3 - ac - bd;
}

char* karatsuba(karatsuba_string_t *a, karatsuba_string_t *b, karatsuba_string_t *c, karatsuba_string_t *d){
    if (a->size > 1 && c->size > 1){
        char* ac = karatsuba();
        char* bd = karatsuba();

        char* step3 = karatsuba();
        return string_sum()
    }


    return step3 - ac - bd;
}
