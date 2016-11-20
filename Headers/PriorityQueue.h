//
// Created by John on 18-Nov-16.
//

#ifndef TRAVELING_SALESMAN_PROBLEM_PRIORITYQUEUE_H
#define TRAVELING_SALESMAN_PROBLEM_PRIORITYQUEUE_H

#include "Solution.h"
#include <string>
using namespace std;

class PriorityQueue {
private:
    int id;
    int size;
    Solution** root;
    string cl;
    string cr;
    string cp;
    void orderAfterAdding();
    void printBT(string sp, string sn, int v);
public:
    PriorityQueue();
    void orderAfterRemoving();
    void add(Solution*);
    void remove();
    Solution* getFirst();
    void display();
    ~PriorityQueue();
};


#endif //TRAVELING_SALESMAN_PROBLEM_PRIORITYQUEUE_H
