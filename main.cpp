#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define MAX_CAPASITY 1000
#define MAX_SIZE 1000
#define ERRONEOUS_VALUE 666
typedef int tipe_t;



enum Stack_err_t {
    STACK_OK                = 0,
    STACK_MEMORY_ERROR      = 1,  //ошибка выделения памяти
    STACK_INVALID_PTR       = 2,  //неправильный указетель на стек
    STACK_INVALID_CAPACITY  = 3,  // плохой capasity
    STACK_INVALID_SIZE      = 4,  // плохой size
    STACK_CORRUPTED         = 5   //повреждена структура стека
};

struct Stack_t {
    tipe_t *data;  
    ssize_t size;
    ssize_t capasity;
};


Stack_err_t stack_destroy(Stack_t *stk);
Stack_err_t stack_init(Stack_t *stk, tipe_t capasity);
Stack_err_t stack_push(Stack_t *stk, tipe_t valie);
Stack_err_t stack_pop(Stack_t *stk, tipe_t *err);
Stack_err_t stack_verify(Stack_t * stk);
Stack_err_t stack_dump(Stack_t *stk);
void stack_output_err(Stack_err_t err);
void stack_fill_poizon(Stack_t *stk);

int main() {
    Stack_t stk1 = {0};
    tipe_t capasity = 100;
    Stack_err_t err = stack_init(&stk1, capasity);
    if (err != STACK_OK) {
        stack_output_err(err);
    }
    stack_push(&stk1, 10);
    
    tipe_t value = 0; //сюда будет извлечен верхний эл-т стека
    err = stack_pop(&stk1, &value);
    stack_destroy(&stk1);
    printf("%d", value);
    return 0;
}

Stack_err_t stack_pop(Stack_t *stk, tipe_t *value) {
    Stack_err_t err = stack_verify(stk);
    if (err != STACK_OK) {
        stack_dump(stk);
            return err;
    }
    stk -> size--;
    *value = stk -> data[stk -> size - 1];
    stk->data[stk->size - 1] = ERRONEOUS_VALUE; 
    

    err = stack_verify(stk);
    if (err != STACK_OK) {
        stack_dump(stk);
            return err;
    }
    return STACK_OK;
}

Stack_err_t stack_push(Stack_t *stk, tipe_t value) {
    Stack_err_t err = stack_verify(stk);
    if (err != STACK_OK) {
        stack_dump(stk);
            return err;
    }
    stk -> data[stk -> size] = value;
    stk -> size++;

    err = stack_verify(stk);
    if (err != STACK_OK) {
        stack_dump(stk);
            return err;
    }

    return STACK_OK;
}

Stack_err_t stack_init(Stack_t *stk, tipe_t capasity) {

    Stack_err_t err = stack_verify(stk);
    // if (err != STACK_OK) {
    //     stack_dump(stk);
    //         return err;
    // }
    stk -> data = (tipe_t*)calloc((size_t)capasity , sizeof(tipe_t));
    stk -> size = 0;
    stk -> capasity = capasity;

    
    stack_fill_poizon(stk);

    err = stack_verify(stk);
    if (err != STACK_OK) {
        stack_dump(stk);
            return err;
    }
    return STACK_OK;
}

Stack_err_t stack_destroy(Stack_t *stk) {

    Stack_err_t err = stack_verify(stk);
    if (err != STACK_OK) {
        stack_dump(stk);
            return err;
    }
    //stack_fill_poizon(stk);
    free(stk -> data);
    stk -> data = NULL;
    stk -> size = 0;
    stk -> capasity = 0;

    err = stack_verify(stk);
    if (err != STACK_OK) {
        stack_dump(stk);
            return err;
    }
    return STACK_OK;
}

Stack_err_t stack_dump(Stack_t *stk) {
    printf("\n=== STACK DUMP ===\n");
    printf("addres\t= %p\n", stk);
    printf("size\t= %zd\n", stk -> size);
    printf("capasity= %zd\n", stk -> capasity);
    for (ssize_t i = 0; i < stk -> size; i++){
        printf("[%zd] = %d\n", i, stk -> data[i]);

    }
    
    return STACK_OK;

}
Stack_err_t stack_verify(Stack_t * stk) {
    Stack_err_t err = STACK_OK;
    if (stk == NULL)
        err = STACK_INVALID_PTR;
    if (stk -> capasity <= 0 || stk -> capasity > MAX_CAPASITY) 
        err = STACK_INVALID_CAPACITY;
    if (stk -> size < 0) 
        err = STACK_INVALID_SIZE; 
    if (stk -> size > stk -> capasity) 
        err = STACK_CORRUPTED;
    if (stk -> data == NULL) {
        err = STACK_MEMORY_ERROR;
    }
    // if (err != STACK_OK) 
    //     stack_output_err(err);
    return err;
}

void stack_output_err(Stack_err_t err) {
    switch (err) {
        case STACK_OK:
            break;
        case STACK_MEMORY_ERROR:
            printf("ошибка выделения памяти\n");
            break;
        case STACK_INVALID_PTR:
            printf("неверный указатель\n");
            break;
        case STACK_INVALID_CAPACITY:
            printf("ошибка в размере стека\n");
            break;
        case STACK_INVALID_SIZE:
            printf("ошибка в кол-ве элементов стека\n");
            break;
        case STACK_CORRUPTED:
            printf("ошибка в структуре стека, количество элементов больше, чем допустимый размер\n");
            break;
        default:
            printf("ошибка возвращаемого значения");
    }
    return;
}

void stack_fill_poizon(Stack_t *stk) {
    if (stk == NULL || stk->data == NULL) return;
    for (ssize_t i = 0; i < stk -> capasity; i++) {
        stk -> data[i] = ERRONEOUS_VALUE;
    }
}
