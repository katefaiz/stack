
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <sys/stat.h>

#include "stack_funks.h" 

struct Processor {
    Stack_t stk;   
    int code[100] = {};
    int counter = 0;
    int regs[10] = {}; // мне регистры создавать как enum или в массив               
};

enum Processor_err {
    NO_ERROR                = 0,
    OPENFILE_ERROR          = 1,
    STACK_ERROR             = 2

};

void input_calculate(Stack_t *stk, char * command, type_t *value);
Commands comparing_commands(const char *command);
void stack_calculate (Stack_t *stk, char *command, int value);
Processor_err asm_commands_data(int *program);
Processor_err disasm_commands_data(int program[]);
Processor_err bite_code_file(int program[], int size);
Processor_err bite_code_read(Processor *processor);




int main() { 
    // Stack_t stk1 = {};
    // type_t capasity = 10;
    // Stack_err_t err = stack_init(&stk1, capasity);
    // if (err != NO_ERROR) {
    //     stack_output_err(err);
    // }

    Processor processor;

    int program[100] = {}; 
    asm_commands_data(program);
    //disasm_commands_data(program);
    // для калькулятора:
    // type_t value = 0;
    // char command[10] = "";
    // input_calculate(&stk1, command, &value);

    // stack_dump(&stk1, err);
    //--------------
    // stack_destroy(&stk1);
    bite_code_file(program, 100);
    bite_code_read(&processor);
    for (int i = 0; i < 50; i++) {
        printf("%d ", processor.code[i]);
    }
}


Processor_err bite_code_file(int program[], int size) { // записывает массив с кодом в файл
    FILE *filestream = fopen("bite_code.txt", "w");
    if (filestream == NULL) {
        printf("Ошибка открытия файла \n");
        return OPENFILE_ERROR;
    }
    
    int i = 0;
    while (i < size && program[i] != 0) {
        fprintf(filestream, "%d ", program[i]);
        i++;
    }
    if (i < size) {
        fprintf(filestream, "%d", program[i]);
    }
    
    fclose(filestream);
    return NO_ERROR;

}

Processor_err bite_code_read(Processor *processor) { //читает файл с кодом и записывает в массив 
    assert(processor != NULL);
    
    FILE* filesteam = fopen("bite_code.txt", "r");
    if (filesteam == NULL) {
        printf("Ошибка: не удалось открыть файл\n");
        return OPENFILE_ERROR;
    }
    
    int count = 0;
    while (count < 100 && fscanf(filesteam, "%d", &processor->code[count]) == 1) {
        count++;
        if (processor->code[count - 1] == 0)
            break;

    }
    
    fclose(filesteam);
    return NO_ERROR;

}


Processor_err asm_commands_data(int *program) { //считывает файл с командами и записывает байт-код в файл 

    assert(program != NULL);

    FILE * filestream = fopen("commands_data.txt", "r");
    if (filestream == NULL) 
        return OPENFILE_ERROR;

    // struct stat st;
    // if (stat("commands_data.txt", &st) == -1) {
    //     fclose(filestream);
    //         OPENFILE_ERROR;    
    // }
    // long fsize = st.st_size;

    char line[100]; // каждая отдельная строка
    int count = 0; //счетчик для массива

    while(fgets(line, sizeof(line), filestream)) {
        char command[5] = {};
        char value_str[50] = {};
        int value = 0;
        int ind = 0;
        //printf("Считана строка: '%s'", line);
        while (line[ind] != ' ' && line[ind] != '\0' && line[ind] != '\n'){
            command[ind] = line[ind]; //копирую команду
            ind++;
        }
        command[ind] = '\0';
        Commands cmd_code = comparing_commands(command);
        program[count++] = cmd_code;
        //printf("\n%d", cmd_code);
        if (cmd_code == PUSH) {
            if (line[ind] == ' ') { //копирую значение
                int value_ind = 0;
                for (int i = ind + 1; line[i] != '\0'; i++) {
                    value_str[value_ind] = line[i];
                    value_ind++;
                }
                value_str[value_ind] = '\0';
                value = atoi(value_str); // TODO: atoi(line + ind + 1)
                program[count++] = value;
                }
        }    
    }
    fclose(filestream);
    return NO_ERROR;
}




Processor_err disasm_commands_data(int program[]) { // проверка ассемблирования
    int index = 0;
    while (program[index] != HLT) {
        switch (program[index]) {
            case 0:
                printf("HLT\n");
                break;
            case 1:
                printf("PUSH %d\n", program[index + 1]);
                index += 2;
                break;
            case 2:
                printf("ADD\n");
                index++;
                break;
            case 3:
                printf("SUB\n");
                index++;
                break;
            case 4:
                printf("MUL\n");
                index++;
                break;
            case 5:
                printf("DIV\n");
                index++;
                break;
            case 6:
                printf("OUT\n");
                index++;
                break;
            case 7:
                printf("SQRT\n");
                index++;
                break;
            case 666:
                printf("ERROR\n");
                index++;
                break;
            default:
                printf("ERROR!!!\n");          
        }      
    }
    return NO_ERROR;
}


// Stack_err_t run_commands_data(int program[]) {
//     Stack_t *stk;

//     for (int i = 0; program[i] != 0; i++) {
//         Commands command = comparing_commands(program[i]);
//         if (program[i] == 1) {
//             stack_calculate(stk, program[i], program[i + 1]);
//             i++;
//         }

//     }


//     return NO_ERROR;
// }



// void input_calculate(Stack_t *stk, char *command, type_t *value) {
//     printf("Введите команду (или 'HLT' для выхода):\n");

//     while (1) {
        
//         if (scanf("%4s", command) != 1) { 
//             printf("Ошибка чтения команды.\n");
//             clear_enter(); 
//             continue; 
//         }

//         if (comparing_commands(command) == HLT) {
    
//             return; 
//         }

//         if (comparing_commands(command) == PUSH) {
//             if (scanf("%d", value) != 1) {
//                 printf("Ошибка чтения значения для PUSH.\n");
//                 clear_enter();
//                 continue;
//             }
//         } 
//         else {
//             *value = 0; // Обнуляем value для не-PUSH команд
//         }
//         stack_calculate(stk, command, *value);
//     } 
// }

Commands comparing_commands(const char *command) { 

    if (strcmp(command, "PUSH") == 0)   
        return PUSH;
    if (strcmp(command, "ADD") == 0)    
        return ADD;
    if (strcmp(command, "SUB") == 0)    
        return SUB;
    if (strcmp(command, "MUL") == 0)    
        return MUL;
    if (strcmp(command, "DIV") == 0)    
        return DIV;
    if (strcmp(command, "OUT") == 0)    
        return OUT;
    if (strcmp(command, "HLT") == 0)    
        return HLT;
    if (strcmp(command, "SQRT") == 0)   
        return SQRT;
    else                                
        return ERROR;
}

void stack_calculate (Stack_t *stk, char* command, int value) { 

    switch (comparing_commands(command)) {
        case  PUSH: {
           // int value = 0;//todo надо будет считать из массива 
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
            stack_push(stk, val2 / val1); 
            break;
        }
        case OUT: {
            type_t val = 0;
            stack_pop(stk, &val);
            printf("%d", val);
            break;
        }
        case HLT: 
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

