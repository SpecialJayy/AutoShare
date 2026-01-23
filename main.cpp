#include <iostream>

#include "Client.h"
#include "clientManager.h"

using namespace std;

int main() {
    Client loggedInClient;
    string username;
    string password;

    cout<< "Podaj login" << endl;
    cin >> username;

    cout << "Podaj haslo" << endl;
    cin >> password;

    if (login(username,password)) {
        cout << "Login successful, you are now logged as " << username << endl;
        createClientClass(loggedInClient,username);
    } else {
        cout << "Login failed" << endl;
    }

    // komendy do obsługi serwisu
    string command;
    while (command != "zakoncz") {
        cout<< "====================================" << endl;
        cout<< " Prosze podac komende" << endl;
        cin >> command;

        ///komendy
        if (command == "help") {
            cout << "Dostepne komendy" << endl;
            cout << "help -- pokazuje dostepne komendy" << endl;
            cout << "zakoncz -- wylogowywuje z serwisu" << endl;
            cout << "pojazdy -- pokazuje wypozyczone pojazdy" << endl;
            cout << "wyloguj -- wylogowywuje uzytkownika i prosi o ponowne zalogowanie" << endl;
            cout << "lista -- wyswietla liste dostepnych pojazdow" << endl;
            cout << "wyporzycz -- rozpoczyna proces wyporzyczania pojazdu" << endl;
            cout << "zwolnij -- oddaje pojazd spowrotem do wyporzyczalni" << endl;
            cout << "dane -- pokazuje dane klienta" << endl;
        } else if (command == "dane") {
            loggedInClient.createRaport();
        }

    }

    //koniec programu

    cout << "Dziekujemy za skorzystanie z naszych uslug :)" << endl;

    return 0;
}