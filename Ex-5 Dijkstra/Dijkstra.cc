#include <iostream>
#include <chrono>
#include<math.h>

#include "graph_routines.h"
#include "heap.h"

#define N 6  // number of vertices in the graph


/**
 *  An array of vertices with `V` with `n` numbers have source vertex `s` . The graph is represented by an adjaceny matrix.
 *  The queue data structure is used here which comes from graph_routines.h
  */
template<class Q>
void dijkstra(int graph[][N], Vertex V[], const std::size_t n, Vertex& s) {
    s.d = 0;  // intitally source distance is 0
    Q q{V, n};  // build queue from the vertices
    // iterate until while there are still nodes to finalize
    while (!q.is_empty()) {
        // extract the minimum and mark it as no longer in queue if it is not empty.
        Vertex& u = V[q.extract_min()];
        u.on_queue = false;
        // iterating neighbours
        for (std::size_t i=0; i < n; ++i) {
            int w = graph[u.index][i];  // the weight of the edge
            Vertex& v = V[i];
            // -1 means for no edge.
            if (w != -1 && v.on_queue == true) {  // if  neighbors  are still in the queue
                // perform the relaxation step of Dijkstra's algorithm.
                //
                // if the candidate distance of v is greater than its parent's distance plus the weight of the edge,
                // update the queue and v distance and u is the predecessor in the shortest path tree.
                if (u.d + w < v.d) {
                    q.decrease(v.index, u.d + w);
                    v.d = u.d + w;
                    v.pred = u.index;
                }
            }
        }
    }
}

/****************************************************
******************Main function***********************
 ****************************************************/


int main() {

    Vertex* vertices = new Vertex[N]; // intializing new vertices.
    for (int i = 0; i < N; ++i) {
        vertices[i] = Vertex{i};
    }

    int graph[N][N] = {{-1, 1, 5, -1, -1, -1}, {-1, -1, -1, -1, -1, 15}, {-1, -1, -1, 2, -1, -1}, {-1, -1, -1, -1, 1, -1}, {-1, -1, -1, -1, -1, 3}, {-1, -1, -1, -1, -1, 3}};

    //  BinaryHeap graph
    std::cout << " Graph Test" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    dijkstra<BinaryHeap<Vertex, CompareVertex>>(graph, vertices, N, vertices[0]);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "BinaryHeap implementation: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << std::endl;
    // checking result
    for (int i=0; i < 6; ++i) {
        std::cout << "node number: " << vertices[i].index << " has distance: " << vertices[i].d << std::endl;
    }
    // reset vertices' members
    for (int i=0; i < 6; ++i) {
        vertices[i].on_queue = true;
        vertices[i].pred = -1;
        vertices[i].d = INT8_MAX;
    }
    //  Queue test
    start = std::chrono::high_resolution_clock::now();
    dijkstra<Queue>(graph, vertices, N, vertices[0]);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Array implementation: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << std::endl;
    // check result
    for (int i=0; i < 6; ++i) {
        std::cout << "node number: " << vertices[i].index << " has distance: " << vertices[i].d << std::endl;
    }
    // deallocate
    delete[] vertices;
    return 0;
}
