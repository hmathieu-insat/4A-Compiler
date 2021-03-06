/**
 * @file instr.c
 * @author Hugo Mathieu (hmathieu@insa-toulouse.fr) Guillaume Aubut (@Ger0th)
 * @brief
 * @version 0.1
 * @date 2022-03-19
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "instr.h"
#include "../external/macrologger.h"

#define TAILLE 1025

instruction instrArray[TAILLE];

void initInstrArray()
{
    instruction instrInit = {
        .ope = ADD,
        .ops = {
            -1,
            -1,
            -1
        }
    };
    for (int i = 0; i < TAILLE - 1; i++)
    {
        instrArray[i] = instrInit;
    }
}

int addInstruction(instruction instr)
{
    int i = 0;
    while (i < TAILLE - 1 && instrArray[i].ops[0] != -1)
    {
        i++;
    }
    if (i == TAILLE - 1)
    {
        fprintf(stderr, "Maximum instruction array size exceeded\n");
        exit(-1);
    }
    instrArray[i] = instr;
    // LOG_DEBUG("Instruction added %s", stringOfInstruction(instr));
    return i;
}

instruction getInstruction(int i) {
    if (i < 0 || i >= TAILLE - 1)
    {
        instruction instr = {
            .ope = -1,
            .ops = {
                -1,
                -1,
                -1
            }
        };
        return instr;
    }
    return instrArray[i];
}

int printInstrTable()
{
    for (int i = 0; i < TAILLE - 1; i++)
    {
        printf("%d - ", i);
        printf(stringOfInstruction(instrArray[i]));
        printf("\n");
    }
    return 0;
}

char *stringOfInstruction(instruction instruction)
{
    if (instruction.ops[0] == -1)
    {
        exit(0);
    }

    char* str_out = malloc(100); char str_operator[7];
    strcpy(str_out, "Instruction: ");
    strcpy(str_operator, operator_string[instruction.ope]);
    strcat(str_out, str_operator);
    strcat(str_out, "  ");

    int i = 0;
    char op[100];
    strcpy(op, " ");
    while (instruction.ops[i] != -1 && i < 3)
    {
        sprintf(op, "%d  ", instruction.ops[i]);
        strcat(str_out, op);
        i++;
    }
    return str_out;
}

int getNumberOfInstructions()
{
    int i = 0;
    while (instrArray[i].ops[0] != -1)
    {
        i++;
    }
    return i;
}

int patchJmpInstruction(int at, int to, operator jmpType) {
    switch (jmpType) {
        case JMP:
            instrArray[at].ops[0] = to;
            break;
        case JMF:
            instrArray[at].ops[1] = to;
            break;
        default:
            return -1;
            break;
    }
    return 0;
}
    