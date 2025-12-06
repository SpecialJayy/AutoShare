#include "clientManager.h"
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

int login(string login, string password) {
    string query = "SELECT login FROM customers WHERE password = '" + password +"';";

}
