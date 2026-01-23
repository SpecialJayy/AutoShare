#include <iostream>

#include "Client.h"
#include "clientManager.h"
#include "Color.h"

using namespace std;

int main() {
    Color colorCout; // deklaracja do wypisu konsoli w kolorze colorCout<<"<Rtekst czerwony>"
    Client loggedInClient;
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