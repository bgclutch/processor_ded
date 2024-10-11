#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#include "assembler.h"

size_t command_words_num(char* buffer, size_t size)
{
    size_t counter = 0;
    for(size_t i = 0; i < size; i++)
    {
        if(isspace(buffer[i]))
            counter++;
    }

    return counter;

}

Asm_Commands translation_func(const char* command_word)
{
         if(!strncmp(command_word, c_push, sizeof(c_push))) return my_push;
    else if(!strncmp(command_word, c_add,  sizeof(c_add)))  return my_add;
    else if(!strncmp(command_word, c_sub,  sizeof(c_sub)))  return my_sub;
    else if(!strncmp(command_word, c_mul,  sizeof(c_mul)))  return my_mul;
    else if(!strncmp(command_word, c_div,  sizeof(c_div)))  return my_div;
    else if(!strncmp(command_word, c_in,   sizeof(c_in)))   return my_in;
    else if(!strncmp(command_word, c_out,  sizeof(c_out)))  return my_out;
    else if(!strncmp(command_word, c_sqrt, sizeof(c_sqrt))) return my_sqrt;
    else if(!strncmp(command_word, c_sin,  sizeof(c_sin)))  return my_sin;
    else if(!strncmp(command_word, c_cos,  sizeof(c_cos)))  return my_cos;
    else if(!strncmp(command_word, c_dump, sizeof(c_dump))) return my_dump;
    else if(!strncmp(command_word, c_hlt,  sizeof(c_hlt)))  return my_hlt;
    else return my_num;
}



