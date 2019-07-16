#include <iostream>
#include <chrono>

#include "heap.h"
#define MAX_VALUE 25


template<class T>
struct CompareItems {
    // default constructor
    CompareItems() = default;
    // overload of operator(); returns true if a > b
    bool operator()(const T a, const T b) {
        return a > b;
    }
};

int main() {


    std::cout << " IMPLEMENTATION OF HEAPIFY:" << std::endl;
    // random seed
    srand(11);
    // loop over the set of dimensions to investigate
    for (std::size_t dim : {1000, 5000, 10000, 50000, 100000, 500000, 1000000}) {
        int test[dim];
        for (std::size_t i=0; i < dim; ++i) {
            test[i] = rand()%(2*MAX_VALUE)-MAX_VALUE;
        }
        {
            // build a max-heap of int, having elements in 'test' and dimensions 'dim'
            BinaryHeap<int, CompareItems<int>> h{test, dim};
            h[0] = 0.0;    // break heap property
            auto start = std::chrono::high_resolution_clock::now();
            h.heapify(0);
            auto end = std::chrono::high_resolution_clock::now();
            std::cout << "Size: " << dim << std::endl;
            std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << std::endl;
        }
    }
    return 0;
}
