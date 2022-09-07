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
 * @param arr The memory.
 * @param location The specified location.
 */
void read(int arr[], const size_t *location);

/**
 * @brief Write a word from specific location in memory to the screen.
 *
 * @param arr The memory.
 * @param location The specified location.
 */
void write(int arr[], const size_t *location);

/**
 * @brief Load a word from a specific location in memory into the accumulator.
 *
 * @param arr The memory.
 * @param location The specified location.
 * @param accumulator The accumulator.
 */
void load(const int arr[], const size_t *location, int *accumulator);

/**
 * @brief Store a word from the accumulator into a specific location in memory.
 *
 * @param arr The memory.
 * @param location The specified location.
 * @param accumulator The accumulator.
 */
void store(int arr[], const size_t *location, const int *accumulator);

/**
 * @brief Add a word from a specific location in memory to the word in accumulator.
 *
 * @param arr The memory.
 * @param location The specified location.
 * @param accumulator The accumulator.
 */
void add(const int arr[], const size_t *location, int *accumulator);

/**
 * @brief Subtract a word from a specific locatiom in memory to the word in accumulator.
 *
 * @param arr The memory.
 * @param location The specified location.
 * @param accumulator The accumulator.
 */
void subtract(const int arr[], const size_t *location, int *accumulator);

/**
 * @brief Divide a word from a specific locatiom in memory to the word in accumulator.
 *
 * @param arr The memory.
 * @param location The specified location.
 * @param accumulator The accumulator.
 */
void divide(const int arr[], const size_t *location, int *accumulator);

/**
 * @brief Multiply a word from a specific locatiom in memory to the word in accumulator.
 *
 * @param arr The memory.
 * @param location The specified location.
 * @param accumulator The accumulator.
 */
void multiply(const int arr[], const size_t *location, int *accumulator);

/**
 * @brief Branch to a specific location in memory.
 *
 * @param location The specified location.
 * @param programCounter The program counter.
 */
void branch(const size_t *location, size_t *programCounter);

/**
 * @brief Branch to a specific location in memory if the accumulator is negative.
 *
 * @param location The specified location.
 * @param accumulator The accumulator.
 * @param programCounter The program counter.
 */
void branchNeg(const size_t *location, const int *accumulator, size_t *programCounter);

/**
 * @brief Branch to a specific locatiom in memory if the accumulator is zero.
 *
 * @param location The specified location.
 * @param accumulator The accumulator.
 * @param programCounter The program counter.
 */
void branchZero(const size_t *location, const int *accumulator, size_t *programCounter);

/**
 * @brief Execute program instructions.
 *
 * @param memory The memory.
 */
void executeProgram(int memory[]);

int main()
{
    int memory[MEMORY_SIZE] = {4300};

    // Program to read two numbers from keyboard and print the larger value
    memory[0] = 1009;
    memory[1] = 1010;
    memory[2] = 2009;
    memory[3] = 3110;
    memory[4] = 4107;
    memory[5] = 1109;
    memory[6] = 4300;
    memory[7] = 1110;
    memory[8] = 4300;


    executeProgram(memory);

    return 0;
}

void read(int arr[], const size_t *location)
{
    printf("%s", "Enter an integer: ");
    int value = 0;
    scanf("%d", &value);

    arr[*location] = value;
}

void write(int arr[], const size_t *location)
{
    printf("Output: %d\n", arr[*location]);
}

void load(const int arr[], const size_t *location, int *accumulator)
{
    *accumulator = arr[*location];
}

void store(int arr[], const size_t *location, const int *accumulator)
{
    arr[*location] = *accumulator;
}

void add(const int arr[], const size_t *location, int *accumulator)
{
    *accumulator += arr[*location];
}

void subtract(const int arr[], const size_t *location, int *accumulator)
{
    *accumulator -= arr[*location];
}

void divide(const int arr[], const size_t *location, int *accumulator)
{
    *accumulator /= arr[*location];
}

void multiply(const int arr[], const size_t *location, int *accumulator)
{
    *accumulator *= arr[*location];
}

void branch(const size_t *location, size_t *programCounter)
{
    *programCounter = *location;
}

void branchNeg(const size_t *location, const int *accumulator, size_t *programCounter)
{
    if (*accumulator < 0)
        *programCounter = *location;
    else
        *programCounter += 1;
}

void branchZero(const size_t *location, const int *accumulator, size_t *programCounter)
{
    if (*accumulator == 0)
        *programCounter = *location;
    else
        *programCounter += 1;
}

void executeProgram(int memory[])
{
    size_t programCounter = 0;
    int accumulator = 0;
    int operation = 0;
    size_t memoryAddress = 00;

    do
    {
        operation = memory[programCounter] / 100;
        memoryAddress = memory[programCounter] % 100;

        switch (operation)
        {
        case READ:
            read(memory, &memoryAddress);
            programCounter++;
            break;
        case WRITE:
            write(memory, &memoryAddress);
            programCounter++;
            break;
        case LOAD:
            load(memory, &memoryAddress, &accumulator);
            programCounter++;
            break;
        case STORE:
            store(memory, &memoryAddress, &accumulator);
            programCounter++;
            break;
        case ADD:
            add(memory, &memoryAddress, &accumulator);
            programCounter++;
            break;
        case SUBTRACT:
            subtract(memory, &memoryAddress, &accumulator);
            programCounter++;
            break;
        case DIVIDE:
            divide(memory, &memoryAddress, &accumulator);
            programCounter++;
            break;
        case MULTIPLY:
            multiply(memory, &memoryAddress, &accumulator);
            programCounter++;
            break;
        case BRANCH:
            branch(&memoryAddress, &programCounter);
            break;
        case BRANCHNEG:
            branchNeg(&memoryAddress, &accumulator, &programCounter);
            break;
        case BRANCHZERO:
            branchZero(&memoryAddress, &accumulator, &programCounter);
            break;
        }

    } while (operation != HALT);
}