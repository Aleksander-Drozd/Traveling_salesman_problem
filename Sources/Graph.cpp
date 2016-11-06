//
// Created by John on 06-Nov-16.
//

#include "../Headers/Graph.h"
#include <iostream>
#include <climits>

using namespace std;

Graph::Graph() {
    graph = NULL;
    graphSize = 0;
}

Graph::~Graph() {
    for(int i=0; i<graphSize; i++)
        delete graph[i];

    delete [] graph;
}

void Graph::addLeaf(int** matrix, int size, int lowerBound) {
    Leaf* newLeaf;

    if(size == 0){
        graph = new Leaf* [1];
        newLeaf = new Leaf();
        newLeaf -> matrix = matrix;
        newLeaf -> matrixSize = size;
        graph[0] = newLeaf;
        graphSize++;
        return;
    }


}

Leaf* Graph::returnBestLeaf(int* index) {
    int min = INT_MAX;
    Leaf* leaf;

    for(int i=0; i<graphSize; i++)
        if(graph[i] != NULL){
            if(graph[i] -> lowerBound < min){
                leaf = graph[i];
                *index = i;
            }
        }

    return leaf;
}
