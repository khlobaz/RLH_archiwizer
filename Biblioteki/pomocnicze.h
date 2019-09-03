#ifndef POMOCNICZE_H
#define POMOCNICZE_H
void wczytaj_blok_danych (vector <unsigned char> &blok_wejscie,ifstream &wejscie,int rozmiar);
void zapisz_blok_danych (vector <unsigned char> &blok_wyjscie,ofstream &wyjscie);

unsigned int zamien_char_na_int(unsigned char znak1,unsigned char znak2,unsigned char znak3,unsigned char znak4);
void zamien_int_na_char(unsigned int liczba,unsigned char &znak1,unsigned char &znak2,unsigned char &znak3,unsigned char &znak4);
unsigned int zamien_char_na_short_int(unsigned char znak1,unsigned char znak2);
void zamien_short_int_na_char(unsigned int liczba,unsigned char &znak1,unsigned char &znak2);

void zamien_char_na_bity(unsigned char znak,bool *tab);
unsigned char zamien_bity_na_char(bool *tab);

#include "pomocnicze.cpp"
#endif
