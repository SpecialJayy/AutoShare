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
    char driverLicenses[4]{};
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
    void setDriverLicenses(char lic[4]);
    void setVehicles(std::vector<Vehicle>);

    //metody

    friend std::ostream& operator <<(std::ostream& os, Client& c);


};
#endif //AUTOSHARE_CLIENT_H
