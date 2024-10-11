#include <stdio.h>
#include <string.h>
#include "../stack_ded/stack_headers/stack.h"
#include "../stack_ded/stack_headers/colorised_output.h"
//#include "../processor_headers/processor.h"

int main(int argc, void* argv)
{
    Main_Stack_Struct stack_data = {};
    ctor_stack(stack_data);
// TODO func!!!
    if(argc != 1)
        FILE* file_read = fopen("argv[1]", "r");
    else
        FILE* file_read = fopen("default_assembler_code.asm", "r");

    assert(file_read && "file read error");

    fseek( file_read, 0, SEEK_END);
    size_t file_size = ftell(file_read);
    fseek( file_read, 0, SEEK_SET);

    char* buffer = (char*) calloc(file_size + 1, sizeof(char));
    fread(buffer, sizeof(char), file_size, file_read);
    buffer[file_size] = '\n';

    size_t c_words_num = command_words_num(buffer, file_size + 1);
    fprintf(stderr, "words num %lu\n", c_words_num);

    size_t* translation_buffer = (size_t*) calloc(c_words_num, sizeof(size_t));



    for(size_t i = 0; i < c_words_num; i++)
    {
        char command_word[25] = "";

        for(size_t j = 0; !isspace(buffer[index]) && index < file_size; j++, index++)
        {
            command_word[j] = buffer[index];
        }
        index++;

        translation_buffer[i] = strtol(command_word, NULL, 10);

        fprintf(stderr, "transl_buff %lu", translation_buffer[i]);
    }


    size_t ip = 0; // TODO to struct!


    return 0;
}