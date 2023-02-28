#ifndef MY_LIBRARY_H_
#define MY_LIBRARY_H_

#include<string>
using namespace std;

// check input data is usigned interger or 0?
bool isUnsignedInterger(string str);
void printArray(unsigned int[], unsigned int size_array);
// return true(Y/y) or false(N/n)
bool YNQuestion();
void selectionSort(unsigned int* arr, unsigned int size_array);
void bubbleSort(unsigned int* arr, unsigned int size_array);

#endif// !MY_LIBRARY_H
