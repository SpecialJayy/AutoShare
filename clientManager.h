#ifndef AUTOSHARE_CLIENTMANAGER_H
#define AUTOSHARE_CLIENTMANAGER_H
#include <string>

#include "Client.h"

//dodawanie klientów do bazy danych
bool addClient(std::string login , std::string password);

//usuwanie klientow z bazy danych
bool removeClient();

//edytowanie danych klienta
bool editClient();

//logowanie do serwisu
bool login(std::string login, std::string password);

//tworzenie klasy klienta
bool createClientClass(Client& client,std::string username);

#endif //AUTOSHARE_CLIENTMANAGER_H