#include <iostream>
#include <windows.h>
#include <ctime>
#include "../Headers/SalesmanProblem.h"

using namespace std;

void showMenu() {
    int input, citesQuantity;

    SalesmanProblem *salesmanProblem = new SalesmanProblem();;

    while(true){
        system("CLS");
        cout << "1) Wczytaj z pliku" << endl;
        cout << "2) Generuj losowo" << endl;
        cout << "3) Algorytm podzialu i ograniczen" << endl;
        cout << "4) Wyjdz" << endl<<endl;

        cin >> input;
        system("CLS");

        switch (input){
            case 1:{
                string filename;

                cout<<"Nazwa pliku: ";
                cin>>filename;

                salesmanProblem -> readFromFile(filename + ".txt");
                break;
            }
            case 2:{
                cout<<"Ilosc miast: ";
                cin>>citesQuantity;
                salesmanProblem -> generate(citesQuantity);
                break;
            }
            case 3:{
                salesmanProblem->branchAndBoundAlgorithm();
                break;
            }
            case 4:{
                delete salesmanProblem;
                return;
            }
            case 5:{
                salesmanProblem -> readFromFile("tsp10.txt");
                salesmanProblem->branchAndBoundAlgorithm();
            }
        }
    }
}

void test(int citiesQuantity){
    SalesmanProblem* TSP;

    LARGE_INTEGER clockFrequency;
    QueryPerformanceFrequency(&clockFrequency);
    LARGE_INTEGER startTime, endTime;
    LARGE_INTEGER delta;

    int loops = 30;
    double time = 0;

    for(int i=0; i<loops; i++)
    {
        TSP = new SalesmanProblem();
        TSP -> generate(citiesQuantity);

        QueryPerformanceCounter(&startTime);
        TSP -> branchAndBoundAlgorithm();
        QueryPerformanceCounter(&endTime);
        delta.QuadPart = endTime.QuadPart - startTime.QuadPart;
        time += ((double)delta.QuadPart) / clockFrequency.QuadPart;
        cout<<((double)delta.QuadPart) / clockFrequency.QuadPart<<endl;

        delete TSP;
    }

    time = time/loops;

    cout<<"Algorytm podzialu i ograniczen: "<<endl<<endl;;
    cout<<"Ilosc miast = "<<citiesQuantity<<endl;
    cout<<"Czas "<<time<<endl<<endl;
    system("pause");
}

int main() {
    srand(time(NULL));
    test(33);

//    test(34);
//    test(35);
//    test(36);
//    test(37);
//    test(38);
//    test(39);
    //showMenu();
    return 0;
}