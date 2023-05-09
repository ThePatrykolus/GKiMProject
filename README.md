# GKiMProjekt
## Specyfikacja 
Przygotowany na zajęciach format graficzny pozwala na przechowywanie informacji o grafikach rastrowych o wymiarach 256x170 pikseli. Zapisane w nim pliki mogą przyjmować 9 postaci, które nazywać będziemy typami obrazka.
Każdy plik zaczyna się od nagłówku składającego się z kolejno:
- 2 znakowy (char) identyfikator 
  - 2 bajty (char) 
- 1 znak (char) określający typ obrazka 
  - 1 bajt (char) 
- Szerokość obrazka w pikselach 
  - 2 bajty (Uint16)
- Wysokość obrazka w pikselach 
  - 2 bajty (Uint16)

Czyli nagłówek zajmuje 7 bajtów. Dalej kolejno zapisywana jest paleta dedykowana (128*3= 384 bajtów) jeśli dany typ obrazka jej wymaga, a następnie informacje o kolorach każdego kolejnego piksela w postaci odpowiedniej dla każdego typu obrazka

Typy obrazków:
-	N – 7-bitowe RGB wykorzystujące paletę narzuconą, każdy pixel(7 bitów) jest zapisany na 1 bajcie
-	B – 7-bitowa skala szarości, każdy pixel(7 bitów) jest zapisany na 1 bajcie
-	D – 7-bitowe RGB wykorzystujące paletę dedykowaną, która w przypadku konwersji na nasz format jest generowana z pomocą algorytmu medianCut i sortowania kubełkowego, a informacja o kolorze każdego pixela, odpowiadający kolor z palety(7 bitów) jest zapisana na 1 bajcie
-	n – 7-bitowe RGB kompresowane przy użyciu algorytmu byteRun
-	b – 7 bitowa skala szarości kompresowana przy użyciu algorytmu byteRun
-	d – 7-bitowe RGB wykorzystujące paletę dedykowaną, gdzie informacje o kolorach są skompresowane algorytmem byteRun
-	p – 7-bitowa skala szarości przy czym dane są upakowane w ten sposób, że informacja o kolorze każdych kolejnych 8 pixeli jest zapisane na 7 bajtach, wykorzystując każdy bit danych
-	m – 7 bitowe RGB wykorzystujące paletę narzuconą, przy czym dane są upakowane w ten sposób, że informacja o kolorze każdych kolejnych 8 pixeli jest zapisane na 7 bajtach, wykorzystując każdy bit danych
-	t – 7 bitowa paleta dedykowana, przy czym dane są upakowane w ten sposób, że informacja o kolorze każdych kolejnych 8 pixeli jest zapisane na 7 bajtach, wykorzystując każdy bit danych

## Wnioski

Obrazki są wymiarów 170*256 pixeli, czyli każdy sklada się z 43500 pixeli(i tyleż bajtów w przypadku zapisu bez kompresji gdzie każde 7 bitów jest zapisane na jednym bajcie).

Nagłówek to 2 znakowy identyfikator(2bajty), jednoznakowy typ orbazka(1bajt), szerokość obrazka(2 bajty), wysokość obrazka(2bajty), co daje w sumie 7 bajtow danych.

W przypadku zapisywania palety dedykowanej, kazda paleta to 128 elementow typu SDL_Color(3 bajty każdy), co powieksza rozmiar pliku o 384 bajty. 

W przypadku zapisywania plikow bez kompresji w skali szarości(B), lub kolorze w palecie narzuconej(N) możemy się spodziewać, że pliki z obrazkami zajma dokładnie 7+43500 = 43507 bajtow, w przypadku palety dedykowanej bez kompresji(D) będzie to o 384 bajty więcej czyli 43911 i tak właśnie jest.

Nasz format wykorzystuje tylko 7bitow do opisu koloru każdego pixela, ale jako że dane o tych kolorach przechowujemy w zmiennych 8-bitowych to jeden bit jest wykorzystywany niepotrzebnie.

Rezygnujac z niego i zapisując każdy kolor w pamięci na dysku faktycznie przy użyciu jedynie 7 bitów możemy liczyć na oszczędności w okolicach 12.5%(5420 bajtów), czyli kolory każdego pixela będą opisane na 
43500*7/8 =  38080 bajtach. 

W przypadku korzystania z algorytmu kompresji byteRun możemy się spodziewać, że w sytuacji pesymistycznej gdy każdy następujący po sobie pixel będzie reprezentowany przez inną wartość liczbową to plik po kompresji będzie większy o 43500/128 = 384 bajty, bo tyle razy algorytm zapisywałby na 1 bajcie informację, ze następna sekwencja 128 pixeli będzie niepowtarzalna.

W przypadku optymistycznym(obrazek w jendym kolorze) każde 128 pixeli byłoby zapisane na 2 bajtach, czyli informacje o kolorze każdego pixela zajęłyby 43500/128*2 = 680 bajtow, co stanowi tylko 1/64, czyli około 1.5% pierwotnej wartości. W przypadku menu głównego z gry Super Mario Bros 3, który został podany przez prowadzącego, a który to obrazek ma jednolity kolor tła, byteRun pozwala ograniczyć zajmowaną pamięć do 10382 bajtow, czyli ponad czterokrotnie.
Powyższe przypuszczenia pokrywają się z obserwacjami. 
