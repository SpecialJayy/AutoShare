#include "commandConfig.h"

#include <iostream>
#include <ostream>

#include "Client.h"

using namespace std;

CommandConfig::CommandConfig() {
    //syćkie komendy
    commandMap = {
        {"help", []() {
            cout << "Dostepne komendy" << endl;
            cout << "help -- pokazuje dostepne komendy" << endl;
            cout << "zakoncz -- wylogowywuje z serwisu" << endl;
            cout << "pojazdy -- pokazuje wypozyczone pojazdy" << endl;
            cout << "wyloguj -- wylogowywuje uzytkownika i prosi o ponowne zalogowanie" << endl;
            cout << "lista -- wyswietla liste dostepnych pojazdow" << endl;
            cout << "wyporzycz -- rozpoczyna proces wyporzyczania pojazdu" << endl;
            cout << "zwolnij -- oddaje pojazd spowrotem do wyporzyczalni" << endl;
            cout << "dane -- pokazuje dane klienta" << endl;
        }},
        {"zakoncz", []() {
            cout << "Dziekujemy za skorzystanie z uslug serwisu AutoShare+ :)" << endl;
        }},
        {"dane", []() {
            //client.createRaport();
        }},
    };
}

void CommandConfig::commandController(std::string &command) {

    //zmiana komedny na małe litery jesli uzytkownik wpisał np "HelP"
    for (char& ch: command) {
        ch = tolower(ch);
    }

    auto it = commandMap.find(command);

    //commandMap.find zwraca pare <KEY , VALUE>
    //Key w naszym przypadu to komenda a Value to nasza funkcja

    if (it != commandMap.end()) {
        //it->second to nasza funkcja którą opdalamy
        it->second();
    } else {
        cout << "Podano komende która nie instnieje" << endl;
    }
}
