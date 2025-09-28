#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define MAX_CAPASITY 1000
#define MAX_SIZE 1000
#define ERRONEOUS_VALUE 666
typedef int type_t;



enum Stack_err_t {
    STACK_OK                = 0,
    STACK_MEMORY_ERROR      = 1,  //ошибка выделения памяти
    STACK_INVALID_PTR       = 2,  //неправильный указетель на стек
    STACK_INVALID_CAPACITY  = 3,  //плохой capasity
    STACK_INVALID_SIZE      = 4,  //плохой size
    STACK_CORRUPTED         = 5   //повреждена структура стека
};

enum Commands {
    PUSH    = 0, //добавление эл-та
    ADD     = 1, //сложение
    SUB     = 2, //вычитание
    MUL     = 3, //умножение
    DIV     = 4, //деление
    OUT     = 5, //вывод последнего элемента через pop
    HTL     = 6, //выход из цикла ???
    SQRT    = 7, //квадратный корень
    ERROR   = 8  //для ошибки

};

struct Stack_t {
    type_t *data;  
    ssize_t size;
    ssize_t capasity;
};


Stack_err_t stack_destroy(Stack_t *stk);
Stack_err_t stack_init(Stack_t *stk, type_t capasity);
Stack_err_t stack_push(Stack_t *stk, type_t valie);    
Stack_err_t stack_pop(Stack_t *stk, type_t *err);
Stack_err_t stack_verify(Stack_t * stk);
Stack_err_t stack_dump(Stack_t *stk);
void stack_output_err(Stack_err_t err);
void stack_fill_poizon(Stack_t *stk);
void clear_enter (void);
void input_calculate(Stack_t *stk, char * command, type_t *value);
Commands comparing_commands(char *command);
void stack_calculate (Stack_t *stk, char *command, int value);

int main() { 
    Stack_t stk1 = {0};
    type_t capasity = 10;
    Stack_err_t err = stack_init(&stk1, capasity);
    if (err != STACK_OK) {
        stack_output_err(err);
    }
    //stack_push(&stk1, 10);
    
    // type_t value_pop = 0; //сюда будет извлечен верхний эл-т стека
    // err = stack_pop(&stk1, &value_pop);

    // для калькулятора:
    char command[7];
    type_t value = 0;
    input_calculate(&stk1, command, &value);
    stack_dump(&stk1);
    //--------------
    stack_destroy(&stk1);
    printf("%d\n", value);
    return 0;
}

Stack_err_t stack_pop(Stack_t *stk, type_t *value) {
    Stack_err_t err = stack_verify(stk);
    if (err != STACK_OK) {
        stack_dump(stk);
            return err;
    }
    *value = stk -> data[stk -> size - 1];
    stk->data[stk->size - 1] = ERRONEOUS_VALUE; 
    stk -> size--; 
    

    err = stack_verify(stk);
    if (err != STACK_OK) {
        stack_dump(stk);
            return err;
    }
    return STACK_OK;
}

Stack_err_t stack_push(Stack_t *stk, type_t value) {
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

Stack_err_t stack_init(Stack_t *stk, type_t capasity) {

    Stack_err_t err = stack_verify(stk);
    // if (err != STACK_OK) {
    //     stack_dump(stk);
    //         return err;
    // }
    stk -> data = (type_t*)calloc((size_t)capasity , sizeof(type_t));
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
        printf("*[%zd] = %d\n", i, stk -> data[i]);
    }
    for (ssize_t i = stk -> size; i < stk -> capasity; i++) {
        printf("[%zd] = %d (poizon)\n", i, stk -> data[i]);
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

    for (ssize_t i = 0; i < stk -> capasity; i++) { //как лучше, сразу заполнить мусором, или заполнять мусором ячейки от size до capasity
        stk -> data[i] = ERRONEOUS_VALUE;
    }
}

void clear_enter (void) { 
    int ch = NAN;
    while ((ch = getchar( )) != EOF && ch  != '\n')
        ;
}

void input_calculate(Stack_t *stk, char *command, type_t *value) {
    printf("Введите команду (или 'QUIT' для выхода):\n");
    while (1) {
        
        if (scanf("%4s", command) != 1) { 
            printf("Ошибка чтения команды.\n");
            clear_enter(); 
            continue; 
        }

        if (comparing_commands(command) == HTL) {
            //printf("Завершение ввода команд.\n");
            return; 
        }

        if (comparing_commands(command) == PUSH) {
            if (scanf("%d", value) != 1) {
                printf("Ошибка чтения значения для PUSH.\n");
                clear_enter();
                continue;
            }
        } else {
            *value = 0; // Обнуляем value для не-PUSH команд
        }
        stack_calculate(stk, command, *value);
    }
    
    
}


Commands comparing_commands(char *command) {

    if (strcmp(command, "PUSH") == 0)   return PUSH;
    if (strcmp(command, "ADD") == 0)    return ADD;
    if (strcmp(command, "SUB") == 0)    return SUB;
    if (strcmp(command, "MUL") == 0)    return MUL;
    if (strcmp(command, "DIV") == 0)    return DIV;
    if (strcmp(command, "OUT") == 0)    return OUT;
    if (strcmp(command, "HTL") == 0)    return HTL;
    if (strcmp(command, "SQRT") == 0)   return SQRT;
    else                                    return ERROR;
}

void stack_calculate (Stack_t *stk, char* command, int value) {

    switch (comparing_commands(command)) {
        case  PUSH: {
            stack_push(stk, value);
            break;
        }
        case  ADD: {
            type_t val1 = 0;
            stack_pop(stk, &val1);
            type_t val2 = 0;
            stack_pop(stk, &val2);
            stack_push(stk, val1 + val2);
            break;
        }
        case SUB: {
            type_t val1 = 0;
            stack_pop(stk, &val1);
            type_t val2 = 0;
            stack_pop(stk, &val2);
            stack_push(stk, val1 - val2);
            break;
        }
        case MUL: {
            type_t val1 = 0;
            stack_pop(stk, &val1);
            type_t val2 = 0;
            stack_pop(stk, &val2);
            stack_push(stk, val1 * val2);
            break;
        }   
        case DIV: {
            type_t val1 = 0;
            stack_pop(stk, &val1);
            type_t val2 = 0;
            stack_pop(stk, &val2);
            stack_push(stk, val1 / val2); // проблема, что 2 аргумент должен быть интом, а это не гаранируется
            break;
        }
        case OUT: {
            type_t val = 0;
            stack_pop(stk, &val);
            printf("%d", val);
            break;
        }
        case HTL: // зачем это вообще???
            break;
        case SQRT: {
            type_t val = 0;
            stack_pop(stk, &val);
            val = sqrtf(val);
            stack_push(stk, val);
            break;
        }
        case ERROR:
            break;
        default:
            printf("Команда не распознана, введите еще раз\n");
    }
}
