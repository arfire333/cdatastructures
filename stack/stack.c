#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>

const uint64_t DEFAULT_MAX_STACK_SIZE=10;

#define STACK_NAME(type,name) type##name
#define DEFINE_STACK(type) \
typedef struct STACK_NAME(type,_stack_t) STACK_NAME(type,_stack_t);\
struct STACK_NAME(type,_stack_t) { \
    type *data; \
    uint64_t size; \
    uint64_t max_size; \
};\
\
STACK_NAME(type,_stack_t) *STACK_NAME(type,_stack_create)(){ \
    STACK_NAME(type,_stack_t) *stack=calloc(1,sizeof(STACK_NAME(type,_stack_t)));\
    if( stack == NULL ){ \
        return NULL; \
    }\
    stack->data=calloc(DEFAULT_MAX_STACK_SIZE,sizeof(type));\
    if( stack->data == NULL ){\
        free( stack );\
        return NULL;\
    }\
    stack->size=0;\
    stack->max_size=DEFAULT_MAX_STACK_SIZE;\
    return stack;\
} \
\
int STACK_NAME(type,_stack_resize)(STACK_NAME(type,_stack_t) *stack, uint64_t new_max_size){\
    if( new_max_size < stack->size ){\
        errno = EPERM; \
        return -1;\
    }\
    type *new_data = reallocarray(stack->data, new_max_size, sizeof(type));\
    if( new_data ){\
        stack->data = new_data;\
        stack->max_size = new_max_size;\
        return 0;\
    }\
    return -1;\
};\
\
int STACK_NAME(type,_stack_push)(STACK_NAME(type,_stack_t) *stack, type val){\
    int result=0;\
    if( stack->size >= stack->max_size ){\
        if( STACK_NAME(type,_stack_resize)(stack, 2*stack->max_size )){\
            return -1;\
        };\
    }\
    stack->data[stack->size++] = val;\
    return 0;\
};\
\
type STACK_NAME(type,_stack_pop)(STACK_NAME(type,_stack_t) *stack){\
    if( stack->size > 0 ){\
        errno=0;\
        return stack->data[--stack->size];\
    }\
    errno = EDOM; \
    return 0;\
};

DEFINE_STACK(int)
DEFINE_STACK(float)

int main(int argc, char *argv[]){
    printf("Prepare to stack!\n");    
    int_stack_t *si=int_stack_create();
    float_stack_t *sf=float_stack_create();

    int_stack_push(si,42);
    int_stack_push(si,21);
    float_stack_push(sf,42.1);
    float_stack_push(sf,21.4);
    while(si->size){
        printf("Popped: %d\n", int_stack_pop(si));
    }
    while(sf->size){
        printf("Popped: %3.2f\n", float_stack_pop(sf));
    }

    return 0;
}