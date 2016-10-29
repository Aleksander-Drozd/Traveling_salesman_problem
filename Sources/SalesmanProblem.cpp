//
// Created by John on 12-Oct-16.
//

#include <fstream>
#include <cstdlib>
#include <climits>
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
    int min, lowerLimit = 0;
    int* minTab = new int[2*size];
    int** matrix = costMatrix;
    int *rowsIndexes = new int[size];
    int *columnIndexes = new int[size];
    int rows, columns;

    for(int i=0; i<size; i++){
        rowsIndexes[i] = i;
        columnIndexes[i] = i;
    }

    //min szukane i odejmowane w wierszach
    for(int i=0; i<size; i++){
        min = INT_MAX;
        for(int j=0; j<size; j++){
            if(i != j && costMatrix[i][j] < min)
                min = costMatrix[i][j];
        }
        cout<<min<<endl;
        minTab[i] = min;
        for(int j=0; j<size; j++){
            if(i != j)
                costMatrix[i][j] -= min;
        }
    }
    display();

    //min szukane i odejmowane w kolumnach
    for(int i=0; i<size; i++){
        min = INT_MAX;
        for(int j=0; j<size; j++){
            if(i != j && costMatrix[j][i] < min)
                min = costMatrix[j][i];
        }
        cout<<min<<endl;
        minTab[size + i] = min;
        for(int j=0; j<size; j++){
            if(i != j)
                costMatrix[j][i] -= min;
        }
    }
    display();

    //sumowanie dolnego ograniczenia
    for(int i=0; i<2*size; i++){
        cout<<minTab[i]<<" ";
        lowerLimit += minTab[i];
    }
    cout<<lowerLimit<<endl;

    bool wasZero;
    //szukanie min w wierszach bez zer*
    for(int i=0; i<size; i++){
        min = INT_MAX;
        wasZero = false;
        for(int j=0; j<size; j++){
            if(i == j)
                continue;
            if(costMatrix[i][j] == 0){
                if(wasZero == true){
                    min = 0;
                    break;
                }
                else{
                    wasZero = true;
                    continue;
                }
            }
            else if(costMatrix[i][j] < min)
                    min = costMatrix[i][j];
        }
        cout<<min<<endl;
        minTab[i] = min;
    }

    //szukanie min w kolumnach bez zer*
    for(int i=0; i<size; i++){
        min = INT_MAX;
        wasZero = false;
        for(int j=0; j<size; j++){
            if(i == j)
                continue;
            if(costMatrix[j][i] == 0){
                if(wasZero == true){
                    min = 0;
                    break;
                }
                else{
                    wasZero = true;
                    continue;
                }
            }
            else if(costMatrix[j][i] < min)
                    min = costMatrix[j][i];

        }
        cout<<min<<endl;
        minTab[size + i] = min;
    }

    int max = 0;
    for(int i=0; i<2*size; i++){
        cout<<minTab[i]<<" ";
        if(minTab[i] > max)
            max = minTab[i];
    }
    cout<<max<<endl<<endl;
    display();

    delete [] minTab;
    system("pause");
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

void SalesmanProblem::smartDisplay(int** matrix, int* rowIndexes, int rows, int* columnIndexes, int columns) {
    cout<<endl<<"   ";
    for(int i=0; i<rows; i++)
        cout<<rowIndexes[i]<<"  ";
    cout<<endl<<"   ";
    for(int i=0; i<rows; i++)
        cout<<"-- ";
    cout<<endl;

    for(int i=0; i<rows; i++)
    {
        cout<<columnIndexes[i]<<"| ";
        for(int j=0; j<columns; j++){
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }

    cout<<endl;
    system("pause");
}
