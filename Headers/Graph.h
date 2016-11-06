//
// Created by John on 06-Nov-16.
//

#ifndef TRAVELING_SALESMAN_PROBLEM_GRAPH_H
#define TRAVELING_SALESMAN_PROBLEM_GRAPH_H


class Graph {
private:
    struct Leaf{
        int** matrix;
        int matrixSize;
        int lowerBound;
    };
    Leaf** graph;
    int graphSize;
public:
    Graph();
    void addLeaf(int**, int, int);
    Leaf* returnBestLeaf(int*);
    ~Graph();
};


#endif //TRAVELING_SALESMAN_PROBLEM_GRAPH_H
