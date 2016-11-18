//
// Created by John on 18-Nov-16.
//

#ifndef TRAVELING_SALESMAN_PROBLEM_PRIORITYQUEUE_H
#define TRAVELING_SALESMAN_PROBLEM_PRIORITYQUEUE_H


class PriorityQueue {
public:
    struct treeNode {
        int** matrix;
        int* rowIndexes;
        int* columnIndexes;
        int size;
        int lowerBound;
        int id;
    };
    PriorityQueue();
    ~PriorityQueue();
    void add(int**, int*, int*, int, int);
    void orderAfterAdding();
    void remove ();
    void orderAfterRemoving();
    treeNode* getFirst();
    void display();
private:
    int id;
    int size;
    treeNode** root;
};


#endif //TRAVELING_SALESMAN_PROBLEM_PRIORITYQUEUE_H
