#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include "../../stack_ded/stack_headers/stack.h"
#include "../../stack_ded/stack_headers/colorised_output.h"
#include "../processor_headers/processor.h"
#include "../../lib_buffer_proc/buffer.h"
#include "../../lib_file_proc/file.h"


int main(int argc, char* argv[])
{
    // if(argc < 2) // FIXME *expected value* instead of '0' and add execution default file
    // {
    //     fprintf(stderr, "Default code will be executed\n"); // FIXME podumat'
    //     return 0;
    // }
    // TODO decoder!!!
    Struct_SPU SPU = {};

    FILE* file_read = nullptr;
    file_read = file_read_open(file_read, "machine_code.asm");

    if(!res_checker((ssize_t)file_read)) //TODO fprintf error
        return 0;


    size_t buffer_size = symbols_number(file_read); // buffer create potential alert (data types)

    ctor_proc(&SPU, buffer_size);

    SPU.execode = (ssize_t*) buffer_create(buffer_size, sizeof(ssize_t), file_read);


    while(SPU.flag) // FIXME func!!!!!!
    {
        switch(SPU.execode[SPU.ip])
        {
            case(PUSH):
            {
                Error_Codes stk_push_err = stack_push(&SPU.stack, SPU.execode[SPU.ip + 1]);
                SPU.ip += 2;
                break;
            }
            case(ADD):
            {
                StackElem_t addition_1 = 0;
                StackElem_t addition_2 = 0;
                Error_Codes stk_pop_add_1_err = stack_pop(&SPU.stack, &addition_2);
                Error_Codes std_pop_add_2_err = stack_pop(&SPU.stack, &addition_1);
                Error_Codes stk_push_err = stack_push(&SPU.stack, addition_1 + addition_2);
                SPU.ip++;
                break;
            }
            case(SUB):
            {
                StackElem_t minued     = 0;
                StackElem_t subtrahend = 0;
                Error_Codes stk_pop_sbtr_err = stack_pop(&SPU.stack, &subtrahend);
                Error_Codes std_pop_mnd_err  = stack_pop(&SPU.stack, &minued);
                Error_Codes stk_push_err = stack_push(&SPU.stack, minued - subtrahend);
                SPU.ip++;
                break;
            }
            case(MUL):
            {
                StackElem_t multiplier_first  = 0;
                StackElem_t multiplier_second = 0;
                Error_Codes stk_pop_mlt_frst_err = stack_pop(&SPU.stack, &multiplier_second);
                Error_Codes std_pop_mlt_scnd_err = stack_pop(&SPU.stack, &multiplier_first);
                Error_Codes stk_push_err = stack_push(&SPU.stack, multiplier_first * multiplier_second);
                SPU.ip++;
                break;
            }
            case(DIV):
            {
                StackElem_t divident = 0;
                StackElem_t divisor  = 0;
                Error_Codes stk_pop_dvdnt_err = stack_pop(&SPU.stack, &divisor);
                Error_Codes std_pop_dvsr_err  = stack_pop(&SPU.stack, &divident);
                Error_Codes stk_push_err = stack_push(&SPU.stack, divident / divisor); // TODO check div 0
                SPU.ip++;
                break;
            }
            case(IN):
            {
                StackElem_t elem_input = 0;
                printf("please, input a number:"); // FIXME add checks?
                scanf("%ld", &elem_input);
                Error_Codes stk_push_err = stack_push(&SPU.stack, elem_input);
                SPU.ip++;
                break;
            }
            case(OUT):
            {
                StackElem_t elem_out = 0;
                Error_Codes stk_pop_err = stack_pop(&SPU.stack, &elem_out);
                printf(BLUE_TEXT("outputed element ") GREEN_TEXT("%ld\n"), elem_out);
                SPU.ip++;
                break;
            }
            case(SQRT):
            {
                StackElem_t elem = 0;
                Error_Codes stk_pop_err = stack_pop(&SPU.stack, &elem);
                elem = sqrt(elem);
                Error_Codes stk_push_err = stack_push(&SPU.stack, elem);
                SPU.ip++;
                break;
            }
            case(SIN):
            {
                StackElem_t elem = 0;
                Error_Codes stk_pop_err = stack_pop(&SPU.stack, &elem);
                elem = sin(elem);
                Error_Codes stk_push_err = stack_push(&SPU.stack, elem);
                SPU.ip++;
                break;
            }
            case(COS):
            {
                StackElem_t elem = 0;
                Error_Codes stk_pop_err = stack_pop(&SPU.stack, &elem);
                elem = cos(elem);
                Error_Codes stk_push_err = stack_push(&SPU.stack, elem);
                SPU.ip++;
                break;
            }
            case(DUMP):
            {
                stack_dump(&SPU.stack, __FILE__, __func__, __LINE__);
                SPU.ip++;
                break;
            }
            case(JMP):
            {
                SPU.ip = SPU.execode[SPU.ip + 1];
                break;
            }
            case(JA):
            {
                StackElem_t elem_1 = 0;
                StackElem_t elem_2 = 0;
                Error_Codes stk_pop_elm_2_err = stack_pop(&SPU.stack, &elem_2);
                Error_Codes stk_pop_elm_1_err = stack_pop(&SPU.stack, &elem_1);
                if(elem_1 > elem_2)
                    SPU.ip = SPU.execode[SPU.ip + 1];
                else
                    SPU.ip++;
                break;
            }
            case(JAE):
            {
                StackElem_t elem_1 = 0;
                StackElem_t elem_2 = 0;
                Error_Codes stk_pop_elm_2_err = stack_pop(&SPU.stack, &elem_2);
                Error_Codes stk_pop_elm_1_err = stack_pop(&SPU.stack, &elem_1);
                if(elem_1 >= elem_2)
                    SPU.ip = SPU.execode[SPU.ip + 1];
                else
                    SPU.ip++;
                break;
            }
            case(JB):
            {
                StackElem_t elem_1 = 0;
                StackElem_t elem_2 = 0;
                Error_Codes stk_pop_elm_2_err = stack_pop(&SPU.stack, &elem_2);
                Error_Codes stk_pop_elm_1_err = stack_pop(&SPU.stack, &elem_1);
                if(elem_1 < elem_2)
                    SPU.ip = SPU.execode[SPU.ip + 1];
                else
                    SPU.ip++;
                break;
            }
            case(JBE):
            {
                StackElem_t elem_1 = 0;
                StackElem_t elem_2 = 0;
                Error_Codes stk_pop_elm_2_err = stack_pop(&SPU.stack, &elem_2);
                Error_Codes stk_pop_elm_1_err = stack_pop(&SPU.stack, &elem_1);
                if(elem_1 <= elem_2)
                    SPU.ip = SPU.execode[SPU.ip + 1];
                else
                    SPU.ip++;
                break;
            }
            case(JE):
            {
                StackElem_t elem_1 = 0;
                StackElem_t elem_2 = 0;
                Error_Codes stk_pop_elm_2_err = stack_pop(&SPU.stack, &elem_2);
                Error_Codes stk_pop_elm_1_err = stack_pop(&SPU.stack, &elem_1);
                if(elem_1 == elem_2)
                    SPU.ip = SPU.execode[SPU.ip + 1];
                else
                    SPU.ip++;
                break;
            }
            case(JNE):
            {
                StackElem_t elem_1 = 0;
                StackElem_t elem_2 = 0;
                Error_Codes stk_pop_elm_2_err = stack_pop(&SPU.stack, &elem_2);
                Error_Codes stk_pop_elm_1_err = stack_pop(&SPU.stack, &elem_1);
                if(elem_1 != elem_2)
                    SPU.ip = SPU.execode[SPU.ip + 1];
                else
                    SPU.ip++;
                break;
            }
            case(PSHR):
            {
                StackElem_t elem = SPU.registers[SPU.execode[SPU.ip + 1]];
                Error_Codes stk_push_err = stack_push(&SPU.stack, elem);
                SPU.ip += 2;
                break;
            }
            case(POP):
            {
                StackElem_t elem = 0;
                Error_Codes stk_pop_err = stack_pop(&SPU.stack, &elem);
                SPU.registers[SPU.execode[SPU.ip + 1]] = elem;
                SPU.ip += 2;
                break;
            }
            case(HLT):
            {
                Error_Codes dtor_err_code = dtor_proc(&SPU);
                SPU.flag = 0;
                return 0;
                break;
            }
            default:
            {
                assert(0 && "proizoshla zalupa, srochno fixit' + vova pidor");
            };
        }
    }

    dtor_proc(&SPU);
    return 0;
}