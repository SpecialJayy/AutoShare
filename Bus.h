#ifndef AUTOSHARE_BUS_H
#define AUTOSHARE_BUS_H
#include "Vehicle.h"

class Bus: public Vehicle {

public:
    Bus(int id, std::string brand, std::string model,int horsePower, std::string fuelType, int year) : Vehicle(id, brand, model) {
        technicalSpecs.horsePower = horsePower;
        technicalSpecs.fuelType = fuelType;
        technicalSpecs.year = year;
    };

    double calculateRentalPrice() const override {
        /// + 800 za autobus
        double val = 20/(2026-technicalSpecs.year+1)*technicalSpecs.horsePower + 800;
        //zaokraglenie do 2 miejsca po przecinku
        return std::ceil(val * 100.0) / 100.0;
    }

    void printInfo() const override {
        Color colorCout;
        Vehicle::printInfo();
        technicalSpecs.specs();
        colorCout << "Typ: <P Autobus> \n";
    }
};

#endif //AUTOSHARE_BUS_H