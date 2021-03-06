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

#define FUNCTION_JMP_ADDR 1024
#define SYMBOL_TABLE_SIZE 1024
#define BASE_ARGS 1009
#define BASE_VAR_TEMP 925
#define FUNCTION_TABLE_SIZE 64

typedef enum type
{
    t_int
} type;

/**
 * @brief Creates a new temporary variable in the symbol table.
 *
 * @return  The address of the new temporary variable. Or -1 if the table was full.
 */
int newTmp();

/**
 * @brief Free the temporary addresses.
 *
 */
void freeAddrsTemp();

/**
 * @brief Affects the value to the temporary address addr_temp1 or addr_temp2 if 1 is unavailable.
 *
 * @param value Value to be stored at the address.
 * @return The temporary address used.
 */
int affectToAddrTemp(int value);

/**
 * @brief Increases the depth of a variable when entering a new body (if or while)
 *
 */
void increaseDepth();

/**
 * @brief Decreases the depth of a variable when exiting a new body (if or while)
 *
 */
void decreaseDepth();

/**
 * @brief Increases the current function depth
 *
 */
void increaseFunctionDepth();

/**
 * @brief Reset the current function depth before entering the main
 *
 */
void resetFunctionDepth();

typedef struct symbol
{
    char *symbolName;
    type typ;
    int depth;
    int functionDepth;
} symbol;

typedef struct Function
{
    char *functionName;
    int functionAddress;
    int returnAddress;
    int functionDepth;
    int returnVarAddress;
} Function;

typedef struct SymbolTable
{
    symbol symbolArray[SYMBOL_TABLE_SIZE];
    int topSymbolIndex;
    int topIndexTemp;
    int topIndexArgs;
} SymbolTable;

typedef struct FunctionTable
{
    Function functionArray[FUNCTION_TABLE_SIZE];
    int topFunctionIndex;
} FunctionTable;

/**
 * @brief Initialise the table at the start of the compilation
 *
 */
void initTable();

/**
 * @brief Initializes the function table at the start of the compilation
 *
 */
void initFunctionTable();

/**
 * @brief Add a new symbol to the table
 *
 * @param symbolName
 * @param size_of_symbol The size of the symbol in bytes
 * @param type For now int only
 * @return The address of the symbol if added correctly. -1 if the symbol could not be added. (table full)
 */
int addSymbol(char *symbolName, int sizeofSymbol, enum type typ);

/**
 * @brief Add a new function name to the function table
 *
 * @param functionName
 * @param functionAddress The address of the first line of assembler code of the function
 * @return 0 if the function was correctly. -1 if the function could not be added. (table full)
 */
int addFunction(char *FunctionName, int functionAddress);

/**
 * @brief Delete the symbol at the top of the table.
 *
 * @return 1 if the symbol was successfully deleted. Fails with -1 and prints an error message if trying to delete while table is empty.
 */
int deleteSymbol();

/**
 * @brief Checks if the SymbolTable is empty.
 *
 * @return 1 if the SymbolTable is empty.
 */
int isSymbolTableEmpty();

/**
 * @brief Removes all symbols at the highest scope from the table
 *
 * @return 0 if executed correctly. -1 if the table is empty.
 */
int deleteFromChangeScope();

/**
 * @brief Checks if the symbol is present in the table and returns its address if present
 *
 * @param symbol
 * @return The address of the symbol if the symbol is present. -1 if the symbol is not present
 */
int getSymbolAddress(char *symbol);

/**
 * @brief Checks if the function has been declared and returns the address of its first line of code if present
 *
 * @param functionName
 * @return The address of the first line of assembler code of the function. -1 if the function is not present
 */
int getFunctionAddress(char *functionName);

/**
 * @brief Checks if the function has been declared and returns its depth (function identifier == rank at which
 * the function has been declared)
 * @param functionName
 * @return The identifier of the function (depth). -1 if the function is not preset.
 */
int getFunctionDepth(char *functionName);

/**
 * @brief Set the current Function to the depth corresponding of the function going to.
 *
 * @param functionName
 * @return 0 if effected correclty. -1 if the function could not be found.
 */
int setFunctionScope(char *functionName);

/**
 * @brief Get the Top Index of the SymbolTable (Testing purposes)
 *
 * @return the index of the top.
 */
int getTopIndex();

/**
 * @brief Set the address of the return instruction in the function
 *
 * @param functionName
 * @param returnAddress The address of the return instruction in the function
 * @return 0 if the operation executed correctly. -1 if the function could not be found.
 */
int setFunctionReturnAddress(char *functionName, int returnAddress);

/**
 * @brief Get the return address corresponding to the current function then resets it.
 *
 * @param functionName
 * @return The address the function must return to. Or -1 if the return address is not set.
 */
int getFunctionReturnAddress(char *functionName);

/**
 * @brief Set the address of the return variable in the function
 *
 * @param returnVarAddress The address of the return variable of the function in the symbolTable
 * @return 0 if the operation executed correctly. -1 if the function could not be found.
 */
int setFunctionReturnVarAddress(int returnVarAddress);

/**
 * @brief Get the return variable address corresponding to the function then resets it.
 *
 * @param functionName
 * @return The address of the return variable in the symbol table. Or -1 if the return variable address is not set.
 */
int getFunctionReturnVarAddress(char *functionName);

/**
 * @brief Get the address of the functions's parameter of given index
 *
 * @param functionName Name of the function
 * @param parameterIndex Index of the parameter (starting at 1)
 * @return The address of the parameter. -1 if the function could not be found. -2 if the parameter index is invalid.
 */
int getFunctionParameterAddress(char *functionName, int parameterIndex);

/**
 * @brief Add a new argument to the table of arguments
 *
 * @return The address of the added arguments if the argument was correctly added. -1 if the argument could not be added. (table full)
 */
int addArgument();

/**
 * @brief Get the next available argument address
 *
 * @return The address of the next argument. -1 if there are no more arguments (or no arguments were defined).
 */
int getNextArgumentAddress();

/**
 * @brief Clears all the arguments in the table
 *
 */
void clearArgumentTable();

/**
 * @brief Testing function displaying the table of symbols.
 * Called when the program has finished running.
 *
 */
void printSymbolTable();

#endif
