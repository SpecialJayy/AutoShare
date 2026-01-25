#include <iostream>

#include "Client.h"
#include "clientManager.h"
#include "Color.h"
#include <cctype>
#include <limits>

using namespace std;

//funkcje pomocnicze
static void printHeader() {
    std::cout << " "
              << std::left << std::setw(6) << "ID" << "| "
              << std::setw(15) << "MARKA" << "| "
              << std::setw(15) << "MODEL" << "| "
              << std::setw(8)  << "MOC" << "| "
              << std::setw(6)  << "ROK" << "| "
              << std::setw(10) << "PALIWO"
              << std::endl;

    std::cout << std::string(85, '-') << std::endl;
}

int getIntInput(const string& prompt) {
    int value = 0;
    cout << prompt;

    while (true) {
        if (cin >> value) {
            break;
        }

        cout << "Podano zly typ danych. Sprobuj ponownie: ";
        cin.clear(); // Czyścimy flagi błędów
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Opróżniamy bufor
    }

    return value;
}

int main() {
    bool isAppRunning = true;
    Color colorCout;

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
                cout << "pojazdy -- pokazuje twoje wypozyczone pojazdy" << endl;
                cout << "wyloguj -- wylogowywuje uzytkownika i prosi o ponowne zalogowanie" << endl;
                cout << "lista -- wyswietla liste dostepnych pojazdow" << endl;
                cout << "wypozycz -- rozpoczyna proces wypozyczania pojazdu" << endl;
                cout << "zwolnij -- oddaje pojazd spowrotem do wypozyczalni" << endl;
                cout << "dane -- pokazuje dane klienta" << endl;
            }
            else if (command == "dane") {
                cout << (*loggedInClient);
            }
            else if (command == "pojazdy") {
                cout << "Twoje wypozyczone pojazdy" << endl;
                if ((*loggedInClient).getVehicleCount() == 0 ) {
                    cout << "Nie wypozyczyles jeszcze zadnych pojazdow" << endl;
                } else {
                    printHeader();
                    (*loggedInClient).listVehicles();
                }
            }
            else if (command == "lista") {
                cout << "Dostepne pojazdy do wypozyczenia:" << endl;
                printHeader();
                listAllAvailableVehicles();
            }
            else if (command == "wypozycz") {
                int id = getIntInput("Prosze podac ID pojazdu, ktory chce Pan/Pani wypozyczyc: ");
                rentVehicle(*loggedInClient, id);
            }
            else if (command == "zwolnij") {
                int id = getIntInput("Prosze podac ID pojazdu, ktory chce Pan/Pani oddac: ");
                returnVehicle(*loggedInClient, id);
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

