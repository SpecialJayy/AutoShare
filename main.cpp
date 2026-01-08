#include <iostream>

#include "Client.h"
#include "clientManager.h"
#include "commandConfig.h"

using namespace std;

int main() {
    Client loggedInUser();
    CommandConfig commandConfig;

    string username;
    string password;

    cout<< "Podaj login" << endl;
    cin >> username;

    cout << "Podaj haslo" << endl;
    cin >> password;

    if (login(username,password)) {
        cout << "Login successful, you are now logged as " << username << endl;
        loggedInUser(); // tu koniec
    } else {
        cout << "Login failed" << endl;
    }

    // komendy do obsługi serwisu
    string command;
    while (command != "zakoncz") {
        cout<< "====================================" << endl;
        cout<< " Prosze podac komende" << endl;
        cin >> command;
        commandConfig.commandController(command);
    }


    return 0;
}