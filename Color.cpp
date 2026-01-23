#include "Color.h"
#include <windows.h>

void Color::zakolorujIWypisz()  {
    std::string tekst = bufor.str();
    bufor.str("");
    bufor.clear();
    for (int i =0; i < tekst.size(); i++) {

        if (tekst[i] == '<') {
            zmienKolor(tekst[i+1]);
            i++;
        }else if ( tekst[i]== '>') {
            resetujKolor();
        }else {
            std::cout << tekst[i];
        }
    }
}

void Color::zmienKolor(const char kod) {
    static HANDLE handlerOne = GetStdHandle(STD_OUTPUT_HANDLE);
    switch (kod) {
        case 'N': SetConsoleTextAttribute(handlerOne, 1); break;// navy
        case 'G': SetConsoleTextAttribute(handlerOne, 2); break;// green
        case 'T': SetConsoleTextAttribute(handlerOne, 3); break;// turqoise - jasny nibieski
        case 'C': SetConsoleTextAttribute(handlerOne, 4); break;// crimson
        case 'P': SetConsoleTextAttribute(handlerOne, 5); break;// purple
        case 'Y': SetConsoleTextAttribute(handlerOne, 6); break;// yellow
        case 'H': SetConsoleTextAttribute(handlerOne, 8); break;// gray
        case 'B': SetConsoleTextAttribute(handlerOne, 9); break;// blue
        case 'L': SetConsoleTextAttribute(handlerOne, 10); break;// lime
        case 'A': SetConsoleTextAttribute(handlerOne, 11); break;// aqua
        case 'R': SetConsoleTextAttribute(handlerOne, 12); break;// red
        case 'M': SetConsoleTextAttribute(handlerOne, 13); break;// magenta
        case 'U': SetConsoleTextAttribute(handlerOne, 14); break;// light yellow
        case 'W': SetConsoleTextAttribute(handlerOne, 15); break;// white - bardziej bialy
        default: break;
    }
}

void Color::resetujKolor() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);//kolor podstawowy konsoli
}

//metoda do czyszczenia bufora
void Color::clear() {
    bufor.str("");
    bufor.clear();
}
