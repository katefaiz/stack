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
    STACK_MEMORY_ERROR      = 1, //ошибка выделения памяти
    STACK_INVALID_PTR       = 2, //неправильный указетель на стек
    STACK_INVALID_CAPACITY  = 3, // ошибка в размере стека
    STACK_INVALID_SIZE      = 4,
    STACK_CORRUPTED         = 5 //повреждена структура стека
};

struct Stack_t {
    tipe_t data[MAX_SIZE];  
    ssize_t size;
    ssize_t capasity;
};


Stack_err_t stack_destroy(Stack_t *stk);
Stack_err_t stack_init(Stack_t *stk, tipe_t capasity);
Stack_err_t stack_push(Stack_t *stk, tipe_t valie);
Stack_err_t stack_pop(Stack_t *stk, tipe_t *err);
Stack_err_t stack_verify(Stack_t * stk);
void stack_dump(Stack_t *stk);
void stack_output_err(Stack_err_t err);

int main() {
    Stack_t stk1 = {};
    tipe_t capasity = 100;
    stack_init(&stk1, capasity);
    stack_push(&stk1, 10);
    int err = 0;
    tipe_t value = 0; //сюда будет извлечен верхний эл-т стека
    int element = stack_pop(&stk1, &value);
    stack_destroy(&stk1);

    return 0;
}
Stack_err_t stack_pop(Stack_t *stk, tipe_t *value) {

    /*if (err != NULL)
        *err = ERRONEOUS_VALUE;*/
    *value = stk -> data[stk -> size - 1];
    stk -> size--;
    return STACK_OK;
}

Stack_err_t stack_push(Stack_t *stk, tipe_t value) {
    Stack_err_t err = stack_verify(stk);
    /*if (err)
    stack_dump(stk);
        return err;*/
    stk -> data[stk -> size] = value;
    stk -> size++;
    return STACK_OK;
}

Stack_err_t stack_init(Stack_t *stk, tipe_t capasity) {
    if (stk == NULL) {
        stack_dump(stk);
    }
    
    stk -> data = (tipe_t*)calloc((size_t)stk -> capasity , sizeof(tipe_t));
    stk -> size = 0;
    stk -> capasity = capasity;

    return STACK_OK;
}

Stack_err_t stack_destroy(Stack_t *stk) {

    free(stk -> data);
    stk -> data = NULL;
    stk -> size = ERRONEOUS_VALUE;
    stk -> capasity = ERRONEOUS_VALUE;

    return STACK_OK;
}

void stack_dump(Stack_t *stk) {
    printf("\n=== STACK DUMP ===\n");
    printf("%p", stk);
    printf("size\t=%zd", stk -> size);
    printf("capasity\t=%zd", stk -> capasity);
    for (ssize_t i = 0; i < stk -> size; i++){
        printf("[%zd] = %d\n", i, stk -> data[i]);

    }

    return;

}
Stack_err_t stack_verify(Stack_t * stk) {
    Stack_err_t err = STACK_OK;
    if (stk == NULL)
        err = STACK_INVALID_PTR;

    if (stk -> capasity <= 0 || stk -> capasity > MAX_CAPASITY) 
        err = STACK_INVALID_CAPACITY;
    if (stk -> size <= 0) 
        err = STACK_INVALID_SIZE;
    
    if (stk -> size > stk -> capasity) 
        err = STACK_CORRUPTED;
    if (stk -> data == NULL) {
        err = STACK_MEMORY_ERROR;
    }
    stack_output_err(err);
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
