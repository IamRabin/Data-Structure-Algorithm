#include <iostream>
#include <chrono>

#include "sort_routine.h"

#define MAX_VALUE 25

/**
 * This function is used in select algorithm ,here pivot is selected based on the median of the median to optimize the sorting algorthim.
  */
template<class T>
int select_pivot(T* A, int low, int high) {
    // With one chunk just use the insertion sort and return the median.
    if ((high - low + 1) <= 5) {
        insertion_sort(A + low, high - low + 1);
        return (low + high + 1) / 2;
    }
    // splitting the array into five chunks and sorting successively.

    for (int i=low; i <= high; i+=5) {
        int a{i + 4};  //last elemet index
        //take care of chunk other than multiple of 5
        insertion_sort(A + i, (a > high) ? (high - low + 1) % 5 : 5);
    }
    int ind{low};  // counter

    for (int i=low; i <= high; i+=5) {
        int a{i + 2};  // the median index
        swap(A, low + ind, (a > high) ? high : a);// shift medians to the start of the array
        ++ind;
    }
    int n = (high - low + 1) / 5;  //total chunks

    return select_pivot(A, low, low + n); //recusively find the median of the medians
}

/**
  *This function used for select will stash all the repeated pivot element at the end of the subarray and the last one will be the pivot.
  */
template<class T>
int partition_select(T* A, int low, int high, int pivot) {
    swap(A, low, pivot);// swapping the first element and the pivot
    int left = low + 1;
    int right = high;

    while (left <= right) {
        // Move upwards if A [left] is lower than Pivot.
        if (A[left] < A[low]) {
            ++left;
        }
        // if A[left] is equal to pivot swap with right and move both directions

        else if (A[left] == A[low]) {
            swap(A, left, right);
            ++left;
            --right;
        }
   }
   swap(A, right, low);
   // 'right' gives the first pivot in the array section
   return right;
}

/**
  * This function implements select algoithm which simply sorts array below the threshold. It avoids recusive calls for improved efficieny.
  */
template<class T>
int select(T* A, int i, int low, int high, int threshold=10) {
    while (true) {
        // For smaller array than threshold just simply use insertion_sort.
        if ((high - low + 1) <= threshold) {
            insertion_sort(A + low, high - low + 1);
            return low + i;
        }
        int j = select_pivot(A, low, high); //selects pivot

        // using the sleceted pivot j to partition the array with pivot positioned in between smaller and greater elements.
        int k = partition(A, low, high, j);

        //if pivot is smaller than the element, we are in the greater section of the array in w.r.t pivot.

        if (i > k) {
            low = k + 1;

            return select(A, i, k + 1, high);
        }
        // for repeated pivot

        else {
            // The first pivot happens in start index and the repeated pivot is before the start pivot.
            int start = partition_select(A, low, k, k);

            if (start <= i && i <= k) {
                return k; //returns the pivot as k itself is the pivot .
            }
            //
            // continuing in the section other than repeated section.
            else if (i < start) {
                high = start - 1;
                return select(A, i, low, start - 1);
            }
        }
    }
}

/****************************************
  * ************Main function***************
  ****************************************/


int main() {
    std::cout << "Implementing Select" << std::endl;
    for (std::size_t dim : {10,50, 100, 1000, 3000, 8000, 10000, 100000}) {
        double test[dim];
        for (std::size_t i=0; i < dim; ++i) {
            test[i] = rand()%(2*MAX_VALUE)-MAX_VALUE;
        }

        int i = rand() % dim;
        auto start = std::chrono::high_resolution_clock::now();
        select(test, i, 0, dim - 1);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Size: " << dim << std::endl;
        std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
    }
    return 0;
}
