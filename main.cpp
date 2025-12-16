#include <iostream>
#include "clientManager.h"

using namespace std;

int main() {

    while (true) {
        cout<< " Prosze podac komende" << endl;
        string login;
        string password;
        cout << "login: " << endl;
        cin >> login;
        cout << "password: " << endl;
        cin >> password;
        addClient(login, password);
    }

    return 0;
}