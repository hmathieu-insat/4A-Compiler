/**
 * @file instr.h
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

#ifndef INSTR_H
#define INSTR_H

#define TAILLE 1025

typedef enum operator {
    ADD,
    SUB,
    MUL,
    DIV,
    COP,
    AFC,
    JMP,
    JMX,
    JMF,
    INF,
    SUP,
    EQUAL,
    NEQUAL,
    EQINF,
    EQSUP,
    AND,
    OR,
    PRI,
    ENTRY,
} operator;

static const char* const operator_string[] = {
    [ADD] = "ADD",
    [SUB] = "SUB",
    [MUL] = "MUL",
    [DIV] = "DIV",
    [COP]= "COP",
    [AFC]= "AFC",
    [JMP]= "JMP",
    [JMX]= "JMX", // Jump unconditionnaly to the instruction contained at the adress given in the operand
    [JMF]= "JMF",
    [INF]= "INF",
    [SUP]= "SUP",
    [EQUAL]= "EQUAL",
    [NEQUAL]= "NEQUAL",
    [EQINF]= "EQINF",
    [EQSUP]= "EQU",
    [AND]= "AND",
    [OR]= "OR",
    [PRI]= "PRI",
    [ENTRY]= "ENTRY"
};

typedef struct instruction
{
    operator ope;
    int ops[3];
} instruction;

/**
 * @brief Initializes the array of instructions to instructions without specified operator and operands to -1
 *
 */
void initInstrArray();

/**
 * @brief Adds an instruction to the array
 *
 * @param instr Asm instruction to add
 * @return The number of the instruction line added if excecuted correctly. -1 otherwise.
 */
int addInstruction(instruction instr);

/**
 * @brief Get the Instruction at the specified index
 * 
 * @param i 
 * @return instrArray[i]
 */
instruction getInstruction(int i);

/**
 * @brief Prints the entire array of instructions.
 *
 * @return 0 if executed successfully.
 */
int printInstrTable();

/**
 * @brief Function to convert an instruction to a string.
 *
 * @param instr Structure instruction to convert.
 * @return Formatted string representation of the instruction.
 */
char *stringOfInstruction(instruction instr);

/**
 * @brief Get the Number Of Instructions in the table
 * 
 * @return int 
 */
int getNumberOfInstructions();

/**
 * @brief Patch the jump based instruction with the correct address
 * 
 * @param at Address where the jump instruction is at
 * @param to Address to where the jump must go to
 * @param jmpType Type of jump (JMP or JMF)
 * 
 * @return 0 if executed successfully. -1 if the jump type is not supported.
 */
int patchJmpInstruction(int at, int to, operator jmpType);

#endif