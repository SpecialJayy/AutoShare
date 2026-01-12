# AutoShare++




## Autorzy

`-Paweł Błahut`

`-Szymon Broniowski`

`-Jan Gańczarczyk`

Politechnika Krakowska im. Tadeusza Kościuszki w Krakowie

WIEIK - Informatyka W Inżynierii Komputerowej
## Dokumentacja

Aplikacja to system zarządzania wypożyczalnią pojazdów

Pozwala na logowanie sie do panelu klienta, oraz wypożyczanie pojazdów bo uprzedniej weryfikacji kategorii prawa jazdy.

Aplikacja przeznaczona jest dla osób poszukujących pojazdów na wynajem, na długi jak i krótki okres

Aplikacja posiada także panel admina umożliwiający edycje klientów w bazie danych, dodawanie, usuwanie, oraz edycje dostępnych pojazdów

AutoShare++ używa bazy danych SQLite


## Wymagania

To poprawnego działania aplikacji podrzebne są:

SQLite w wersji `3.45.1` lub późniejszej

Python w wersji `3.13.5` lub późniejszej

Aplikacja zbudowana pod systemy operacyjne:
`Windows 10/11`

Aplikacja działa poprawnie jeśli w kosoli wyświetli się prośba o zalogowanie



## Używanie

AutoShare++ to konsolowa aplikacja, więc wszelkie interakcje nawiązuje się poprzez wpisywanie komend do konsoli.

Przykład komendy

`help`

Wynik
```
help -- pokazuje dostepne komendy
zakoncz -- wylogowywuje z serwisu
pojazdy -- pokazuje wypozyczone pojazdy
wyloguj -- wylogowywuje uzytkownika i prosi o ponowne zalogowanie
lista -- wyswietla liste dostepnych pojazdow
wypozycz -- rozpoczyna proces wypozyczania pojazdu
zwolnij -- oddaje pojazd do wypozyczalni
dane -- pokazuje dane klienta
```




## Struktura Projektu

Projekt jest podzielony na poszczególne pliki zarządzające


DBM (Data Base Manager) - Klasa która zarządza bazą danych, w szczególności przepływem informacji, dostęp do niej ma tylko i wyłącznie `ClientManager`, `VehicleManager` oraz inne pliki w których niezbędna jest bezpośrednia komunikacja z bazą danych, dostęp jest celowo ograniczony zgodnie z zasadą hermetyzacji


`ClientManager` - Klasa zarządzająca klientami, dodawaniem, usuwaniem, logowaniem, zmianą danych i tym podobne, posiada dostęp do `DBM`

`VehicleManager` - Podobnie jak klasa ClientManager zarządza pojazdami, ich dodawaniem, usuwaniem, edycją i podobnymi, posiada dostęp do `DMB`

`main` - okno główne aplikacji w którym użytkownik może wchodzić w interakcje z aplikacją. nie posiada dostępu do `DBM`

`Vehicle` - klasa pojazdu, która posiada klasy, które po niej dziedziczą

`Client` - klasa klienta, która posiada metody umożliwiające iterakcje z aplikacją
