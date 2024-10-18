#ifndef PROCESSOR_H_
#define PROCESSOR_H_

#include "../../stack_ded/stack_headers/stack.h"


enum Proc_Command
{
    PUSH = 0x11,
    ADD  = 0x12,
    SUB  = 0x13,
    MUL  = 0x14,
    DIV  = 0x15,
    IN   = 0x16,
    OUT  = 0x17,
    SQRT = 0x18,
    SIN  = 0x19,
    COS  = 0x1A,
    DUMP = 0x1B,
    JMP  = 0x20,
    JA   = 0x21,
    JAE  = 0x22,
    JB   = 0x23,
    JBE  = 0x24,
    JE   = 0x25,
    JNE  = 0x26,
    PSHR = 0x30,
    POP  = 0x31,
    HLT  = 0xFF,
};

enum Registers
{
    MY_AX   = 0x00,
    MY_BX   = 0x01,
    MY_CX   = 0x02,
    MY_DX   = 0x03,
    REGCOUNT
};


enum Error_Codes_SPU
{
    CTOR_ERR     = 0x01,
    DTOR_ERR     = 0x02,
    CODE_VER_ERR = 0x03,
};


struct Struct_SPU
{
    StackElem_t* execode;
    StackElem_t registers[REGCOUNT];
    Main_Stack_Struct stack;
    size_t ip;
    int flag;
};

Error_Codes ctor_proc(Struct_SPU *SPU, size_t commands_num);

Error_Codes dtor_proc(Struct_SPU *SPU);


#endif // PROCESSOR_H_