#include <iostream>

#include "Client.h"
#include "clientManager.h"
#include "Color.h"
#include <cctype>

using namespace std;

int main() {
    Color colorCout;
    bool isAppRunning = true;

    //outer loop
    while (isAppRunning) {
        Client* loggedInClient = new Client();
        string username, password;
        bool isAuthenticated = false;

        while (!isAuthenticated) {
            colorCout << "<APodaj login> (lub 'zakoncz' wyjscie, 'rejestracja' nowe konto)\n";
            cin >> username;

            if (username == "zakoncz") {
                isAppRunning = false;
                break;
            }

            if (username == "rejestracja") {
                string newLogin, newPass, licInput;
                cout << "--- KREATOR KONTA ---" << endl;
                cout << "Podaj nowy login: "; cin >> newLogin;
                cout << "Podaj haslo: "; cin >> newPass;
                cout << "Podaj kategorie (np. AB, B, ACD): "; cin >> licInput;

                char newLicenses[4]{}; // inicjalizacja zerami
                for (char c : licInput) {
                    c = tolower(c);
                    if (c == 'a') newLicenses[0] = 'a';
                    else if (c == 'b') newLicenses[1] = 'b';
                    else if (c == 'c') newLicenses[2] = 'c';
                    else if (c == 'd') newLicenses[3] = 'd';
                }

                if (addClient(newLogin, newPass, newLicenses)) {
                    colorCout << "<GKonto utworzone!> Zaloguj sie.\n";
                }
                continue;
            }

            cout << "Podaj haslo" << endl;
            cin >> password;

            if (login(username, password)) {
                colorCout << "<GZalogowano>" << "\n";
                cout << "Dzien dobry ";
                colorCout << "<M" << username << ">\n";

                createClientClass((*loggedInClient), username);
                isAuthenticated = true;
            } else {
                colorCout << "<CLogin failed> Sprobuj ponownie.\n";
            }
        }

        if (!isAppRunning) {
            delete loggedInClient;
            break;
        }

        //inner loop
        string command;
        bool isLoggedIn = true;

        while (isLoggedIn) {
            cout << endl << "====================================" << endl;
            colorCout << "Prosze podac <Lkomende>\n";
            cin >> command;

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
                cout << "wyloguj -- wylogowywuje uzytkownika" << endl;
            }
            else if (command == "dane") {
                cout << (*loggedInClient);
            }
            else if (command == "wyloguj") {
                cout << "Wylogowywanie..." << endl;
                isLoggedIn = false;
            }
            else if (command == "zakoncz") {
                cout << "Zamykanie programu..." << endl;
                isLoggedIn = false;
                isAppRunning = false;
            }
        }

        delete loggedInClient;
        loggedInClient = nullptr;
    }

    cout << "Dziekujemy za skorzystanie z naszych uslug :)" << endl;
    return 0;
}