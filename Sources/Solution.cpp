#include <climits>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include "../Headers/Solution.h"

using namespace std;

Solution::Solution() {
    matrix = NULL;
    rowIndexes = NULL;
    columnIndexes = NULL;
    size = 0;
    lowerBound = 0;
    id = 0;
}

Solution::Solution(int** m, int s, int LB) {
    matrix = m;
    size = s;
    lowerBound = LB;
    id = 0;
    route = new Connection*[size-2];

    rowIndexes = new int[size];
    columnIndexes = new int[size];

    for (int i = 0; i < size; i++) {
        rowIndexes[i] = i;
        columnIndexes[i] = i;
    }
}

Solution::~Solution() {
    for(int i=0; i<size-2; i++)
        delete route[i];

    delete [] route;
    delete [] rowIndexes;
    delete [] columnIndexes;
}

void Solution::reduceRows(int* minTab) {
    int min;

    for (int i = 0; i < size; i++) {
        min = INT_MAX;
        for (int j = 0; j < size; j++)
            if (matrix[i][j] != -1 && matrix[i][j] < min)
                min = matrix[i][j];

        cout << min << endl;
        minTab[i] = min;

        for (int j = 0; j < size; j++) {
            if (matrix[i][j] != -1)
                matrix[i][j] -= min;
        }
    }
}

void Solution::reduceColumns(int* minTab) {
    int min;

    for (int i = 0; i < size; i++) {
        min = INT_MAX;
        for (int j = 0; j < size; j++)
            if (matrix[j][i] != -1 && matrix[j][i] < min)
                min = matrix[j][i];

        cout << min << endl;
        minTab[size + i] = min;
        for (int j = 0; j < size; j++) {
            if (matrix[j][i] != -1)
                matrix[j][i] -= min;
        }
    }
}

void Solution::blockConnection(int row, int column) {
    int r = -1, c = -1;

    for(int i=0; i<size; i++){
        if(rowIndexes[i] == column)
            r = i;
        if(columnIndexes[i] == row)
            c = i;
    }
    if(r < 0 || c < 0)
        return;
    matrix[r][c] = -1;
}

void Solution::downgradeMatrix(int rowIndex, int columnIndex) {
    int** newMatrix = new int* [size-1];
    int x = 0;

    for(int i=0; i<size; i++, x++)
    {
        if(i == rowIndex){
            x--;
            continue;
        }

        newMatrix[x] = new int[size - 1];
        memcpy(newMatrix[x], matrix[i], columnIndex*sizeof(int));
        memcpy(newMatrix[x] + columnIndex, matrix[i] + columnIndex + 1, (size - columnIndex - 1)*sizeof(int));
    }

    for(int i=0; i<size; i++){
        delete [] matrix[i];
    }
    delete [] matrix;

    matrix = newMatrix;
}

int* Solution::downgradeArray(int* array, int index) {
    int* newArray = new int[size-1];

    memcpy(newArray, array, index* sizeof(int));
    memcpy(newArray + index, array + index + 1, (size - index - 1)*sizeof(int));

    delete [] array;

    return newArray;
}

void Solution::display() {
    cout<<endl<<"   ";
    for(int i=0; i<size; i++)
        cout<<i<<"  ";
    cout<<endl<<"   ";
    for(int i=0; i<size; i++)
        cout<<"-- ";
    cout<<endl;

    for(int i=0; i<size; i++)
    {
        cout<<i<<"| ";
        for(int j=0; j<size; j++){
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }

    cout<<endl;
    system("pause");
}
