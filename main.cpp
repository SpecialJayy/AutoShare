#include <iostream>

#include "Client.h"
#include "clientManager.h"
#include "Color.h"
#include "commandConfig.h"

using namespace std;

int main() {
    Color colorCout; // deklaracja do wypisu konsoli w kolorze colorCout<<"<Rtekst czerwony>"
    Client loggedInClient;
    CommandConfig commandConfig;
    string username;
    string password;

    colorCout<<"<APodaj login>\n";
    cin >> username;

    cout << "Podaj haslo" << endl;
    cin >> password;

    if (login(username,password)) {
        colorCout<<"Login <Gsuccessful>";
        cout << ", you are now logged as " << endl;
        colorCout<<"<M"<<username<<">";
        createClientClass(loggedInClient,username);
    } else {
        colorCout<<"<CLogin failed>\n";
    }

    // komendy do obsługi serwisu
    string command;
    while (command != "zakoncz") {
        cout<< "====================================" << endl;
        colorCout<<"Prosze podac <Lkomende>\n";
        cin >> command;
        commandConfig.commandController(command);
    }

    return 0;
}