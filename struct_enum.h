#ifndef ENUM_H
#define ENUM_H

#include <math.h>

typedef int type_t;

const type_t CANARY_VALUE = 999;
const type_t POIZON = 666;

enum Stack_err_t {
    NO_ERROR                = 0,
    STACK_MEMORY_ERROR      = 1,  //ошибка выделения памяти
    STACK_INVALID_PTR       = 2,  //неправильный указетель на стек
    STACK_INVALID_CAPACITY  = 3,  //плохой capasity
    STACK_INVALID_SIZE      = 4,  //плохой size
    STACK_CORRUPTED         = 5,  //повреждена структура стека
    CANARY_CORRUPTED        = 6,  //повреждение канарейки
    STACK_POIZON_ERROR      = 7,   //ошибка в заполнении пойзонами 
    OPENFILE_ERROR          = 8    //ошибка открытия файла
};

enum Commands {
    HLT     = 0,
    PUSH    = 1, //добавление эл-та
    ADD     = 2, //сложение
    SUB     = 3, //вычитание
    MUL     = 4, //умножение
    DIV     = 5, //деление
    OUT     = 6, //вывод последнего элемента через pop
    SQRT    = 7, //квадратный корень
    ERROR   = 666  //для ошибки

};

struct Stack_t {
    type_t left_canary;
    type_t *data;  //конорейки для даты
    ssize_t size;
    ssize_t capasity;
    type_t right_canary;
};

#endif //ENUM_H
