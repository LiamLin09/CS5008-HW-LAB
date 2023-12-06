**Instructions** 

- Discuss and answer the following questions (Make sure to elaborate and justify your responses):
- If you would like to hand write or draw your answers, then scan or take a picture of a file called exercises.pdf or exercises.png and put it in this directory.


# Exercises

1. Explain: What do you think the Big-O (worst-case) complexity of the merge sort algorithm is and why? 

the Big-O (worst-case) complexity of the merge sort algorithm is O(nlogn).
this complexity arises due to the nature of the algo's divide and merge approach.
the merge sort algo starts by dividing the array into sub-arrays. this division process is recursive, 
halving the arrays until each sub-array contains only one element. the division of the array into two halves continues, which takes logn divisions for an array of size n. after the division, the algo starts merging these sub-array back together. each merge operation requires comparing elements and placing them in order, which take linear time in the size of the sub-array. 
since the merging process happens at each level of the divided arrays, and there are logn levels, the total time for merging across all levels of the recursion is nlogn.

2. Explain: What do you think the best-case complexity of the merge sort algorithm is and why?

the Big-O (best-case) complexity of the merge sort algorithm is O(nlogn).
the complexity remains consistent across all cases - best, average, and worst-case scenarios.
Merge sort employs a divide-and-merge strategy, consistently dividing the array into halves until each sub-array contains a single element.
these sub-arrays are then merged back together in a sorted manner.
the overall time complexity is a product of these two steps, resulting in Big-O (nlongn).
the reason it is the same for all cases is due to the methodical way merge sort divides and merges the array, which does not change regradless of the initial order of elements.


3. Does merge sort require any additional storage beyond the original array? If so how much and why?

yes, merge sort requires additional storage beyond the original array. this additional storage is used during the merging phase of the algo.
1) when two halves of an array are merged, they need to be combined into a new array to maintain the sorted order. this necessitates creating additional arrays to hold the merged result before it is copied back into the original array.
2) the amount of additional storage required is proportional to the size of the array being sorted. in the worst-case scenario, you would need additional space equal to the size of the original array. this is because, at the final merging stage, you are combining two halves of the original array, which collectively contain all the elements of the original array.

4. How much time in Big-O does it take to merge all of the subarrays together? Explain or draw why?

the time complexity of merging all of the subarrays in merge sort is O(nlogn).
1) merging two sorted arrays: the basic operation in merge sort is merging two sorted arrays. this operation has a time complexity of O(n), where n is the total number of elements in both arrays. this is because each element in both arrays is visited exactly once during the merge process.
2) merge sort structure: merge sort recursively divides the array into two halves, sorts each half, and then merges them back together. the division of the array continues until the sub-arrays have only one element, after which the merge process begins.
3) levels of merging: the number of levels in merge sort is logn, where n is the number of elements in the original array. this is because, the array is repeatly halved. for example, an array of 8 elements is split into 4, then into 2, and finally into individual elements, resulting in 3 levels.
4) merging at each level: at each level, the total number of elements across all sub-arrays being merged is n. even though the sub-arrays are smaller, when combined at each level, they sum up to n.
5) combining the factors: since there are logn levels, and at each level, the merge operation takes O(n) time, the overall time complexity is O(nlogn).

