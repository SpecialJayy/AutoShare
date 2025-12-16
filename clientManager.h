#ifndef AUTOSHARE_CLIENTMANAGER_H
#define AUTOSHARE_CLIENTMANAGER_H
#include <string>

//dodawanie klientów do bazy danych
bool addClient(std::string login , std::string password);

//usuwanie klientow z bazy danych
bool removeClient();

//edytowanie danych klienta
bool editClient();

//logowanie do serwisu
int login(std::string login, std::string password);

#endif //AUTOSHARE_CLIENTMANAGER_H