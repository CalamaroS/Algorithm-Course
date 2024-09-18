#ifndef __ASSIGNMENT_1_H__
#define __ASSIGNMENT_1_H__


#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#define MAX_DIGIT_NUMBER 64
#define MAX(a, b) ((a >= b) ? a : b)
#define MIN(a, b) ((a <= b) ? a : b)

#define DEBUG

#ifdef DEBUG
#define DPRINT printf
#else
#define DPRINT(...)
#endif

typedef struct karatsuba_string_s
{
    char *value;
    int digits;
} karatsuba_string_t;

void get_input(karatsuba_string_t *);

void multiply(karatsuba_string_t *, karatsuba_string_t *, karatsuba_string_t *);

void add(karatsuba_string_t *, karatsuba_string_t *, karatsuba_string_t *);

void sub(karatsuba_string_t *, karatsuba_string_t *, karatsuba_string_t *);

void compose(karatsuba_string_t *, karatsuba_string_t *, karatsuba_string_t *, karatsuba_string_t *, int n);

uint32_t value(karatsuba_string_t *);

void inplace_reverse(char *);

void format(karatsuba_string_t *r);

void karatsuba_init(karatsuba_string_t *);

void karatsuba_deinit(karatsuba_string_t *);

long power(int x, unsigned n);


#endif
