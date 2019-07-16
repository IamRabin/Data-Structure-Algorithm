#ifndef __HEAP__
#define __HEAP__

#include <iostream>
#include <math.h>

#define LEFT(x) 2*x + 1
#define RIGHT(x) 2*x + 2
#define PARENT(x) (x - 1) / 2
#define GET_ROOT() 0
#define IS_ROOT(x) x == 0

/**
 * BinaryHeap comprise of templated data type and compare type .
  */
template<class T, class Comp>
struct BinaryHeap {
    // data
    std::size_t size;  // heap size
    T* data;  // array of data
    Comp compare;  // comparison operator
    // constructor  which implements heap sort inplace.

    BinaryHeap(T* array, const std::size_t n, const bool inplace=false) : size{n}, data{}, compare{} {
        if (inplace) {

            data = array;
        }
        // if not inplace , allocate memory space and copy array elements into data.
        else {
            data = new T[size];
            for (std::size_t i=0; i < size; ++i) {
                data[i] = array[i];
            }
        }
        // calling heapify in bottom fashion
        for (int i=PARENT(size-1); i >= 0; --i) {
            heapify(i);
        }
    }
    // overload of operator[]
    T& operator[](const std::size_t i) noexcept {
        return data[i];
    }
    bool is_empty() const noexcept {
        return size == 0;
    }
    // HEAP_MINIMUM removes the minimum

    int extract_min() noexcept {
        //  replacing with the rightmost leaf
        int ans = data[0].index;
        data[0] = data[size - 1];
        // updating size and free space
        --size;
        // calling heapify on the root
        heapify(GET_ROOT());
        return ans;
    }
    //Decreasing key ;  decrease the element H[i] to 'value'
    void decrease(std::size_t i, const T& value) {
        // abort the program if the value is not eligible to decrease
        if (compare(data[i], value)) {
            std::cout << "value is not smaller than H[i]" << std::endl;
            abort();
        }
        data[i] = value;
        // problem goes level up to the root
        bubble_up(i);
    }
    //  Necessary for binary heap-based implementation of Dijkstra's algorithm applied  to the  member of the Vertex class
    void decrease(std::size_t i, const int value) {
    // abort the program if the value is not eligible to decrease
         if (compare(data[i], value)) {
            std::cout << "value is not smaller than H[i]" << std::endl;
            abort();
        }
        data[i].d = value;
        bubble_up(i);
    }



    // HEAPIFY routine, iterative version
    void heapify(std::size_t i) noexcept {
          std::size_t m{i};
          //iterating to apply heapify property, else break
          while (true) {
                //  if it is a valid node and the key is smaller or equal than the current node.
                if (is_valid_node(LEFT(i)) && compare(data[LEFT(i)], data[m])) {
                    m = LEFT(i);
                }
                if (is_valid_node(RIGHT(i)) && compare(data[RIGHT(i)], data[m])) {
                    m = RIGHT(i);
                }
                // if i is different from m,it breaks the heap property so we swap.
                if (i != m) {
                    swap(i, m);
                    i = m;
                }
                // by induction the heap property holds and we stop.
                else break;
           }
    }

    void swap(const std::size_t i, const std::size_t m) noexcept {
        T temp{data[m]};
        data[m] = data[i];
        data[i] = temp;
    }
   //check whether the index corresponds to valid node.

    bool is_valid_node(const std::size_t i) const noexcept {return size-1 >= i;}
    // bubble-up helper function
    void bubble_up(std::size_t i) noexcept {
        // if the node is not root and violates heap property , we swap.
        while (!(IS_ROOT(i)) && compare(data[i], data[PARENT(i)])) {
            swap(i, PARENT(i));
            i = PARENT(i);
        }
    }
    ~BinaryHeap() {
    }
};

#endif // __HEAP__
