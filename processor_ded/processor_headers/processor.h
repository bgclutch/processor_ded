#ifndef PROCESSOR_H_
#define PROCESSOR_H_

#include "../stack_ded/stack_headers/stack.h"


enum Proc_Commands
{
    PUSH = 0x01,
    ADD  = 0x02,
    SUB  = 0x03,
    MUL  = 0x04,
    DIV  = 0x05,
    IN   = 0x06,
    OUT  = 0x07,
    SQRT = 0x08,
    SIN  = 0x09,
    COS  = 0x0A,
    DUMP = 0x0B,
    JMP  = 0x10,
    JA   = 0x11,
    JAE  = 0x12,
    JB   = 0x13,
    JBE  = 0x14,
    JE   = 0x15,
    JNE  = 0x16,
    PSHR = 0x20,
    POP  = 0x21,
    HLT  = 0x00,
};


enum Error_Codes
{
    CTOR_ERR     = 0x01,
    DTOR_ERR     = 0x02,
    CODE_VER_ERR = 0x03,
};


struct Struct_SPU
{
    StackElem_t* execode;
    ssize_t registers[4];
    Main_Stack_Struct stack;
    size_t ip;
    int flag;
};

Error_Codes ctor_proc(Struct_SPU *SPU, size_t commands_num);

Error_Codes dtor_proc(Struct_SPU *SPU);


#endif // PROCESSOR_H_