//
// Created by John on 18-Nov-16.
//

#ifndef TRAVELING_SALESMAN_PROBLEM_PRIORITYQUEUE_H
#define TRAVELING_SALESMAN_PROBLEM_PRIORITYQUEUE_H

#include "Solution.h"
#include <string>
using namespace std;

class PriorityQueue {
public:
    PriorityQueue();
    ~PriorityQueue();
    void add(int**, int*, int*, int, int);
    void orderAfterAdding();
    void remove ();
    void orderAfterRemoving();
    Solution* getFirst();
    void display();
    void printBT(string sp, string sn, int v);
private:
    int id;
    int size;
    Solution** root;
    string cl;
    string cr;
    string cp;
};


#endif //TRAVELING_SALESMAN_PROBLEM_PRIORITYQUEUE_H
