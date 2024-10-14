#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

#include "assembler.h"
#include "../lib_buffer_proc/buffer.h"
#include "../lib_file_proc/file.h"


size_t command_words_num(char* buffer, size_t size)
{
    size_t counter = 0;
    for(size_t i = 1; i < size; i++)
    {
        if(isspace(buffer[i - 1]) && isalnum(buffer[i])) // FIXME double space
            counter++;
    }

    return counter;

}

Asm_Commands translation_func(const char* command_word, size_t wrd_size)
{
         if(strncmp(command_word, c_push, wrd_size) == 0) return MY_PUSH;
    else if(strncmp(command_word, c_add,  wrd_size) == 0) return MY_ADD;
    else if(strncmp(command_word, c_sub,  wrd_size) == 0) return MY_SUB;
    else if(strncmp(command_word, c_mul,  wrd_size) == 0) return MY_MUL;
    else if(strncmp(command_word, c_div,  wrd_size) == 0) return MY_DIV;
    else if(strncmp(command_word, c_in,   wrd_size) == 0) return MY_IN;
    else if(strncmp(command_word, c_out,  wrd_size) == 0) return MY_OUT;
    else if(strncmp(command_word, c_sqrt, wrd_size) == 0) return MY_SQRT;
    else if(strncmp(command_word, c_sin,  wrd_size) == 0) return MY_SIN;
    else if(strncmp(command_word, c_cos,  wrd_size) == 0) return MY_COS;
    else if(strncmp(command_word, c_dump, wrd_size) == 0) return MY_DUMP;
    else if(strncmp(command_word, c_hlt,  wrd_size) == 0) return MY_HLT;
    else if(strncmp(command_word, c_pshr, wrd_size) == 0) return MY_PSHR;
    else if(strncmp(command_word, c_pop,  wrd_size) == 0) return MY_POP;
    else if(strncmp(command_word, c_jmp,  wrd_size) == 0) return MY_JMP;
    else if(strncmp(command_word, c_ja,   wrd_size) == 0) return MY_JA;
    else if(strncmp(command_word, c_jae,  wrd_size) == 0) return MY_JAE;
    else if(strncmp(command_word, c_jb,   wrd_size) == 0) return MY_JB;
    else if(strncmp(command_word, c_jbe,  wrd_size) == 0) return MY_JBE;
    else if(strncmp(command_word, c_je,   wrd_size) == 0) return MY_JE;
    else if(strncmp(command_word, c_jne,  wrd_size) == 0) return MY_JNE;
    else return MATVEY;
}


int translator(char* buffer, size_t words_num, FILE* file, size_t size)
{
    size_t index = 0;

    for(size_t i = 0; i <= words_num && index < size; i++)  // TODO remove buffer
    {
        Asm_Commands command_num = put_command_word(buffer, size, &index);

        if(command_num == MATVEY)
        {
            fprintf(stderr, "SNTXERR\n");
            return 0;
        }

        fprintf(file, "%d ", command_num);

        if(command_num == MY_PUSH || command_num == MY_POP || command_num == MY_PSHR)
        {
            ssize_t number = put_command_num(buffer, size, &index);
            fprintf(file, "%ld ", number);
            i++;
        }
    }
    return 1;
}


char* find_command_word_begin(char* start_address, size_t index, const size_t size)
{
    while(index < size && !isalnum(start_address[index]))
       index++;

    return start_address + index;
}


size_t find_command_word_len(char* start_address, size_t index, const size_t size)
{
    size_t counter = 0;

    while(index + counter < size && isalnum(start_address[counter]))
        counter++;

    return counter;
}


Asm_Commands put_command_word(char* buffer, size_t size, size_t* index)
{
    char* wrd_begin = find_command_word_begin(buffer, *index, size);
    size_t wrd_len  = find_command_word_len(wrd_begin, *index, size);

    *index = (size_t)(wrd_begin + wrd_len - buffer);

    char* compare = wrd_begin;

    Asm_Commands command_num = translation_func(compare, wrd_len);

    return command_num;
}


ssize_t put_command_num(char* buffer, size_t size, size_t* index)
{
    char* wrd_begin = find_command_word_begin(buffer, *index, size);
    size_t wrd_len  = find_command_word_len(wrd_begin, *index, size);

    *index = (size_t)(wrd_begin + wrd_len - buffer);

    char* compare = wrd_begin;

    ssize_t number = 0;

    for(size_t i = 0; i < wrd_len - 1; i++) // -1???
    {
        number += strtol(compare + i, NULL, 10);
        number *= 10;
    }
    number /= 10; // 100???

    return number;
}
