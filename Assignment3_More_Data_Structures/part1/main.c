// Compile this assignment with: gcc -g -Wall main.c -o main
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "my_dll.h"
// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.

int test_create_free() {
    dll_t* test = create_dll();
    free_dll(test);
    return 1;
}

int test_push_pop_back() {
    int passed = 0;
    dll_t* test = create_dll();
    dll_push_back(test, 142);
    dll_pop_back(test);
    if (0 == dll_size(test)) {
        passed = 1;
    }
    free_dll(test);
    return passed;
}

int test_push_pop_front() {
    int passed = 0;
    dll_t* tset = create_dll();
    dll_push_front(test, 142);
    dll_pop_front(test);
    if (0 == dll_size(test)) {
        passed = 1;
    }
    free_dll(test);
    return passed;
}

int test_insert_remove() {
    int passed = 0;
    dll_t* test = create_dll();
    dll_insert(test, 0, 142);
    dll_remove(test, 0);
    if (0 == dll_size(test)) {
        passed = 1;
    }
    free_dll(test);
    return passed;
}

int test_get_get() {
    int passed = 0;
    dll_t* test = create_dll();
    dll_push_back(test, 142);
    dll_set(test, 0, 143);
    if (143 == dll_get(test, 0)) {
        passed = 1;
    }
    free_dll(test);
    return passed;
}

int test_size() {
    int passed = 0;
    dll_t* test = create_dll();
    dll_push_back(test, 142);
    dll_push_front(test, 142);
    dll_pop_back(test);
    if (1 == dll_size(test)) {
        passed = 1;
    }
    free_dll(test);
    return passed;
}

int (*unitTtests[]) (int) = {
    test_create_free,
    test_push_pop_back,
    test_push_pop_front,
    test_insert_remove,
    test_get_get,
    test_size,
    NULL
};

// ====================================================
// ================== Program Entry ===================
// ====================================================
int main(){
    // dll_t * dll = create_dll();
    unsigned int testsPassed = 0;
    int counter = 0;
    while(unitTests[counter] != NULL) {
        printf("==============Unit Test %d=============\n", counter);
        if (1 == unitTtests[counter](1)) {
            printf("passed test!!!\n");
            testsPassed++;
        } else {
            printf("SORRY!!test failed, missing functionality, or incorrect test\n");
        }
        counter++;
    }
    printf("%d of %d tests passed!\n", testsPassed, counter);


    return 0;
}
