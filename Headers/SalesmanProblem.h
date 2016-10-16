//
// Created by John on 12-Oct-16.
//

#ifndef TRAVELING_SALESMAN_PROBLEM_SALESMANPROBLEM_H
#define TRAVELING_SALESMAN_PROBLEM_SALESMANPROBLEM_H

#include <iostream>

using namespace std;

class SalesmanProblem {
private:
    int **matrix;
    int size;
public:
    SalesmanProblem();
    ~SalesmanProblem();
    void randomGenerate();
    void readFromFile(string);
    void bisectionMethod();
    void constraintsMethod();
    void display();
};


#endif //TRAVELING_SALESMAN_PROBLEM_SALESMANPROBLEM_H
