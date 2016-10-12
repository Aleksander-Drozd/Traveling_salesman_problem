#include <iostream>
#include <cstdlib>

using namespace std;

void showMenu() {
    int input;

    cout << "1) Wczytaj z pliku" << endl;
    cout << "2) Generuj losowo" << endl;
    cout << "3) Algorytm podzialu" << endl;
    cout << "3) Algorytm ograniczen" << endl;
    cout << "5) Wyjdz" << endl<<endl;

    cin >> input;

    switch (input){
        case 1:{

        }
        case 2:{

        }
        case 3:{

        }
        case 4:{

        }
        case 5:{
            return;
        }
    }
}

int main() {
    showMenu();
    return 0;
}