// CS 5008 LAB 8
// Author: Nianlong Lin
// Date: 10/30/2023

#include <stdio.h>

// TODO: Implement iterative solution here
int factorial(int n){

  if (n < 0) return -1;
  int result = 1;
  for (int i = 1; i <= n; i++) {
    result = result * i;
  }
  return result;
};

// TODO: Implement recursive solution here
int factorial_rec(int n){
  if (n < 0) {
    return -1;
  }
  if (n == 0) {
    return 1;
  }
  return n * factorial_rec(n - 1);
}

int main(){

  // Both of these should print the same result!
  printf("factorial(10) = %d\n",factorial(10));
  printf("factorial_rec(10) = %d\n",factorial_rec(10));


  return 0;
}
