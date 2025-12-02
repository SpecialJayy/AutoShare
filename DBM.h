#ifndef DBM_H
#define DBM_H

#include <iostream>
#include <vector>
#include <string>
#include "sqlite3.h"

class DBM {
private:
    sqlite3* db;
    std::string dbPath;

public:
    // Konstruktor
    DBM(std::string dbName);
    
    // Destruktor
    ~DBM();

    // Metody prywatne
    private:
        bool connectDb();
        void closeDb();

    // Metody publiczne
    public:
        std::vector<std::string> loadData(const std::string& query);
        bool writeData(const std::string& query);
};

#endif