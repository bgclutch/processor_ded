#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

#include "assembler.h"


int main(void)
{
    FILE* file_read = fopen("assembler_code.asm", "r");
    assert(file_read && "reading file wasn't opened");

    fseek(file_read, 0,SEEK_END);
    size_t file_size = ftell(file_read);
    fseek(file_read, 0, SEEK_SET);

    char* buffer = (char*) calloc(file_size + 1, sizeof(char));
    fread(buffer, sizeof(char), file_size, file_read);
    buffer[file_size] = '\n';

    size_t c_words_num = command_words_num(buffer, file_size + 1);
    fprintf(stderr, "words num %lu\n", c_words_num);

    size_t* translation_buffer = (size_t*) calloc(c_words_num, sizeof(size_t));

    size_t index = 0;


    for(size_t i = 0; i < c_words_num; i++)
    {
        char command_word[25] = "";

        for(size_t j = 0; !isspace(buffer[index]) && index < file_size; j++, index++)
        {
            command_word[j] = buffer[index];
        }
        index++;

        Asm_Commands symb = translation_func(command_word);

        if(symb != my_num)
            translation_buffer[i] = (size_t)symb;
        else
            translation_buffer[i] = strtol(command_word, NULL, 10);
    }

    assert(!fclose(file_read) && "file read wasn't closed");


    FILE* file_write = fopen("machine_code.asm", "w");

    fwrite(translation_buffer, sizeof(size_t), c_words_num, file_write);

    for(size_t i = 0; i < c_words_num; i++)
    {
        fprintf(stderr, "%lu ", translation_buffer[i]);
    }
    assert(!fclose(file_write) && "file write wasn't closed");


    free(buffer);
    buffer = nullptr;
    free(translation_buffer);
    translation_buffer = nullptr;

    return 0;
}