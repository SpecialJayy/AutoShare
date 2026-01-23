#include "Client.h"
#include <iostream>
#include <windows.h>

Client::Client() {};

Client::~Client() {
    std::cout << "usunieto klase klienta" << std::endl;
}

//settery
void Client::setId(const int id) {
    this->id = id;
};
void Client::setLogin(const std::string login) {
    this->login = login;
};
void Client::setDriverLicenses(char lic[4]){
    for (int i = 0; i < 4; i++) {
        this->driverLicenses[i] = lic[i];
    }
};
void Client::setVehicles(const std::vector<Vehicle> rentedVehicles) {
    this->rentedVehicles = rentedVehicles;
}

//metody

std::ostream& operator <<(std::ostream& os,Client& c) {
    std::cout << "DANE KLIENTA" << std::endl;
    std::cout << "Id klienta ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
    std::cout <<  c.id << std::endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
    std::cout << "Login klienta " << c.login << std::endl;
    std::cout << "Posiadane Uprawnienia: " << std::endl;
    for (char license: c.driverLicenses) {
        if (license !=0) {
            std::cout << "kat." << license << std::endl;
        }
    }
    return os;
}
