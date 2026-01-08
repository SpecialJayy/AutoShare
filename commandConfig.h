#ifndef AUTOSHARE_COMMANDCONFIG_H
#define AUTOSHARE_COMMANDCONFIG_H
#include <functional>
#include <string>
#include <unordered_map>

//dictionary troche jak w pythonie
//mamy string jako klucz oraz funkcje void jako to co sie wykona
using CommandAction = std::function<void()>;

class CommandConfig {
    private:
        std::unordered_map<std::string, CommandAction> commandMap;

    public:
        CommandConfig();
        void commandController(std::string& command);
};

#endif //AUTOSHARE_COMMANDCONFIG_H