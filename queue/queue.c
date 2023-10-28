#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

const uint64_t DEFAULT_MAX_QUEUE_SIZE=5;

#define QUEUE_NAME(type,name) type##name
#define DEFINE_QUEUE(type) \
typedef struct QUEUE_NAME(type,_queue_t) QUEUE_NAME(type,_queue_t);\
struct QUEUE_NAME(type,_queue_t) { \
    type *data; \
    uint64_t front; \
    uint64_t back; \
    uint64_t size; \
    uint64_t max_size; \
};\
\
QUEUE_NAME(type,_queue_t) *QUEUE_NAME(type,_queue_create)(){ \
    QUEUE_NAME(type,_queue_t) *queue=(QUEUE_NAME(type,_queue_t)*)calloc(1,sizeof(QUEUE_NAME(type,_queue_t)));\
    if( queue == NULL ){ \
        return NULL; \
    }\
    queue->data=(type *)calloc(DEFAULT_MAX_QUEUE_SIZE,sizeof(type));\
    if( queue->data == NULL ){\
        free(queue);\
        return NULL;\
    }\
    queue->front=0;\
    queue->back=-1;\
    queue->size=0;\
    queue->max_size=DEFAULT_MAX_QUEUE_SIZE;\
    return queue;\
} \
\
void QUEUE_NAME(type,_queue_destroy)(QUEUE_NAME(type,_queue_t) *queue){\
    free(queue->data);\
    free(queue);\
}\
\
int QUEUE_NAME(type,_queue_resize)(QUEUE_NAME(type,_queue_t) *queue, uint64_t new_max_size){\
    if( new_max_size < queue->max_size ){\
        errno = EPERM; \
        return -1;\
    }\
    type *new_data = (type *)realloc(queue->data, new_max_size * sizeof(type));\
    if( new_data ){\
        queue->data = new_data;\
        if( queue->front > queue->back){\
            uint8_t delta_size = new_max_size - queue->max_size;\
            memmove(&queue->data[queue->front+delta_size],&queue->data[queue->front],(queue->max_size-queue->front)*sizeof(type));\
            queue->front += delta_size;\
        }\
        queue->max_size = new_max_size;\
        return 0;\
    }\
    return -1;\
};\
\
int QUEUE_NAME(type,_queue_push)(QUEUE_NAME(type,_queue_t) *queue, type val){\
    int result=0;\
    if( queue->size==0){\
        queue->front=0;\
        queue->back=-1;\
    }\
    if( queue->size >= queue->max_size ){\
        if( QUEUE_NAME(type,_queue_resize)(queue, 2*queue->max_size )){\
            return -1;\
        };\
    }\
    queue->back=(queue->back+1)%queue->max_size;\
    queue->data[queue->back] = val;\
    queue->size++;\
    return 0;\
};\
\
type QUEUE_NAME(type,_queue_pop)(QUEUE_NAME(type,_queue_t) *queue){\
    if( queue->size > 0 ){\
        errno=0;\
        type *result=&queue->data[queue->front++];\
        queue->front=queue->front % queue->max_size;\
        queue->size--;\
        return *result;\
    }\
    errno = EDOM; \
    return 0;\
};

#ifndef EXCLUDE_MAIN
DEFINE_QUEUE(int)
DEFINE_QUEUE(float)

int main(int argc, char *argv[]){
    printf("Prepare to queue!\n");    
    int_queue_t *si=int_queue_create();
    float_queue_t *sf=float_queue_create();

    int_queue_push(si,2);
    int_queue_push(si,3);
    int_queue_push(si,4);
    int_queue_pop(si);
    int_queue_push(si,5);
    int_queue_push(si,6);
    int_queue_push(si,7);
    float_queue_push(sf,42.1);
    float_queue_push(sf,21.4);
    while(si->size){
        printf("Popped: %d\n", int_queue_pop(si));
    }
    while(sf->size){
        printf("Popped: %3.2f\n", float_queue_pop(sf));
    }
    
    int_queue_push(si,42);
    float_queue_push(sf,42.1);

    int_queue_destroy(si);
    float_queue_destroy(sf);
    return 0;
}
#endif