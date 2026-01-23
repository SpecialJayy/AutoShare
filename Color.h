#ifndef UNTITLED_COLOR_H
#define UNTITLED_COLOR_H

#include <sstream>
#include <iostream>

class Color {
private:
    std::ostringstream bufor;//strumien wyjsciowy do pamieci, dziala tak jak cout ale zapisuje do pamieci
    //bufor to tymczasowe miejsce w pamieci do ktorego trafia tekst zanim zostanie wypisany w konsoi

public:
    Color() = default;

    template <typename T> //umozliwia zapis wszyskiego co mozna wypisac cout np int,float,strind itd
    Color& operator<<(const T& text) {
        //zapis teksu do zmiennej
        bufor << text;

        //faktyczne wypisuwanie
        zakolorujIWypisz();
        return *this;
    };

    void clear();
private:
    void zakolorujIWypisz();

    void zmienKolor(char kod);

    void resetujKolor();
};


#endif //UNTITLED_COLOR_H