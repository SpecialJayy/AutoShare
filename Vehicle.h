#ifndef AUTOSHARE_VEHICLE_H
#define AUTOSHARE_VEHICLE_H
#include <iomanip>
#include <iostream>
#include <string>

class Vehicle {
    protected:
    int id;
    std::string brand;
    std::string model;

    ///klasa wewnętrzna
    struct  TechnicalSpecs {
        int horsePower;
        std::string fuelType;
        int year;

        void specs() const {
            std::cout << std::left
        << std::setw(8) << (std::to_string(horsePower) + "KM") << "| "
        << std::setw(6) << year << "| "
        << std::setw(10) << fuelType;

        }
    };

    TechnicalSpecs technicalSpecs;

    public:
    Vehicle(int id, std::string brand, std::string model): id(id), brand(brand), model(model) {
        technicalSpecs ={0,"none",0};
    };

    virtual ~Vehicle() {}

    //polimorfizm
    virtual double calculateRentalPrice() const = 0;

    virtual void printInfo() const {
        std::cout << " " << std::left
                     << std::setw(6) << id << "| "
                     << std::setw(15) << brand << "| "
                     << std::setw(15) << model << "| ";
    }

    //gettery

    const int getId() const {
        return id;
    };
};


#endif //AUTOSHARE_VEHICLE_H