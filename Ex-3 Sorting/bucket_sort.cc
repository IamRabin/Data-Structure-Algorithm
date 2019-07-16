#include <iostream>
#include <cmath>
#include <chrono>

#include "sort_routine.h"

#define MAX_VALUE 25

/**
  * Dyanmic array which changes its size and manages memory efficiently.
  */
template<class T>
class List {
    std::size_t free_slots;  // free space
    std::size_t _size;  // number of elements
    T* data;  // array of data
  public:
    // default constructor, initializes a 1-dimensional array
    List() : free_slots{0}, _size{0}, data{new T[1]} {}
    // returns  the size
    std::size_t size() const noexcept {
        return _size;
    }
    // inserts a new value
    void append(const T& value) {
        // check if there is free space, if not reallocate data
        check_and_alloc();
        // append value and update members
        data[_size] = value;
        ++_size;
        --free_slots;
    }
    // sorts the bucket. Uses insertion_sort
    void sort() noexcept {
        insertion_sort(data, _size);
    }
    // overload of operator[]
    T& operator[](const std::size_t i) const noexcept {
        return data[i];
    }
    // Destructor
    ~List() {
        delete[] data;
    }

  private:
    void check_and_alloc() {
        // if still free space in the data, do nothing
        if (free_slots != 0) {
            return;
        }
        // Allocating double the size of the array
        T* new_data{new T[_size * 2]};
        // copy the elements one by one
        for (std::size_t i=0; i < _size; ++i) {
            new_data[i] = data[i];
        }
        data = new_data;
        new_data = nullptr;
        delete[] new_data;
        free_slots = _size;
    }
};

/**
  * Bucket sort; takes an array to sort 'A', its size 'n' and the number of buckets 'k'. Builds an
  * array of List objects as buckets
  */
void bucket_sort(double* A, const std::size_t n, const std::size_t k) {
    // allocate an array of empty lists, as many as the number of buckets
    List<double>* B{new List<double>[k]{}};
    // append the values of A to the corresponding bucket
    for (std::size_t i=0; i < n; ++i) {
        B[int(floor(A[i] * k))].append(A[i]);
    }
    std::size_t i{0};
    // iterate over the buckets
    for (std::size_t j=0; j < k; ++j) {
        List<double>& bucket = B[j];
        // sort the bucket
        bucket.sort();
        // reverse the bucket into A
        for (std::size_t l=0; l < B[j].size(); ++l) {
            A[i] = B[j][l];
            ++i;
        }
    }
    
}

/**
  * Main function
  */
int main() {



    std::cout << "BUCKET SORT" << std::endl;
    for (std::size_t dim : {10,50, 100, 1000, 3000, 6000, 10000, 100000}) {
        double test[dim];
        for (std::size_t i=0; i < dim; ++i) {
            test[i] = rand() / (RAND_MAX + 1.);  // sample from [0, 1]
        }
        // measure time
        auto start = std::chrono::high_resolution_clock::now();
        bucket_sort(test, dim, dim / 2);
        auto end = std::chrono::high_resolution_clock::now();
        // print result
        std::cout << "Size: " << dim << std::endl;
        std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
    }

    return 0;
}
