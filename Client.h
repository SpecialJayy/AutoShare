#ifndef AUTOSHARE_CLIENT_H
#define AUTOSHARE_CLIENT_H
#include <string>
#include <vector>

#include "Vehicle.h"

class Client {
    //metody prywatne / parametry
private:
    int id;
    std::string login;
    std::vector<char> driverLicenses;
    std::vector<Vehicle> rentedVehicles;

    //metody publiczne
public:
    // Konstruktory
    Client();

    // Destruktor
    ~Client();

    //settery
    void setId(int id);
    void setLogin(std::string login);
    void setDriverLicenses(std::vector <char>);
    void setVehicles(std::vector<Vehicle>);

    //metody

    void createRaport();
};
#endif //AUTOSHARE_CLIENT_H
