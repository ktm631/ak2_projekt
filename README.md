# ak2_projekt
Opis działania skryptów testowych:
1) test
2) user
3) cache
4) cpuusage

1) test
Skrypt służy do przeprowadzania pomiarów w wybranych scenariuszach.

Użytkownik ma możliwość zmiany nazw plików w zależności od potrzeb. Nazwa pliku z wynikami pomiarów składa się z 4 sekcji oddzielonych znakiem "_" i oznaczonych zmiennymi:
a)name1 - identyfikator częstotliwości cpu. Do celów pomiarowych używane są 3 nazwy - min <częstotliwość minimalna 1100/1200 MHz>, min <częstotliwość średnia 1700 MHz> oraz max <częstotliwość minimalna 2200 MHz>
b)name2 - identyfikator scenariusza. Do celów pomiarowych używane są 3 nazwy - stress <obciążenie procesora 100%>, user <10 kart firefoxa, pakiet libre office>, min <tryb tekstowy, wyłączone bluetooth i sieć>
c)name3 - opcjonalny dodatek używany tylko do testów szybkości uruchomienia aplikacji ze scenariusza user. Do celów pomiarowych używana jest jedna nazwa - times.
d)e1 lub e2 - rozszerzenie pliku. e1 to .csv, e2 to .txt

Dodatkowo użytkownik ustawia parametry pracy procesora oznaczone zmiennymi:
a) cpus - liczba rdzeni logicznych cpu
b) min - minimalna częstotliwość taktowania procesora. Podawana w Hz. 
c) max - maksymalna częstotliwość taktowania procesora. Podawana w Hz.
Do celów pomiarowych używane są 3 wartości zmiennych min i max - 1100000/1200000, 1700000/1800000 i 2200000.

Użytkownik ustawia też parametry testowania wydajności oznaczone zmiennymi:
a) time - czas zbierania danych w sekundach
b) x - liczba powtórzeń testów
c) i - iterator pętli testującej

Sekcje skryptu:
a) #wyłączenie nmi_watchdog
Jednorazowa dezaktywacja NMI watchdog w celu przeprowadzenia pomiarów.
b) #ustawienie czestotliwosci cpu
Petla ustawia strażnika pracy procesora na modyfikowalny ręcznie oraz ustawia wybraną częstotliość pracy dla każdego rdzenia logicznego cpu.
c) #petla przeprowadzajaca testy
Pętla przeprowadzająca testy pomiarowe.
d) #czyszczenie cache
Uruchomienie skryptu cache, który ma zapewnić identyczne warunki pomiarowe dla każdego testu poprzez nadpisanie danych z poprzednich testów znajdujących się w pamięci cache procesora.
e) #user_start
Uruchomienie skryptu user. Należy odkomentować zawartość sekcji w celu przepowadzenia testów w scenariuszu user. W przeciwnym wypadku zawartość powinna pozostać zakomentowana.
f) #start intel pcm.x
Sekcja wykonująca pomiary za pomocą oprogramowania Intel PCM. Próbki pobierane są co 1 sekundę, wynik zapisywany do pliku.
g) #start powerstat
Sekcja wykonująca pomiary za pomocą oprogramowania powerstat. Próbki pobierane są co 1 sekundę, wynik zapisywany do pliku.
!W sekcjach f i g znajdują się komendy dla każdego realizowanego scenariusza. Należy odkomentować odpowiednią linię.!
h) #procedury koncowe
Zmiana uprawnień do plików wynikowych aby możliwa była ich edycja bez uprawnień root.
i) #user_koniec
Zakończenie działania aplikacji używanych w scenariuszu user. Zmiana uprawnień do pliku wynikowego. Należy odkomentować zawartość sekcji w celu przepowadzenia testów w scenariuszu user. W przeciwnym wypadku zawartość powinna pozostać zakomentowana.
j) #przywrocenie dynamicznego skalowania czestotliwoscia cpu
Ustawienie strażnika cpu dynamicznie skalującego częstotliwością.

Skrypt należy uruchamiać jako root.
Potrzebne aplikacje:
a) intel pcm.x
b) cpufreq-utils
c) stress
d) powerstat
e) firefox
f) pakiet libre office




2) user
Skrypt używany do przeprowadzenia testów w sceanriuszu user.

Użytkownik ma możliwość zmiany nazw plików w zależności od potrzeb. Nazwa pliku z wynikami pomiarów składa się z 4 sekcji oddzielonych znakiem "_" i oznaczonych zmiennymi:
a)name1 - identyfikator częstotliwości cpu. Do celów pomiarowych używane są 3 nazwy - min <częstotliwość minimalna 1100/1200 MHz>, min <częstotliwość średnia 1700/1800 MHz> oraz max <częstotliwość minimalna 2200 MHz>
b)name2 - identyfikator scenariusza. Do celów pomiarowych używana 1 nazwa - user <10 kart firefoxa, pakiet libre office>.
c)name3 - opcjonalny dodatek używany tylko do testów szybkości uruchomienia aplikacji ze scenariusza user. Do celów pomiarowych używana jest jedna nazwa - times.
d)e1 lub e2 - rozszerzenie pliku. e1 to .csv, e2 to .txt

Dodatkowo skyrpt wykorzystuje zmienne:
a) start - czas startu uruchamiania aplikacji
b) end - czas zakończenia uruchamiania aplikacji
c) wynik - różnica end-start podawana w nanosekundach. To łączny czas uruchamiania aplikacji.

Skrypt uruchamia przeglądarkę firefox z adresami zawartymi w pliku url w nowych kartach <10 kart> oraz aplikacje pakietu libre office - writer, calc i impress.

Czas uruchamiania aplikacji zapisywany jest do pliku.

Potrzebne aplikacje:
a) firefox
b) pakiet libre office
c) xargs





3) cache
Skrypt służy do zapewnienia identycznych warunków pomiarowych dla każdego testu poprzez nadpisanie danych z poprzednich testów znajdujących się w pamięci cache procesora.
Aby skrypt zadziałał należy go zapisać ze zmianą rozszerzenia z .txt na .c oraz skompilować poleceniem:
gcc -I /usr/src/linux-headers-4.2.0.35-/include/ cache.c -o cache



4)cpuusage
Skrypt służy do pobierania informacji o procentowym wykorzystaniu pamięci i procesora przez aplikacje uruchamiane w scenariuszu user. Z tego względu używany tylko w scenariuszu user. Wyniki pomiaru zapisywane są do 2 plików- każdy związany z inną aplikacją. Dane pobiarane są co 1 sekundę.

Użytkownik ma możliwość zmiany nazw plików w zależności od potrzeb. Nazwa pliku z wynikami pomiarów składa się z 4 sekcji oddzielonych znakiem "_" i oznaczonych zmiennymi:
a) nazwa - identyfikator aplikacji. Przechowywane w 2 zmiennych - name1 i name2. Name1 to identyrikator aplikacji firefox, name2 - identyfikator pakietu libreoffice. 
b) pomiar - identyfikator pomiaru. Przekazywany do skryptu jako parametr 1. Do celów pomiarowych używane 2 nazwy - intel (pomiar aktywności procesora programem intel pcm) oraz power (pomiar zużycia energii programem powerstat).
c) numer iteracji - identyfikator numeru iteracji pomiarowej. Przekazywany do skryptu jako parametr 2. 
d) ext - rozszerzenie pliku (.csv)

Dodatkowo tworzone są 3 zmienne:
a) pid1 - PID aplikacji firefox
b) pid2 - PID pakietu libreoffice
3) time - liczba operacji

Sekcje skryptu:
a) #tworzenie odpowiednich plikow
Utworzenie plików w których zapisywane są dane pomiarowe.
b) #zapis nagłówków danych do plików
Zapisanie nagłówków mierzonych danych do plików.
c) #pomiary
Pętla pomiarowa pobierająca interesujące użytkownika dane.
d) #procedury końcowe
Zmiana uprawnień do plików wynikowych.

Potrzebne aplikacje:
a) ps
b) awk



