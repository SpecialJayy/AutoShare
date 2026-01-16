#include <iostream>

#include "Client.h"
#include "clientManager.h"
#include "Color.h"
#include "commandConfig.h"

using namespace std;

int main() {
    Client loggedInClient;
    CommandConfig commandConfig;
    string username;
    string password;

    cout<<"Podaj login "<<endl;
    cin >> username;

    cout << "Podaj haslo" << endl;
    cin >> password;

    if (login(username,password)) {
        Color::Lime("Login successful");
        cout << ", you are now logged as " << endl;
        Color::Gold(username);
        createClientClass(loggedInClient,username);
    } else {
        Color::Red("Login failed");
    }

    // komendy do obsługi serwisu
    string command;
    while (command != "zakoncz") {
        cout<< "====================================" << endl;
        cout<<"Prosze podac komende";
        cin >> command;
        commandConfig.commandController(command);
    }

    return 0;
}