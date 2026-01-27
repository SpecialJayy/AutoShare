#ifndef AUTOSHARE_BIKE_H
#define AUTOSHARE_BIKE_H
#include <cmath>

#include "Color.h"
#include "Vehicle.h"

class Bike : public Vehicle {
    public:
    Bike(int id, std::string brand, std::string model,int horsePower, std::string fuelType, int year) : Vehicle(id, brand, model) {
        technicalSpecs.horsePower = horsePower;
        technicalSpecs.fuelType = fuelType;
        technicalSpecs.year = year;
    }

    double calculateRentalPrice() const override {
        double val = 20/(2026-technicalSpecs.year+1)*technicalSpecs.horsePower;
        //zaokraglenie do 2 miejsca po przecinku
        return std::ceil(val * 100.0) / 100.0;
    }


    void printInfo() const override {
        Color colorCout;
        Vehicle::printInfo();
        technicalSpecs.specs();
        colorCout << "Typ: <N Motocykl> \n";
    }
};

#endif //AUTOSHARE_BIKE_H