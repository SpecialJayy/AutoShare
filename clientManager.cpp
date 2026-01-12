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

bool addClient(string login ,string password) {
    string checkQuery = "SELECT login FROM customers";
    vector<string> logins = DBM.loadData(checkQuery);

    //sprawdzamy czy uzytkownik juz istnieje
    for (int i = 0; i < logins.size(); i++) {
        if (logins[i] == login) {
        cout << "Uzytkownik o tej nazwie juz istnieje" << endl;
            return false;
        }
    }

    string query = "INSERT INTO customers (login,password) VALUES ('" + login + "', '" + password + "');";

    return tryToExecuteQuery(query,"Nie udalo sie dodac uzytkownika");
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
        cout << "zalogowano poprawnie" << endl;
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
    client.setId(stoi(success[0]));
    client.setLogin(success[1]);
    //celowo nie przypisujemy hasła w obiekcie klienta

    string queryLicenses = "SELECT * FROM driving_license WHERE customer_id = " + success[0] + ";";
    success = DBM.loadData(queryLicenses);

    vector<char> licenses;

    string lic = "iiabcd";

    for (int i = 2; i <= 5; i++) {
        if (success[i].data() == "1") {
            licenses.push_back(lic[i]);
        }
    }

    client.setDriverLicenses(licenses);

    return true;
}
