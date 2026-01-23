# AutoShare++




## Autorzy

`-Paweł Błahut`

`-Szymon Broniowski`

`-Jan Gańczarczyk`

Politechnika Krakowska im. Tadeusza Kościuszki w Krakowie

WIEIK - Informatyka w Inżynierii Komputerowej
## Dokumentacja

Aplikacja to system zarządzania wypożyczalnią pojazdów

Pozwala na logowanie się do panelu klienta oraz na wypożyczanie pojazdów po uprzedniej weryfikacji kategorii prawa jazdy.

Aplikacja przeznaczona jest dla osób poszukujących pojazdów na wynajem, na długi jak i krótki okres czasu. 

Aplikacja posiada także panel admina umożliwiający edycję klientów w bazie danych, dodawanie, usuwanie, oraz edycję dostępnych pojazdów. 

AutoShare++ używa bazy danych SQLite. 


## Wymagania

Do poprawnego działania aplikacji potrzebne są:

SQLite w wersji `3.45.1` lub późniejszej

Python w wersji `3.13.5` lub późniejszej

Aplikacja zbudowana pod systemy operacyjne:
`Windows 10/11`

Aplikacja działa poprawnie jeżeli w konsoli wyświetli się prośba o zalogowanie. 



## Używanie

AutoShare++ to konsolowa aplikacja, więc wszelkie interakcje nawiązuje się poprzez wpisywanie komend do konsoli.

Przykład komendy

`help`

Wynik
```
help -- pokazuje dostępne komendy
zakoncz -- wylogowywuje z serwisu
pojazdy -- pokazuje wypożyczone pojazdy
wyloguj -- wylogowywuje użytkownika i prosi o ponowne zalogowanie
lista -- wyświetla listę dostępnych pojazdów
wypozycz -- rozpoczyna proces wypożyczania pojazdu
zwolnij -- oddaje pojazd do wypożyczalni 
dane -- pokazuje dane klienta
```




## Struktura Projektu

Projekt jest podzielony na poszczególne pliki zarządzające: 


DBM (Data Base Manager) - Klasa, która zarządza bazą danych, w szczególności przepływem informacji. Dostęp do niej ma tylko i wyłącznie `ClientManager`, `VehicleManager` oraz inne pliki, w których niezbędna jest bezpośrednia komunikacja z bazą danych, dostęp jest celowo ograniczony zgodnie z zasadą hermetyzacji. 


`ClientManager` - Klasa zarządzająca klientami, dodawaniem, usuwaniem, logowaniem, zmianą danych i tym podobne, posiada dostęp do `DBM`. 

`VehicleManager` - Podobnie jak klasa ClientManager zarządza pojazdami, ich dodawaniem, usuwaniem, edycją i podobnymi, posiada dostęp do `DBM`. 

`main` - Okno główne aplikacji, w którym użytkownik może wchodzić w interakcję z aplikacją. Nie posiada dostępu do `DBM`. 

`Vehicle` - Klasa pojazdu, która posiada klasy, które po niej dziedziczą. 

`Client` - Klasa klienta, która posiada metody umożliwiające interakcję z aplikacją. 
