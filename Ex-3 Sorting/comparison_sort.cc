#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <cmath>

#include "heap.h"
#include "sort_routine.h"
#define MAX_VALUE 25


template<class T>
void quicksort(T* A, int low, int high, int (*func)(const int, const int)=[](const int low, const int high) {(void)high; return low;}) {
    // as long as the current subarray has length > 1
    while (low < high) {
        int pivot = partition(A, low, high-1, func(low, high));//chooses pivot
        quicksort(A, low, pivot, func);//recursively sorting from low index to pivot.
        low = pivot + 1; //moving to the right of the pivot
    }
}

/**
  *
  * It is  used to create a max-heap
  */
template<class T>
struct CompareItems {
    // default constructor
    CompareItems() = default;
    // overload of operator(); returns true if a > b, false otherwise
    bool operator()(const T a, const T b) {
        return a > b;
    }
};

/**
 * This function implements heapsort algorithm .It sorts in place by building a max heap included in header file.
  */
template<class T>
void heapsort(T* A, const std::size_t n) {
    // Root will the maximum in the heap
    BinaryHeap<T, CompareItems<T>> h{A, n, true};
    // for each element - 1
    for (std::size_t i=n-1; i >= 1; --i) {
        // swapping the i-th element and the root
        h.swap(i, 0);
        // removing the last leaf
        --h.size;
        // fix the max-heap
        h.heapify(0);
    }
    //
    // sorted when data members of the heap points to the same memo location
}

/****************************************************************
  ************************Main function****************************
  ****************************************************************/

int main() {



    // Insertion Sort has time complexity of O(n^2) in the worst case

    std::cout << "INSERTION_SORT FOR THE WORST CASE:" << std::endl;
    for (std::size_t dim : {10,30, 60, 100, 1000, 3000, 6000, 10000, 100000}) {
        int test[dim];
        // reverse-sorted values, which is the worst-case for insertion sort
        int count = 0;
        for (int i=dim-1; i >= 0; --i) {
            test[i] = count;
            ++count;
        }
        // measure time
        auto start = std::chrono::high_resolution_clock::now();
        insertion_sort(test, dim);
        auto end = std::chrono::high_resolution_clock::now();
        // print result
        std::cout << "Size: " << dim << std::endl;
        std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
    }

    // the following block of code proves by testing that Insertion Sort takes time O(n) in the best case

    std::cout << " INSERTION_SORT FOR THE BEST CASE:" << std::endl;
    for (std::size_t dim : {10,30, 60, 100, 1000, 3000, 6000, 10000, 100000}) {
        int test[dim];
        // sorted values, the best case for insertion sort
        for (std::size_t i=0; i < dim; ++i) {
            test[i] = i;
        }
        // measure time
        auto start = std::chrono::high_resolution_clock::now();
        insertion_sort(test, dim);
        auto end = std::chrono::high_resolution_clock::now();
        // print result
        std::cout << "Size: " << dim << std::endl;
        std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
    }

    //  Quicksort takes time O(n^2) in the worst case

    int (*choose_pivot) (const int, const int);   // function pointer selects the pivot here.
    choose_pivot = [] (const int low, const int high) -> int {(void)high; return low;};  //  returns the first element, which is the worst case for Quicksort
    std::cout << "TESTING THE IMPLEMENTATION OF QUICKSORT IN THE WORST CASE:" << std::endl;
    for (std::size_t dim : {10,30, 60, 100, 1000, 3000, 6000, 10000, 100000}) {
        int test[dim];
        // initialize already sorted array
        for (std::size_t i=0; i < dim; ++i) {
            test[i] = i;
        }
        auto start = std::chrono::high_resolution_clock::now();
        quicksort<int>(test, 0, dim, choose_pivot);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Size: " << dim << std::endl;
        std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
    }

    //  Quicksort has time complexity of  O(nlogn) for best case

    choose_pivot = [] (const int low, const int high) -> int {return (low + high) / 2;};  //  returns the midpoint,which is the best case for Quicksort with ascendingly or descendingly sorted
    std::cout << " QUICKSORT FOR THE BEST CASE:" << std::endl;
    for (std::size_t dim : {10,30, 60, 100, 1000, 3000, 6000, 10000, 100000}) {
        int test[dim];
        // initialize already sorted array
        for (std::size_t i=0; i < dim; ++i) {
            test[i] = i;
        }
        auto start = std::chrono::high_resolution_clock::now();
        quicksort<int>(test, 0, dim, choose_pivot);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Size: " << dim << std::endl;
        std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
    }

    // Heapsort

    std::cout << " HEAPSORT:" << std::endl;
    for (std::size_t dim : {10,30, 60, 100, 1000, 3000, 6000, 10000, 100000}) {
        int test[dim];
        // initialize array of random values
        for (std::size_t i=0; i < dim; ++i) {
            test[i] = rand()%(2*MAX_VALUE)-MAX_VALUE;
        }
        auto start = std::chrono::high_resolution_clock::now();
        heapsort(test, dim);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Size: " << dim << std::endl;
        std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
    }

    return 0;
}
