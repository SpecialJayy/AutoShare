#ifndef AUTOSHARE_CAR_H
#define AUTOSHARE_CAR_H
#include "Vehicle.h"

class Car: public Vehicle {

public:
    Car(int id, std::string brand, std::string model,int horsePower, std::string fuelType, int year) : Vehicle(id, brand, model) {
        technicalSpecs.horsePower = horsePower;
        technicalSpecs.fuelType = fuelType;
        technicalSpecs.year = year;
    };

    double calculateRentalPrice() const override {
        /// + 200 za samochód osobowy
        double val = 20/(2026-technicalSpecs.year+1)*technicalSpecs.horsePower + 200;
        //zaokraglenie do 2 miejsca po przecinku
        return std::ceil(val * 100.0) / 100.0;
    }

    void printInfo() const override {
        Vehicle::printInfo();
        technicalSpecs.specs();
        colorCout << "Typ: <T Samochod osobowy> \n";
    }
};

#endif //AUTOSHARE_CAR_H