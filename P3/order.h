#ifndef ORDER_H
#define ORDER_H


/* Reorders the pointed-to values such that *a <= *b. */
void ascending2(int* a, int* b);

/* Reorders the pointed-to values such that *a <= *b <= *c. */
void ascending3(int* a, int* b, int* c);

/* Reorders the pointed-to values such that *a >= *b. */
void descending2(int* a, int* b);

/* Reorders the pointed-to values such that *a >= *b >= *c. */
void descending3(int* a, int* b, int* c);


#endif
