# High Performance Linked Lists
This project aims to provide a better and efficient way of implementing the C++ Linked Lists Data Structure.
The conventional implementation method makes use of malloc() function, this function is used to allocate the system memory for the Linked List Node by making a System call. Everytime a system call is made, the operating system halts the program execution, allocates the required chunk of memory and then resumes the program. In case, the frequency of allocation and deallocation is very high(a huge size of the linked list might bring up the case), this might affect the execution time of the program, making the data structure highly ineffcient for such tasks.
Now comes the saviour: Memory Pool.
The project makes use of the concept of memory pool in which, a sufficient enough chunk of memory is reserved in advance so that the program does not require making a system call, and the memory requirements for the node be fulfilled by just allocating from the reserved pool.
The above procedure definitely makes the program faster and more efficient.

# The Repository consists of 2 directories:
# 1) Simple Linked Lists: 
    The implementation of the concept on the normal C++ Linked Lists Data Structure.
    ![Screenshot](https://github.com/Akashi96/High-Performance-Linked-Lists/tree/master/Simple%20Linked%20Lists-Memory%20Pool/Screenshot.png)
# 2) Stratified Linked Lists: 
    The implementation of the concept on a modified and more advanced model of the Linked Lists Data Structure.  
