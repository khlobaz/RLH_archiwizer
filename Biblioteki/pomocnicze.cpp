

void wczytaj_blok_danych (vector <unsigned char> &blok_wejscie,ifstream &wejscie,int rozmiar)
{
char znak;
int licznik=0;
while((licznik<rozmiar)&&(wejscie.get(znak)!=NULL))
        {
        blok_wejscie.push_back(znak);
        licznik++;
        }
}

void zapisz_blok_danych (vector <unsigned char> &blok_wyjscie,ofstream &wyjscie)
{
for (unsigned int i=0;(i<blok_wyjscie.size());i++)
        {
        wyjscie.put(blok_wyjscie.at(i));
        }
}

unsigned int zamien_char_na_int(unsigned char znak1,unsigned char znak2,unsigned char znak3,unsigned char znak4)
{
unsigned int liczba1,liczba2,liczba3,liczba4,liczba_koncowa;
liczba1=int(znak1); liczba1=liczba1<<24;
liczba2=int(znak2); liczba2=liczba2<<16;
liczba3=int(znak3); liczba3=liczba3<<8;
liczba4=int(znak4);
liczba_koncowa=liczba1+liczba2+liczba3+liczba4;
return liczba_koncowa;
}

void zamien_int_na_char(unsigned int liczba,unsigned char &znak1,unsigned char &znak2,unsigned char &znak3,unsigned char &znak4)
{
unsigned int liczba1,liczba2,liczba3,liczba4;
znak1=liczba>>24;
znak2=liczba>>16;
znak3=liczba>>8;
znak4=liczba;
}

unsigned int zamien_char_na_short_int(unsigned char znak1,unsigned char znak2)
{
unsigned int liczba1,liczba2,liczba_koncowa;
liczba1=int(znak1); liczba1=liczba1<<8;
liczba2=int(znak2);
liczba_koncowa=liczba1+liczba2;
return liczba_koncowa;
}

void zamien_short_int_na_char(unsigned int liczba,unsigned char &znak1,unsigned char &znak2)
{
znak1=liczba>>8;
znak2=liczba;
}

void zamien_char_na_bity(unsigned char znak,bool *tab)
{
unsigned char pomoc[8];
for (unsigned int i=0;i<8;i++)
        {
        pomoc[i]=znak;
        pomoc[i]=pomoc[i]<<i;
        pomoc[i]=pomoc[i]>>7;
        tab[i]=pomoc[i];
        }
}

unsigned char zamien_bity_na_char(bool *tab)
{
unsigned char pomoc[8];
unsigned char koniec=0;
for (unsigned int i=0;i<8;i++)
        {
        pomoc[i]=tab[i];
        pomoc[i]=pomoc[i]<<(7-i);
        koniec=koniec+pomoc[i];
        }
return koniec;
}


