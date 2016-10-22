//
// Created by John on 12-Oct-16.
//

#include <fstream>
#include <cstdlib>
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

}

void SalesmanProblem::display() {
    cout<<endl<<"   ";
    for(int i=0; i<size; i++)
        cout<<i<<" ";
    cout<<endl<<"   ";
    for(int i=0; i<size; i++)
        cout<<"- ";
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
