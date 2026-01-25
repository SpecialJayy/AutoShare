#include "DBM.h"
#include <iostream>

using namespace std;

DBM::DBM(string dbName) {
    this->dbPath = dbName;
    this->db = nullptr;

    if (connectDb()) {
        cout << "Connection to database established We balling" << endl;
    } else {
        cout << "Connection to database failed" << endl;
    }
}

DBM::~DBM() {
    closeDb(); //zamkniecie bazy danych pod koniec
}

bool DBM::connectDb() {
    if (sqlite3_open(("../" + dbPath).c_str(), &db) != SQLITE_OK) {
        cerr << "X Failed to open database: " << sqlite3_errmsg(db) << endl;
        return false;
    }
    return true;
}

void DBM::closeDb() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
        cout << "Database closed" << endl;
    }
}

// Funkcja do SELECT
vector<string> DBM::loadData(const string& query) {
    vector<string> res;
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "X Failed to prepare SELECT: " << sqlite3_errmsg(db) << endl;
        return res;
    }

    int colCount = sqlite3_column_count(stmt);


    //służy do sparsowanego wyświetlania///

    // for (int i = 0; i < colCount; ++i) {
    //     cout << sqlite3_column_name(stmt, i) << "\t";
    // }
    // cout << "\n--------------------------\n";

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        for (int i = 0; i < colCount; ++i) {
            const unsigned char* text = sqlite3_column_text(stmt, i);
            string val = (text ? reinterpret_cast<const char*>(text) : "NULL");

            //służy do sparsowanego wyświetlania///
            //cout << val << "\t";
            res.push_back(val); //dodawanie do wektora
        }

        //służy do sparsowanego wyświetlania///
        //cout << endl;
    }

    sqlite3_finalize(stmt);

    return res;
}

// Funkcja do INSERT / UPDATE / DELETE
bool DBM::writeData(const string& query) {
    return executeQuery(query);
}

//funcja do innych zapytań
bool DBM::executeQuery(string query) {
    char* errMsg = nullptr;

    int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg);

    if (rc != SQLITE_OK) {
        cerr << "X SQL Error " << errMsg << endl;
        sqlite3_free(errMsg); // zwalnianie pamieci bledu
        return false;
    }

    // cout << "Query executed successfully " << endl;
    return true;
}