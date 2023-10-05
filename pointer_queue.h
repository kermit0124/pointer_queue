#ifndef __POINTER_QUEUE_H__
#define __POINTER_QUEUE_H__

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    uint8_t *pBufferBase ;
    uint32_t numberOfSlot ;
    uint32_t sizePerItem ;
    uint8_t *pOut ;
    uint8_t *pIn ;
    uint32_t outIndex ;
    uint32_t inIndex ;
    bool empty ;
    bool full ;
} pointer_queue_t ;

typedef enum {
    POINTER_QUEUE_RES_PASS,
    POINTER_QUEUE_RES_FAIL_FULL,
    POINTER_QUEUE_RES_FAIL_EMPTY
} POINTER_QUEUE_RES_ENUM_t ;

void pointerQueue_initial(pointer_queue_t* queue,uint8_t *pBufferBase,uint32_t numberOfSlot,uint32_t sizePerItem) ;
POINTER_QUEUE_RES_ENUM_t pointerQueue_enqueue(pointer_queue_t* queue, uint8_t *pItem) ;
POINTER_QUEUE_RES_ENUM_t pointerQueue_dequeue(pointer_queue_t* queue, uint8_t *pItem) ;

#endif