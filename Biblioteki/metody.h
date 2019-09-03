#ifndef METODY_H
#define METODY_H
///////////////////////////////////RLE///////////////////////////////////////////////////////
void zapisz_zgodne(unsigned char dane,unsigned int ilosc,vector <unsigned char> &blok_wyjscie);
void zapisz_niezgodne(vector <unsigned char> &dane, vector <unsigned char> &blok_wyjscie);
void kompresja_rle(vector <unsigned char> &blok_wejscie, vector <unsigned char> &blok_wyjscie);
void dekompresja_rle(vector <unsigned char> &blok_wejscie, vector <unsigned char> &blok_wyjscie);

///////////////////////////////////LZ78///////////////////////////////////////////////////////
const unsigned int LZ78_ilosc_dopuszczalnych_fraz=65536;

struct wezel
{
unsigned short int wezel_indeks;
wezel *dzieci[256];
wezel();
};

unsigned int LZ78_kom_indeks=0;
wezel *LZ78_null;
wezel *LZ78_indeksowanie_wezlow[LZ78_ilosc_dopuszczalnych_fraz];

wezel::wezel()
{
wezel_indeks=LZ78_kom_indeks;
LZ78_indeksowanie_wezlow[wezel_indeks]=this;
LZ78_kom_indeks++;
for (unsigned int i=0;i<256;i++)
        {
        dzieci[i]=NULL;
        }
}

struct slowo
{
vector <unsigned char> wyraz;
slowo(unsigned char znak,unsigned int indeks_w_slowniku);
slowo();
};

unsigned int LZ78_dekom_indeks=0;
slowo *slownik[LZ78_ilosc_dopuszczalnych_fraz];

slowo::slowo(unsigned char znak,unsigned int indeks_w_slowniku)
{
wyraz=slownik[indeks_w_slowniku]->wyraz;
wyraz.push_back(znak);
LZ78_dekom_indeks=LZ78_dekom_indeks+1;
}
slowo::slowo()
{
LZ78_dekom_indeks++;
}

void kompresja_LZ78(vector <unsigned char> &blok_wejscie, vector <unsigned char> &blok_wyjscie);
void wyczysc_slownik_kompresja_LZ78();
void dekompresja_LZ78(vector <unsigned char> &blok_wejscie, vector <unsigned char> &blok_wyjscie);
void wyczysc_slownik_dekompresja_LZ78();
///////////////////////////////////HUFFMAN///////////////////////////////////////////////////////

struct huff_wezel
{
unsigned int waga;
unsigned char znak;
unsigned short int numer_wierzcholka;
huff_wezel *rodzic;
huff_wezel *syn_lewy;
huff_wezel *syn_prawy;
huff_wezel(unsigned int w, unsigned char z);
};

vector <huff_wezel*> huff_zbior_wezlow;
unsigned short int numer_wierzch=511;

huff_wezel::huff_wezel(unsigned int w, unsigned char z)
{
waga=w;
znak=z;
rodzic=0;
syn_lewy=0;
syn_prawy=0;
numer_wierzcholka=numer_wierzch;
numer_wierzch=numer_wierzch-1;
}

struct spis_wezlow
{
bool czy_jest;
huff_wezel *wskaznik_do_wezla;
spis_wezlow();
};

spis_wezlow::spis_wezlow()
{
czy_jest=0;
wskaznik_do_wezla=NULL;
}
spis_wezlow informacja_o_wezle[256];

void zamien_wezly(huff_wezel *pierwszy, huff_wezel *drugi);
void powiaz_wezly(huff_wezel *o, huff_wezel *s_p, huff_wezel *s_l);
void uaktualnij_drzewo(unsigned int i);
void kompresja_Huffman(vector <unsigned char> &blok_wejscie, vector <unsigned char> &blok_wyjscie);
void dekompresja_Huffman(vector <unsigned char> &blok_wejscie, vector <unsigned char> &blok_wyjscie);
void usun_drzewo();
//////////////////////////////////////////////////////////////////////////////////////////////////
#include "metody.cpp"
#endif
