#include <stdio.h>
#include "../processor_headers/processor.h"
#include "../stack_ded/stack_headers/stack.h"


Error_Codes ctor_proc(Struct_SPU *SPU, size_t commands_num)
{
    SPU->execode = (ssize_t*) calloc(commands_num, sizeof(ssize_t));
    SPU->registers[4] = {0};
    ctor_stack(&SPU->stack);
    SPU->ip = 0;
    SPU->flag = 1;
}

Error_Codes dtor_proc(Struct_SPU *SPU)
{
    free(SPU->execode);
    SPU->execode = nullptr;
    SPU->registers[4] = {0};
    dtor_stack(&SPU->stack);
    SPU->ip = 0;
    SPU->flag = 0;
}