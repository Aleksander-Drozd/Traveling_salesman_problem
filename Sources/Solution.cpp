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
    routeLength = 0;
}

Solution::Solution(int** originalMatrix, int s) {
    size = s;
    routeLength = 0;
    lowerBound = 0;
    route = new Connection*[size-2];

    rowIndexes = new int[size];
    columnIndexes = new int[size];

    setMatrix(originalMatrix);

    for (int i = 0; i < size; i++) {
        rowIndexes[i] = i;
        columnIndexes[i] = i;
    }
}

Solution::~Solution() {
    for(int i=0; i<size-2; i++)
        delete route[i];

    for(int i=0; i<size; i++)
        delete [] matrix[i];

    delete [] route;
    delete [] rowIndexes;
    delete [] columnIndexes;
    delete [] matrix;
}

void Solution::reduceRows(int* minTab) {
    int min;

    for (int i = 0; i < size; i++) {
        min = INT_MAX;
        for (int j = 0; j < size; j++)
            if (matrix[i][j] != -1 && matrix[i][j] < min)
                min = matrix[i][j];

        cout << min << endl;
        lowerBound += min;
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
        lowerBound += min;
        minTab[size + i] = min;
        for (int j = 0; j < size; j++) {
            if (matrix[j][i] != -1)
                matrix[j][i] -= min;
        }
    }
}

void Solution::findRowsMinimum(int* minTab) {
    bool wasZero;
    int min;
    //szukanie min w wierszach bez zer*
    for (int i = 0; i < size; i++) {
        min = INT_MAX;
        wasZero = false;
        for (int j = 0; j < size; j++) {
            if (matrix[i][j] == -1)
                continue;
            if (matrix[i][j] == 0) {
                if (wasZero) {
                    min = 0;
                    break;
                } else {
                    wasZero = true;
                    continue;
                }
            } else if (matrix[i][j] < min)
                min = matrix[i][j];
        }
        minTab[i] = min;
    }
}

void Solution::findColumnsMinimum(int* minTab) {
    bool wasZero;
    int min;

    for (int i = 0; i < size; i++) {
        min = INT_MAX;
        wasZero = false;
        for (int j = 0; j < size; j++) {
            if (matrix[j][i] == -1)
                continue;
            if (matrix[j][i] == 0) {
                if (wasZero) {
                    min = 0;
                    break;
                } else {
                    wasZero = true;
                    continue;
                }
            } else if (matrix[j][i] < min)
                min = matrix[j][i];
        }
        minTab[size + i] = min;
    }
}

Solution::Connection* Solution::determineConnection(int maxIndex) {
    //szukanie 0 w wierszu/kolumnie zawierajacej maksymalne minimim
    int zeroIndex = 0;
    Connection* connection = new Connection();

    if (maxIndex < size) {
        //szukanie zera w wierszu z minimum
        for (int i = 0; i < size; i++) {
            if(matrix[maxIndex][i] == 0){
                zeroIndex = i;
                break;
            }
        }

        connection -> c1 = rowIndexes[maxIndex];
        connection -> c2 = columnIndexes[zeroIndex];
        route[routeLength] = connection;
        cout<<"Usuwam ("<<connection -> c1<<", "<<connection -> c2<<")"<<endl;
        //costMatrix[columnIndexes[zeroIndex]][rowIndexes[maxIndex]] = -1;
        blockConnection(columnIndexes[zeroIndex], rowIndexes[maxIndex]);
        downgradeMatrix(maxIndex, zeroIndex);
        rowIndexes = downgradeArray(rowIndexes, maxIndex);
        columnIndexes = downgradeArray(columnIndexes, zeroIndex);
    } else {
        maxIndex -= size;
        //szukanie zera w kolumnie z minimum
        for (int i = 0; i < size; i++) {
            if(matrix[i][maxIndex] == 0){
                zeroIndex = i;
                break;
            }
        }

        connection -> c1 = rowIndexes[zeroIndex];
        connection -> c2 = columnIndexes[maxIndex];
        cout<<"Usuwam ("<<connection -> c1<<", "<<connection -> c2<<")"<<endl;
        //costMatrix[columnIndexes[maxIndex]][rowIndexes[zeroIndex]] = -1;
        blockConnection(columnIndexes[maxIndex], rowIndexes[zeroIndex]);
        downgradeMatrix(zeroIndex, maxIndex);
        rowIndexes = downgradeArray(rowIndexes, zeroIndex);
        columnIndexes = downgradeArray(columnIndexes, maxIndex);
    }

    size--;
    route[routeLength] = connection;
    routeLength++;
    return connection;
}

void Solution::blockConnection(int row, int column) {
    int r = -1, c = -1;

    for(int i=0; i<size; i++){
        if(rowIndexes[i] == row)
            r = i;
        if(columnIndexes[i] == column)
            c = i;
    }
    if(r < 0 || c < 0)
        return;
    matrix[r][c] = -1;
}

//wstawia -1 w miejsce zera w podanym wierszu
void Solution::blockConnection(int rowNumber) {
    int rowIndex;
    for (int i=0; i<size; i++)
        if(rowIndexes[i] == rowNumber){
            rowIndex = rowIndexes[i];
            break;
        }

    for(int i=0; i<size; i++)
        if(matrix[rowIndex][i] == 0){
            matrix[rowIndex][i] = -1;
            return;
        }
}

int Solution::getRowIndex(int rowNumber) {
    for(int i=0; i<size; i++)
        if(rowIndexes[i] == rowNumber)
            return i;

    return 0;
}

int Solution::getColumnIndex(int columnNumber) {
    for(int i=0; i<size; i++)
        if(columnIndexes[i] == columnNumber)
            return i;

    return 0;
}

int Solution::getMinFromRow(int rowIndex) {
    int min = INT_MAX;

    for(int i=0; i<size; i++)
        if(matrix[rowIndex][i] != -1 && matrix[rowIndex][i] < min)
            min = matrix[rowIndex][i];

    return min;
}

int Solution::getMinFromColumn(int columnIndex) {
    int min = INT_MAX;

    for(int i=0; i<size; i++)
        if(matrix[i][columnIndex] != -1 && matrix[i][columnIndex] < min)
            min = matrix[i][columnIndex];

    return min;
}

Solution::Connection *Solution::checkForSubtour() {
    int city;
    Connection* forbiddenConnection;
    city = route[routeLength-1] -> c2;

    for(int i=0; i<routeLength; i++)
        if(city == route[i] -> c1){
            city = route[i] -> c2;
            i = -1;
        }

    if(city != route[routeLength-1] -> c2){
        forbiddenConnection = new Connection();
        forbiddenConnection -> c1 = city;
        forbiddenConnection -> c2 = route[routeLength-1] -> c1;
        return forbiddenConnection;
    }

    city = route[routeLength-1] -> c1;

    for(int i=0; i<routeLength; i++)
        if(city == route[i] -> c2){
            city = route[i] -> c1;
            i = -1;
        }

    if(city != route[routeLength-1] -> c1){
        forbiddenConnection = new Connection();
        forbiddenConnection -> c1 = route[routeLength-1] -> c2;
        forbiddenConnection -> c2 = city;
        return forbiddenConnection;
    }

    return nullptr;
}

void Solution::downgradeMatrix(int rowIndex, int columnIndex) {
    int** newMatrix = new int* [size-1];
    int x = 0;

    for(int i=0; i<size; i++, x++) {
        if(i == rowIndex){
            x--;
            continue;
        }

        newMatrix[x] = new int[size - 1];
        memcpy(newMatrix[x], matrix[i], columnIndex*sizeof(int));
        memcpy(newMatrix[x] + columnIndex, matrix[i] + columnIndex + 1, (size - columnIndex - 1)*sizeof(int));
    }

    for(int i=0; i<size; i++)
        delete [] matrix[i];
    delete [] matrix;

    matrix = newMatrix;
}

int* Solution::downgradeArray(int* array, int index) {
    int* newArray = new int[size-1];

    memcpy(newArray, array, index*sizeof(int));
    memcpy(newArray + index, array + index + 1, (size - index - 1)*sizeof(int));

    delete [] array;

    return newArray;
}

void Solution::display() {
    cout<<endl<<"   ";
    for(int i=0; i<size; i++)
        cout<<columnIndexes[i]<<"  ";
    cout<<endl<<"   ";
    for(int i=0; i<size; i++)
        cout<<"-- ";
    cout<<endl;

    for(int i=0; i<size; i++) {
        cout<<rowIndexes[i]<<"| ";
        for(int j=0; j<size; j++){
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }

    cout<<endl<<"LB: "<<lowerBound<<endl;
    system("pause");
}

void Solution::displayRoute(int** costMatrix) {
    int sum = 0;

    for(int i=0; i<routeLength; i++){
        cout<<"("<<route[i] -> c1<<", "<<route[i] -> c2<<") - ";
        cout<<costMatrix[route[i] -> c1][route[i] -> c2]<<endl;
        sum += costMatrix[route[i] -> c1][route[i] -> c2];
    }

    cout<<"Calkowity koszt drogi = "<<sum<<endl;
    system("pause");
}

Solution* Solution::createCopy() {
    Solution* solution = new Solution();

    solution -> setSize(size);
    solution -> setLowerBound(lowerBound);
    solution -> setRouteLength(routeLength);
    solution -> setMatrix(matrix);
    solution -> setRowIndexes(rowIndexes);
    solution -> setColumnIndexes(columnIndexes);
    solution -> setRoute(route);

    return solution;
}

int Solution::getLowerBound() {
    return lowerBound;
}

void Solution::setLowerBound(int LB) {
    lowerBound = LB;
}

int Solution::getSize() {
    return size;
}

void Solution::setMatrix(int **originalMatrix) {
    matrix = new int*[size];

    for(int i=0; i<size; i++) {
        matrix[i] = new int [size];
        memcpy(matrix[i], originalMatrix[i], size*sizeof(int));
    }
}

void Solution::setSize(int size) {
    Solution::size = size;
}

void Solution::setRouteLength(int routeLength) {
    Solution::routeLength = routeLength;
}

void Solution::setRoute(Connection **originalRoute) {
    route = new Connection* [size];

    for(int i=0; i<routeLength; i++) {
        route[i] = new Connection();
        memcpy(route[i], originalRoute[i], sizeof(Connection));
    }
}

void Solution::setRowIndexes(int *originalRowIndexes) {
    rowIndexes = new int [size];
    memcpy(rowIndexes, originalRowIndexes, size*sizeof(int));
}

void Solution::setColumnIndexes(int* originalColumnIndexes) {
    columnIndexes = new int [size];
    memcpy(columnIndexes, originalColumnIndexes, size*sizeof(int));
}
