
// CS 5008 Lab 3
// Author: Nianlong Lin
// Date:9/24/2023
// this program is to build a little tool to count assembly instructions.


#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH = 100

int main(int argc, char *argv[]) {
    // if the argc is not equal to 2, print out the info and quit
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // open the file
    char *filename = argv[1];
    FILE *fp = fopen(filename, "r");
    if (fp = NULL) {
        printf("Failed to open the file: %s\n", filename);
        return 1;
    }

    int add_count = 0, mov_count = 0, imul_count = 0;
    int div_count = 0, lea_count = 0, push_count = 0, pop_count = 0, ret_count = 0;
    int total_cycles = 0;

    char line[MAX_LINE_LENGTH];

    // use while loop to get the number of instructions
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        char *token = strtok(line, " \t\n");
        while (token != NULL){
            if (strncasecmp(token, "add", 3) == 0) {
                add_count++;
                total_cycles++;
            } else if (strncasecmp(token, "mov", 3) == 0) {
                mov_count++;
                total_cycles++;
            } else if (strncasecmp(token, "imu", 3) == 0) {
                imul_count++;
                total_cycles += 2;
            } else if (strncasecmp(token, "div", 3) == 0) {
                div_count++;
                total_cycles += 4;
            } else if (strncasecmp(token, "lea", 3) == 0) {
                lea_count++;
                total_cycles++;
            } else if (strncasecmp(token, "pus", 3) == 0) {
                push_count++;
                total_cycles++;
            } else if (strncasecmp(token, "pop", 3) == 0) {
                pop_count++;
                total_cycles++;
            } else if (strncasecmp(token, "ret", 3) == 0) {
                ret_count++;
                total_cycles++;
            }
            token = strtok(NULL, " \t\n");
        }
    }

    // close the file
    fclose(fp);

    // print each number of instructions
    printf("ADD %d\n", add_count);
    printf("MOV %d\n", mov_count);
    printf("IMU %d\n", imul_count);
    printf("DIV %d\n", div_count);
    printf("LEA %d\n", lea_count);
    printf("PUSH %d\n", push_count);
    printf("POP %d\n", pop_count);
    printf("RET %d\n", ret_count);

    printf("\nTotal Instructions = %d\n", add_count + mov_count + imul_count + div_count + lea_count + push_count + pop_count + ret_count);
    printf("Total Cycles = %d\n", total_cycles);


    return 0;
}

