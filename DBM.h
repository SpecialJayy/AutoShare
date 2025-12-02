//
// Created by playp on 18/11/2025.
//

#ifndef AUTOSHARE_DBM_H
#define AUTOSHARE_DBM_H
#include <string>
#include <vector>

///definicja Data Base Managment System

namespace std {
    class DBM {

    private:
        string dbName = "autoshare.db";

    public:
        //konstruktor
        DBM(string dbName);

        //metody
        bool connectDb(const string& dbName);
        vector<string> loadData(const char* sql);
        void writeData();
        void closeDb();
    };
} // std

#endif //AUTOSHARE_DBM_H