# Exercises

Discuss and answer the following questions (Make sure to elaborate and justify your responses):

1. How good is the provided hash function--are we really getting constant time operations with our hashmap?
2. What is one other way you could implement the hash function? Anything creative is acceptable in this answer.
3. If I have to resize the hashmap to add more buckets, what is th Big-O complexity?
4. What is 'open addressing' in regards to hash maps and hash tables?

## Answers:

1. to determine the efficiency of the provided hash function, we need to analyze its collision rate.
if the collision rate is low, then the hash function is good and we can expect constant time operations with our hashmap.
however, if the collision rate is high, then the hash function is not efficient and we may experience slower operations.

2. one other way to implement the hash function is to use ASCII values of the characters in the key.
we can add the ASCII values of the characters in the key and then divide the sum by the number of buckets.
the remainder of the division will be the index of the bucket the key will be stored.

3. if we have to resize the hashmap to add more buckets, the Big-O complexity will be O(n) where n is the number of buckets.
this is because each of the "n" iterms needs to be re-inserted into the new bucket array.

4. open addressing is a method of collision resolution in hash tables.
in open addressing, if a collision occurs, the key is stored in the next available bucket.
this is different from chaining where the key is stored in a linked list in the same bucket.


