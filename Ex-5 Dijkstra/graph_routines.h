#ifndef __GRAPH_ROUTINES__
#define __GRAPH_ROUTINES__

#include <iostream>
#include <math.h>

/**
 * Vertex data structure is implemented here . Integers are used to label vertices and index is used to map labels with integers.
  */

struct Vertex {
    int index;  // index of the vertex
    int d;  // distance
    int pred;  // predecessor in the shortest-paths tree
    bool on_queue;  // vertex on queue

    Vertex() = default;     // Default constructor
    // Constructs a node from a given index 'idx' on queue.
     Vertex(const int idx) : index{idx}, d{INT8_MAX}, pred{-1}, on_queue{true}{}
    ~Vertex() = default;
};

/**
  *This object will perform Vertex comparisons.  Comparisons are based on the member 'd', the distance.
  * To be passed as a template parameter to the BinaryHeap in Dijkstra's algorithm.
  */
struct CompareVertex {
    CompareVertex() = default;
    bool operator()(const Vertex& a, const Vertex& b) const noexcept {
        return a.d < b.d;
    }
    bool operator()(const Vertex& vertex, const int value) const noexcept {
        return vertex.d < value;
    }
    ~CompareVertex() = default;
};

/**
 * Queue data structure which keeps internal array of data .This stores the nodes during the computation of Dijkstra's algorithm.
  */
class Queue {
    std::size_t size;  // the index for the next element after the last one
    std::size_t free_slots;  // the number of slots available, necessary for reallocation
    std::size_t num;  // number of elements still in the queue
    int* data;  // array of data to store

  public:
    // The constructor builds the queue by copying the distance associated to each vertex into data. Array indicaes the adjacency list representation
    // of the graph.

    Queue(Vertex graph[], const std::size_t n) : size{n}, free_slots{0}, num{n}, data{new int[size]} {

        for (std::size_t i=0; i < n; ++i) {
            data[i] = graph[i].d;        // array elements copied .

        }
    }
    // verify the queue does not contain any element
    bool is_empty() const noexcept {
        return num == 0;
    }

    std::size_t extract_min() noexcept {
        //  finding the minimum of an array.
        int minimum{INT8_MAX};
        std::size_t index{0};
        for (std::size_t i=0; i < size; ++i) {
            if (minimum > data[i]) {
                minimum = data[i];
                index = i;
            }
        }
        data[index] = INT8_MAX;  // set the "extracted" element's distance to the maximum, t
        --num;
        ++free_slots; //update members
        return index;
    }

    // UPDATE_DISTANCE
    void decrease(const std::size_t i, const int value) {
        data[i] = value;
    }
    // Destructor
    ~Queue() {
        delete[] data;
    }
};

#endif  // __GRAPH_ROUTINES__
