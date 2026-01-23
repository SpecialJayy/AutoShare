#include "Client.h"
#include <iostream>
#include <windows.h>

Client::Client() {} ;
// Client::Client(int id, std::string login, std::vector<char> driverLicenses, std::vector<Vehicle> rentedVehicles) {
//     this->id = id;
//     this->login = login;
//     this->driverLicenses = driverLicenses;
//     this->rentedVehicles = rentedVehicles;
// }

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
void Client::setDriverLicenses(const std::vector <char> driverLicenses){
    this->driverLicenses = driverLicenses;
};
void Client::setVehicles(const std::vector<Vehicle> rentedVehicles) {
    this->rentedVehicles = rentedVehicles;
}

//metody
void Client::createRaport() {
    std::cout << "DANE KLIENTA" << std::endl;
    std::cout << "Id klienta ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
    std::cout <<  this->id << std::endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
    std::cout << "Login klienta " << this->login << std::endl;
    std::cout << "Posiadane Uprawnienia: " << std::endl;
    for (auto license: this->driverLicenses) {
        std::cout << license << std::endl;
    }
}
