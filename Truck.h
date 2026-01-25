#ifndef AUTOSHARE_TRUCK_H
#define AUTOSHARE_TRUCK_H
#include "Vehicle.h"

class Truck : public Vehicle {
    public:
    Truck(int id, std::string brand, std::string model,int horsePower, std::string fuelType, int year) : Vehicle(id, brand, model) {
        technicalSpecs.horsePower = horsePower;
        technicalSpecs.fuelType = fuelType;
        technicalSpecs.year = year;
    }

    double calculateRentalPrice() const override {
        /// + 400 dla ciężarówek
        double val = 20/(2026-technicalSpecs.year+1)*technicalSpecs.horsePower + 400;
        //zaokraglenie do 2 miejsca po przecinku
        return std::ceil(val * 100.0) / 100.0;
    }

    void printInfo() const override {
        Vehicle::printInfo();
        technicalSpecs.specs();
        colorCout << "Typ: <Y Samochod Ciezarowy> \n";
    }
};

#endif //AUTOSHARE_TRUCK_H