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
#define HALT 43         // Halt - the program has completed its task.


int main()
{
    return 0;
}