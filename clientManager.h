#ifndef AUTOSHARE_CLIENTMANAGER_H
#define AUTOSHARE_CLIENTMANAGER_H
#include <string>

#include "Client.h"

//dodawanie klientów do bazy danych
bool addClient(std::string login , std::string password, char licenses[4]);

//usuwanie klientow z bazy danych
bool removeClient(std::string&);

//edytowanie danych klienta
bool editClient();

//logowanie do serwisu
bool login(std::string login, std::string password);

//tworzenie klasy klienta
bool createClientClass(Client& client,std::string username);

//wyswietlanie wszystkich dostepnych do wynajecia pojazdow
void listAllAvailableVehicles();

//wyswietlenie wszystkich pojazdow nawet tych wypozyczonych
void listAllVehicles();

//wypozyczanie pojazdu
bool rentVehicle(Client& client, int id);

//oddawanie pojazdu
bool returnVehicle(Client &client, int id);

//wyswietlanie klientow
bool viewAllClients();

//wyswietlanie raportow
bool viewAllRaports();

//edycja danych klienta
bool editClient(int id, std::string newLogin, std::string newPassword, std::string newLicenseStr);

#endif //AUTOSHARE_CLIENTMANAGER_H