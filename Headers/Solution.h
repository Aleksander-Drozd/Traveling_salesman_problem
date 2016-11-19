//
// Created by John on 19-Nov-16.
//

#ifndef TRAVELING_SALESMAN_PROBLEM_SOLUTION_H
#define TRAVELING_SALESMAN_PROBLEM_SOLUTION_H


class Solution {
private:
    int** matrix;
    int* rowIndexes;
    int* columnIndexes;
    int size;
    int lowerBound;
    int id;
    struct Connection{
        int c1;
        int c2;
    };

    Connection** route;
public:
    Solution();
    Solution(int**, int, int);
    void reduceRows(int*);
    void reduceColumns(int*);
    void blockConnection(int, int);
    void downgradeMatrix(int, int);
    int* downgradeArray(int*, int);
    void display();
    ~Solution();
};


#endif //TRAVELING_SALESMAN_PROBLEM_SOLUTION_H
