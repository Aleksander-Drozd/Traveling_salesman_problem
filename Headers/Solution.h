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
    int routeLength;
    struct Connection{
        int c1;
        int c2;
    };

    Connection** route;
public:
    Solution();
    Solution(int**, int);
    void reduceRows(int*);
    void reduceColumns(int*);
    void blockConnection(int, int);
    void blockConnection(int);
    int getMinFromRow(int);
    void downgradeMatrix(int, int);
    int* downgradeArray(int*, int);
    void findRowsMinimum(int*);
    void findColumnsMinimum(int*);
    int determineConnection(int);
    void display();
    void displayRoute(int**);
    Solution* createCopy();
    ~Solution();

    int getLowerBound();

    void setLowerBound(int);int getSize();
    void setMatrix(int**);
    void setSize(int size);
    void setRouteLength(int routeLength);
    void setRoute(Connection **route);
    void setRowIndexes(int*);
    void setColumnIndexes(int*);
};


#endif //TRAVELING_SALESMAN_PROBLEM_SOLUTION_H
