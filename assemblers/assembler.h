#ifndef ASSEMBLER_H_
#define ASSEMBLER_H_


const char c_push[] = "push";
const char c_add[]  = "add";
const char c_sub[]  = "sub";
const char c_mul[]  = "mul";
const char c_div[]  = "div";
const char c_in[]   = "in";
const char c_out[]  = "out";
const char c_sqrt[] = "sqrt";
const char c_sin[]  = "sin";
const char c_cos[]  = "cos";
const char c_dump[] = "dump";
const char c_hlt[]  = "hlt";

enum Asm_Commands
{
    my_push = 0x01,
    my_add  = 0x02,
    my_sub  = 0x03,
    my_mul  = 0x04,
    my_div  = 0x05,
    my_in   = 0x06,
    my_out  = 0x07,
    my_sqrt = 0x08,
    my_sin  = 0x09,
    my_cos  = 0x0A,
    my_dump = 0x0B,
    my_num  = 0x0C,
    my_hlt  = 0x00,

};

size_t command_words_num(char* buffer, size_t size);

Asm_Commands translation_func(const char*);

#endif // ASSEMBLER_H_