#include "clientManager.h"
#include "iostream"
#include "DBM.h"

DBM DBM("autoshare.db");

bool addClient(std::string login , std::string password) {
    std::string checkQuery = "SELECT login FROM customers";
    std::vector<std::string> logins = DBM.loadData(checkQuery);

    for (int i = 0; i < logins.size(); i++) {
        if (logins[i] == login) {
            std::cout << "Login ju" << std::endl;
        }
    }

    std::string query = "INSERT INTO clients VALUES (login, password);";
}

bool removeClient() {

}
bool editClient() {

}

int login() {}