#include <iostream>
#include <cmath>
#include <chrono>

#include "sort_routine.h"

#define MAX_VALUE 20

/**
 * This function implements counting sort which tkaes an array A  of size n and puts into another array B.
 *
  *
  */
template<class T>
void counting_sort(T* A, T* B, const std::size_t low, const std::size_t high, const std::size_t n) {
    std::size_t k{high - low + 1};  // length
    // allocating a new array
    int* C{new int[k]};
    for (std::size_t j=0; j < k; ++j) {
        C[j] = 0;//initalise to 0
    }
    for (std::size_t i=0; i < n; ++i) {
        ++C[A[i] - low];
    }

    for (std::size_t j=1; j < k; ++j) {
        C[j] += C[j - 1];
    }
    // iterate backward on A and use C to place the elements in their correct position in B
    for (std::size_t i=n; i >= 1; --i) {
        T v{A[i - 1]};
        B[C[v - low] - 1] = v;
        --C[v - low];
    }
    // deallocate
    delete[] C;
}

/**
  * Dyanmic array which changes its size and manages memory efficiently. It is used in bucket_sort.
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

        check_and_alloc(); //checking free space to allocate
        // assign values and update
        data[_size] = value;
        ++_size;
        --free_slots;
    }
    // sorts the bucket using insertion_sort
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
    //  dynamically reallocate the array
    void check_and_alloc() {
        // iif free space , its ok
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

int main() {

  std::cout << " COUNTING SORT" << std::endl;
  for (std::size_t dim :{10,30, 60, 100, 1000, 3000, 6000, 10000, 100000}) {
      int test[dim];
      int b[dim];
      // initialize array of random values
      for (std::size_t i=0; i < dim; ++i) {
          test[i] = rand()%(2*MAX_VALUE)-MAX_VALUE;
      }
      // measure time
      auto start = std::chrono::high_resolution_clock::now();
      counting_sort(test, b, -MAX_VALUE, MAX_VALUE, dim);
      auto end = std::chrono::high_resolution_clock::now();
      // print result
      std::cout << "Size: " << dim << std::endl;
      std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
  }
  return 0;
}
