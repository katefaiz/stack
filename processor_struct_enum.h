#ifndef ENUMPR_H
#define ENUMPR_H

#include "stack_funks.h" 


struct Processor {
    Stack_t stk;   
    int code[50] = {};
    int counter = 0; //текщая команда
    int regs[4] = {}; // мне регистры создавать как enum или в массив               
};

enum Processor_err {
    NO_ERROR                = 0,
    OPENFILE_ERROR          = 1,
    STACK_ERROR             = 2

};

enum Registers { //это надо вообще??? или просто массив с регистрами 
    RAX = 10,
    RBX = 11,
    RCX = 12,
    RDX = 13
};//структура регистров, где будет enum и имя
//todo processor_destroy


#endif //ENUMPR_H