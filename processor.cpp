
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <sys/stat.h>

#include "stack_funks.h" 

struct Command_line {
    Commands cmd;   
    int value;               
};

void input_calculate(Stack_t *stk, char * command, type_t *value);
Commands comparing_commands(const char *command);
void stack_calculate (Stack_t *stk, char *command, int value);
Stack_err_t read_commands_data(int *program);

int main() { 
    Stack_t stk1 = {};
    type_t capasity = 10;
    Stack_err_t err = stack_init(&stk1, capasity);
    if (err != NO_ERROR) {
        stack_output_err(err);
    }
    int program[100] = {}; 
    read_commands_data(program);
    // для калькулятора:
    type_t value = 0;
    char command[10] = "";
    input_calculate(&stk1, command, &value);

    stack_dump(&stk1, err);
    //--------------
    stack_destroy(&stk1);
    for (int i = 0; i < sizeof(program)/sizeof(int); i++) {
        printf("%d ", program[i]);
    }
    return 0;
}


void input_calculate(Stack_t *stk, char *command, type_t *value) {
    printf("Введите команду (или 'HLT' для выхода):\n");

    while (1) {
        
        if (scanf("%4s", command) != 1) { 
            printf("Ошибка чтения команды.\n");
            clear_enter(); 
            continue; 
        }

        if (comparing_commands(command) == HLT) {
    
            return; 
        }

        if (comparing_commands(command) == PUSH) {
            if (scanf("%d", value) != 1) {
                printf("Ошибка чтения значения для PUSH.\n");
                clear_enter();
                continue;
            }
        } 
        else {
            *value = 0; // Обнуляем value для не-PUSH команд
        }
        stack_calculate(stk, command, *value);
    } 
}

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


Stack_err_t read_commands_data(int *program) { 

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
