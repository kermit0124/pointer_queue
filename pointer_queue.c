#include "pointer_queue.h"

void pointerQueue_initial(pointer_queue_t* pPtrQueue,uint8_t *pBufferBase,uint32_t numberOfSlot,uint32_t sizePerItem) {
    pPtrQueue->pBufferBase = pBufferBase ;
    pPtrQueue->numberOfSlot = numberOfSlot ;
    pPtrQueue->sizePerItem = sizePerItem ;
    pPtrQueue->pOut = pBufferBase ;
    pPtrQueue->pIn = pBufferBase ;
    pPtrQueue->outIndex = 0 ;
    pPtrQueue->inIndex = 0 ;
    pPtrQueue->empty = true ;
    pPtrQueue->full = false ;
}

POINTER_QUEUE_RES_ENUM_t pointerQueue_enqueue(pointer_queue_t* pPtrQueue, uint8_t *pItem) {
    if (pPtrQueue->full) {
        return POINTER_QUEUE_RES_FAIL_FULL;
    }

    memcpy(pPtrQueue->pIn,pItem,pPtrQueue->sizePerItem) ;

    uint32_t next = pPtrQueue->inIndex + 1 ;

    if (pPtrQueue->empty == false) {
        if (
            ((next) == pPtrQueue->outIndex)
            || ((next) == (pPtrQueue->outIndex+pPtrQueue->numberOfSlot))
        ) {
            pPtrQueue->full = true ;
        }
    }
    pPtrQueue->empty = false ;

    if (next >= pPtrQueue->numberOfSlot){
        pPtrQueue->inIndex = 0 ;
        pPtrQueue->pIn = pPtrQueue->pBufferBase ;
    }
    else {
        pPtrQueue->inIndex++ ;
        pPtrQueue->pIn += pPtrQueue->sizePerItem ;
    }

    return POINTER_QUEUE_RES_PASS ;
}

POINTER_QUEUE_RES_ENUM_t pointerQueue_dequeue(pointer_queue_t* pPtrQueue, uint8_t *pItem) {
    if (pPtrQueue->empty) {
        return POINTER_QUEUE_RES_FAIL_EMPTY ; 
    }

    memcpy(pItem,pPtrQueue->pOut,pPtrQueue->sizePerItem) ;

    uint32_t next = pPtrQueue->outIndex+1 ;
    
    if (pPtrQueue->full == false) {
        if (
            ((next) == pPtrQueue->inIndex)
            || ((next) == (pPtrQueue->inIndex+pPtrQueue->numberOfSlot))
        ) {
            pPtrQueue->empty = true ;
        }
    }
    pPtrQueue->full = false ;

    if (next >= pPtrQueue->numberOfSlot){
        pPtrQueue->outIndex = 0 ;
        pPtrQueue->pOut = pPtrQueue->pBufferBase ;
    }
    else {
        pPtrQueue->outIndex++ ;
        pPtrQueue->pOut += pPtrQueue->sizePerItem ;
    }

    return POINTER_QUEUE_RES_PASS;
}
