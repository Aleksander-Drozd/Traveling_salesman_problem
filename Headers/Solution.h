#ifndef TRAVELING_SALESMAN_PROBLEM_SOLUTION_H
#define TRAVELING_SALESMAN_PROBLEM_SOLUTION_H

class Solution {
public:
    struct Connection{
        int c1;
        int c2;
    };
private:
    int** matrix;
    int* rowIndexes;
    int* columnIndexes;
    int size;
    int lowerBound;
    int routeLength;
    Connection** route;
public:
    Solution();
    Solution(int**, int);
    void reduceRows(int*);
    void reduceColumns(int*);
    void reduce(int, int);
    void blockConnection(int, int);
    Connection* checkForSubtour();
    void downgradeMatrix(int, int);
    int* downgradeArray(int*, int);
    void findRowsMinimum(int*);
    void findColumnsMinimum(int*);
    void computeFinalTourCost();
    Connection* determineConnection(int);
    void display();
    void displayRoute(int**);
    Solution* createCopy();
    ~Solution();

    int getLowerBound();
    int getSize();

    void setLowerBound(int);
    void setMatrix(int**);
    void setSize(int size);
    void setRouteLength(int routeLength);
    void setRoute(Connection **route);
    void setRowIndexes(int*);
    void setColumnIndexes(int*);
};

#endif //TRAVELING_SALESMAN_PROBLEM_SOLUTION_H
