//
// Created by John on 12-Oct-16.
//

#include <fstream>
#include <cstdlib>
#include "../Headers/SalesmanProblem.h"

SalesmanProblem::SalesmanProblem(){
    matrix = NULL;
    size = 0;
}

SalesmanProblem::~SalesmanProblem(){
    for(int i=0; i<size; i++)
        delete [] matrix[i];

    delete [] matrix;
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
    matrix = new int *[size];

    for(int i=0; i<size; i++)
    {
        matrix[i] = new int [size];
        for(int j=0; j<size; j++){
            file >> cost;
            matrix[i][j] = cost;
        }
    }
    file.close();
    display();
}

void SalesmanProblem::randomGenerate() {

}

void SalesmanProblem::bisectionMethod() {

}

void SalesmanProblem::constraintsMethod() {

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
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    system("pause");
}
