#include "assignment1_lib.h"

void karatsuba_init(karatsuba_string_t *s)
{
    s->value = malloc((MAX_DIGIT_NUMBER + 1) * sizeof(char));
    s->digits = 0;
}

void karatsuba_deinit(karatsuba_string_t *s)
{
    free(s->value);
}

void format(karatsuba_string_t *r)
{
    r->value[r->digits] = 0;
    inplace_reverse(r->value);
}

void inplace_reverse(char *str)
{
    if (str)
    {
        char *end = str + strlen(str) - 1;

        // swap the values in the two given variables
        // XXX: fails when a and b refer to same memory location
#define XOR_SWAP(a, b) \
    do                 \
    {                  \
        a ^= b;        \
        b ^= a;        \
        a ^= b;        \
    } while (0)

        // walk inwards from both ends of the string,
        // swapping until we get to the middle
        while (str < end)
        {
            XOR_SWAP(*str, *end);
            str++;
            end--;
        }
#undef XOR_SWAP
    }
}

void get_input(karatsuba_string_t *s)
{
    printf("Enter number: ");
    s->value = malloc((MAX_DIGIT_NUMBER + 1) * sizeof(char));
    scanf("%s", s->value);
    inplace_reverse(s->value);
    s->digits = (int)strlen(s->value);
}

long power(int x, unsigned n)
{
    // Initialize result to 1
    long long pow = 1;

    // Multiply x for n times
    for (int i = 0; i < n; i++) {
        pow = pow * x;
    }

    return pow;
}

uint32_t value(karatsuba_string_t *s)
{
    //DPRINT("line %d - value - input %s\n", __LINE__, s->value);
    uint32_t val = 0;
    if (s->digits > 31)
        return -1;
    for (int i = 0; i < s->digits; i++){
        val += (s->value[i] - '0') * power(10,i);
        //DPRINT("line %d - value - val = %u\n", __LINE__, val);
    }
    return val;
}

void string(uint32_t n, karatsuba_string_t *s)
{
    uint32_t i = 0;
    do
    {
        s->value[i++] = n % 10 + '0';
        n = n / 10;
    } while (n > 0);

    s->digits = i;
    s->value[s->digits] = 0;
}

void multiply(karatsuba_string_t *x, karatsuba_string_t *y, karatsuba_string_t *res)
{
    karatsuba_string_t a, b, c, d, a_plus_b, c_plus_d, step1, step2, step3, step4;
    int n;

    n = MAX(y->digits, x->digits);

    DPRINT("line %d - multiply - n = %d\n", __LINE__, n);

    // allocazione degli array per contenere i char
    a.value = malloc(n * sizeof(char));
    b.value = malloc(n * sizeof(char));
    c.value = malloc(n * sizeof(char));
    d.value = malloc(n * sizeof(char));
    a_plus_b.value = malloc(n * sizeof(char));
    c_plus_d.value = malloc(n * sizeof(char));
    step1.value = malloc(n * sizeof(char));
    step2.value = malloc(n * sizeof(char));
    step3.value = malloc(n * sizeof(char));
    step4.value = malloc(n * sizeof(char));

    b.digits = x->digits >> 1;
    a.digits = x->digits - (x->digits >> 1);
    d.digits = y->digits >> 1;
    c.digits = y->digits - (y->digits >> 1);

    memcpy(a.value, x->value + b.digits, a.digits);
    memcpy(b.value, x->value, b.digits);
    memcpy(c.value, y->value + d.digits, c.digits);
    memcpy(d.value, y->value, d.digits);

    b.value[b.digits] = 0;
    a.value[a.digits] = 0;
    d.value[d.digits] = 0;
    c.value[c.digits] = 0;

    add(&a, &b, &a_plus_b);
    add(&c, &d, &c_plus_d);

    DPRINT("line %d - multiply - value(&a) = %d\n", __LINE__, value(&a));
    DPRINT("line %d - multiply - value(&b) = %d\n", __LINE__, value(&b));
    DPRINT("line %d - multiply - value(&c) = %d\n", __LINE__, value(&c));
    DPRINT("line %d - multiply - value(&d) = %d\n", __LINE__, value(&d));
    DPRINT("line %d - multiply - value(&a_plus_b) = %d\n", __LINE__, value(&a_plus_b));
    DPRINT("line %d - multiply - value(&c_plus_d) = %d\n", __LINE__, value(&c_plus_d));
    if (n <= 2)
    {
        string(value(&a) * value(&c), &step1);
        string(value(&b) * value(&d), &step2);
        string(value(&a_plus_b) * value(&c_plus_d), &step3);
    }
    else
    {
        multiply(&a, &c, &step1);
        multiply(&b, &d, &step2);
        multiply(&a_plus_b, &c_plus_d, &step3);
    }

    DPRINT("line %d - multiply - step3 (%d * %d)= %d\n", __LINE__, value(&c_plus_d), value(&a_plus_b), value(&step3));

    sub(&step3, &step2, &step4);
    sub(&step4, &step1, &step4);

    // implement step5
    compose(&step1, &step2, &step4, res, n);

    free(a_plus_b.value);
    free(c_plus_d.value);
    free(step1.value);
    free(step2.value);
    free(step3.value);
    free(step4.value);
    return;
}

void sub(karatsuba_string_t *x, karatsuba_string_t *y, karatsuba_string_t *z)
{
    DPRINT("line %d - subtract - inputs (reverse) = %s, %s\n", __LINE__, x->value, y->value);

    int N, n, res, rep;
    n = MIN(x->digits, y->digits);
    N = MAX(x->digits, y->digits);
    rep = 0;

    for (int i = 0; i < n; i++)
    {
        res = 10 + (x->value[i] - '0') - (y->value[i] - '0') - rep;
        rep = 1 - (res / 10);
        z->value[i] = '0' + res % 10;
    }

    while (n < N)
    {
        res = 10 + (x->value[n] - '0') - rep;
        rep = 1 - (res / 10);
        z->value[n++] = '0' + res % 10;
    }

    z->value[N] = 0;
    z->digits = N;

    DPRINT("line %d - subtract - result (reverse) = %s\n", __LINE__, z->value);
}

void add(karatsuba_string_t *x, karatsuba_string_t *y, karatsuba_string_t *z)
{
    DPRINT("line %d - add - inputs (reverse) = %s, %s\n", __LINE__, x->value, y->value);

    int N, n, res, rep;
    n = MIN(x->digits, y->digits);
    N = MAX(x->digits, y->digits);
    rep = 0;

    for (int i = 0; i < n; i++)
    {
        res = (x->value[i] - '0') + (y->value[i] - '0') + rep;
        rep = (res / 10);
        z->value[i] = '0' + res % 10;
    }

    while (n < N)
    {
        res = (( x->digits > y->digits ? x->value[n] : y->value[n]) - '0') + rep;
        rep = ((res%20) / 10);
        z->value[n++] = '0' + res % 10;
    }

    if (rep == 1){
        z->value[n++] = '1';
        N++;

    }

    z->value[N] = 0;
    z->digits = N;

    DPRINT("line %d - add - result (reverse) = %s\n", __LINE__, z->value);

}


void compose(karatsuba_string_t *s1, karatsuba_string_t *s2, karatsuba_string_t *s4, karatsuba_string_t *result, int n)
{
    char *p1, *p4, *pr;
    int p1_size, p4_size, pr_size, n_half;

    DPRINT("line %d - compose - s1.value (reverse) = %s\n", __LINE__, s1->value);
    DPRINT("line %d - compose - s4.value (reverse) = %s\n", __LINE__, s4->value);
    DPRINT("line %d - compose - s2.value (reverse) = %s\n", __LINE__, s2->value);

    n_half = n / 2;
    p1_size = (1 + n + s1->digits) * sizeof(char);
    p4_size = (1 + n_half + s4->digits) * sizeof(char);
    pr_size = (1 + n + 1 + MAX_DIGIT_NUMBER) * sizeof(char);

    p1 = malloc(p1_size);
    p4 = malloc(p4_size);
    pr = malloc(pr_size);

    DPRINT("line %d - compose - n = %d\n", __LINE__, n);

    memset(p1, '0', n);
    memcpy(p1 + n, s1->value, s1->digits);
    p1[p1_size] = 0;

    DPRINT("line %d - compose - p1 (reverse) = %s\n", __LINE__, p1);

    memset(p4, '0', n_half);
    memcpy(p4 + n_half, s4->value, s4->digits);
    p4[p4_size-1] = 0;

    result->value = pr;

    DPRINT("line %d - compose - p4 (reverse) = %s\n", __LINE__, p4);

    free(s1->value);
    free(s4->value);

    s1->value = p1;
    s1->digits = p1_size-1;
    s4->value = p4;
    s4->digits = p4_size-1;

    add(s1, s4, result);
    DPRINT("line %d - compose - reverse result partial = %s\n", __LINE__, result->value);

    add(result, s2, result);
    DPRINT("line %d - compose - reverse result total = %s\n", __LINE__, result->value);

}
