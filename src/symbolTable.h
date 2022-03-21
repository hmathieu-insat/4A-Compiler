/**
 * @file symbolTable.h
 * @author Hugo Mathieu (hmathieu@insa-toulouse.fr) @Ger0th
 * @brief Symbol table for the compiler
 * @version 0.1
 * @date 2022-03-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef SYMBOLTABLES_H
#define SYMBOLTABLES_H

#define TABLE_SIZE 1025

typedef enum type
{
    t_int
} type;

/**
 * @brief Increases the depth of a variable when entering a new body (if or while)
 *
 * @return 0 if executed correctly.
 */
int increaseDepth();

/**
 * @brief Decreases the depth of a variable when exiting a new body (if or while)
 *
 * @return 0 if executed correctly.
 */
int decreaseDepth();

typedef struct symbol
{
    char *symbolName;
    type typ;
    int depth;
} symbol;

typedef struct symbolTable
{
    symbol symbolArray[TABLE_SIZE];
    int topIndex;
} symbolTable;

/**
 * @brief Initializes the table at the start of the compilation
 *
 * @return 0 if executed correctly
 */
int initTable();

/**
 * @brief Add a new symbol to the table
 *
 * @param symbolName
 * @param typ For now t_int only
 * @param depth Corresponding to the scope of the variable (vars in main being at depth 0)
 * @return 0 if the symbol was correctly. -1 if the symbol could not be added. (table full)
 */
int addSymbol(char *symbolName, int sizeofSymbol, enum type typ);

/**
 * @brief Delete the symbol at the top of the table.
 *
 * @return 1 if the symbol was successfully deleted. Fails with -1 and prints an error message if trying to delete while table is empty.
 */
int deleteSymbol();

/**
 * @brief Checks if the symbolTable is empty.
 *
 * @return 1 if the symbolTable is empty.
 */
int isEmpty();

/**
 * @brief Removes all symbols at the highest scope from the table
 *
 * @return 0 if executed correctly
 */
int deleteFromChangeScope();

/**
 * @brief Checks if the symbol is present in the table and returns its address if present
 *
 * @param symbol
 * @return The address of the symbol if the symbol is present. -1 if the symbol is not present
 */
int getAddressSymbol(char *symbol);

/**
 * @brief Get the Top Index of the symbolTable (Testing purposes)
 *
 * @return the index of the top.
 */
int getTopIndex();

/**
 * @brief Testing function displaying the table of symbols.
 * Called when the program has finished running.
 *
 */
void printSymbolTable();

#endif
