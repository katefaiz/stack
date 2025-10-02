
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "struct_enum.h"
#include "stack_check.h"
#include "stack_funks.h"

Stack_err_t stack_pop(Stack_t *stk, type_t *value) {
    Stack_err_t err = stack_verify(stk);
    if (err != STACK_OK) {
        stack_dump(stk, err);
            return err;
    }
    if (stk -> size == 0) {
        printf("Нельзя удалить элемент из пустого стека\n");
        return STACK_INVALID_SIZE;  
    }
    *value = (stk -> data[stk -> size - 1]);
    stk -> data[stk -> size - 1] = POIZON;
    stk -> size--; 
    

    err = stack_verify(stk);
    if (err != STACK_OK) {
        stack_dump(stk, err);
            return err;
    }
    return STACK_OK;
}

Stack_err_t stack_push(Stack_t *stk, type_t value) {
    Stack_err_t err = stack_verify(stk);
    if (err != STACK_OK) {
        stack_dump(stk, err);
            return err;
    }
    if (stk -> size >= stk -> capasity) {
        ssize_t new_capasity = stk -> capasity * 2;
        type_t* new_data = (type_t*)realloc(stk -> data, (size_t)new_capasity * sizeof(type_t)); 
        
        if (new_data == NULL) {
            printf("Не сработал realloc\n");
            return STACK_MEMORY_ERROR;
        }
                
        stk -> data = new_data;
        stk -> capasity = new_capasity;
        stack_fill_poizon(stk);
    }
    

    stk -> data[stk -> size] = value * 1000;
    stk -> size++;

    err = stack_verify(stk);
    if (err != STACK_OK) {
        stack_dump(stk, err);
            return err;
    }

    return STACK_OK;
}

Stack_err_t stack_init(Stack_t *stk, type_t capasity) {
    assert(stk != NULL);

    stk -> left_canary = CANARY_VALUE;
    stk -> right_canary = CANARY_VALUE;

    stk->data = NULL;
    stk -> data = (type_t*)calloc((size_t)capasity , sizeof(type_t));
   
    stk -> size = 0;
    stk -> capasity = capasity;
    stack_fill_poizon(stk);

    Stack_err_t err = stack_verify(stk);
    if (err != STACK_OK) {
        stack_dump(stk, err);
            return err;
    }
    return STACK_OK;
}

Stack_err_t stack_destroy(Stack_t *stk) {

    Stack_err_t err = stack_verify(stk);
    if (err != STACK_OK) {
        stack_dump(stk, err);
            return err;
    }
    
    free(stk -> data);
    
    stk -> data = NULL;
    stk -> size = 0;
    stk -> capasity = 0;

    return STACK_OK;
}
