//
// Created by playp on 18/11/2025.
//

#include "DBM.h"
#include "iostream"
#include "sqlite3.h"


//deklaracja klasy Data Base Managment System
namespace std {
    sqlite3* db;
    sqlite3_stmt* stmt;

    ///konstruktor
    DBM::DBM(string dbName) {
        dbName = dbName;

        if (connectDb(dbName)) {
            cout << "Connection to database established." << endl;
        } else {
            cout << "Connection to database failed." << endl;
        };
    }

    bool DBM::connectDb(const string& dbName) {
        if (sqlite3_open(("../"+dbName).c_str(), &db) != SQLITE_OK) {
            std::cerr << "X Failed to open database: " << sqlite3_errmsg(db) << std::endl;
            return false;
        }

        return true;
    }

    vector<string> DBM::loadData(const char* query) {

        vector<string> res;

        if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
            std::cerr << "X Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return vector<string>();
        }
        int colCount = sqlite3_column_count(stmt);

        for (int i = 0; i < colCount; ++i) {
            std::cout << sqlite3_column_name(stmt, i) << "\t";
        }
        std::cout << "\n--------------------------\n";

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            for (int i = 0; i < colCount; ++i) {
                const unsigned char* text = sqlite3_column_text(stmt, i);
                res[i] = (text ? reinterpret_cast<const char*>(text) : "NULL");
            }
        }

        sqlite3_finalize(stmt);

        closeDb();

        return res;

    };

    void DBM::writeData() {

    };

    void DBM::closeDb() {
        sqlite3_close(db);
    };


}