#include <exception>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <vector>
using namespace std;


SDL_Window* window = NULL;
SDL_Surface* screen = NULL;

#define szerokosc 512
#define wysokosc 340

#define tytul "GKiM2022 - Projekt - Zespół 31"


void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B);
SDL_Color getPixel (int x, int y);

// Struktura ktora przechowuje osiem 7-bajtowych wartosci, kazda wartosc na osobnym bajcie
struct kolor8x7bitNa8bajtach {
    Uint8 bajt1; // maja miec postac 0b0xxxxxxx, najstarszy bit zawsze zero
    Uint8 bajt2; // kazda z tych wartosci nie wykorzystuje najstarszego bitu(z lewej strony)
    Uint8 bajt3;
    Uint8 bajt4;
    Uint8 bajt5;
    Uint8 bajt6;
    Uint8 bajt7;
    Uint8 bajt8;
    void print() {
        cout << endl
             << (int)bajt1 << "\t"
             << (int)bajt2 << "\t"
             << (int)bajt3 << "\t"
             << (int)bajt4 << "\t"
             << (int)bajt5 << "\t"
             << (int)bajt6 << "\t"
             << (int)bajt7 << "\t"
             << (int)bajt8 << "\t" << endl;
    }
};

// Struktura ktora przechowuje upakowane 7-bajtowe wartosci - zamiast 8 na 8 bajtach to 8 na 7 bajtach
struct kolor8x7bitNa7bajtach {
    Uint8 bajt1full; // w tej strukturze kazdy bit jest wykorzystywany
    Uint8 bajt2full; // czyli maja miec postac 0bxxxxxxxx
    Uint8 bajt3full;
    Uint8 bajt4full; // pola ponazywalem full(upchane sa), zeby sie nie mylilo potem
    Uint8 bajt5full;
    Uint8 bajt6full;
    Uint8 bajt7full;
    void print() {
        cout << endl
             << (int)bajt1full << "\t"
             << (int)bajt2full << "\t"
             << (int)bajt3full << "\t"
             << (int)bajt4full << "\t"
             << (int)bajt5full << "\t"
             << (int)bajt6full << "\t"
             << (int)bajt7full << "\t" << endl;
    }
};

void czyscEkran(Uint8 R, Uint8 G, Uint8 B);

void Funkcja1();
void Funkcja2();
void Funkcja3();
void Funkcja4();
void Funkcja5();
void Funkcja6();
void Funkcja7();
void Funkcja8();
void Funkcja9();

Uint8 z24RGBna7RGB(SDL_Color kolor);
SDL_Color z7RGBna24RGB(Uint8 kolor7bit);

Uint8 z24RGBna7BW(SDL_Color kolor);
SDL_Color z7BWna24RGB(Uint8 BW7bit);

void kompresjaByteRun(Uint8 wejscie[], int dlugosc);

// funkcje do zapisywania 7-bitowych wartosci w paczkach

/**
  * upychanie
  */
kolor8x7bitNa7bajtach upchaj8x7bitNa7bajtach(kolor8x7bitNa8bajtach doUpchania);


/**
  * rozpakowywanie
  */
kolor8x7bitNa8bajtach wypakujDo8x7bitNa8bajtach(kolor8x7bitNa7bajtach doRozpakowania);


void Funkcja1() {

    SDL_Color kolor;
    int R, G, B;
    int kolor8bit;
    int nowyR, nowyG, nowyB;

    for(int y = 0; y < wysokosc / 2; y++) {
        for(int x = 0; x < szerokosc / 2; x++) {

            kolor = getPixel(x, y);

            R = kolor.r;
            G = kolor.g;
            B = kolor.b;

            // wersja 1

            nowyR = R >> 5;
            nowyG = G >> 5;
            nowyB = B >> 6;

            kolor8bit = (nowyR << 5) + (nowyG << 2) + (nowyB);

            //cout << "nowyR: " << nowyR << ", nowyG: " << nowyG << ", nowyB: " << nowyB << endl;
            //cout << "kolor8bit: " << kolor8bit << endl;

            R = nowyR << 5;
            G = nowyG << 5;
            B = nowyB << 6;

            setPixel(x + szerokosc / 2, y, R, G, B);

            // wersja 2

            R = nowyR * 255.0 / 7.0;
            G = nowyG * 255.0 / 7.0;
            B = nowyB * 255.0 / 3.0;
            setPixel(x, y + wysokosc / 2, R, G, B);

            // wersja 3

            R = kolor.r;
            G = kolor.g;
            B = kolor.b;

            nowyR = round(R * 7.0 / 255.0);
            nowyG = round(G * 7.0 / 255.0);
            nowyB = round(B * 3.0 / 255.0);

            kolor8bit = (nowyR << 5) + (nowyG << 2) + (nowyB);

            //cout << "nowyR: " << nowyR << ", nowyG: " << nowyG << ", nowyB: " << nowyB << endl;
            //cout << "kolor8bit: " << kolor8bit << endl;

            R = nowyR * 255.0 / 7.0;
            G = nowyG * 255.0 / 7.0;
            B = nowyB * 255.0 / 3.0;
            setPixel(x + szerokosc / 2, y + wysokosc / 2, R, G, B);
        }
    }

    SDL_UpdateWindowSurface(window);
}

void Funkcja2() {

    SDL_Color kolor;
    int R, G, B;
    int kolor7bit;
    int nowyR, nowyG, nowyB;

    for(int y = 0; y < wysokosc / 2; y++) {
        for(int x = 0; x < szerokosc / 2; x++) {

            kolor = getPixel(x, y);

            R = kolor.r;
            G = kolor.g;
            B = kolor.b;

            // wersja 1

            nowyR = R >> 6;
            nowyG = G >> 5;
            nowyB = B >> 6;

            kolor7bit = (nowyR << 5) + (nowyG << 2) + (nowyB);

            //cout << "nowyR: " << nowyR << ", nowyG: " << nowyG << ", nowyB: " << nowyB << endl;
            //cout << "kolor8bit: " << kolor8bit << endl;

            R = nowyR << 6;
            G = nowyG << 5;
            B = nowyB << 6;

            setPixel(x + szerokosc / 2, y, R, G, B);

            // wersja 2

            R = nowyR * 255.0 / 3.0;
            G = nowyG * 255.0 / 7.0;
            B = nowyB * 255.0 / 3.0;
            setPixel(x, y + wysokosc / 2, R, G, B);

            // wersja 3

            R = kolor.r;
            G = kolor.g;
            B = kolor.b;

            nowyR = round(R * 3.0 / 255.0);
            nowyG = round(G * 7.0 / 255.0);
            nowyB = round(B * 3.0 / 255.0);

            kolor7bit = (nowyR << 5) + (nowyG << 2) + (nowyB);

            //cout << "nowyR: " << nowyR << ", nowyG: " << nowyG << ", nowyB: " << nowyB << endl;
            //cout << "kolor8bit: " << kolor8bit << endl;

            R = nowyR * 255.0 / 3.0;
            G = nowyG * 255.0 / 7.0;
            B = nowyB * 255.0 / 3.0;
            setPixel(x + szerokosc / 2, y + wysokosc / 2, R, G, B);
        }
    }

    SDL_UpdateWindowSurface(window);
}

void Funkcja3() {

    SDL_Color kolor;
    Uint8 kolor7bit;

    for(int y = 0; y < wysokosc / 2; y++) {
        for(int x = 0; x < szerokosc / 2; x++) {
            kolor = getPixel(x, y);
            kolor7bit = z24RGBna7RGB(kolor);
            kolor = z7RGBna24RGB(kolor7bit);
            setPixel(x + szerokosc / 2, y, kolor.r, kolor.g, kolor.b);
        }
    }

    SDL_UpdateWindowSurface(window);
}

void Funkcja4() {

    SDL_Color BW;
    Uint8 BW7bit;

    for(int y = 0; y < wysokosc / 2; y++) {
        for(int x = 0; x < szerokosc / 2; x++) {
            BW = getPixel(x, y);
            BW7bit = z24RGBna7BW(BW);
            BW = z7BWna24RGB(BW7bit);
            setPixel(x + szerokosc / 2, y, BW.r, BW.g, BW.b);
        }
    }

    SDL_UpdateWindowSurface(window);
}

int ileKolorow = 0;
SDL_Color paleta[256 * 170];

SDL_Color paleta7d[128];
SDL_Color paleta7n[128];
SDL_Color paleta7bw[128];


int dodajKolor(SDL_Color kolor) {
    int aktualnyKolor = ileKolorow;
    paleta[aktualnyKolor] = kolor;
    /*if(aktualnyKolor <= 127)
    cout << aktualnyKolor << ": [" << (int)kolor.r << ", " << (int)kolor.g << ", " << (int)kolor.b << "]\n";*/
    ileKolorow++;
    return aktualnyKolor;
}

bool porownajKolory(SDL_Color kolor1, SDL_Color kolor2) {
    if(kolor1.r == kolor2.r && kolor1.g == kolor2.g && kolor1.b == kolor2.b)
        return true;
    return false;
}

int sprawdzKolor(SDL_Color kolor) {
    if(ileKolorow > 0) {
        for(int k = 0; k < ileKolorow; k++) {
            if(porownajKolory(kolor, paleta[k]))
                return k;
        }
    }

    return dodajKolor(kolor);
}

void Funkcja5() {

    SDL_Color kolor;
    int nrKoloru;
    ileKolorow = 0;
    for(int y = 0; y < wysokosc / 2; y++) {
        for(int x = 0; x < szerokosc / 2; x++) {
            kolor = getPixel(x, y);
            nrKoloru = sprawdzKolor(kolor);
        }
    }
    cout << "wszystkich pikseli: " << 256 * 170 << endl;
    cout << "wszystkich kolorow: " << ileKolorow << endl;

    for(int k = 0; k < 128; k++) {
        paleta7n[k] = z7RGBna24RGB(k);
        paleta7bw[k] = z7BWna24RGB(k);
    }

    if(ileKolorow < 128) {
        for(int k = 0; k < 128; k++) {
            paleta7d[k] = {0, 0, 0};
        }
        for(int k = 0; k < ileKolorow; k++) {
            paleta7d[k] = paleta[k];
        }
    }

    for(int k = 0; k < 128; k++) {
        for(int y = 0; y < 10; y++) {
            setPixel(k, y + wysokosc / 2, paleta7n[k].r, paleta7n[k].g, paleta7n[k].b);
            setPixel(k, y + 20 + wysokosc / 2, paleta7bw[k].r, paleta7bw[k].g, paleta7bw[k].b);
            setPixel(k, y + 40 + wysokosc / 2, paleta7d[k].r, paleta7d[k].g, paleta7d[k].b);
        }
    }

    SDL_UpdateWindowSurface(window);
}

void narysujPalete(int px, int py, SDL_Color paleta7[]) {
    SDL_Color kolor;
    int nrKoloru;
    ileKolorow = 0;
    for(int y = 0; y < wysokosc / 2; y++) {
        for(int x = 0; x < szerokosc / 2; x++) {
            kolor = getPixel(x, y);
            nrKoloru = sprawdzKolor(kolor);
        }
    }

    for(int k = 0; k < 128; k++) {
        paleta7n[k] = z7RGBna24RGB(k);
        paleta7bw[k] = z7BWna24RGB(k);
    }

    if(ileKolorow <= 128) {
        for(int k = 0; k < 128; k++) {
            paleta7d[k] = {0, 0, 0};
        }
        for(int k = 0; k < ileKolorow; k++) {
            paleta7d[k] = paleta[k];
        }
    }
    else {
        for(int k = 0; k < 128; k++) {
            paleta7d[k] = {0, 0, 0};
        }
    }

    int index;
    for(int y = 0; y < wysokosc / 2; y++) {
        for(int x = 0; x < szerokosc / 2; x++) {
            index = (x / 16) + (y / 21) * 16;
            if(index <= 127) setPixel(x + px, y + py, paleta7[index].r, paleta7[index].g, paleta7[index].b);
        }
    }
}

void Funkcja6() {

    narysujPalete(szerokosc / 2, 0,  paleta7n);
    narysujPalete(0, wysokosc / 2,  paleta7bw);
    narysujPalete(szerokosc / 2, wysokosc / 2,  paleta7d);

    SDL_UpdateWindowSurface(window);
}

SDL_Color paleta7D[128];

int ileKolorow7 = 0;
SDL_Color obrazek[(szerokosc / 2) * (wysokosc / 2)];

Uint8 najwiekszaRoznica(int start, int koniec) {
    int minRed = 255, maxRed = 0;
    int minGreen = 255, maxGreen = 0;
    int minBlue = 255, maxBlue = 0;
    for(int i = start; i < koniec; i++) {
        if(obrazek[i].r > maxRed) maxRed = obrazek[i].r;
        if(obrazek[i].r < minRed) minRed = obrazek[i].r;
        if(obrazek[i].g > maxGreen) maxGreen = obrazek[i].g;
        if(obrazek[i].g < minGreen) minGreen = obrazek[i].g;
        if(obrazek[i].b > maxBlue) maxBlue = obrazek[i].b;
        if(obrazek[i].b < minBlue) minBlue = obrazek[i].b;
    }
    int biggestDifference = maxRed - minRed;
    int answer = 1;
    if (maxGreen - minGreen > biggestDifference) {
        biggestDifference = maxGreen - minGreen;
        answer = 2;
    }
    if (maxBlue - minBlue > biggestDifference) {
        answer = 3;
    }
    return answer;
}

void sortujKubelek(int start, int koniec, Uint8 ktoraSkladowa) {
    int maksimum = start;
    for(int p = start; p < koniec; p++) {
        maksimum = p;
        for(int i = p; i < koniec; i++) {
            switch(ktoraSkladowa) {
                case 1:
                    if(obrazek[i].r > obrazek[maksimum].r) {
                        maksimum = i;
                    }
                    break;
                case 2:
                    if(obrazek[i].g > obrazek[maksimum].g) {
                        maksimum = i;
                    }
                    break;
                case 3:
                    if(obrazek[i].b > obrazek[maksimum].b) {
                        maksimum = i;
                    }
                    break;
            }
            swap(obrazek[p], obrazek[maksimum]);
        }
    }
}


/**
    ¯\_(ツ)_/¯
*/
void medianCut(int start, int koniec, int iteracja) {
    if(iteracja > 0) {
        // najpierw sortujemy kubełek, a później dzielimy na dwa mniejsze
        // Konieczne jest ustalić względem której składowej posortować kubełek
        Uint8 ktoraSkladowa = najwiekszaRoznica(start, koniec);
        sortujKubelek(start, koniec, ktoraSkladowa); // sortujKubelek(start, koniec, ktoraSkladowa);

        cout << "Dzielimy kubelek na poziomie: " << iteracja << endl;
        int srodek = (start + koniec) / 2; // wyznaczamy srodek podzialu zakładając, że zawsze można podzielić na równo
        medianCut(start, srodek, iteracja - 1);
        medianCut(srodek + 1, koniec, iteracja - 1);
        cout << "Zakonczono podzial na poziomie: " << iteracja << endl;
    }
    else {
        // budujemy paletę uśredniając kolory z określonego kubełka
        int sumaR = 0;
        int sumaG = 0;
        int sumaB = 0;
        for(int p = start; p < koniec; p++) {
            sumaR += obrazek[p].r;
            sumaG += obrazek[p].g;
            sumaB += obrazek[p].b;
        }
        Uint8 Red = sumaR / (koniec - start);
        Uint8 Green = sumaG / (koniec - start);
        Uint8 Blue = sumaB / (koniec - start);
        SDL_Color nowyKolor = {Red, Green, Blue};
        paleta7D[ileKolorow7] = nowyKolor;
        cout << ileKolorow7 << ": ["<<(int)nowyKolor.r << ", " << (int)nowyKolor.g << ", " << (int)nowyKolor.b << "]\n";
        ileKolorow7++;
    }
}


/**
    Szuka dla danego koloru(SDL_Color, zwykle 24bit) odpowiadajacy(najbardziej podobny)
    kolor z palety podanej jako drugi argument
    Paleta jako 2 argument to tablica
    zwraca index tej tablicy kolorow palety
*/
int znajdzSasiada(SDL_Color kolor, SDL_Color paleta7[]) {
    int minimum = 999;
    int indexMinimum = 0;

    SDL_Color kolorPaleta;
    int odleglosc;

    for(int i = 0; i < 128; i++) {
        kolorPaleta = paleta7[i];
        odleglosc = (abs(kolor.r - kolorPaleta.r) + abs(kolor.g - kolorPaleta.g) + abs(kolor.b - kolorPaleta.b)) / 3;
        if(odleglosc < minimum) {
            indexMinimum = i;
            minimum = odleglosc;
        }
    }
    return indexMinimum;
}

void narysujPalete7(int px, int py, SDL_Color paleta7[]) {
    int index;
    for(int y = 0; y < wysokosc / 2; y++) {
        for(int x = 0; x < szerokosc / 2; x++) {
            index = (x / 16) + (y / 21) * 16;
            if(index <= 127) setPixel(x + px, y + py, paleta7[index].r, paleta7[index].g, paleta7[index].b);
        }
    }
}

void narysujObrazek7(int px, int py, SDL_Color paleta7[]) {
    SDL_Color kolor;
    int indexKoloru;
    for(int y = 0; y < wysokosc / 2; y++) {
        for(int x = 0; x < szerokosc / 2; x++) {
            kolor = getPixel(x, y);
            indexKoloru = znajdzSasiada(kolor, paleta7);
            setPixel(x, y + wysokosc / 2, paleta7[indexKoloru].r, paleta7[indexKoloru].g, paleta7[indexKoloru].b);
        }
    }
}

void Funkcja7() {

    SDL_Color kolor;
    Uint8 kolor7bit;
    int ilePikseli = 0;

    for(int y = 0; y < wysokosc / 2; y++) {
        for(int x = 0; x < szerokosc / 2; x++) {
            kolor = getPixel(x, y);
            kolor7bit = z24RGBna7RGB(kolor);
            kolor = z7RGBna24RGB(kolor7bit);
            obrazek[ilePikseli] = {kolor.r, kolor.g, kolor.b};
            ilePikseli++;
            //setPixel(x, y, kolor.r, kolor.g, kolor.b);
        }
    }

    //SDL_UpdateWindowSurface(window);

    ileKolorow7 = 0;
    medianCut(0, ilePikseli, 7);

    narysujPalete7(szerokosc / 2, wysokosc / 2, paleta7D);

    //SDL_UpdateWindowSurface(window);

    narysujObrazek7(0, wysokosc / 2, paleta7D);

    SDL_UpdateWindowSurface(window);
}

/**
    Generuje palete
*/
void generujPalete(){
    SDL_Color kolor;
    Uint8 kolor7bit;
    int ilePikseli = 0;

    for(int y = 0; y < wysokosc / 2; y++) {
        for(int x = 0; x < szerokosc / 2; x++) {
            kolor = getPixel(x, y);
            kolor7bit = z24RGBna7RGB(kolor);
            kolor = z7RGBna24RGB(kolor7bit);
            obrazek[ilePikseli] = {kolor.r, kolor.g, kolor.b};
            ilePikseli++;
        }
    }

    ileKolorow7 = 0;
    medianCut(0, ilePikseli, 7);

}

void zapiszObraz24a(){

    // metoda alternatywna - nie będziemy z niej korzystać
    SDL_Color kolor;

    Uint16 szerokoscObrazka = szerokosc/2;
    Uint16 wysokoscObrazka = wysokosc/2;

    cout << "Zapisujemy plik 'obraz24.bin' uzywajac << " << endl;
    ofstream wyjscie("obra  z24.bin");

    //
    wyjscie << "ID" << (Uint8)szerokoscObrazka  << (Uint8)(szerokoscObrazka>>8)
            << (Uint8)wysokoscObrazka   << (Uint8)(wysokoscObrazka>>8);

    for(int y = 0; y < wysokosc / 2; y++) {
        for(int x = 0; x < szerokosc / 2; x++) {
            kolor = getPixel(x, y);
            wyjscie << kolor.r << kolor.g << kolor.b;
        }
    }

    wyjscie.close();
}

void zapiszObraz24(){

    SDL_Color kolor;

    Uint16 szerokoscObrazka = szerokosc/2;
    Uint16 wysokoscObrazka = wysokosc/2;

    char identyfikator[] = "DG";

    cout << "Zapisujemy plik 'obraz24.bin' uzywajac metody write()" << endl; // metoda write pozwala zapisywac serie znakow do naszego wyjscia
    ofstream wyjscie("obraz24.bin", ios::binary); // flagujemy openmode binary zeby ... bylo git lol

    // podajemy jako argument zrzutowany na char wskaznik na zmienna ktora chcemy zapisac
    // plus trzeba podac recznie rozmiar zczytywanych przez wskaznik danych

    wyjscie.write((char*)&identyfikator, sizeof(char)*2);
    wyjscie.write((char*)&szerokoscObrazka, sizeof(Uint16));
    wyjscie.write((char*)&wysokoscObrazka, sizeof(Uint16));



    for(int y = 0; y < wysokosc / 2; y++) {
        for(int x = 0; x < szerokosc / 2; x++) {
            kolor = getPixel(x, y);
            wyjscie.write((char*)&kolor.r, sizeof(Uint8));
            wyjscie.write((char*)&kolor.g, sizeof(Uint8));
            wyjscie.write((char*)&kolor.b, sizeof(Uint8));
        }
    }

    wyjscie.close();
}

void odczytajObraz24(){
    SDL_Color kolor;

    Uint16 szerokoscObrazka = 0;
    Uint16 wysokoscObrazka = 0;
    char identyfikator[2];

    cout << "Odczytujemy plik 'obraz24.bin' uzywajac metody read()" << endl;
    ifstream wejscie("obraz24.bin", ios::binary);

    wejscie.read((char*)&identyfikator, sizeof(char)*2);
    wejscie.read((char*)&szerokoscObrazka, sizeof(Uint16));
    wejscie.read((char*)&wysokoscObrazka, sizeof(Uint16));

    cout << "id: " << identyfikator << endl;
    cout <<  "szerokosc: " << szerokoscObrazka << endl;
    cout <<  "wysokosc: " << wysokoscObrazka << endl;

    for(int y = 0; y < wysokoscObrazka; y++) {
        for(int x = 0; x < szerokoscObrazka; x++) {
            wejscie.read((char*)&kolor.r, sizeof(Uint8));
            wejscie.read((char*)&kolor.g, sizeof(Uint8));
            wejscie.read((char*)&kolor.b, sizeof(Uint8));

            setPixel(x + szerokoscObrazka, y, kolor.r, kolor.g, kolor.b);
        }
    }

}

/**
    Zapis w kolejnosci:
    identyfikator - typObrazka - szerokosc - wysokosc - wartosci kolorow kolejnych pixeli
*/
void zapiszObraz7BW(){

    SDL_Color kolor; // kolor wyciagany z pomoca getPixel
    Uint8 wartosc; // kolor po konwersji

    char identyfikator[] = "DG";
    char typObrazka = 'B'; // umawiamy sie ze typ obrazka to 2 znaki char
    Uint16 szerokoscObrazka = szerokosc/2;
    Uint16 wysokoscObrazka = wysokosc/2;

    cout << "Zapisujemy plik 'obraz7.bin' uzywajac metody write()" << endl; // metoda write pozwala zapisywac serie znakow do naszego wyjscia
    ofstream wyjscie("obraz7.bin", ios::binary); // flagujemy openmode binary zeby ... bylo git lol

    // podajemy jako argument zrzutowany na char wskaznik na zmienna ktora chcemy zapisac
    // plus trzeba podac recznie rozmiar zczytywanych przez wskaznik danych

    wyjscie.write((char*)&identyfikator, sizeof(char)*2);
    wyjscie.write((char*)&typObrazka, sizeof(char));
    wyjscie.write((char*)&szerokoscObrazka, sizeof(Uint16));
    wyjscie.write((char*)&wysokoscObrazka, sizeof(Uint16));

    for(int y = 0; y < wysokosc / 2; y++) {
        for(int x = 0; x < szerokosc / 2; x++) {
            kolor = getPixel(x, y);
            wartosc = z24RGBna7BW(kolor);

            wyjscie.write((char*)&wartosc, sizeof(Uint8)); // trzeba zmienic rozmiar na mniejszy
        }
    }

    wyjscie.close();
}

/**
    Zapis w kolejnosci:
    identyfikator - typObrazka - szerokosc - wysokosc - wartosci kolorow kolejnych pixeli
*/
void zapiszObraz7N(){

    SDL_Color kolor; // kolor wyciagany z pomoca getPixel
    Uint8 wartosc; // kolor po konwersji

    char identyfikator[] = "DG";
    char typObrazka = 'N'; // umawiamy sie ze typ obrazka to 1 znak char
    Uint16 szerokoscObrazka = szerokosc/2;
    Uint16 wysokoscObrazka = wysokosc/2;

    cout << "Zapisujemy plik 'obraz7.bin' uzywajac metody write()" << endl;
    ofstream wyjscie("obraz7.bin", ios::binary);

    // podajemy jako argument zrzutowany na char wskaznik na zmienna ktora chcemy zapisac
    // plus trzeba podac recznie rozmiar zczytywanych przez wskaznik danych

    wyjscie.write((char*)&identyfikator, sizeof(char)*2);
    wyjscie.write((char*)&typObrazka, sizeof(char));
    wyjscie.write((char*)&szerokoscObrazka, sizeof(Uint16));
    wyjscie.write((char*)&wysokoscObrazka, sizeof(Uint16));



    for(int y = 0; y < wysokosc / 2; y++) {
        for(int x = 0; x < szerokosc / 2; x++) {
            kolor = getPixel(x, y);
            wartosc = z24RGBna7RGB(kolor);
            wyjscie.write((char*)&wartosc, sizeof(Uint8)); // trzeba zmienic rozmiar na mniejszy
        }
    }

    wyjscie.close();
}

/**
    Zapis w kolejnosci:
    identyfikator - typObrazka - szerokosc - wysokosc - paleta, czyli tablica 128 kolejnych kolorow -
    - indexy odpowiadajace kolorom w palecie-tablicy
*/
void zapiszObraz7D(){
    SDL_Color kolor; // kolor wyciagany z pomoca getPixel
    Uint8 indexPalety7D; // odpowiadajacy kolorowi index w palecie

    char identyfikator[] = "DG";
    char typObrazka = 'D'; // umawiamy sie ze typ obrazka to 1 znak char
    Uint16 szerokoscObrazka = szerokosc/2;
    Uint16 wysokoscObrazka = wysokosc/2;

    cout << "Zapisujemy plik 'obraz7.bin' uzywajac metody write()" << endl;
    ofstream wyjscie("obraz7.bin", ios::binary);

    // podajemy jako argument zrzutowany na char wskaznik na zmienna ktora chcemy zapisac
    // plus trzeba podac recznie rozmiar zczytywanych przez wskaznik danych

    wyjscie.write((char*)&identyfikator, sizeof(char)*2);
    wyjscie.write((char*)&typObrazka, sizeof(char));
    wyjscie.write((char*)&szerokoscObrazka, sizeof(Uint16));
    wyjscie.write((char*)&wysokoscObrazka, sizeof(Uint16));

    // generuj palete
    generujPalete();

    // zapisz palete w pliku
    for ( int i = 0; i < 128; i++){
        wyjscie.write((char*)&paleta7D[i], sizeof(Uint8)*3);
    }

    // zapisz w pliku indexy palety odpowiadajace kolejnym pixelom
    for(int y = 0; y < wysokosc / 2; y++) {
        for(int x = 0; x < szerokosc / 2; x++) {
            kolor = getPixel(x, y);
            indexPalety7D = znajdzSasiada(kolor, paleta7D);
            wyjscie.write((char*)&indexPalety7D, sizeof(Uint8)); // trzeba zmienic rozmiar na mniejszy(7bit)
        }
    }
    wyjscie.close();
}


void odczytajObraz7N(){
    SDL_Color kolor;

    Uint16 szerokoscObrazka = 0;
    Uint16 wysokoscObrazka = 0;
    char identyfikator[2];
    char typObrazka;
    Uint8 wartosc = 0;

    cout << "Odczytujemy plik 'obraz7.bin' uzywajac metody read()" << endl;
    ifstream wejscie("obraz7.bin", ios::binary);

    wejscie.read((char*)&identyfikator, sizeof(char)*2);
    wejscie.read((char*)&typObrazka, sizeof(char)); // typ obrazka to 1 znak char
    wejscie.read((char*)&szerokoscObrazka, sizeof(Uint16));
    wejscie.read((char*)&wysokoscObrazka, sizeof(Uint16));

    cout << "id: " << identyfikator << endl;
    cout <<  "szerokosc: " << szerokoscObrazka << endl;
    cout <<  "wysokosc: " << wysokoscObrazka << endl;

    for(int y = 0; y < wysokoscObrazka; y++) {
        for(int x = 0; x < szerokoscObrazka; x++) {
            wejscie.read((char*)&wartosc, sizeof(Uint8));
            kolor = z7RGBna24RGB(wartosc);
            setPixel(x, y + wysokoscObrazka, kolor.r, kolor.g, kolor.b);
        }
    }

}

void odczytajObraz7BW(){
    SDL_Color kolor; // kolor wyciagany z pomoca getPixel
    Uint8 wartosc; // kolor po konwersji

    char identyfikator[2];
    char typObrazka; // umawiamy sie ze typ obrazka to 1 znak char
    Uint16 szerokoscObrazka = 0;
    Uint16 wysokoscObrazka = 0;


    cout << "Odczytujemy plik 'obraz7.bin' uzywajac metody read()" << endl;
    ifstream wejscie("obraz7.bin", ios::binary);

    wejscie.read((char*)&identyfikator, sizeof(char)*2);
    wejscie.read((char*)&typObrazka, sizeof(char)); // typ obrazka to 1 znak char
    wejscie.read((char*)&szerokoscObrazka, sizeof(Uint16));
    wejscie.read((char*)&wysokoscObrazka, sizeof(Uint16));

    cout << "id: " << identyfikator << endl;
    cout << "szerokosc: " << szerokoscObrazka << endl;
    cout << "wysokosc: " << wysokoscObrazka << endl;

    for(int y = 0; y < wysokoscObrazka; y++) {
        for(int x = 0; x < szerokoscObrazka; x++) {
            wejscie.read((char*)&wartosc, sizeof(Uint8));
            kolor = z7BWna24RGB(wartosc);
            setPixel(x + szerokoscObrazka, y + wysokoscObrazka, kolor.r, kolor.g, kolor.b);
        }
    }
}




/**
    Typ obrazka to 1 znak char:
    "B" - 7-bit grayscale
    "N" - 7-bit RGB natywne?
    "D" - 7-bit paleta dedykowana
*/
void odczytajObraz(){

    SDL_Color kolor;
    SDL_Color odczytanaPaleta[128];

    Uint16 szerokoscObrazka = 0;
    Uint16 wysokoscObrazka = 0;
    char identyfikator[2];
    char typObrazka; // umawiamy sie ze typ obrazka to 1 znak char
    Uint8 wartosc = 0;


    //cout<<"Odczytujemy plik 'obraz7.bin' uzywajca metody read()"<<endl;
    ifstream wejscie("obraz7.bin", ios::binary);
    wejscie.read((char*)&identyfikator, sizeof(char)*2);
    wejscie.read((char*)&typObrazka, sizeof(char)); // typ obrazka to 1 znak char
    wejscie.read((char*)&szerokoscObrazka, sizeof(Uint16));
    wejscie.read((char*)&wysokoscObrazka, sizeof(Uint16));

    if(typObrazka == 'B') { // BW
        cout << "Odczytuje typ obrazka - BW" << endl;
        for(int y = 0; y < wysokoscObrazka; y++) {
            for(int x = 0; x < szerokoscObrazka; x++) {
                wejscie.read((char*)&wartosc,sizeof(Uint8));
                kolor = z7BWna24RGB(wartosc);
                setPixel(x+szerokoscObrazka,y+wysokoscObrazka,kolor.r,kolor.g,kolor.b);
            }
        }
    } else if(typObrazka == 'N') { // Paleta natywna
        cout << "Odczytuje typ obrazka - N" << endl;
        for(int y = 0; y < wysokoscObrazka; y++) {
            for(int x = 0; x < szerokoscObrazka; x++){
                wejscie.read((char*)&wartosc,sizeof(Uint8));
                kolor = z7RGBna24RGB(wartosc);
                setPixel(x,y+wysokoscObrazka,kolor.r,kolor.g,kolor.b);
            }
        }
    } else if(typObrazka=='D') { // paleta dedykowana
        /*
            Wersja w której zapisujemy 7 bitow na 8 bitach
            strumien moze odczytywac/zapisywac wielokrotnosc bajta
            wiec chcac to zapisywac w bardziej oszczedny sposob
            trzebaby zapisywac paczkami(8 pixeli po 7 bitow na 7 bajtach)
            i odczytywac paczkami, to pewnie nie teraz
        */
        cout << "Odczytuje typ obrazka - D" << endl;

        //Odczytuje palete, zapisuje ja do lokalnej zmiennej tablicowej
        for(int i = 0; i < 128; i++){
            wejscie.read((char*)&kolor,sizeof(Uint8)*3);
            odczytanaPaleta[i] = kolor;
        }

        //rysuje obrazek na podstawie odczytanej palety wyzej palety
        for(int y = 0; y < wysokoscObrazka; y++) {
            for(int x = 0; x < szerokoscObrazka; x++){
                wejscie.read((char*)&wartosc,sizeof(Uint8)); // czyta index palety do zmiennej wartosc
                kolor = odczytanaPaleta[wartosc];
                setPixel(x + szerokoscObrazka,y,kolor.r,kolor.g,kolor.b);
            }
        }
    }
}


/*
1.  Metody zapiszObrazXbw(), zapiszObrazXn(), zapiszObrazXd()
    zapisujemy zawsze do pliku o takiej samej nazwie
    w przypadku metody zapiszObrazXd() konieczne jest wygenerowanie plaety dedykowanej
    i zapisanie palety w naglowku pliku
2.  Metoda odczytajObrazX() ktora jest w stanie wykryc jaki obrazek odczytuje (bw, n, d)
    i dekoduje dane z obrazka (i ewentualnie odczytuje paletę dedykowaną) oraz
    rysuje obrazek na ekranie.

    Pierwsze dane zapisane do pliku to: identyfikator - typObrazka - szerokoscObrazka - wysokoscObrazka
    Format obrazka(bw, n, d) zapisujemy do postaci
*/

void test1(){
    Uint8 wartoscOut, wartoscIn;
    ofstream wyjscie("test1.bin", ios::binary);
    ifstream wejscie("test1.bin", ios::binary);

    wartoscOut = 100;
    cout << "wartoscOut = " << (int)wartoscOut << endl;
    wyjscie.write((char*)&wartoscOut, sizeof(Uint8));
    wyjscie.close();

    wejscie.read((char*)&wartoscIn,sizeof(Uint8));
    cout << "wartoscIn =  " << (int)wartoscIn << endl;

}

void Funkcja8() {

    zapiszObraz7BW();
    odczytajObraz();

    zapiszObraz7N();
    odczytajObraz();

    zapiszObraz7D();
    odczytajObraz();

    SDL_UpdateWindowSurface(window);
}

void kompresjaByteRun(Uint8 wejscie[], int dlugosc) {
    int i = 0;

    // dopoki wszystkie bajty nie sa skompresowane
    while (i < dlugosc) {
        // sekwencja powtarzajacych sie minimum 2 bajtow
        if ((wejscie[i] == wejscie [i+1]) && (i < dlugosc - 1)) {
            // mierzymy dlugosc sekwencji
            int licznik = 0;
            while ( (wejscie[i+licznik] == wejscie[i+licznik+1]) &&
                    (i + licznik < dlugosc - 1) &&
                    (licznik < 127) ) {
                licznik++;
            }
            cout << -licznik << ", " << wejscie[i+licznik] << ", ";

            // przesuwamy wskaznik o dlugosc sekwencji
            i += (licznik + 1);
        }
            //sekwencja roznych bajtow
        else {
            // mierzymy dlugosc sekwencji
            int licznik = 0;
            while ( (i+licznik < dlugosc - 1) &&
                    (wejscie[i+licznik] != wejscie[i+licznik+1]) &&
                    (licznik < 127) ) {
                licznik++;
            }
            // dodajemy jeszcze koncowke
            if ( (i+licznik == dlugosc - 1) && (licznik <127) ) {
                licznik++;
            }

            // wypisujemy "skompresowana" sekwencje
            cout << (licznik - 1) << ", ";
            for (int k = 0; k<licznik; k++) {
                cout << wejscie[i+k] << ", ";
            }
            i += licznik;
        }
    }
}

void dekompresjaByteRun(Uint8 wejscie[], int dlugosc) {

    int i = 0;

    // dopoki wszystkie bajty nie zostana zdekompresowane
    while (i < dlugosc) {

        // kod pusty
        if (wejscie[i] == 128) {
            i++;
        }
            // sekwencja powtarzajacych sie bajtow
        else if (wejscie[i] < 0) {
            int licznik = -(wejscie[i]-1);
            for (int k=0; k<licznik; k++) {
                cout << wejscie[i+1] << ", ";
            }
            // przesuwamy wskaznik o dlugosci sekwencji
            i += 2;
        } else { // sekwencja roznych bajtow
            int licznik = wejscie[i] + 1;
            for (int k = 0; k < licznik; k++) {
                cout << wejscie[i+k+1] << ", ";
            }
            // przesuwamy wskaznik o dlugosci sekwencji
            i += wejscie[i]+2;
        }
    }
}

/*
1. metody zapiszSkompresowanyObrazXbw(), zapiszSkompresowanyObrazXn(), zapiszSkompresowanyObrazXd()
    zapisują obrazek pod tą samą nazwą , ale uzwględniają w nagłówku informację o tym, że dane obrazku są skompresowane
    i kompresujemy odpowiednim algorytmem tylko dane dotyczące obrazu(n-bitowe dane o piksela)
2. metoda odczytajObrazX() która jest w stanie wykryć także fakt, że dane o obrazie są skompresowane i dekoduje dane z
    obrazka odpowiednim algorytmem oraz rysuje orbazek na ekranie
*/

/**
  * Funkcja przeprowadza kompresje byteRun na wejsciowej tablicy i zapisuje wynik do tablicy wyjsciowej
  * kompresuje dane 7 bitowe
  * @param wyjscie dynamiczna tablica wyjscia, przez referencje, do ktorej bedziemy zapisywac dane po kompresji, jest typu char bo potrzebujemy wartosci ujemnych
  * @param wejscie - tablica wejsciowa danych typu Uint8, dane musza byc na 7 bitach, brak exception handling
  * @param dlugosc - rozmiar tablicy wejsciowej
  */
void kompresjaByteRun2(Uint8 wejscie[], vector<char>& wyjscie, int dlugosc) {
    int i = 0;

    // dopoki wszystkie bajty nie sa skompresowane
    while (i < dlugosc) {
        // sekwencja powtarzajacych sie minimum 2 bajtow
        if ((wejscie[i] == wejscie [i+1]) && (i < dlugosc - 1)) {
            // mierzymy dlugosc sekwencji
            char licznik = 0;
            while ( (wejscie[i+licznik] == wejscie[i+licznik+1]) &&
                    (i + licznik < dlugosc - 1) &&
                    (licznik < 127) ) {
                licznik++;
            }

            // zapisujemy do tablicy wyjsciowej
            wyjscie.push_back(-licznik);
            //if(wejscie[i+licznik]>127) cout << "out of scope!" << endl;
            wyjscie.push_back(wejscie[i+licznik]);
            // przesuwamy wskaznik o dlugosc sekwencji
            i += (licznik + 1);
        }
            //sekwencja roznych bajtow
        else {
            // mierzymy dlugosc sekwencji
            int licznik = 0;
            while ( (i+licznik < dlugosc - 1) &&
                    (wejscie[i+licznik] != wejscie[i+licznik+1]) &&
                    (licznik < 127) ) {
                licznik++;
            }
            // dodajemy jeszcze koncowke
            if ( (i+licznik == dlugosc - 1) && (licznik <127) ) {
                licznik++;
            }

            // zapisujemy do tablicy wyjsciowej sekwencje roznych bajtow
            wyjscie.push_back(licznik - 1);
            for (int k = 0; k<licznik; k++) {
                wyjscie.push_back(wejscie[i+k]);
            }

            i += licznik;
        }
    }
}

/**
  * Funkcja przeprowadza dekompresje byteRun na wejsciowej tablicy vector i zapisuje wynik do tablicy wyjsciowej vector
  * @param wejscie - dynamiczna tablica ze skompresowanymi algorytmem byteRun danymi
  * @param wyjscie - dynamiczna tablica do ktorej zapisujemy zdekompresowane dane
  */
void dekompresjaByteRun2(vector<char>& wejscie, vector<Uint8>& wyjscie) {

    int i = 0;
    int dlugosc = wejscie.size();
    // dopoki wszystkie bajty nie zostana zdekompresowane
    while (i < dlugosc) {

        // kod pusty
        if (wejscie[i] == 128) {
            i++;
        }
            // sekwencja powtarzajacych sie bajtow
        else if (wejscie[i] < 0) {
            Uint8 licznik = -(wejscie[i]-1);
            for (int k=0; k<licznik; k++) {
                wyjscie.push_back(wejscie[i+1]);
            }
            // przesuwamy wskaznik o dlugosci sekwencji
            i += 2;
        } else { // sekwencja roznych bajtow
            int licznik = wejscie[i] + 1;
            for (int k = 0; k < licznik; k++) {
                wyjscie.push_back(wejscie[i+k+1]);
            }
            // przesuwamy wskaznik o dlugosci sekwencji
            i += wejscie[i]+2;
        }
    }
}

/**
  * Zapis w kolejnosci(w nawiasie typy danych które rzutuja ile bajtow dana informacja ma zajac):
  * identyfikator(char) - typObrazka(char) - szerokosc(Uint16) - wysokosc(Uint16) -
  * - rozmiar skompresowanej tablicy indexow(int) -
  * - SKOMPRESOWANE PRZEZ BYTERUN kolorki bw(char)
  */
void zapiszSkompresowanyObraz7bw(){

    Uint8* picture7bitArr;  // tablica z zapisanymi kolorami 7bit, ktora bedziemy kompresowac
    vector<char> skompresowaneDane; // wskaźnik na 1 el. tablicy ze skompresowanymi danymi

    char identyfikator[] = "DG";
    char typObrazka = 'b'; // umawiamy sie ze typ obrazka to 1 znak char
    Uint16 szerokoscObrazka = szerokosc/2;
    Uint16 wysokoscObrazka = wysokosc/2;

    picture7bitArr = new Uint8[szerokosc/2*wysokosc/2];

    cout << "Zapisujemy plik 'obraz7.bin' uzywajac metody write()" << endl; // metoda write pozwala zapisywac serie znakow do naszego wyjscia
    ofstream wyjscie("obraz7.bin", ios::binary); // flagujemy openmode binary zeby ... bylo git lol

    // podajemy jako argument zrzutowany na char wskaznik na zmienna ktora chcemy zapisac
    // plus trzeba podac recznie rozmiar zczytywanych przez wskaznik danych

    wyjscie.write((char*)&identyfikator, sizeof(char)*2);
    wyjscie.write((char*)&typObrazka, sizeof(char));
    wyjscie.write((char*)&szerokoscObrazka, sizeof(Uint16));
    wyjscie.write((char*)&wysokoscObrazka, sizeof(Uint16));

    // przechwytujemy obraz pixel po pixelu, konwertujemy do 7 bit i zapisujemy w tablicy
    for(int y = 0; y < wysokosc / 2; y++) {
        for(int x = 0; x < szerokosc / 2; x++) {
            picture7bitArr[x+y*szerokoscObrazka] = z24RGBna7BW(getPixel(x, y));
        }
    }

    // kompresujemy byteRunem
    kompresjaByteRun2(picture7bitArr, skompresowaneDane, szerokoscObrazka*wysokoscObrazka);

    int rozmiar = skompresowaneDane.size();
    // zapisujemy w pliku rozmiar skompresowanych danych
    cout << "rozmiar skompresowanych danych = " << rozmiar << endl;
    wyjscie << rozmiar;

    // zapisujemy skompresowane dane w pliku
    for(int i = 0; i < skompresowaneDane.size() ; i++) {
        wyjscie << skompresowaneDane[i];
        //wyjscie.write((char*)&skompresowaneDane[i], sizeof(char)); // to!!!
    }

    wyjscie.close();
}

/**
  * Zapis w kolejnosci(w nawiasie typy danych które rzutuja ile bajtow dana informacja ma zajac):
  * identyfikator(char) - typObrazka(char) - szerokosc(Uint16) - wysokosc(Uint16) -
  * - rozmiar skompresowanej tablicy indexow(int) -
  * - SKOMPRESOWANE PRZEZ BYTERUN kolorki narzucone(char)
  */
void zapiszSkompresowanyObraz7n(){
    Uint8 picture7bitArr[szerokosc/2*wysokosc/2];  // tablica z zapisanymi kolorami 7bit, ktora bedziemy kompresowac
    vector<char> skompresowaneDane; // wskaźnik na 1 el. tablicy ze skompresowanymi danymi

    char identyfikator[] = "DG";
    char typObrazka = 'n'; // umawiamy sie ze typ obrazka to 1 znak char
    Uint16 szerokoscObrazka = szerokosc/2;
    Uint16 wysokoscObrazka = wysokosc/2;

    cout << "Zapisujemy plik 'obraz7.bin' uzywajac metody write()" << endl; // metoda write pozwala zapisywac serie znakow do naszego wyjscia
    ofstream wyjscie("obraz7.bin", ios::binary); // flagujemy openmode binary zeby ... bylo git lol

    // podajemy jako argument zrzutowany na char wskaznik na zmienna ktora chcemy zapisac
    // plus trzeba podac recznie rozmiar zczytywanych przez wskaznik danych

    wyjscie.write((char*)&identyfikator, sizeof(char)*2);
    wyjscie.write((char*)&typObrazka, sizeof(char));
    wyjscie.write((char*)&szerokoscObrazka, sizeof(Uint16));
    wyjscie.write((char*)&wysokoscObrazka, sizeof(Uint16));

    // przechwytujemy obraz pixel po pixelu, konwertujemy do 7 bit i zapisujemy w tablicy
    for(int y = 0; y < wysokosc / 2; y++) {
        for(int x = 0; x < szerokosc / 2; x++) {
            picture7bitArr[x+y*szerokoscObrazka] = z24RGBna7RGB(getPixel(x, y));
        }
    }

    // kompresujemy byteRunem
    kompresjaByteRun2(picture7bitArr, skompresowaneDane, szerokoscObrazka*wysokoscObrazka);

    int rozmiar = skompresowaneDane.size();
    // zapisujemy w pliku rozmiar skompresowanych danych
    cout << "rozmiar skompresowanych danych = " << rozmiar << endl;
    wyjscie << rozmiar;

    // zapisujemy skompresowane dane w pliku
    for(int i = 0; i < skompresowaneDane.size() ; i++) {
        wyjscie << skompresowaneDane[i];
    }

    wyjscie.close();
}

/**
  * Zapis w kolejnosci(w nawiasie typy danych które rzutuja ile bajtow dana informacja ma zajac):
  * identyfikator(char) - typObrazka(char) - szerokosc(Uint16) - wysokosc(Uint16) -
  * - paleta, czyli tablica 128 kolejnych kolorow SDL_Color 128x[(Uint8)*3] -
  * - rozmiar skompresowanej tablicy indexow(int) -
  * - SKOMPRESOWANE PRZEZ BYTERUN indexy odpowiadajace kolorom w palecie-tablicy(char)
  */
void zapiszSkompresowanyObraz7d(){

    Uint8 picture7bitArr[szerokosc/2*wysokosc/2];  // tablica z zapisanymi kolorami 7bit, ktora bedziemy kompresowac
    vector<char> skompresowaneDane; // wskaźnik na 1 el. tablicy ze skompresowanymi danymi

    SDL_Color kolor; // kolor wyciagany z pomoca getPixel
    Uint8 indexPalety7D; // odpowiadajacy kolorowi index w palecie

    char identyfikator[] = "DG";
    char typObrazka = 'd'; // umawiamy sie ze typ obrazka to 1 znak char
    Uint16 szerokoscObrazka = szerokosc/2;
    Uint16 wysokoscObrazka = wysokosc/2;

    cout << "Zapisujemy plik 'obraz7.bin' uzywajac metody write()" << endl;
    ofstream wyjscie("obraz7.bin", ios::binary);

    // podajemy jako argument zrzutowany na char wskaznik na zmienna ktora chcemy zapisac
    // plus trzeba podac recznie rozmiar zczytywanych przez wskaznik danych

    wyjscie.write((char*)&identyfikator, sizeof(char)*2);
    wyjscie.write((char*)&typObrazka, sizeof(char));
    wyjscie.write((char*)&szerokoscObrazka, sizeof(Uint16));
    wyjscie.write((char*)&wysokoscObrazka, sizeof(Uint16));

    // generuj palete
    generujPalete();

    // zapisz palete w pliku(palety nie kompresujemy)
    for ( int i = 0; i < 128; i++){
        wyjscie.write((char*)&paleta7D[i], sizeof(Uint8)*3);
    }

    // zapisz w tablicy indexy palety odpowiadajace kolejnym pixelom - do późniejszej kompresji
    for(int y = 0; y < wysokosc / 2; y++) {
        for(int x = 0; x < szerokosc / 2; x++) {
            kolor = getPixel(x, y);
            indexPalety7D = znajdzSasiada(kolor, paleta7D);
            //wyjscie.write((char*)&indexPalety7D, sizeof(Uint8));
            picture7bitArr[x+y*szerokoscObrazka] =  indexPalety7D;
        }
    }

    // kompresja 2d tablicy indexow byteRunem
    kompresjaByteRun2(picture7bitArr, skompresowaneDane, szerokoscObrazka*wysokoscObrazka);

    // zapisujemy w pliku rozmiar skompresowanych danych
    int rozmiar = skompresowaneDane.size();
    cout << "rozmiar skompresowanych danych = " << rozmiar << endl;
    wyjscie << rozmiar;

    // zapisanie skompresowanej tablicy dedykowanej do pliku
    for(int i = 0; i < skompresowaneDane.size() ; i++) {
        wyjscie << skompresowaneDane[i];
    }

    wyjscie.close();
}

/**
  * Funkcja na zajecia 22.12.2022
  * Odczytuje obrazek z pliku "obraz7.bin" wg reguł, ta wersja odczytuje 6 rodzajow obrazkow z pliku:
  * BW, N, D oraz ich skompresowanych wersji
  * Typ obrazka to 1 znak char, 6 opcji:
  * "B" - 7-bit grayscale
  * "N" - 7-bit RGB natywne?
  * "D" - 7-bit paleta dedykowana
  * "b" - 7-bit grayscale skompresowane byteRunem
  * "n" - 7-bit RGB natywne? skompresowane byteRunem
  * "d" - 7-bit paleta dedykowana skompresowane byteRunem
  */
void odczytajObraz7(){

    SDL_Color kolor;
    SDL_Color odczytanaPaleta[128];

    Uint16 szerokoscObrazka = 0;
    Uint16 wysokoscObrazka = 0;
    char identyfikator[2];
    char typObrazka; // umawiamy sie ze typ obrazka to 1 znak char
    Uint8 wartosc = 0;


    //cout<<"Odczytujemy plik 'obraz7.bin' uzywajca metody read()"<<endl;
    ifstream wejscie("obraz7.bin", ios::binary);

    // Czytamy identyfikator(char) - typObrazka(char) - szerokosc(Uint16) - wysokosc(Uint16)
    wejscie.read((char*)&identyfikator, sizeof(char)*2);
    wejscie.read((char*)&typObrazka, sizeof(char)); // typ obrazka to 1 znak char
    wejscie.read((char*)&szerokoscObrazka, sizeof(Uint16));
    wejscie.read((char*)&wysokoscObrazka, sizeof(Uint16));

    // 6 przypadkow dla 6 typow obrazkow w klauzulach warunkowych if - else if
    if(typObrazka == 'B') { // BW
        cout << "Odczytuje typ obrazka - BW" << endl;
        for(int y = 0; y < wysokoscObrazka; y++) {
            for(int x = 0; x < szerokoscObrazka; x++) {
                wejscie.read((char*)&wartosc,sizeof(Uint8));
                kolor = z7BWna24RGB(wartosc);
                setPixel(x+szerokoscObrazka,y+wysokoscObrazka,kolor.r,kolor.g,kolor.b);
            }
        }
    } else if(typObrazka == 'N') { // Paleta narzucona
        cout << "Odczytuje typ obrazka - N" << endl;
        for(int y = 0; y < wysokoscObrazka; y++) {
            for(int x = 0; x < szerokoscObrazka; x++){
                wejscie.read((char*)&wartosc,sizeof(Uint8));
                kolor = z7RGBna24RGB(wartosc);
                setPixel(x,y+wysokoscObrazka,kolor.r,kolor.g,kolor.b);
            }
        }
    } else if(typObrazka=='D') { // paleta dedykowana

        cout << "Odczytuje typ obrazka - D" << endl;

        //Odczytuje palete, zapisuje ja do lokalnej zmiennej tablicowej
        for(int i = 0; i < 128; i++){
            wejscie.read((char*)&kolor,sizeof(Uint8)*3);
            odczytanaPaleta[i] = kolor;
        }

        //rysuje obrazek na podstawie odczytanej palety wyzej palety
        for(int y = 0; y < wysokoscObrazka; y++) {
            for(int x = 0; x < szerokoscObrazka; x++){
                wejscie.read((char*)&wartosc,sizeof(Uint8)); // czyta index palety do zmiennej wartosc
                kolor = odczytanaPaleta[wartosc];
                setPixel(x + szerokoscObrazka,y,kolor.r,kolor.g,kolor.b);
            }
        }
    } else if(typObrazka=='b') {// bw skompresowane
        cout << "Odczytuje typ obrazka - BW skompresowane" << endl;
        vector<char> zippedData;
        vector<Uint8> unzippedData;
        char odczyt;
        int sizeOfZippedData;
        wejscie >> sizeOfZippedData;
        cout << "sizeOfZippedData = " << sizeOfZippedData << endl;

        //odczytuje skompresowane dane
        for(int i = 0; i < sizeOfZippedData ; i++) {
            // trzeba odczytwac dane z pliku zawsze z wykorzystaniem metody read() bo >> chyba czasem sczytuje wiecej niz 1 bajt
            // wejscie >> odczyt; // to gubiło/zjadało nam bajty przy odczycie
            // i robiło artefakty, ze po dekompresji bylo mniej pixeli zapisanych niż sie znajduje na obrazku
            wejscie.read((char*)&odczyt,sizeof(char));
            zippedData.push_back(odczyt);
        }

        // dekompresja
        dekompresjaByteRun2(zippedData, unzippedData);
        //cout << "unzippedData.size() = " << unzippedData.size() << endl;

        // rysowanie ze zdekompresowanych danych
        for(int y = 0; y < wysokoscObrazka; y++) {
            for(int x = 0; x < szerokoscObrazka; x++) {
                wartosc = unzippedData[x+y*szerokoscObrazka];
                kolor = z7BWna24RGB(wartosc);
                setPixel(x+szerokoscObrazka,y+wysokoscObrazka,kolor.r,kolor.g,kolor.b);
            }
        }

    } else if(typObrazka=='n') {// paleta narzucona skompresowane
        cout << "Odczytuje typ obrazka - N skompresowane" << endl;
        vector<char> zippedData;
        vector<Uint8> unzippedData;
        char odczyt;
        int sizeOfZippedData;
        wejscie >> sizeOfZippedData;
        cout << "sizeOfZippedData = " << sizeOfZippedData << endl;

        //odczytuje skompresowane dane
        for(int i = 0; i < sizeOfZippedData ; i++) {
            // wejscie >> odczyt; // to sczytuje czasem za duzo
            wejscie.read((char*)&odczyt,sizeof(char));
            zippedData.push_back(odczyt);
        }

        // dekompresja
        dekompresjaByteRun2(zippedData, unzippedData);

        cout << "unzippedData.size() = " << unzippedData.size() << endl;

        // rysowanie ze zdekompresowanych danych
        for(int y = 0; y < wysokoscObrazka; y++) {
            for(int x = 0; x < szerokoscObrazka; x++) {
                wartosc = unzippedData[x+y*szerokoscObrazka];
                kolor = z7RGBna24RGB(wartosc);
                setPixel(x,y+wysokoscObrazka,kolor.r,kolor.g,kolor.b);
            }
        }

    } else if(typObrazka=='d') {// paleta dedykowana skompresowane
        /**
          * Zapisuje do obrazka kolejno:
          * - palete dedykowana(po staremu),
          * - rozmiar skompresowanej tablicy opisujacej kolory kazdego pixela
          * - skompresowana tablica przypisujaca kazdemu pixelowi index koloru z palety
          * Kompresujemy jedynie indexy, nie kompresujemy palety, bo to bez sensu
          *
          */
        cout << "Odczytuje typ obrazka - D skomrpesowane" << endl;
        vector<char> zippedData;
        vector<Uint8> unzippedData;
        char odczyt;
        int sizeOfZippedData;

        //Odczytuje palete, zapisuje ja do lokalnej zmiennej tablicowej
        for(int i = 0; i < 128; i++){
            wejscie.read((char*)&kolor,sizeof(Uint8)*3);
            odczytanaPaleta[i] = kolor;
        }

        // Odczytujemy rozmiar zapisanych danych
        wejscie >> sizeOfZippedData; // sczytujemy inta, ktory jest 4-bajtowy, warto miec to na uwadze
        //cout << "sizeOfZippedData = " << sizeOfZippedData << endl;

        // odczytuje skompresowane dane
        for(int i = 0; i < sizeOfZippedData ; i++) {
            // wejscie >> odczyt; // to sczytuje czasem za duzo
            wejscie.read((char*)&odczyt,sizeof(char));
            zippedData.push_back(odczyt);
        }

        // dekompresja
        dekompresjaByteRun2(zippedData, unzippedData);

        //rysuje obrazek na podstawie odczytanej palety wyzej palety
        for(int y = 0; y < wysokoscObrazka; y++) {
            for(int x = 0; x < szerokoscObrazka; x++){
                wartosc = unzippedData[x+y*szerokoscObrazka]; // wyciagam index z palety do zmiennej wartosc dla kolejnych pikseli
                kolor = odczytanaPaleta[wartosc]; // do zmiennej kolor przypisuje kolor odpowiadajacy indeksowi
                setPixel(x + szerokoscObrazka,y,kolor.r,kolor.g,kolor.b); // rysuje piksel
            }
        }
    }
}

void Funkcja9() {

    /*
    vector<char> skompresowane;
    vector<Uint8> poDekompresji;
    //int dlugosc = 28;

    Uint8 nieskompresowane[200];
    for(int i = 0; i < 200 ; i++) nieskompresowane[i] = i;
    int dlugosc = 200;

    cout << "wejscie: " << endl;
    for(int c = 0; c < dlugosc; c++) {
        cout << (int)nieskompresowane[c] << ", ";
    }
    cout << endl;

    kompresjaByteRun2(nieskompresowane, skompresowane, dlugosc);

    cout << "skompresowane : " << endl;
    for(int c = 0; c < skompresowane.size(); c++) {
        cout << (int)skompresowane[c] << ", ";
    }

    cout << endl << "skompresowane.size() = " << skompresowane.size() << endl;

    cout << endl << "skompresowane wejscie: " << endl;
    for (int c=0; c<skompresowane.size(); c++) {
        cout << (int)skompresowane[c] << ", ";
    }
    cout << endl;

    dekompresjaByteRun2(skompresowane, poDekompresji);
    cout << "zdekompresowane wyjscie: " << endl;
    for (int c=0; c<poDekompresji.size(); c++) {
        cout << (int)poDekompresji[c] << ", ";
    }

    if(dlugosc!=poDekompresji.size()) cout << "niezgodnosc rozmiaru przed i po kompresji" << endl;
    for(int i = 0; i<dlugosc; i++){
        if(poDekompresji[i] != nieskompresowane[i]) cout << "niezgodnosc przed i po kompresji" << endl;
    } */


    zapiszSkompresowanyObraz7bw();
    odczytajObraz7();
    zapiszSkompresowanyObraz7n();
    odczytajObraz7();
    zapiszSkompresowanyObraz7d(); // dla jednego obrazka menu glownego SMB3 roznica jest 11kB vs 43kB
    odczytajObraz7();


    SDL_UpdateWindowSurface(window);
}

// Na ostatnie zajecia kody - zapisywanie ośmiu 7-bit wartosci na 7 bajtach(wykorzystywanie calych bajtow)
// W sumie to się prosi, zeby robic na tablicach a nie na strukturach tbh ...


// upychanie
kolor8x7bitNa7bajtach upchaj8x7bitNa7bajtach(kolor8x7bitNa8bajtach doUpchania) {
    kolor8x7bitNa7bajtach upchane; // do tego upychamy

    upchane.bajt1full = (doUpchania.bajt1 << 1) + ((doUpchania.bajt2&(0b01000000)) >> 6);
    upchane.bajt2full = (doUpchania.bajt2 << 2) + ((doUpchania.bajt3&(0b01100000)) >> 5);
    upchane.bajt3full = (doUpchania.bajt3 << 3) + ((doUpchania.bajt4&(0b01110000)) >> 4);
    upchane.bajt4full = (doUpchania.bajt4 << 4) + ((doUpchania.bajt5&(0b01111000)) >> 3);
    upchane.bajt5full = (doUpchania.bajt5 << 5) + ((doUpchania.bajt6&(0b01111100)) >> 2);
    upchane.bajt6full = (doUpchania.bajt6 << 6) + ((doUpchania.bajt7&(0b01111110)) >> 1);
    upchane.bajt7full = (doUpchania.bajt7 << 7) + ((doUpchania.bajt8&(0b01111111)) >> 0);
    // nic nie przesuwamy w ostatnim, zapis tak dla jasnosci
    return upchane;
}

// rozpakowywanie
kolor8x7bitNa8bajtach wypakujDo8x7bitNa8bajtach(kolor8x7bitNa7bajtach doRozpakowania) {
    kolor8x7bitNa8bajtach rozpakowane;
    rozpakowane.bajt1 = ((doRozpakowania.bajt1full >> 1));
    rozpakowane.bajt2 = ((doRozpakowania.bajt1full&(0b00000001)) << 6) + (doRozpakowania.bajt2full >> 2);
    rozpakowane.bajt3 = ((doRozpakowania.bajt2full&(0b00000011)) << 5) + (doRozpakowania.bajt3full >> 3);
    rozpakowane.bajt4 = ((doRozpakowania.bajt3full&(0b00000111)) << 4) + (doRozpakowania.bajt4full >> 4);
    rozpakowane.bajt5 = ((doRozpakowania.bajt4full&(0b00001111)) << 3) + (doRozpakowania.bajt5full >> 5);
    rozpakowane.bajt6 = ((doRozpakowania.bajt5full&(0b00011111)) << 2) + (doRozpakowania.bajt6full >> 6);
    rozpakowane.bajt7 = ((doRozpakowania.bajt6full&(0b00111111)) << 1) + (doRozpakowania.bajt7full >> 7);
    rozpakowane.bajt8 = ((doRozpakowania.bajt7full&(0b01111111)));

    return rozpakowane;
}


void Funkcja0() {

    //kolor8x7bitNa8bajtach nieupchane {120, 121, 122, 123, 124, 125, 126, 127};
    //kolor8x7bitNa8bajtach nieupchane {1, 13, 17, 39, 63, 71, 83, 12};
    kolor8x7bitNa8bajtach nieupchane {1, 127, 10, 117, 20, 107, 30, 97};
    //kolor8x7bitNa8bajtach nieupchane {127, 127, 127, 127, 127, 127, 127, 127};

    nieupchane.print();

    kolor8x7bitNa7bajtach upchane = upchaj8x7bitNa7bajtach(nieupchane);
    upchane.print();

    kolor8x7bitNa8bajtach rozpakowane = wypakujDo8x7bitNa8bajtach(upchane);
    rozpakowane.print();

    SDL_UpdateWindowSurface(window);
}



// Inne rzeczy starsze

Uint8 z24RGBna7RGB(SDL_Color kolor) {
    int R, G, B;
    int nowyR, nowyG, nowyB;

    R = kolor.r;
    G = kolor.g;
    B = kolor.b;

    nowyR = round(R * 3.0 / 255.0);
    nowyG = round(G * 7.0 / 255.0);
    nowyB = round(B * 3.0 / 255.0);

    return (nowyR << 5) + (nowyG << 2) + (nowyB);
}

SDL_Color z7RGBna24RGB(Uint8 kolor7bit) {
    int tmpR, tmpG, tmpB;
    SDL_Color kolor;

    tmpR = (kolor7bit & (0b01100000)) >> 5;
    tmpG = (kolor7bit & (0b00011100)) >> 2;
    tmpB = kolor7bit & (0b00000011);

    kolor.r = tmpR * 255.0 / 3.0;
    kolor.g = tmpG * 255.0 / 7.0;
    kolor.b = tmpB * 255.0 / 3.0;

    return kolor;
    //return {.r, .g, .b};
}

Uint8 z24RGBna7BW(SDL_Color kolor) {
    int R, G, B;
    Uint8 BW;

    R = kolor.r;
    G = kolor.g;
    B = kolor.b;

    BW = 0.299 * R + 0.587 * G + 0.114 * B;

    return (BW >> 1);
}

SDL_Color z7BWna24RGB(Uint8 BW7bit) {
    SDL_Color BW;

    BW.r = BW.g = BW.b = (BW7bit << 1);

    return BW;
    //return {.r, .g, .b};
}

void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
    if ((x>=0) && (x<szerokosc) && (y>=0) && (y<wysokosc))
    {
        /* Zamieniamy poszczególne składowe koloru na format koloru piksela */
        Uint32 pixel = SDL_MapRGB(screen->format, R, G, B);

        /* Pobieramy informację ile bajtów zajmuje jeden piksel */
        int bpp = screen->format->BytesPerPixel;

        /* Obliczamy adres piksela */
        Uint8 *p1 = (Uint8 *)screen->pixels + (y*2) * screen->pitch + (x*2) * bpp;
        Uint8 *p2 = (Uint8 *)screen->pixels + (y*2+1) * screen->pitch + (x*2) * bpp;
        Uint8 *p3 = (Uint8 *)screen->pixels + (y*2) * screen->pitch + (x*2+1) * bpp;
        Uint8 *p4 = (Uint8 *)screen->pixels + (y*2+1) * screen->pitch + (x*2+1) * bpp;

        /* Ustawiamy wartość piksela, w zależnoœci od formatu powierzchni*/
        switch(bpp)
        {
            case 1: //8-bit
                *p1 = pixel;
                *p2 = pixel;
                *p3 = pixel;
                *p4 = pixel;
                break;

            case 2: //16-bit
                *(Uint16 *)p1 = pixel;
                *(Uint16 *)p2 = pixel;
                *(Uint16 *)p3 = pixel;
                *(Uint16 *)p4 = pixel;
                break;

            case 3: //24-bit
                if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                    p1[0] = (pixel >> 16) & 0xff;
                    p1[1] = (pixel >> 8) & 0xff;
                    p1[2] = pixel & 0xff;
                    p2[0] = (pixel >> 16) & 0xff;
                    p2[1] = (pixel >> 8) & 0xff;
                    p2[2] = pixel & 0xff;
                    p3[0] = (pixel >> 16) & 0xff;
                    p3[1] = (pixel >> 8) & 0xff;
                    p3[2] = pixel & 0xff;
                    p4[0] = (pixel >> 16) & 0xff;
                    p4[1] = (pixel >> 8) & 0xff;
                    p4[2] = pixel & 0xff;
                } else {
                    p1[0] = pixel & 0xff;
                    p1[1] = (pixel >> 8) & 0xff;
                    p1[2] = (pixel >> 16) & 0xff;
                    p2[0] = pixel & 0xff;
                    p2[1] = (pixel >> 8) & 0xff;
                    p2[2] = (pixel >> 16) & 0xff;
                    p3[0] = pixel & 0xff;
                    p3[1] = (pixel >> 8) & 0xff;
                    p3[2] = (pixel >> 16) & 0xff;
                    p4[0] = pixel & 0xff;
                    p4[1] = (pixel >> 8) & 0xff;
                    p4[2] = (pixel >> 16) & 0xff;
                }
                break;

            case 4: //32-bit
                *(Uint32 *)p1 = pixel;
                *(Uint32 *)p2 = pixel;
                *(Uint32 *)p3 = pixel;
                *(Uint32 *)p4 = pixel;
                break;

        }
    }
}

void setPixelSurface(int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
    if ((x>=0) && (x<szerokosc*2) && (y>=0) && (y<wysokosc*2))
    {
        /* Zamieniamy poszczególne składowe koloru na format koloru piksela */
        Uint32 pixel = SDL_MapRGB(screen->format, R, G, B);

        /* Pobieramy informację ile bajtów zajmuje jeden piksel */
        int bpp = screen->format->BytesPerPixel;

        /* Obliczamy adres piksela */
        Uint8 *p = (Uint8 *)screen->pixels + y * screen->pitch + x * bpp;

        /* Ustawiamy wartość piksela, w zależności od formatu powierzchni*/
        switch(bpp)
        {
            case 1: //8-bit
                *p = pixel;
                break;

            case 2: //16-bit
                *(Uint16 *)p = pixel;
                break;

            case 3: //24-bit
                if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                    p[0] = (pixel >> 16) & 0xff;
                    p[1] = (pixel >> 8) & 0xff;
                    p[2] = pixel & 0xff;
                } else {
                    p[0] = pixel & 0xff;
                    p[1] = (pixel >> 8) & 0xff;
                    p[2] = (pixel >> 16) & 0xff;
                }
                break;

            case 4: //32-bit
                *(Uint32 *)p = pixel;
                break;
        }
    }
}

SDL_Color getPixel(int x, int y) {
    SDL_Color color ;
    Uint32 col = 0 ;
    if ((x>=0) && (x<szerokosc) && (y>=0) && (y<wysokosc)) {
        //określamy pozycję
        char* pPosition=(char*)screen->pixels ;

        //przesunięcie względem y
        pPosition+=(screen->pitch*y*2) ;

        //przesunięcie względem x
        pPosition+=(screen->format->BytesPerPixel*x*2);

        //kopiujemy dane piksela
        memcpy(&col, pPosition, screen->format->BytesPerPixel);

        //konwertujemy kolor
        SDL_GetRGB(col, screen->format, &color.r, &color.g, &color.b);
    }
    return ( color ) ;
}

SDL_Color getPixelSurface(int x, int y, SDL_Surface *surface) {
    SDL_Color color ;
    Uint32 col = 0 ;
    if ((x>=0) && (x<szerokosc) && (y>=0) && (y<wysokosc)) {
        //określamy pozycję
        char* pPosition=(char*)surface->pixels ;

        //przesunięcie względem y
        pPosition+=(surface->pitch*y) ;

        //przesunięcie względem x
        pPosition+=(surface->format->BytesPerPixel*x);

        //kopiujemy dane piksela
        memcpy(&col, pPosition, surface->format->BytesPerPixel);

        //konwertujemy kolor
        SDL_GetRGB(col, surface->format, &color.r, &color.g, &color.b);
    }
    return ( color ) ;
}


void ladujBMP(char const* nazwa, int x, int y)
{
    SDL_Surface* bmp = SDL_LoadBMP(nazwa);
    if (!bmp)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
    }
    else
    {
        SDL_Color kolor;
        for (int yy=0; yy<bmp->h; yy++) {
            for (int xx=0; xx<bmp->w; xx++) {
                kolor = getPixelSurface(xx, yy, bmp);
                setPixel(xx, yy, kolor.r, kolor.g, kolor.b);
            }
        }
        SDL_FreeSurface(bmp);
        SDL_UpdateWindowSurface(window);
    }

}


void czyscEkran(Uint8 R, Uint8 G, Uint8 B)
{
    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, R, G, B));
    SDL_UpdateWindowSurface(window);
}



int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    window = SDL_CreateWindow(tytul, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szerokosc*2, wysokosc*2, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    screen = SDL_GetWindowSurface(window);
    if (screen == NULL) {
        fprintf(stderr, "SDL_GetWindowSurface Error: %s\n", SDL_GetError());
        return false;
    }
    SDL_UpdateWindowSurface(window);


    bool done = false;
    SDL_Event event;
    // główna pętla programu
    while (SDL_WaitEvent(&event)) {
        // sprawdzamy czy pojawiło się zdarzenie
        switch (event.type) {
            case SDL_QUIT:
                done = true;
                break;

                // sprawdzamy czy został wciśnięty klawisz
            case SDL_KEYDOWN: {
                // wychodzimy, gdy wciśnięto ESC
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    done = true;
                if (event.key.keysym.sym == SDLK_1)
                    Funkcja1();
                if (event.key.keysym.sym == SDLK_2)
                    Funkcja2();
                if (event.key.keysym.sym == SDLK_3)
                    Funkcja3();
                if (event.key.keysym.sym == SDLK_4)
                    Funkcja4();
                if (event.key.keysym.sym == SDLK_5)
                    Funkcja5();
                if (event.key.keysym.sym == SDLK_6)
                    Funkcja6();
                if (event.key.keysym.sym == SDLK_7)
                    Funkcja7();
                if (event.key.keysym.sym == SDLK_8)
                    Funkcja8();
                if (event.key.keysym.sym == SDLK_9)
                    Funkcja9();
                if (event.key.keysym.sym == SDLK_0) // dopisane
                    Funkcja0(); // dopisane
                if (event.key.keysym.sym == SDLK_a)
                    ladujBMP("obrazek1.bmp", 0, 0);
                if (event.key.keysym.sym == SDLK_s)
                    ladujBMP("obrazek2.bmp", 0, 0);
                if (event.key.keysym.sym == SDLK_d)
                    ladujBMP("obrazek3.bmp", 0, 0);
                if (event.key.keysym.sym == SDLK_f)
                    ladujBMP("obrazek4.bmp", 0, 0);
                if (event.key.keysym.sym == SDLK_g)
                    ladujBMP("obrazek5.bmp", 0, 0);
                if (event.key.keysym.sym == SDLK_h)
                    ladujBMP("obrazek6.bmp", 0, 0);
                if (event.key.keysym.sym == SDLK_j)
                    ladujBMP("obrazek7.bmp", 0, 0);
                if (event.key.keysym.sym == SDLK_b)
                    czyscEkran(0, 0, 10);
                else
                    break;
            }
        }
        if (done) break;
    }

    if (screen) {
        SDL_FreeSurface(screen);
    }

    if (window) {
        SDL_DestroyWindow(window);
    }


    SDL_Quit();
    return 0;
}
