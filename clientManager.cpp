#include "clientManager.h"
#include "Bike.h"
#include "Bus.h"
#include "Car.h"
#include "iostream"
#include "DBM.h"
#include "Truck.h"
#include <cctype>
#include <iomanip>
Color colorCout;

using namespace std;

DBM DBM("autoshare.db");

///System zarządzający klientami, obslugujący komunikacje z bazą danych

bool tryToExecuteQuery(string query, string errorMsg) {
    bool success = DBM.executeQuery(query);

    if (!success) {
        cout << errorMsg << endl;
        return false;
    }

    return true;
}

bool addClient(string login, string password,char licenses[4]) {

    //sprawdzamy czy login to nie admin
    if (login  == "admin") {
        cout << "niepoprawna nazwa uzytkownika " << endl;
        return false;
    }

    //patrzymy czy uzytkownik juz istnieje
    vector<string> logins = DBM.loadData("SELECT login FROM customers");
    for (const auto& l : logins) {
        if (l == login) {
            cout << "Uzytkownik juz istnieje" << endl;
            return false;
        }
    }

    //dodanie uzytkownika
    string queryUser = "INSERT INTO customers (login, password) VALUES ('" + login + "', '" + password + "');";
    if (!DBM.executeQuery(queryUser)) {
        cout << "Nie udalo sie dodac klienta do bazy" << endl;
        return false;
    }

    //pobranie ID wygenerowanego przez bazę
    string queryId = "SELECT id FROM customers WHERE login = '" + login + "';";
    vector<string> res = DBM.loadData(queryId);

    if (res.empty()) return false;
    string newId = res[0];

    //parsowanie licencji na format bazy (0 lub 1)
    string catA = "0", catB = "0", catC = "0", catD = "0";
    for(int i=0; i<4; i++) {
        if (licenses[i] == 'a') catA = "1";
        if (licenses[i] == 'b') catB = "1";
        if (licenses[i] == 'c') catC = "1";
        if (licenses[i] == 'd') catD = "1";
    }

    //dodanie licencji
    string queryLic = "INSERT INTO driving_license (customer_id, cat_a, cat_b, cat_c, cat_d) VALUES (" + newId + ", " + catA + ", " + catB + ", " + catC + ", " + catD + ");";
    return tryToExecuteQuery(queryLic, "Nie udalo sie utworzyć uzytwkownika");
}



bool login(string login, string password) {

    //logowanie do panelu admina
    if (login == "admin" && password == "admin") {
        return true;
    }

    string query = "SELECT login FROM customers WHERE password = '" + password +"' AND login = '" + login + "';";

    vector<string> success = DBM.loadData(query);

    if (success.size() == 0) {
        cout << "Podano zle haslo lub login" << endl;
        return false;
    }
    if (success.size() == 1) {
        return true;
    }
    cout << "blad wewnetrzny bazy danych ( prawdopodobnie w bazie znajduja sie 2 uzytkownicy o tych samych danych ) " << endl;
    return false;
}

// Funkcja zwraca wektor wskaźników do nowo utworzonych pojazdów
vector<Vehicle*> parseDatabaseResultToVehicles(const vector<string>& dbData) {
    vector<Vehicle*> vehicles;

    // Walidacja danych wejściowych
    if (dbData.empty()) return vehicles;
    if (dbData.size() % 8 != 0) {
        cout << "Blad spójnosci danych pojazdow (niepodzielne przez 8)" << endl;
        return vehicles;
    }

    // Pętla parsująca
    for (size_t i = 0; i < dbData.size() / 8; i++) {
        size_t increment = 8 * i;

        try {
            int id = stoi(dbData[0 + increment]);
            string brand = dbData[2 + increment];
            string model = dbData[3 + increment];
            int horsepower = stoi(dbData[4 + increment]);
            string fuelType = dbData[5 + increment];
            int year = stoi(dbData[6 + increment]);
            char license = dbData[7 + increment][0];

            Vehicle* v = nullptr;

            switch (license) {
                case 'A': v = new Bike(id, brand, model, horsepower, fuelType, year); break;
                case 'B': v = new Car(id, brand, model, horsepower, fuelType, year); break;
                case 'C': v = new Truck(id, brand, model, horsepower, fuelType, year); break;
                case 'D': v = new Bus(id, brand, model, horsepower, fuelType, year); break;
                default: cout << "Nieznany typ: " << license << endl; break;
            }

            if (v != nullptr) {
                vehicles.push_back(v);
            }
        } catch (...) {
            cout << "Blad parsowania rekordu pojazdu numer " << i << endl;
        }
    }

    return vehicles;
}

// 1. Funkcja pomocnicza: Pobranie podstawowych danych klienta (ID, Login)
bool loadClientData(Client& client, const string& username, string& outClientId) {
    string query = "SELECT * FROM customers WHERE login = '" + username + "';";
    vector<string> success = DBM.loadData(query);

    if (success.size() == 0) {
        cout << "Brak uzytkownika " << username << " w bazie danych" << endl;
        return false;
    }

    // tu mamy na 100% klienta
    // stoi - string to int
    // success[0] = id klienta
    outClientId = success[0]; // Zapisujemy ID do zmiennej pomocniczej
    client.setId(stoi(success[0]));
    client.setLogin(success[1]);
    // celowo nie przypisujemy hasła w obiekcie klienta

    return true;
}

// 2. Funkcja pomocnicza: Pobranie i przypisanie licencji
bool loadClientLicenses(Client& client, const string& clientId) {
    string queryLicenses = "SELECT * FROM driving_license WHERE customer_id = " + clientId + ";";
    vector<string> success = DBM.loadData(queryLicenses);

    // Zabezpieczenie, gdyby nie bylo rekordu w tabeli driving_license
    if (success.empty()) return false;

    char licenses[4]{};
    string lic = "abcd";

    // jezeli jakies uprawnienie ma 1 w bazie danych, jej index odpowiada charowi z stringu lic
    for (int i = 2; i <= 5; i++) {
        // Sprawdzamy zakres, żeby nie wywaliło segfaulta
        if (i < success.size() && success[i] == "1") {
            licenses[i-2] = lic[i-2];
        }
    }

    client.setDriverLicenses(licenses);
    return true;
}

// 3. Funkcja pomocnicza: Pobranie pojazdów przypisanych do klienta
bool loadClientVehicles(Client& client, const string& clientId) {
    string queryVehicles = "SELECT * FROM vehicles WHERE id_renter = " + clientId + ";";
    vector<string> rawData = DBM.loadData(queryVehicles);

    vector<Vehicle*> parsedVehicles = parseDatabaseResultToVehicles(rawData);

    for (Vehicle* v : parsedVehicles) {
        client.addVehicle(v);
    }

    return true;
}

// Główna funkcja
bool createClientClass(Client& client, const string username) {
    string clientId;

    // Każdy etap musi zwrócić true, żeby przejść dalej
    if (!loadClientData(client, username, clientId)) {
        return false;
    }

    if (!loadClientLicenses(client, clientId)) {
        return false;
    }

    if (!loadClientVehicles(client, clientId)) {
        return false;
    }

    return true;
}

void listAllAvailableVehicles() {
    string query = "SELECT * FROM vehicles WHERE id_renter = 0;";
    vector<string> rawData = DBM.loadData(query);

    vector<Vehicle*> availableVehicles = parseDatabaseResultToVehicles(rawData);

    if (availableVehicles.empty()) {
        cout << "Brak dostepnych pojazdow." << endl;
        return;
    }

    for (Vehicle* v : availableVehicles) {
        (*v).printInfo();
    }

    //musimy usunac obiekty aby zapobiec memory leakowi
    for (Vehicle* v : availableVehicles) {
        delete v;
    }
}

bool rentVehicle(Client &client, int id) {
    string query = "SELECT * FROM vehicles WHERE id = " + to_string(id) + ";";
    vector<string> rawData = DBM.loadData(query);

    if (rawData.empty()) {
        cout << "Nie ma takiego pojazdu." << endl;
        return false;
    }

    if (stoi(rawData[1]) != 0) {
        colorCout << "<R Pojazd jest niedostepny> \n";
        return false;
    }

    vector<Vehicle*> vehicles = parseDatabaseResultToVehicles(rawData);
    if (vehicles.empty()) return false;

    Vehicle* v = vehicles[0]; // Mamy pewnosc ze jest jeden wynik

    //dla bezpieczenstwa usuwamy jesli z jakiegos powodu z bazy danych by zwrocilo wiecej niz 1 pojazd
    for (size_t i = 1; i < vehicles.size(); i++) {
        delete vehicles[i];
    }

    char requiredLicense = rawData[7][0];
    const char* clientLicenses = client.getDriverLicenses();
    bool hasPermission = false;

    for (int i = 0; i < 4; i++) {
        if (std::tolower(clientLicenses[i]) == std::tolower(requiredLicense)) {
            hasPermission = true;
            break;
        }
    }

    if (!hasPermission) {
        colorCout << "<R Nie posiadasz wymaganych uprawnien > \n";
        delete v;
        return false;
    }

    double price = v->calculateRentalPrice();
    cout << "Cena za wypozyczenie: " << price << " PLN" << endl;

    string queryLend = "UPDATE vehicles SET id_renter = " + to_string(client.getId()) + " WHERE id = " + to_string(id) + ";";

    if (!DBM.executeQuery(queryLend)) {
        cout << "Blad bazy danych. Transakcja anulowana." << endl;
        delete v;
        return false;
    }

    colorCout << "<G Pojazd dostal pomyslnie wypozyczony> \n";

    client.addVehicle(v);

    //tworzymy raport i zapisujemy do bazy danych

    string queryRaport = "INSERT INTO raports (renter_id, name, vehicle_id, price, date) VALUES (" +
                             to_string(client.getId()) + ", '" +
                             client.getLogin() + "', " +
                             to_string(id) + ", " +
                             to_string(price) + ", " +
                             "DATE('now'));";

    if (!DBM.executeQuery(queryRaport)) {
        cout << "Blad przy tworzeniu raportu" << endl;
    }

    return true;
}

bool returnVehicle(Client &client, int id) {
    //sprawdzamy czy uzytkownik ma uprawnienia do zwolnienia pojazdu
    string checkQuery = "SELECT id FROM vehicles WHERE id = " + to_string(id) + " AND id_renter = " + to_string(client.getId()) + ";";
    vector<string> res = DBM.loadData(checkQuery);
    if (res.size() == 0) {
        colorCout << "<C Pojaz nie jest wypozyczony lub brak odpowiednich uprawnien> \n";
        return false;
    }

    string query = "UPDATE vehicles SET id_renter = 0 WHERE id = " + to_string(id) + ";";

    if (!tryToExecuteQuery(query, "Blad bazy danych podczas zwrotu pojazdu")) {
        return false;
    }

    if (client.returnVehicle(id)) {
        cout << "Pojazd o ID " << id << " zostal pomyslnie zwrocony." << endl;
        return true;
    }
    return true;
}

// komendy administratora

bool viewAllClients() {
    // Używamy LEFT JOIN, żeby wyświetlić klienta nawet jak nie ma rekordu licencji
    string query = "SELECT c.id, c.login, c.password, d.cat_a, d.cat_b, d.cat_c, d.cat_d "
                   "FROM customers c "
                   "LEFT JOIN driving_license d ON c.id = d.customer_id;";

    vector<string> res = DBM.loadData(query);

    if (res.empty()) {
        cout << "<C Brak uzytkownikow w bazie>" << endl;
        return false;
    }

    int cols = 7;

    if (res.size() % cols != 0) {
        cout << "<R Blad spojnosci danych>" << endl;
        return false;
    }

    // Iterujemy co 7 elementów
    for (size_t i = 0; i < res.size(); i += cols) {
        string id = res[i];
        string login = res[i+1];
        string password = res[i+2];

        // Budujemy stringa z uprawnieniami (np. "A B")
        string perms = "";
        if (res[i+3] == "1") perms += "A";
        if (res[i+4] == "1") perms += "B";
        if (res[i+5] == "1") perms += "C";
        if (res[i+6] == "1") perms += "D";

        if (perms.empty()) perms = "-"; // Jak nie ma nic, wstawiamy kreskę

        cout << " "
             << left << setw(6) << id << "| "
             << setw(20) << login << "| "
             << setw(20) << password << "| "
             << setw(12) << perms
             << endl;
    }

    return true;
}

bool viewAllRaports() {
    string query = "SELECT id, renter_id, name, vehicle_id, price, date FROM raports";
    vector<string> res = DBM.loadData(query);

    if (res.size() == 0) {
        colorCout << "<C Brak raportow w bazie >\n";
        return false;
    }

    int cols = 6;
    if (res.size() % cols != 0) {
        colorCout << "<R Blad spojnosci danych raportow>\n";
        return false;
    }

    for (size_t i = 0; i < res.size(); i += cols) {
        string id = res[i];
        string renterId = res[i+1];
        string name = res[i+2];
        string vehicleId = res[i+3];
        string price = res[i+4];
        string date = res[i+5];

        cout << " "
             << left << setw(6) << id << "| "
             << setw(11) << renterId << "| "
             << setw(15) << name << "| "
             << setw(11) << vehicleId << "| "
             << setw(10) << (price + " zl") << "| "
             << setw(12) << date
             << endl;
    }

    return true;
}

bool removeClient(string& login) {
    string query = "DELETE FROM customers WHERE login = '" + login + "'";

    return tryToExecuteQuery(query,"Nie udalo sie usunac uzytkownika");
}

bool editClient(int id, string newLogin, string newPassword, string newLicenseStr) {
    bool updateUsers = false;
    string queryUsers = "UPDATE customers SET ";

    if (!newLogin.empty()) {
        queryUsers += "login = '" + newLogin + "'";
        updateUsers = true;
    }

    if (!newPassword.empty()) {
        if (updateUsers) queryUsers += ", ";
        queryUsers += "password = '" + newPassword + "'";
        updateUsers = true;
    }

    queryUsers += " WHERE id = " + to_string(id) + ";";

    if (updateUsers) {
        if (!tryToExecuteQuery(queryUsers, "Blad edycji danych uzytkownika")) {
            cout << "wystapil blad" << endl;
            return false;
        }
    }

    if (!newLicenseStr.empty()) {
        string catA = "0", catB = "0", catC = "0", catD = "0";

        for (char c : newLicenseStr) {
            c = tolower(c);
            if (c == 'a') catA = "1";
            else if (c == 'b') catB = "1";
            else if (c == 'c') catC = "1";
            else if (c == 'd') catD = "1";
        }

        string queryLic = "UPDATE driving_license SET "
                          "cat_a=" + catA + ", "
                          "cat_b=" + catB + ", "
                          "cat_c=" + catC + ", "
                          "cat_d=" + catD +
                          " WHERE customer_id=" + to_string(id) + ";";

        if (!tryToExecuteQuery(queryLic, "Blad edycji licencji")) {
            return false;
        }
    }

    return true;
}

void listAllVehicles() {
    string query = "SELECT * FROM vehicles";
    vector<string> rawData = DBM.loadData(query);

    vector<Vehicle*> availableVehicles = parseDatabaseResultToVehicles(rawData);

    if (availableVehicles.empty()) {
        cout << "Brak dostepnych pojazdow." << endl;
        return;
    }

    for (Vehicle* v : availableVehicles) {
        (*v).printInfo();
    }

    //musimy usunac obiekty aby zapobiec memory leakowi
    for (Vehicle* v : availableVehicles) {
        delete v;
    }
}
