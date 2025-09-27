#include <stdio.h>
#include <stdlib.h>

#define MAX_CAPASITY 1000
#define ERRONEOUS_VALUE 666

typedef int tipe_t;

// Перечисление для кодов ошибок стека
enum Stack_err_t {
    STACK_OK = 0,
    STACK_MEMORY_ERROR,
    STACK_INVALID_PTR,
    STACK_INVALID_CAPACITY,
    STACK_INVALID_SIZE,
    STACK_CORRUPTED,
    STACK_UNDERFLOW // Добавлено: стек пуст
};

// Структура стека
typedef struct {
    tipe_t *data;  // Указатель на данные стека
    ssize_t size;     // Текущий размер стека
    ssize_t capasity; // Максимальная емкость стека
} Stack_t;

// Объявления функций (определения ниже)
Stack_err_t stack_init(Stack_t *stk, tipe_t capasity);
Stack_err_t stack_destroy(Stack_t *stk);
Stack_err_t stack_push(Stack_t *stk, tipe_t value);
Stack_err_t stack_pop(Stack_t *stk, tipe_t *value);
Stack_err_t stack_verify(Stack_t *stk);
//void stack_dump(Stack_t *stk); // stack dump не нужен
void stack_output_err(Stack_err_t err);
void stack_fill_poizon(Stack_t *stk);

int main() {
    Stack_t stk1 = {0}; // Инициализируем стек нулями
    tipe_t capasity = 100;
    Stack_err_t err = stack_init(&stk1, capasity); // Инициализация стека
    if (err != STACK_OK) {
        stack_output_err(err);
        return 1; // Выход с кодом ошибки
    }
    stack_push(&stk1, 10); // Добавляем элемент в стек
    tipe_t value;           // Сюда будет извлечен верхний элемент
    err = stack_pop(&stk1, &value);  //Извлекаем элемент
     if (err != STACK_OK) {
        stack_output_err(err);
        return 1; // Выход с кодом ошибки
    }
    printf("%d\n", value);     // Выводим извлеченное значение
    stack_destroy(&stk1); // Уничтожаем стек и освобождаем память
    return 0;
}
//pop

Stack_err_t stack_pop(Stack_t *stk, tipe_t *value) {
    if (stk == NULL) return STACK_INVALID_PTR;
    if (stk->data == NULL) return STACK_MEMORY_ERROR;
    if (stk->size == 0) return STACK_UNDERFLOW; // Если стек пуст
     stk->size--;
    *value = stk->data[stk->size];
    stk->data[stk->size] = ERRONEOUS_VALUE;  // Отравляем освободившуюся ячейку
    return STACK_OK;
}

//push
Stack_err_t stack_push(Stack_t *stk, tipe_t value) {
    if (stk == NULL) return STACK_INVALID_PTR;
    if (stk->data == NULL) return STACK_MEMORY_ERROR;
    if (stk->size >= stk->capasity) return STACK_CORRUPTED;//или можно увеличивать capasity

    stk->data[stk->size] = value;
    stk->size++;
    return STACK_OK;
}
//init
Stack_err_t stack_init(Stack_t *stk, tipe_t capasity) {
    if (stk == NULL) return STACK_INVALID_PTR;

    stk->capasity = capasity;
    stk->size = 0;
    stk->data = (tipe_t*)calloc(capasity , sizeof(tipe_t));
    if (stk->data == NULL) return STACK_MEMORY_ERROR;

 stack_fill_poizon(stk);

    return STACK_OK;
}
//destroy

Stack_err_t stack_destroy(Stack_t *stk) {
    if (stk == NULL) return STACK_INVALID_PTR;
    free(stk->data);
    stk->data = NULL;
    stk->size = 0;
    stk->capasity = 0;

    return STACK_OK;
}
//отравление стека
void stack_fill_poizon(Stack_t *stk) {
     if (stk == NULL || stk->data == NULL) return;
    for (ssize_t i = 0; i < stk->capasity; i++) {
        stk->data[i] = ERRONEOUS_VALUE;
    }
}


void stack_output_err(Stack_err_t err) {
    switch (err) {
        case STACK_OK:             break;
        case STACK_MEMORY_ERROR:   printf("Memory error\n");   break;
        case STACK_INVALID_PTR:    printf("Invalid pointer\n");  break;
        case STACK_INVALID_CAPACITY: printf("Invalid capacity\n"); break;
        case STACK_INVALID_SIZE:   printf("Invalid size\n");  break;
        case STACK_CORRUPTED:      printf("Corrupted stack\n");     break;
        case STACK_UNDERFLOW:      printf("Stack is empty\n");     break;
        default:               printf("Unknown error code\n");
    }
}
