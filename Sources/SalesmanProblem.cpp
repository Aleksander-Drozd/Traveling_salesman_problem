#include <fstream>
#include <cstdlib>
#include <climits>
#include <cstring>
#include <ctime>
#include "../Headers/SalesmanProblem.h"

SalesmanProblem::SalesmanProblem(){
    costMatrix = NULL;
    size = 0;
    queue = new PriorityQueue();
}

SalesmanProblem::~SalesmanProblem(){
    for(int i=0; i<size; i++)
        delete [] costMatrix[i];

    delete [] costMatrix;
    delete queue;
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

void SalesmanProblem::generate(int citiesQuantity) {
    int cost;
    srand(time(NULL));

    size = citiesQuantity;
    costMatrix = new int *[size];

    for(int i=0; i<size; i++)
        costMatrix[i] = new int [size];

    for(int i=0; i<size; i++) {
        for(int j=i+1; j<size; j++){
            cost = rand()%120 + 1;
            costMatrix[i][j] = cost;
            costMatrix[j][i] = cost;
        }
        costMatrix[i][i] = -1;
    }
//    display();
}

void SalesmanProblem::branchAndBoundAlgorithm() {
    int lowerBound = 0;
    int *minTab;
    int localSize;

    Solution* solution = new Solution(costMatrix, size, lowerBound);
    localSize = solution -> getSize();

    while(localSize != 2){
        minTab = new int[2 * localSize];

        //min szukane i odejmowane w wierszach
        solution -> reduceRows(minTab);
        solution -> display();

        //min szukane i odejmowane w kolumnach
        solution -> reduceColumns(minTab);
        solution -> display();

        //sumowanie dolnego ograniczenia
        for (int i = 0; i < 2 * localSize; i++) {
            cout << minTab[i] << " ";
            lowerBound += minTab[i];
        }
        cout << "LB:" << lowerBound << endl;
        solution -> setLowerBound(lowerBound);

        //szukanie min w wierszach bez zer*
        solution -> findRowsMinimum(minTab);

        //szukanie min w kolumnach bez zer*
        solution -> findColumnsMinimum(minTab);

        int max, maxIndex;
        max = findMax(minTab, 2*localSize, &maxIndex);

        //szukanie 0 w wierszu/kolumnie zawierajacej maksymalne minimim
        solution -> determineConnection(maxIndex);

        cout<<"Pomniejszona"<<endl;
        solution -> display();

        localSize = solution -> getSize();
        delete [] minTab;
    }

    display();
    solution -> displayRoute(costMatrix);
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
