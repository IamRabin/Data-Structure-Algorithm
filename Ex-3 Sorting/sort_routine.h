#ifndef __SORT_ROUTINE__
#define __SORT_ROUTINE__


template<class T>
void swap(T* A, const int i, const int j) {
    T temp{A[i]};
    A[i] = A[j];
    A[j] = temp;
}

/**
  *Inplace  Insertion sort
  */
template<class T>
void insertion_sort(T* A, const int n) {

    for (int i=1; i < n; ++i) {
        // first element is sorted on its own so begin from the next to the first element i=1
        int j{i};
        //moving to the left until it finds its sorted position.
        while (j > 0 && A[j] < A[j - 1]) {
            swap(A, j - 1, j);
            --j;
        }
    }
}

/**
  * This function is  used  for partition at the pivot by Quicksort and Select. All the duplicates are stashed to the left.
  */
template<class T>
int partition(T* A, int low, int high, int pivot) {
    swap(A, low, pivot);//swapping pivot and first element
    pivot = low;
    ++low;
    //if A[i] is greater than pivot ,shift towards greater section of the array else in the section holding smaller elements.
    while (low <= high) {
        if (A[low] > A[pivot]) {
            swap(A, low, high);
            --high;
        }

        else {
            ++low;
        }
    }
    swap(A, pivot, high);
    return high;
}

#endif // __SORT_ROUTINE__
