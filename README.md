# CodeSample

These three files were part of a Data Structures and Algorithms class that had us create and implement a hashtable. 
The main file is Hashtable.h. 

# This implementation was done in Hashtable.h and I implemented my hashtable by using an array of pointers to pairs. 

# Hashtable.h: 
The code is done in a C++ template that allows users to input their own data type for the value of the pairs. 
However, the keys must be strings. I created an add function that adds to my hashtable using quadratic probing, a lookup function, a reportAll function
that prints everything in the table, and a resize function for when my table becomes too small to support quadratic probing.
I also implemented a hash function with specified instructions from the assignment. 

# Hashtable.cpp: 
This is where I tested out my hashtable. I tested it against the Birthday Paradox, and I also tested to see if 
initializing my size to a non-prime number would ruin my quadratic probing by sending it into an infinite loop. 

# Makefile:
This generates an executable called hash. This executable runs my Hashtable.cpp program, testing my Hashtable.h implementation.
This can be run by inputting ./hash into the terminal. 

There is also a folder of tests that can be run to test my Hashtable.h implementation. Once you enter the folder for these tests in your terminal,
just type the command "make" and the tests will run automatically. 

I have also included a link to the project writeup for more information. 
# Project Writeup Link: https://bytes.usc.edu/cs104/homework/hw5/programming/
