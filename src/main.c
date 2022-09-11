/**
 * @file main.c
 * @author Olamilekan Akintilebo (olamilekanakintilebo@gmail.com)
 * @brief Simpletron - A simple virtual machine, The Simpletron runs programs
 * written in the only language it directly understands—that is,
 * Simpletron Machine Language, or SML for short. The Simpletron contains
 * an accumulator - a “special register” in which information is put before
 * the Simpletron uses that information in calculations or examines it in various ways.
 * All information in the Simpletron is handled in terms of words.
 * A word is a signed four-digit decimal number such as +3364, -1293, +0007, -0001, etc.
 * The Simpletron is equipped with a 100-word memory, and these words are referenced
 * by their location numbers 00, 01, ..., 99. Before running an SML program,
 * we must load or place the program into memory. The first instruction (or statement)
 * of every SML program is always placed in location 00.
 * @version 0.1
 * @date 2022-09-07
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <stdio.h>

#define MEMORY_SIZE 100

// Read and Write operations.
#define READ 10
#define WRITE 11

// Load and Store operations.
#define LOAD 20
#define STORE 21

// Arithmetic Operations
#define ADD 30
#define SUBTRACT 31
#define DIVIDE 32
#define MULTIPLY 33

// Transfer-of-control operations
#define BRANCH 40
#define BRANCHNEG 41
#define BRANCHZERO 42
#define HALT 43 // Halt - the program has completed its task.

/**
 * @brief Read a word from the keyboard into specific location in memory.
 *
 * @param memory The memory.
 * @param location The specified location in the memory.

 */
void read(int memory[], const size_t *location);

/**
 * @brief Write a word from specific location in memory to the screen.
 *
 * @param memory The memory.
 * @param location The specified location in the memory.
 */
void write(int memory[], const size_t *location);

/**
 * @brief Load a word from a specific location in memory into the accumulator.
 *
 * @param memory The memory.
 * @param location The specified location in the memory.
 * @param accumulator The accumulator.
 */
void load(const int memory[], const size_t *location, int *accumulator);

/**
 * @brief Store a word from the accumulator into a specific location in memory.
 *
 * @param memory The memory.
 * @param location The specified location in the memory.
 * @param accumulator The accumulator.
 */
void store(int memory[], const size_t *location, const int *accumulator);

/**
 * @brief Add a word from a specific location in memory to the word in accumulator.
 *
 * @param memory The memory.
 * @param location The specified location location in the memory.
 * @param accumulator The accumulator.
 */
void add(const int memory[], const size_t *location, int *accumulator);

/**
 * @brief Subtract a word from a specific locatiom in memory to the word in accumulator.
 *
 * @param memory The memory.
 * @param location The specified location in the memory.
 * @param accumulator The accumulator.
 */
void subtract(const int memory[], const size_t *location, int *accumulator);

/**
 * @brief Divide a word from a specific locatiom in memory to the word in accumulator.
 *
 * @param memory The memory.
 * @param location The specified location in the memory.
 * @param accumulator The accumulator.
 * @param instructionCounter The instruction counter
 */
void divide(int memory[], const size_t *location, int *accumulator, const size_t *instructionCounter);

/**
 * @brief Multiply a word from a specific locatiom in memory to the word in accumulator.
 *
 * @param arr The memory.
 * @param location The specified location in the memory.
 * @param accumulator The accumulator.
 */
void multiply(const int arr[], const size_t *location, int *accumulator);

/**
 * @brief Branch to a specific location in memory.
 *
 * @param location The specified location in memory.
 * @param instructionCounter The instruction counter.
 */
void branch(const size_t *location, size_t *instructionCounter);

/**
 * @brief Branch to a specific location in memory if the accumulator is negative.
 *
 * @param location The specified location in the memory.
 * @param accumulator The accumulator.
 * @param instructionCounter The instruction counter.
 */
void branchNeg(const size_t *location, const int *accumulator, size_t *instructionCounter);

/**
 * @brief Branch to a specific locatiom in memory if the accumulator is zero.
 *
 * @param location The specified location in the memory.
 * @param accumulator The accumulator.
 * @param instructionCounter The instruction counter.
 */
void branchZero(const size_t *location, const int *accumulator, size_t *instructionCounter);

/**
 * @brief Execute program instructions.
 *
 * @param memory The memory.
 */
void executeProgram(int memory[]);

/**
 * @brief Type program instructions from keybord and load them into the memory
 *
 * @param memory The memory
 */
void loadProgram(int memory[]);

/**
 * @brief Bring the program to an end
 *
 * @param memory The memory
 * @param instructionCounter The instruction counter
 */
void halt(int memory[], const size_t *instructionCounter);

int main()
{
    int memory[MEMORY_SIZE] = {4300};

    loadProgram(memory);
    executeProgram(memory);

    return 0;
}

void read(int memory[], const size_t *location)
{
    printf("%s", "? ");
    scanf("%d", &memory[*location]);
}

void write(int memory[], const size_t *location)
{
    printf("%d\n", memory[*location]);
}

void load(const int memory[], const size_t *location, int *accumulator)
{
    *accumulator = memory[*location];
}

void store(int memory[], const size_t *location, const int *accumulator)
{
    memory[*location] = *accumulator;
}

void add(const int memory[], const size_t *location, int *accumulator)
{
    *accumulator += memory[*location];
}

void subtract(const int memory[], const size_t *location, int *accumulator)
{
    *accumulator -= memory[*location];
}

void divide(int arr[], const size_t *location, int *accumulator, const size_t *instructionCounter)
{
    if (arr[*location] != 0)
    {
        *accumulator /= arr[*location];
    }
    else
    {
        puts("*** Attempt to divide by zero                  ***");
        halt(arr, instructionCounter);
    }
}

void multiply(const int memory[], const size_t *location, int *accumulator)
{
    *accumulator *= memory[*location];
}

void branch(const size_t *location, size_t *instructionCounter)
{
    *instructionCounter = *location;
}

void branchNeg(const size_t *location, const int *accumulator, size_t *instructionCounter)
{
    if (*accumulator < 0)
        *instructionCounter = *location;
}

void branchZero(const size_t *location, const int *accumulator, size_t *instructionCounter)
{
    if (*accumulator == 0)
        *instructionCounter = *location;
}

void executeProgram(int memory[])
{
    int accumulator = 0;
    size_t instructionCounter = 0;
    int instructionRegister = 0;
    int operationCode = 0;
    size_t operand = 00;

    do
    {
        instructionRegister = memory[instructionCounter++];
        operationCode = instructionRegister / 100;
        operand = instructionRegister % 100;

        switch (operationCode)
        {
        case READ:
            read(memory, &operand);
            break;
        case WRITE:
            write(memory, &operand);
            break;
        case LOAD:
            load(memory, &operand, &accumulator);
            break;
        case STORE:
            store(memory, &operand, &accumulator);
            break;
        case ADD:
            add(memory, &operand, &accumulator);
            break;
        case SUBTRACT:
            subtract(memory, &operand, &accumulator);
            break;
        case DIVIDE:
            divide(memory, &operand, &accumulator, &instructionCounter);
            break;
        case MULTIPLY:
            multiply(memory, &operand, &accumulator);
            break;
        case BRANCH:
            branch(&operand, &instructionCounter);
            break;
        case BRANCHNEG:
            branchNeg(&operand, &accumulator, &instructionCounter);
            break;
        case BRANCHZERO:
            branchZero(&operand, &accumulator, &instructionCounter);
            break;
        case HALT:
            break;
        default:
            puts("*** Invalid operation detected                 ***");
            halt(memory, &instructionCounter);
            break;
        }

    } while (operationCode != HALT);
}

void loadProgram(int memory[])
{
    puts("***           Welcome to Simpletron           ***");
    puts("***                                           ***");
    puts("*** Please enter your program one instruction ***");
    puts("*** (or data word) at a time. I will type the ***");
    puts("*** location number and a question mark (?).  ***");
    puts("*** You then type the word for that location. ***");
    puts("*** Type the sentinel -99999 to stop entering ***");
    puts("*** your program.                             ***\n");

    int location = 0;
    int instruction = 0;

    printf("%02d ? ", location);
    scanf("%d", &instruction);

    while (instruction != -99999)
    {
        memory[location++] = instruction;

        printf("%02d ? ", location);
        scanf("%d", &instruction);
    }

    puts("*** Program loading completed                 ***");
    puts("*** Program execution begins                  ***\n");
}

void halt(int memory[], const size_t *programCounter)
{
    puts("*** Simpletron execution terminated ***");
    memory[*programCounter] = 4300;
}