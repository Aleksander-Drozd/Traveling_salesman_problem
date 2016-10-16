#include <iostream>
#include <cstdlib>
#include "../Headers/SalesmanProblem.h"

using namespace std;

void showMenu() {
    int input;

    SalesmanProblem *salesmanProblem;

    while(true){
        salesmanProblem = new SalesmanProblem();
        system("CLS");
        cout << "1) Wczytaj z pliku" << endl;
        cout << "2) Generuj losowo" << endl;
        cout << "3) Algorytm podzialu" << endl;
        cout << "3) Algorytm ograniczen" << endl;
        cout << "5) Wyjdz" << endl<<endl;

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
                salesmanProblem -> randomGenerate();
                break;
            }
            case 3:{
                salesmanProblem -> bisectionMethod();
                break;
            }
            case 4:{
                salesmanProblem->constraintsMethod();
                break;
            }
            case 5:{
                delete salesmanProblem;
                return;
            }
        }
        delete salesmanProblem;
    }
}

int main() {
    showMenu();
    return 0;
}