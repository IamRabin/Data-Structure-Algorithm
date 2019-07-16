#include <iostream>
#include <cmath>
#include <chrono>

#define MAX_VALUE 20

/**
  *This function implements Radix sort also uses counting sort routine.
  */
void radix_sort(int* A, const int digit, const std::size_t n) {  // digit is the max number of digits
    // C is the counter array, temp will store intermediate results.
    int* C{new int[10]};
    int* temp{new int[n]};
    // From the most significant digit to the least significant digit
    for (int j=pow(10, digit - 1); j >=1; j*=10) {
        //  counting sort according to digit j
        for (std::size_t i=0; i < 10; ++i) {
            C[i] = 0;
        }
        for (std::size_t i=0; i < n; ++i) {
            ++C[(A[i] / j) % 10];
        }
        for (std::size_t i=1; i < 10; ++i) {
            C[i] += C[i - 1];
        }
        for (std::size_t i=n; i >= 1; --i) {
            int v{A[i-1]};
            temp[C[(A[i-1] / j) % 10] - 1] = v;
            --C[(A[i-1] / j) % 10];
        }
        // transfer intermediate result into A
        for (std::size_t i=0; i < n; ++i) {
            A[i] = temp[i];
        }
    }
    // deallocate
    delete[] temp;
    delete[] C;
}

/****************************************************
  ******************* Main function*********************
  ****************************************************/
int main() {


    std::cout << " RADIX SORT" << std::endl;
    for (std::size_t dim : {10,30, 60, 100, 1000, 3000, 6000, 10000, 100000}) {
        int test[dim];
        // initialize array of random values
        for (std::size_t i=0; i < dim; ++i) {
            test[i] = rand()%(2*MAX_VALUE)-MAX_VALUE;
        }
        auto start = std::chrono::high_resolution_clock::now();
        radix_sort(test, 2, dim);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Size: " << dim << std::endl;
        std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
    }

    return 0;
}
