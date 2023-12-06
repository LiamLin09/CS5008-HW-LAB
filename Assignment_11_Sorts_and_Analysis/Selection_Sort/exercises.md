# Exercises

1. What do you think the Big-O (worst-case) complexity of this algorithm is? 
2. What do you think the best-case complexity of this algorithm is? 
	- Note-- assume you do not have any information about if the array is already sorted or not.
3. Does selection sort require any additional storage beyond the original array? 
	- i.e. Did you have to allocate any extra memory to perform the sort?
5. Would the Big-O complexity change if we used a linked list instead of an array?

## Answers:

1. *edit your answer here for question 1*
The Big-O (worst-case) complexity of the selection sort algorithm is O(n^2). This is because the algorithm compares each element to every other element in the array, resulting in quadratic time complexity.

2. *edit your answer here for question 2*
The best-case complexity of the selection sort algorithm is also O(n^2), regardless of whether the array is already sorted or not. This is because selection sort always looks for the smallest or largest element in the unsorted part of the array, even if the array is already sorted.

3. *edit your answer here for question 3*
Selection sort does not require any additional storage beyond the original array. This is because it sorts the elements in place, meaning it rearranges the elements within the array itself without needing additional storage.

4. *edit your answer here for question 4*
The Big-O complexity would not change if we used a linked list instead of an array. The time complexity would still be O(n^2) because the algorithm still needs to compare each element to every other element. However, the space complexity could potentially increase due to the extra space required for the pointers in the linked list.
