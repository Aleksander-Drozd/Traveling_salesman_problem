//
// Created by John on 12-Oct-16.
//

#include <fstream>
#include <cstdlib>
#include <climits>
#include <cstring>
#include "../Headers/SalesmanProblem.h"

SalesmanProblem::SalesmanProblem(){
    costMatrix = NULL;
    size = 0;
}

SalesmanProblem::~SalesmanProblem(){
    for(int i=0; i<size; i++)
        delete [] costMatrix[i];

    delete [] costMatrix;
}

void SalesmanProblem::readFromFile(string filename) {
    ifstream file;
    int cost;

    file.open(filename.c_str());

    if(!file.good()){
        cout<<endl<<endl<<"Blad podczas otwierania pliku"<<endl<<endl;
        system("pause");
        return;
    }

    file >> size;
    costMatrix = new int *[size];

    for(int i=0; i<size; i++)
    {
        costMatrix[i] = new int [size];
        for(int j=0; j<size; j++){
            file >> cost;
            costMatrix[i][j] = cost;
        }
    }
    file.close();
    display();
}

void SalesmanProblem::randomGenerate() {

}

void SalesmanProblem::bisectionConstraintsMethod() {
    int min, lowerLimit = 0, zeroIndex = 0;
    int *minTab;
    int *rowsIndexes = new int[size];
    int *columnIndexes = new int[size];
    int localSize = size;
    int **matrix = new int*[size];
    int pathSize = 0;

    Connection* connection;
    Connection** path = new Connection*[size-2];

    for(int i=0; i<size; i++) {
        matrix[i] = new int [size];
        memcpy(matrix[i], costMatrix[i], size*sizeof(int));
    }

    for (int i = 0; i < size; i++) {
        rowsIndexes[i] = i;
        columnIndexes[i] = i;
    }

    while(localSize != 2){
        minTab = new int[2 * localSize];
        //min szukane i odejmowane w wierszach
        for (int i = 0; i < localSize; i++) {
            min = INT_MAX;
            for (int j = 0; j < localSize; j++) {
                if (matrix[i][j] != -1 && matrix[i][j] < min)
                    min = matrix[i][j];
            }
            cout << min << endl;
            minTab[i] = min;
            for (int j = 0; j < localSize; j++) {
                if (matrix[i][j] != -1)
                    matrix[i][j] -= min;
            }
        }
        smartDisplay(matrix, rowsIndexes, columnIndexes, localSize);

        //min szukane i odejmowane w kolumnach
        for (int i = 0; i < localSize; i++) {
            min = INT_MAX;
            for (int j = 0; j < localSize; j++) {
                if (matrix[j][i] != -1 && matrix[j][i] < min)
                    min = matrix[j][i];
            }
            cout << min << endl;
            minTab[localSize + i] = min;
            for (int j = 0; j < localSize; j++) {
                if (matrix[j][i] != -1)
                    matrix[j][i] -= min;
            }
        }
        smartDisplay(matrix, rowsIndexes, columnIndexes, localSize);

        //sumowanie dolnego ograniczenia

        for (int i = 0; i < 2 * localSize; i++) {
            cout << minTab[i] << " ";
            lowerLimit += minTab[i];
        }
        cout << "LB:" << lowerLimit << endl;

        bool wasZero;
        //szukanie min w wierszach bez zer*
        for (int i = 0; i < localSize; i++) {
            min = INT_MAX;
            wasZero = false;
            for (int j = 0; j < localSize; j++) {
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

        //szukanie min w kolumnach bez zer*
        for (int i = 0; i < localSize; i++) {
            min = INT_MAX;
            wasZero = false;
            for (int j = 0; j < localSize; j++) {
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
            minTab[localSize + i] = min;
        }

        int max, maxIndex = 0, displacement = 0;
        bool connectionFound = false;

        max = findMax(minTab, 2*localSize, &maxIndex);

        connection = new Connection();

        while(!connectionFound)
            //szukanie 0 w wierszu/kolumnie zawierajacej maksymalne minimim
            if (maxIndex < localSize) {
                //szukanie zera w wierszu z minimum
                for (int i = 0; i < localSize; i++) {
                    if(matrix[maxIndex][i] == 0){
                        zeroIndex = i;
                        break;
                    }
                }

                if(costMatrix[columnIndexes[zeroIndex]][rowsIndexes[maxIndex]] != -1)
                    connectionFound = true;
                else{
                    displacement++;
                    maxIndex = findMaxIndex(minTab, localSize*2, max, displacement);
                    if(maxIndex == -1){
                        updateTab(minTab, 2*localSize, max);
                        displacement = 0;
                        max  = findMax(minTab, 2*localSize, &maxIndex);
                    }
                    continue;
                }

                connection -> c1 = rowsIndexes[maxIndex];
                connection -> c2 = columnIndexes[zeroIndex];
                path[pathSize] = connection;
                cout<<"Usuwam ("<<connection -> c1<<", "<<connection -> c2<<")"<<endl;
                costMatrix[rowsIndexes[zeroIndex]][columnIndexes[maxIndex]] = -1;
                matrix = downgradeMatrix(matrix, localSize, maxIndex, zeroIndex);
                rowsIndexes = downgradeArray(rowsIndexes, localSize, maxIndex);
                columnIndexes = downgradeArray(columnIndexes, localSize, zeroIndex);
            } else {
                maxIndex -= localSize;
                //szukanie zera w kolumnie z minimum
                for (int i = 0; i < localSize; i++) {
                    if(matrix[i][maxIndex] == 0){
                        zeroIndex = i;
                        break;
                    }
                }

                if(costMatrix[columnIndexes[maxIndex]][rowsIndexes[zeroIndex]] != -1)
                    connectionFound = true;
                else{
                    displacement++;
                    maxIndex = findMaxIndex(minTab, localSize*2, max, displacement);
                    if(maxIndex == -1){
                        updateTab(minTab, 2*localSize, max);
                        displacement = 0;
                        max  = findMax(minTab, 2*localSize, &maxIndex);
                    }
                    continue;
                }

                connection -> c1 = rowsIndexes[zeroIndex];
                connection -> c2 = columnIndexes[maxIndex];
                cout<<"Usuwam ("<<connection -> c1<<", "<<connection -> c2<<")"<<endl;
                path[pathSize] = connection;
                costMatrix[rowsIndexes[maxIndex]][columnIndexes[zeroIndex]] = -1;
                matrix = downgradeMatrix(matrix, localSize, zeroIndex, maxIndex);
                rowsIndexes = downgradeArray(rowsIndexes, localSize, zeroIndex);
                columnIndexes = downgradeArray(columnIndexes, localSize, maxIndex);
            }

        localSize--;
        lowerLimit += max;

        cout<<"Oryginal"<<endl;
        display();
        cout<<"Pomniejszona"<<endl;
        smartDisplay(matrix, rowsIndexes, columnIndexes, localSize);

        delete [] minTab;
        pathSize++;
    }

    for(int i=0; i<localSize; i++)
        delete [] matrix[i];

    delete [] matrix;

    for(int i=0; i<size-2; i++){
        cout<<"("<<path[i] -> c1<<", "<<path[i] -> c2<<")"<<endl;
    }

    system("pause");
}

int SalesmanProblem::findMaxIndex(int* tab, int size, int max, int displacement) {
    for(int i=0; i<size; i++){
        if(tab[i] == max)
            if(displacement == 0)
                return i;
            else
                displacement--;
    }
    return -1;
}

int SalesmanProblem::findMax(int* tab, int size, int *maxIndex) {
    int max = -1;

    for (int i=0; i<size; i++) {
        cout << tab[i] << " ";
        if (tab[i] > max) {
            max = tab[i];
            *maxIndex = i;
        }
    }
    cout << "Max: "<< max << endl;
    return max;
}

void SalesmanProblem::updateTab(int* tab, int size, int value) {
    for(int i=0; i<size; i++){
        if(tab[i] == value)
            tab[i] = -1;
    }
}

int** SalesmanProblem::downgradeMatrix(int** matrix, int localSize, int rowIndex, int columnIndex) {
    int** newMatrix = new int* [localSize-1];
    int x=0;

    for(int i=0; i<localSize; i++, x++)
    {
        if(i == rowIndex){
            x--;
            continue;
        }

        newMatrix[x] = new int[localSize - 1];
        memcpy(newMatrix[x], matrix[i], columnIndex*sizeof(int));
        memcpy(newMatrix[x] + columnIndex, matrix[i] + columnIndex + 1, (localSize - columnIndex - 1)*sizeof(int));
    }

    for(int i=0; i<localSize; i++){
        delete [] matrix[i];
    }
    delete [] matrix;

    return newMatrix;
}

int* SalesmanProblem::downgradeArray(int *array, int size, int index) {
    int* newArray = new int[size-1];

    memcpy(newArray, array, index* sizeof(int));
    memcpy(newArray + index, array + index + 1, (size - index - 1)*sizeof(int));

    delete [] array;
    return newArray;
}

void SalesmanProblem::display() {
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
            cout<<costMatrix[i][j]<<" ";
        }
        cout<<endl;
    }

    cout<<endl;
    system("pause");
}

void SalesmanProblem::smartDisplay(int** matrix, int* rowIndexes, int* columnIndexes, int localsize) {
    cout<<endl<<"   ";
    for(int i=0; i<localsize; i++)
        cout<<columnIndexes[i]<<"  ";
    cout<<endl<<"   ";
    for(int i=0; i<localsize; i++)
        cout<<"-- ";
    cout<<endl;

    for(int i=0; i<localsize; i++) {
        cout<<rowIndexes[i]<<"| ";
        for(int j=0; j<localsize; j++){
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }

    cout<<endl;
    system("pause");
}
