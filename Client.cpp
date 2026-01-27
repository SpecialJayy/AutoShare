#include "Client.h"
#include <iostream>
#include <windows.h>

#include "Bike.h"

using namespace std;

Client::Client() {};

Client::~Client() {
    Color colorCout;
    for (Vehicle* v : this->rentedVehicles) {
        delete v;
    }
    this->rentedVehicles.clear();
    colorCout << "<GWylogowano pomyslnie>\n";
}

//settery
void Client::setId(const int id) {
    this->id = id;
};
void Client::setLogin(const string login) {
    this->login = login;
};
void Client::setDriverLicenses(char lic[4]){
    for (int i = 0; i < 4; i++) {
        this->driverLicenses[i] = lic[i];
    }
};

//gettery
const char* Client::getDriverLicenses() const {
    return driverLicenses;
}

int Client::getId() const {
    return id;
}

int Client::getVehicleCount() const {
    return this->rentedVehicles.size();
}

string Client::getLogin() const {
    return this->login;
}

//metody

ostream& operator <<(ostream& os,Client& c) {
    cout << "DANE KLIENTA" << endl;
    cout << "Id klienta ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
    cout <<  c.id << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
    cout << "Login klienta " << c.login << endl;
    cout << "Posiadane Uprawnienia: " << endl;
    for (char license: c.driverLicenses) {
        if (license !=0) {
            cout << "kat." << license << endl;
        }
    }
    return os;
}

void Client::addVehicle(Vehicle* v) {
    this->rentedVehicles.push_back(v);
}

bool Client::returnVehicle(int vehicleId) {
    for (int i = 0; i < rentedVehicles.size(); i++) {
        if (rentedVehicles[i]->getId() == vehicleId) {
            delete rentedVehicles[i];
            rentedVehicles.erase(rentedVehicles.begin() + i);
            return true;
        }
    }
    return false;
}

void Client::listVehicles() {
    for (int i = 0; i < this->rentedVehicles.size(); i++) {
        this->rentedVehicles[i]->printInfo();
    }
}