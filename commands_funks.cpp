#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "processor_struct_enum.h"
#include "stack_check.h"
#include "stack_funks.h"

Processor_err processor_HLT(Processor *processor);
Processor_err processor_PUSH(Processor *processor); 
Processor_err processor_ADD(Processor *processor);
Processor_err processor_SUB(Processor *processor);
Processor_err processor_MUL(Processor *processor);
Processor_err processor_DIV(Processor *processor);
Processor_err processor_SQRT(Processor *processor);
Processor_err processor_OUT(Processor *processor);


Processor_err processor_HLT(Processor *processor) {
    printf("Конец\n");
    stack_destroy(&processor->stk); 
    return NO_ERROR;
}
Processor_err processor_PUSH(Processor *processor) {
    //processor->counter++; // переходим к значению
    int value = processor->code[processor->counter + 1];
    
    Stack_err_t err = stack_push(&processor->stk, value);
    if (err != STACK_NO_ERROR) {
        
        stack_dump(&processor->stk, err);
        stack_destroy(&processor->stk);
        return STACK_ERROR;
    }
    printf("PUSH: добавлено значение %d\n", value); // отладочный вывод
    return NO_ERROR;

}

Processor_err processor_ADD(Processor *processor) {
    type_t val1 = 0, val2 = 0;
    stack_pop(&processor->stk, &val1);
    stack_pop(&processor->stk, &val2);
    stack_push(&processor->stk, val1 + val2);
    return NO_ERROR;
    
}

Processor_err processor_SUB(Processor *processor) {
    type_t val1 = 0, val2 = 0;
    stack_pop(&processor->stk, &val1);
    stack_pop(&processor->stk, &val2);
    stack_push(&processor->stk, val2 - val1);
    return NO_ERROR;
    
}

Processor_err processor_MUL(Processor *processor) {
    type_t val1 = 0, val2 = 0;
    stack_pop(&processor->stk, &val1);
    stack_pop(&processor->stk, &val2);
    stack_push(&processor->stk, val1 * val2);
    return NO_ERROR;

}

Processor_err processor_DIV(Processor *processor) {
    type_t val1 = 0, val2 = 0;
    stack_pop(&processor->stk, &val1);
    stack_pop(&processor->stk, &val2);
    if (val2 == 0) {
        printf("Ошибка: деление на ноль\n");
        stack_destroy(&processor->stk);
        return STACK_ERROR;
    }
    stack_push(&processor->stk, val2 / val1);
    return NO_ERROR;
}

Processor_err processor_SQRT(Processor *processor) {
    type_t val = 0;
    stack_pop(&processor->stk, &val);
    if (val < 0) {
        printf("Ошибка: корень из отрицательного числа\n");
        stack_destroy(&processor->stk);
        return STACK_ERROR;
    }
    stack_push(&processor->stk, (type_t)sqrt(val));
    return NO_ERROR;

}

Processor_err processor_OUT(Processor *processor) {
    type_t val = 0;
    stack_pop(&processor->stk, &val);
    printf("OUT: %d\n", val);
    return NO_ERROR;

}




