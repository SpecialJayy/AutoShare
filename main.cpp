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

    return 0;
}