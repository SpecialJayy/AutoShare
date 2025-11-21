#include <iostream>
#include "sqlite3.h"


int main() {
    sqlite3* db;
    sqlite3_stmt* stmt;
    const char* sql = "SELECT * FROM logins;";

    if (sqlite3_open("../klienci.db", &db) != SQLITE_OK) {
        std::cerr << "X Failed to open database: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "X Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 1;
    }

    int colCount = sqlite3_column_count(stmt);

    std::cout << "📋 Table: logins\n";
    std::cout << "--------------------------\n";

    for (int i = 0; i < colCount; ++i) {
        std::cout << sqlite3_column_name(stmt, i) << "\t";
    }
    std::cout << "\n--------------------------\n";

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        for (int i = 0; i < colCount; ++i) {
            const unsigned char* text = sqlite3_column_text(stmt, i);
            std::cout << (text ? reinterpret_cast<const char*>(text) : "NULL") << "\t";
        }
        std::cout << "\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    std::cout << "--------------------------\n";
    std::cout << "✅ Done printing logins table.\n";

    return 0;
}