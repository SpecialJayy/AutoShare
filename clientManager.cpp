#include "clientManager.h"

#include <bits/parse_numbers.h>

#include "iostream"
#include "DBM.h"

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

bool removeClient(string login) {
    string query = "DELETE FROM clients WHERE login == '" + login + "'";

    return tryToExecuteQuery(query,"Nie udalo sie usunac uzytkownika");
}

bool editClient(string login, string newLogin, string newPassword) {
    string query;
    if (newPassword.empty() && !newLogin.empty()) {
        //edycja tylko loginu
        //UPDATE your_table_name
        //SET login = :newLogin
        //WHERE login = :oldLogin
        query = "UPDATE customers SET login = '" + newLogin + "' WHERE login = '" + login + "'; ";
    } else if (!newPassword.empty() && newLogin.empty()) {
        //nowe haslo
        query = "UPDATE customers SET password = '" + newPassword + "' WHERE login = '" + login + "'; ";
    } else if (!newLogin.empty() && !newPassword.empty()) {
        query = "UPDATE customers SET password = '" + newPassword + "' WHERE login = '" + login + "';" + query = "UPDATE customers SET login = '" + newLogin + "' WHERE login = '" + login + "'; ";
        //nowy login i haslo
    }

    return tryToExecuteQuery(query,"Nie udalo sie edytowac danych uzytkownika");
}

bool login(string login, string password) {
    string query = "SELECT login FROM customers WHERE password = '" + password +"';";

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

bool createClientClass (Client& client,const string username){
    string query = "SELECT * FROM customers WHERE login = '" + username + "';";
    vector<string> success = DBM.loadData(query);

    if (success.size() == 0) {
        cout << "Brak uzytkownika " << username << " w bazie danych" << endl;
        return false;
    }
    //tu mamy na 100% klienta
    //stoi - string to int
    client.setId(stoi(success[0]));
    client.setLogin(success[1]);
    //celowo nie przypisujemy hasła w obiekcie klienta

    string queryLicenses = "SELECT * FROM driving_license WHERE customer_id = " + success[0] + ";";
    success = DBM.loadData(queryLicenses);

    char licenses[4]{};

    string lic = "abcd";

    //jezeli jakies uprawnienie ma 1 w bazie danych, jej index odpowiada charowi z stringu lic
    for (int i = 2; i <= 5; i++) {
        if (success[i] == "1") {
            licenses[i-2] = lic[i-2];
        }
    }

    client.setDriverLicenses(licenses);

    return true;
}
