// CS 5008 Assignment 8
// Author: Nianlong Lin
// Date: 10/30/2023


#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "my_bst.h"
// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.

// You may add as many unit tests as you like here
// A few have been provided for your convenience.
// We will use our own test suite (i.e. replacing this file)
// in order to test your implementation from my_bst.

// Testing allocation
int unitTest1(){
    int result;
    bst_t * testBST = bst_create();
    if (testBST!=NULL){
        result = 1;
    }else{
        result = 0;
    }
    bst_free(testBST);
    return result;    
}

// Add and find a node
int unitTest2(){
    int result;
    bst_t * testBST = bst_create();
    bst_add(testBST,78);
    result = bst_find(testBST,78);
    bst_free(testBST);    
    return result;
}

// Sums the nodes in a BST
int unitTest3(){
    int result;
    bst_t * testBST = bst_create();
    bst_add(testBST, 5);
    result = bst_sum(testBST);
    bst_free(testBST);   

    if(result==5){ 
        return 1;
    }
    return 0;
}

// test size funtion.
int unitTest4() {
    int result;
    bst_t* testBST = bst_create();
    bst_add(testBST, 5);
    bst_add(testBST, 10);
    bst_add(testBST, 15);
    result = bst_size(testBST);
    bst_free(testBST);

    if (result == 3) {
        return 1;
    }
    return 0;
}

// test print function.
int unitTest5() {
    int result;
    bst_t* testBST = bst_create();
    bst_add(testBST, 5);
    bst_add(testBST, 10);
    bst_add(testBST, 15);
    printf("Expected output: 5 10 15\n");
    printf("Your output: ");
    bst_print(testBST, 0);
    printf("\n");
    result = 1;
    bst_free(testBST);

    return result;
}

// test empty BST
int unitTest6() {
    int result;
    bst_t* testBST = bst_create();
    result = bst_empty(testBST);
    bst_free(testBST);

    if (result == 1) {
        return 1;
    }
    return 0;
}



// TODO: Add more tests here at your discretion
int (*unitTests[])(int)={
    unitTest1,
    unitTest2,
    unitTest3,
    unitTest4,
    unitTest5,
    unitTest6,
    NULL
};

// ====================================================
// ================== Program Entry ===================
// ====================================================
int main(){
	
	unsigned int testsPassed = 0;
    // List of Unit Tests to test your data structure
    int counter =0;
    while(unitTests[counter]!=NULL){
		printf("========unitTest %d========\n",counter);
		if(1==unitTests[counter](1)){
			printf("passed test\n");
			testsPassed++;	
		}else{
			printf("failed test, missing functionality, or incorrect test\n");
		}
        counter++;
    }

    printf("%d of %d tests passed\n",testsPassed,counter);

    return 0;
}
