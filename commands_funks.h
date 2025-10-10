#ifndef CF_H
#define CF_H

#include "stack_funks.h" 
#include "processor_struct_enum.h"


Processor_err processor_HLT(Processor *processor);
Processor_err processor_PUSH(Processor *processor); 
Processor_err processor_ADD(Processor *processor);
Processor_err processor_SUB(Processor *processor);
Processor_err processor_MUL(Processor *processor);
Processor_err processor_DIV(Processor *processor);
Processor_err processor_SQRT(Processor *processor);
Processor_err processor_OUT(Processor *processor);

#endif //CF_H