#ifndef AUTOSHARE_CLIENTMANAGER_H
#define AUTOSHARE_CLIENTMANAGER_H
#include <string>

bool addClient(std::string login , std::string password);

bool removeClient();

bool editClient();

int login();

#endif //AUTOSHARE_CLIENTMANAGER_H