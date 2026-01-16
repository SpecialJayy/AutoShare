#include <iostream>
#include "Color.h"
#include <windows.h>

void Color::setColor(std::string text, int number) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), number);
    std::cout<<text;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);//resetuje kolor na bialy
}

void Color::Navy(std::string text) {
    setColor(text, 1);
}

void Color::Green(std::string text) {
    setColor(text,2);
}

void Color::Turqoise(std::string text) {
    setColor(text,3);
}

void Color::Crimson(std::string text) {
    setColor(text,4);
}

void Color::Purple(std::string text) {
    setColor(text,5);
}

void Color::Gold(std::string text) {
    setColor(text,6);
}

void Color::Gray(std::string text) {
    setColor(text, 8);
}

void Color::Blue(std::string text) {
    setColor(text,9);
}

void Color::Lime(std::string text) {
    setColor(text,10);
}

void Color::Aqua(std::string text) {
    setColor(text,11);
}

void Color::Red(std::string text) {
    setColor(text,12);
}

void Color::Magenta(std::string text) {
    setColor(text,13);
}

void Color::Yellow(std::string text) {
    setColor(text,14);
}

void Color::MoreWhite(std::string text) {
    setColor(text,15);
}
