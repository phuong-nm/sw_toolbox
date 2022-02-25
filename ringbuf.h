/**
 * @file    ringbuf.h
 * @author  Phuong Nguyen
 */

#ifndef RINGBUF_INCLUDED
#define RINGBUF_INCLUDED

#include <stdint.h>

typedef struct RINGBUF_Ttag
{
    uint8_t             ucSize;
    uint8_t             ucMask;
    volatile uint8_t    ucFirst;
    volatile uint8_t    ucLast;
} RINGBUF_T;

#define RINGBUF_FIRST(x)                ((x)->ucFirst & (x)->ucMask)
#define RINGBUF_LAST(x)                 ((x)->ucLast  & (x)->ucMask)
#define RINGBUF_REMOVE(x)               ((x)->ucFirst++)
#define RINGBUF_INSERT(x)               ((x)->ucLast ++)
#define RINGBUF_COUNT(x)                ((x)->ucLast  - (x)->ucFirst)
#define RINGBUF_EMPTY(x)                ((x)->ucLast == (x)->ucFirst)
#define RINGBUF_FULL(x)                 ((x)->ucSize <= RINGBUF_COUNT(x))
#define RINGBUF_ITEM_FIRST(x, pool)     ((void * )&(pool)[ RINGBUF_FIRST((x)) ])
#define RINGBUF_ITEM_LAST(x, pool)      ((void * )&(pool)[ RINGBUF_LAST((x))  ])

/* size must be a power of 2. */
#define RINGBUF_INIT(x, size) \
    do { \
        (x)->ucSize  = (size); \
        (x)->ucMask  = (x)->ucSize - 1; \
        (x)->ucFirst = 0; \
        (x)->ucLast  = 0; \
    } while (0)


#endif /* RINGBUF_INCLUDED */
