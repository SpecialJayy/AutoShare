#ifndef AUTOSHARE_CLIENT_H
#define AUTOSHARE_CLIENT_H
#include <string>
#include <vector>

#include "Vehicle.h"


class Client {
    //metody prywatne
    private:

    //metody publiczne
    public:
        // Konstruktory
        Client(int id, std::string login, std::vector<char> driverLicenses, std::vector<Vehicle> rentedVehicles);

        Client();

        // Destruktor
        ~Client();
};


#endif //AUTOSHARE_CLIENT_H