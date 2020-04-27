#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <cstdio>
using namespace std;

int Search(int arr[], int requiredKey, int arrSize)
{
	for (int i = 0; i < arrSize; i++)
	{
		if (arr[i] == requiredKey)
			return i;
	}
	return -1;
}

const int n = 100;
int first, last;

void quickSortRec(int *mas, int first, int last)    // сортировка с рекурсией
{
	int mid, count;
	int f = first, l = last;
	mid = mas[(f + l) / 2];
	do
	{
		while (mas[f] < mid) f++;
		while (mas[l] > mid) l--;
		if (f <= l)
		{
			count = mas[f];
			mas[f] = mas[l];
			mas[l] = count;
			f++;
			l--;
		}
	} while (f < l);
	if (first < l) quickSortRec(mas, first, l);
	if (f < last) quickSortRec(mas, f, last);
}

void quickSort(int* a, int first, int last)   // сортировка без рекурсии
{

	int i, j;   			
	int lb, ub;  		
	int lbstack[2000], ubstack[2000];
	long stackpos = 1;   	
	long ppos;            
	int pivot;            
	int temp;
	lbstack[1] = 0;
	ubstack[1] = last ;

	do {
		lb = lbstack[stackpos];
		ub = ubstack[stackpos];
		stackpos--;

		do {
			ppos = (lb + ub) >> 1;
			i = lb; j = ub; pivot = a[ppos];

			do {
				while (a[i] < pivot) i++;
				while (pivot < a[j]) j--;

				if (i <= j) {
					temp = a[i]; a[i] = a[j]; a[j] = temp;
					i++; j--;
				}
			} while (i <= j);
			if (i < ppos) {  
				if (i < ub) {    
					stackpos++;     
					lbstack[stackpos] = i;
					ubstack[stackpos] = ub;
				}
				ub = j;            
			}
			else {       	  
				if (j > lb) {
					stackpos++;
					lbstack[stackpos] = lb;
					ubstack[stackpos] = j;
				}
				lb = i;
			}
		} while (lb < ub);      
	} while (stackpos != 0);   
}

int BSearch(int arr[], int left, int right, int key)
{
	int midle = 0; // 3 пункт
	while (1)	   // реализации в main нет, т.к. в задании об этом не сказано
	{
		midle = (left + right) / 2;
		if (key < arr[midle])
			right = midle - 1;
		else if (key > arr[midle])
			left = midle + 1;
		else return midle;
		if (left > right) return -1;
	}
}

void main()
{
	const int arrSize = 10000;		  // 1 пункт
	int arr[arrSize];
	int key = 0;
	int element = 0;
	srand(time(NULL));
	for (int i = 0; i < arrSize; i++)
	{
		arr[i] = rand() % 2000 - 1000;
	}
	cout << "Required Key? ";
	cin >> key;
	element = Search(arr, key, arrSize);

	if (element != -1)
		cout << key << " is at [" << element << "]" << endl;
	else
		cout << "Key not found" << endl;

	int *Array = new int[n];		  // 2 пункт
	cout << "Before: " << endl;
	for (int i = 0; i < n; i++)
	{
		Array[i] = (rand() % 21) - 10;
		cout << Array[i] << " ";
	}

	first = 0; last = n-1;
	quickSortRec(Array, first, last);   // поменяйте на quickSort, чтобы проверить обычную сортировку (без рекурсии)
	cout << endl << "After: " << endl;
	for (int i = 0; i < n; i++) cout << Array[i] << " ";
	delete[]Array;

	std::clock_t start;				 // 4 пункт
	double unsortedDur;
	double sortedDur;
	start = std::clock();
	for (int i = 0; i < 1000; i++)
	{
		element = Search(arr, key, arrSize);
	}	
	unsortedDur = ((std::clock() - start) / (double)CLOCKS_PER_SEC);   
	cout << endl << "Unsorted search's duration: " << unsortedDur << " ms" << endl;

	quickSortRec(arr, 0, 9999);
	start = std::clock();  // В задании про это ничего не написано, так что оба поиска были обычными (небинарными)
	for (int i = 0; i < 1000; i++)
	{
		element = Search(arr, key, arrSize);
	}
	sortedDur = ((std::clock() - start) / (double)CLOCKS_PER_SEC) ;
	cout << endl << "Sorted search's duration: " << sortedDur << " ms" << endl;
	if (unsortedDur < sortedDur) cout << ("Unsorted search is faster") << endl;
	if (unsortedDur > sortedDur) cout << ("Sorted search is faster") << endl;
	cin.get();
	return;
}
