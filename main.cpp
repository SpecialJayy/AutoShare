#include <iostream>

#include "Client.h"
#include "clientManager.h"
#include "Color.h"
#include <cctype>
#include <limits>
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

static void printClientsHeader() {
    cout << " "
         << left << setw(6) << "ID" << "| "
         << setw(20) << "LOGIN" << "| "
         << setw(20) << "HASLO" << "| "
         << setw(12) << "UPRAWNIENIA" // Nowa kolumna
         << endl;

    cout << string(66, '-') << endl;
}

static void printRaportsHeader() {
    cout << " "
         << left << setw(6) << "ID" << "| "
         << setw(11) << "ID KLIENTA" << "| " // Troszkę szerzej
         << setw(15) << "UZYTKOWNIK" << "| " // name
         << setw(11) << "ID POJAZDU" << "| "
         << setw(10) << "CENA"       << "| "
         << setw(12) << "DATA"
         << endl;

    cout << string(75, '-') << endl;
}

int getIntInput(const string& prompt) {
    int value = 0;
    cout << prompt;

    while (true) {
        if (cin >> value) {
            break;
        }

        cout << "Podano zly typ danych. Sprobuj ponownie: " << endl;
        cin.clear(); // Czyścimy flagi błędów
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Opróżniamy bufor
    }

    return value;
}

int main() {
    bool isAppRunning = true;
    bool isAdmin = false;
    Color colorCout;

    //outer loop
    while (isAppRunning) {
        Client* loggedInClient = new Client();
        string username, password;
        bool isAuthenticated = false;

        while (!isAuthenticated) {
            colorCout << "<APodaj login> (lub wpisz 'zakoncz' aby wyjsc, lub wpisz 'rejestracja' aby utworzyc nowe konto)\n";
            cin >> username;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (username == "zakoncz") {
                isAppRunning = false;
                break;
            }

            if (username == "rejestracja") {
                string newLogin, newPass, licInput;
                cout << "--- KREATOR KONTA ---" << endl;
                cout << "Podaj nowy login: "; cin >> newLogin;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Podaj haslo: "; cin >> newPass;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Podaj kategorie (np. AB, B, ACD): "; cin >> licInput;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (login(username, password)) {
                if (username == "admin") {
                    //zalogowany jako admin
                    colorCout << "<GZalogowano>" << "\n";
                    colorCout << "<A Witamy w panelu admina>" << "\n";
                    isAdmin = true;
                    isAuthenticated = true;
                } else {
                colorCout << "<GZalogowano>" << "\n";
                cout << "Dzien dobry ";
                colorCout << "<M" << username << ">\n";

                createClientClass((*loggedInClient), username);
                isAuthenticated = true;
                }
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
            colorCout << "Prosze podac <Lkomende> (lub wpisz help) \n";
            cin >> command;

            //ignorujemy komendy po spacji
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (command == "help") {
                cout << "Dostepne komendy" << endl;
                cout << "help -- pokazuje dostepne komendy" << endl;
                cout << "zakoncz -- wylogowywuje z serwisu" << endl;
                cout << "wyloguj -- wylogowywuje uzytkownika i prosi o ponowne zalogowanie" << endl;
                cout << "lista -- wyswietla liste dostepnych pojazdow" << endl;
                if (!isAdmin) {
                cout << "pojazdy -- pokazuje twoje wypozyczone pojazdy" << endl;
                cout << "wypozycz -- rozpoczyna proces wypozyczania pojazdu" << endl;
                cout << "zwolnij -- oddaje pojazd spowrotem do wypozyczalni" << endl;
                cout << "dane -- pokazuje dane klienta" << endl;
                }
                //komendy admina
                if (isAdmin) {
                    colorCout << "<BPanel Administratora>" << "\n";
                    cout << "klienci -- lista klientow" << endl;
                    cout << "raports -- wyswietl raporty" << endl;
                    cout << "usun -- rozpoczyna proces usuwania klienta" << endl;
                    cout << "edytuj -- rozpoczyna proces edycji danych klienta" << endl;
                };
            }
            else if (command == "dane" && !isAdmin) {
                cout << (*loggedInClient);
            }
            else if (command == "pojazdy" && !isAdmin) {
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
            else if (command == "wypozycz" && !isAdmin) {
                int id = getIntInput("Prosze podac ID pojazdu, ktory chce Pan/Pani wypozyczyc: ");
                rentVehicle(*loggedInClient, id);
            }
            else if (command == "zwolnij" && !isAdmin) {
                int id = getIntInput("Prosze podac ID pojazdu, ktory chce Pan/Pani oddac: ");
                returnVehicle(*loggedInClient, id);
            }
            else if (command == "wyloguj") {
                cout << "Wylogowywanie..." << endl;
                isLoggedIn = false;
                isAdmin = false;
            }
            else if (command == "zakoncz") {
                cout << "Zamykanie programu..." << endl;
                isLoggedIn = false;
                isAppRunning = false;
            } else if (command == "klienci" && isAdmin) {
                //lista klientow
                printClientsHeader();
                viewAllClients();
            } else if (command == "raporty" && isAdmin) {
                //raporty
                printRaportsHeader();
                viewAllRaports();
            }else if (command == "usun" && isAdmin) {
                string targetLogin;
                cout << "--- USUWANIE KLIENTA ---" << endl;
                cout << "Podaj login uzytkownika do usuniecia: ";
                cin >> targetLogin;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (targetLogin == "admin") {
                    colorCout << "<R Nie mozna usunac konta administratora>\n";
                    continue;
                }

                cout << "Czy na pewno chcesz usunac uzytkownika " << targetLogin << "? (t/n): ";
                char confirm;
                cin >> confirm;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (confirm == 't' || confirm == 'T') {
                    if (removeClient(targetLogin)) {
                        colorCout << "<G Sukces! Uzytkownik " << targetLogin << " zostal wymazany z rzeczywistosci.>\n";
                    } else {
                        colorCout << "<R Operacja nieudana. Sprawdz czy login jest poprawny.>\n";
                    }
                } else {
                    cout << "Anulowano usuwanie." << endl;
                }
            } else if (command == "edytuj" && isAdmin) {
                int targetId;
                cout << "--- EDYCJA KLIENTA ---" << endl;
                targetId = getIntInput("Podaj ID klienta do edycji: ");
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                string newLogin, newPass, newLic;

                cout << "Nowy login (wcisnij ENTER aby pominac): ";
                getline(cin, newLogin);

                cout << "Nowe haslo (wcisnij ENTER aby pominac): ";
                getline(cin, newPass);

                cout << "Nowe uprawnienia np. AB (wcisnij ENTER aby pominac): ";
                getline(cin, newLic);

                if (newLogin.empty() && newPass.empty() && newLic.empty()) {
                    colorCout << "<C Nie wprowadzono zadnych zmian. Anulowano.>\n";
                } else {
                    if (editClient(targetId, newLogin, newPass, newLic)) {
                        colorCout << "<G Dane klienta zostaly zaktualizowane!>\n";
                    } else {
                        colorCout << "<R Wystapil blad podczas aktualizacji.>\n";
                    }
                }
            }
        }

        delete loggedInClient;
        loggedInClient = nullptr;
    }

    cout << "Dziekujemy za skorzystanie z naszych uslug :)" << endl;
    return 0;
}

