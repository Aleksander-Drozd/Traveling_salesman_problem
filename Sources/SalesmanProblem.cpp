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
    int *minTab;
    int localSize, lowerBound;
    Solution::Connection *connection = new Solution::Connection();

    Solution *solution2, *solution = new Solution(costMatrix, size);
    Solution *bestSolution = NULL;
    localSize = size;
    minTab = new int[2 * size];
    solution -> reduceRows(minTab);
    solution -> reduceColumns(minTab);
    lowerBound = solution -> getLowerBound();
    cout<<"Najmniejsze mozliwe LB: "<<lowerBound<<endl<<endl;
    queue -> add(solution);
    int max, maxIndex;

    while(true){
        solution2 = solution -> createCopy();

        max = findMax(minTab, 2*localSize, &maxIndex);
        //skrocenie macierzy
        connection = solution -> determineConnection(maxIndex);
        solution -> display();

        solution2 -> blockConnection(connection -> c1, connection -> c2);
        solution2 -> reduce(connection -> c1, connection -> c2);

        cout<<"Alternatywna droga:"<<endl;
        solution2 -> display();
        connection = solution -> checkForSubtour();
        if(connection != NULL){
            solution -> blockConnection(connection -> c1, connection -> c2);
            //solution -> setLowerBound(solution -> getLowerBound() + solution -> getMinFromRow(solution -> getRowIndex(connection -> c1)));
            cout<<"Zablokowany cykl"<<endl;
            solution -> display();
        }

        //min szukane i odejmowane w wierszach
        solution -> reduceRows(minTab);
        //solution -> display();

        //min szukane i odejmowane w kolumnach
        solution -> reduceColumns(minTab);
        //solution -> display();

        queue -> orderAfterRemoving();
        queue -> add(solution2);
        queue -> display();
        solution = queue -> getFirst();

        if(bestSolution != NULL && solution -> getLowerBound() > bestSolution -> getLowerBound())
            break;

        cout<<"Pracuje na:"<<endl;
        solution -> display();

        while(solution -> getSize() == 2){
            solution -> computeFinalTourCost();

            if(bestSolution == NULL || solution -> getLowerBound() < bestSolution -> getLowerBound())
                bestSolution = solution -> createCopy();
            else if(bestSolution != NULL && solution -> getLowerBound() > bestSolution -> getLowerBound())
                break;

            queue -> remove();
            solution = queue -> getFirst();
        }
        if(bestSolution != NULL && solution -> getLowerBound() > bestSolution -> getLowerBound())
            break;
        localSize = solution -> getSize();

        //szukanie min w wierszach bez zer*
        solution -> findRowsMinimum(minTab);

        //szukanie min w kolumnach bez zer*
        solution -> findColumnsMinimum(minTab);
    }

    delete connection;
    delete [] minTab;
    display();
    bestSolution -> displayRoute(costMatrix);
    delete bestSolution;
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
