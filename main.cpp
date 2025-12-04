#include <iostream>
#include "DBM.h"
#include "sqlite3.h"

DBM DBM("autoshare.db");
using namespace std;

void showAllCustomers() {
    DBM.loadData("SELECT * FROM customers");
}

int main() {
    showAllCustomers();

    // DBM.writeData("INSERT INTO customers (login, password) VALUES ('jasiu', 'kochampienkosza2');");


    return 0;
}