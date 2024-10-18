#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../processor_headers/processor.h"
#include "../../stack_ded/stack_headers/stack.h"


Error_Codes ctor_proc(Struct_SPU *SPU, size_t commands_num)
{
    SPU->execode = (ssize_t*) calloc(commands_num, sizeof(ssize_t));
    memset(SPU->registers, 0, sizeof(SPU->registers[0]) * REGCOUNT);
    ctor_stack(&SPU->stack);
    SPU->ip = 0;
    SPU->flag = 1;
    return ALL_IS_OK;
}

Error_Codes dtor_proc(Struct_SPU *SPU)
{
    free(SPU->execode);
    SPU->execode = nullptr;
    memset(SPU->registers, 0, sizeof(SPU->registers[0]) * REGCOUNT);
    dtor_stack(&SPU->stack);
    SPU->ip = 0;
    SPU->flag = 0;
    return ALL_IS_OK;
}