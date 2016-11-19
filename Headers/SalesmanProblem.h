//
// Created by John on 12-Oct-16.
//

#ifndef TRAVELING_SALESMAN_PROBLEM_SALESMANPROBLEM_H
#define TRAVELING_SALESMAN_PROBLEM_SALESMANPROBLEM_H

#include <iostream>
#include "PriorityQueue.h"

using namespace std;

class SalesmanProblem {
public:
    struct Connection{
        int c1;
        int c2;
    };
private:
    int **costMatrix;
    int size;
    PriorityQueue* queue;
public:
    SalesmanProblem();
    ~SalesmanProblem();
    void generate(int);
    void readFromFile(string);
    void branchAndBoundAlgorithm();
    void updateTab(int*, int, int);
    int findMax(int*, int, int*);
    int findMaxIndex(int*, int, int, int);
    void display();
};


#endif //TRAVELING_SALESMAN_PROBLEM_SALESMANPROBLEM_H
