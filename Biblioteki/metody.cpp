///////////////////////////////////RLE///////////////////////////////////////////////////////
void zapisz_zgodne(unsigned char dane,unsigned int ilosc,vector <unsigned char> &blok_wyjscie)
{
while(ilosc>128)
        {
        blok_wyjscie.push_back(255);
        blok_wyjscie.push_back(dane);
        ilosc=ilosc-128;
        }
if (ilosc>0)
        {
        blok_wyjscie.push_back(127+ilosc);
        blok_wyjscie.push_back(dane);
        }
}
void zapisz_niezgodne(vector <unsigned char> &dane, vector <unsigned char> &blok_wyjscie)
{
unsigned int pomoc=0;
while((dane.size()-pomoc)>128)
        {
        blok_wyjscie.push_back(127);
        for (unsigned int i=0;i<128;i++)
                {
                blok_wyjscie.push_back(dane.at(pomoc));
                pomoc++;
                }
        }
if (pomoc<dane.size())
        {
        blok_wyjscie.push_back((dane.size()-pomoc)-1);
        for (pomoc;pomoc<dane.size();pomoc++)
                {
                blok_wyjscie.push_back(dane.at(pomoc));
                }
        }
}


void kompresja_rle(vector <unsigned char> &blok_wejscie, vector <unsigned char> &blok_wyjscie)
{
unsigned char a,b;
unsigned int zgodne=1,niezgodne=0;
unsigned int i;
if (blok_wejscie.size()>1)
        {
        for (i=0;(i+1)<blok_wejscie.size();i++)
                {
                a=blok_wejscie.at(i);
                b=blok_wejscie.at(i+1);
                if (a==b)
                        {
                        zgodne=zgodne+1;
                        if (niezgodne>0)
                                {
                                vector <unsigned char> tymczasowy_bufor;
                                while (niezgodne>0)
                                        {
                                        tymczasowy_bufor.push_back(blok_wejscie.at(i-niezgodne));
                                        niezgodne=niezgodne-1;
                                        }
                                zapisz_niezgodne(tymczasowy_bufor,blok_wyjscie);
                                }
                        }
                else
                        {
                        niezgodne=niezgodne+1;
                        if (zgodne>1)
                                {
                                zapisz_zgodne(blok_wejscie.at(i),zgodne,blok_wyjscie);
                                niezgodne=niezgodne-1;
                                zgodne=1;
                                }
                        }
                }
        i=i-1;
        if (blok_wejscie.at(i)==blok_wejscie.at(i+1))
                {
                zapisz_zgodne(blok_wejscie.at(i),zgodne,blok_wyjscie);
                }
        else
                {
                vector <unsigned char> tymczasowy_bufor;
                while (niezgodne>0)
                        {
                        tymczasowy_bufor.push_back(blok_wejscie.at((i+1)-niezgodne));
                        niezgodne=niezgodne-1;
                        }
                tymczasowy_bufor.push_back(blok_wejscie.at(i+1));
                zapisz_niezgodne(tymczasowy_bufor,blok_wyjscie);
                }

        }
if (blok_wejscie.size()==1)
        {
        blok_wyjscie.push_back(char(0));
        blok_wyjscie.push_back(blok_wejscie.at(0));
        }
}

void dekompresja_rle(vector <unsigned char> &blok_wejscie, vector <unsigned char> &blok_wyjscie)
{
unsigned char znak1,znak2;
unsigned int i=0;
while ((i)<blok_wejscie.size())
        {
        znak1=blok_wejscie.at(i);
        i=i+1;
        if (znak1>127)
                {
                znak2=blok_wejscie.at(i);
                for (int k=128;k<=znak1;k++)
                        {
                        blok_wyjscie.push_back(znak2);
                        }
                i=i+1;
                }
        else
                {
                for (int l=0;l<=znak1;l++)
                        {
                        blok_wyjscie.push_back(blok_wejscie.at(i+l));
                        }
                i=(i+znak1+1);
                }
        }
}

//////////////////////////////////LZ78////////////////////////////////////////////////////////
void kompresja_LZ78(vector <unsigned char> &blok_wejscie, vector <unsigned char> &blok_wyjscie)
{
if (LZ78_kom_indeks==0)
        {
        LZ78_null = new wezel();
        }
wezel *wezel_pomocniczy;
wezel_pomocniczy=LZ78_null;
for (unsigned int i=0;i<blok_wejscie.size();i++)
        {
        if (wezel_pomocniczy->dzieci[blok_wejscie.at(i)])
                {
                wezel_pomocniczy=wezel_pomocniczy->dzieci[blok_wejscie.at(i)];
                if ((i+1)==blok_wejscie.size())
                        {
                        unsigned char pomoc1,pomoc2;
                        zamien_short_int_na_char(wezel_pomocniczy->wezel_indeks,pomoc1,pomoc2);
                        blok_wyjscie.push_back(pomoc1); blok_wyjscie.push_back(pomoc2);
                        }
                }
        else
                {
                unsigned char pomoc1,pomoc2;
                zamien_short_int_na_char(wezel_pomocniczy->wezel_indeks,pomoc1,pomoc2);
                blok_wyjscie.push_back(pomoc1); blok_wyjscie.push_back(pomoc2);
                blok_wyjscie.push_back(blok_wejscie.at(i));
                if (LZ78_kom_indeks<LZ78_ilosc_dopuszczalnych_fraz)
                        {
                        wezel_pomocniczy->dzieci[blok_wejscie.at(i)]=new wezel();
                        }
                else
                        {
                        wyczysc_slownik_kompresja_LZ78();
                        }
                wezel_pomocniczy=LZ78_null;
                }

        }
}
void wyczysc_slownik_kompresja_LZ78()
{
for (unsigned int i=0;i<LZ78_kom_indeks;i++)
        {
        delete LZ78_indeksowanie_wezlow[i];
        }
LZ78_kom_indeks=0;
LZ78_null = new wezel();
}

void dekompresja_LZ78(vector <unsigned char> &blok_wejscie, vector <unsigned char> &blok_wyjscie)
{
if (LZ78_dekom_indeks==0)
                {
                slownik[0]=new slowo();
                }
for (unsigned int i=0;(i+3)<=blok_wejscie.size();i=i+3)
        {
        unsigned char short_int_1,short_int_2,znak;
        unsigned int indeks_w_slowniku;
        short_int_1=blok_wejscie.at(i); short_int_2=blok_wejscie.at(i+1);
        indeks_w_slowniku=zamien_char_na_short_int(short_int_1,short_int_2);
        znak=blok_wejscie.at(i+2);

        for (unsigned int j=0;j<((slownik[indeks_w_slowniku]->wyraz).size());j++)
                {
                blok_wyjscie.push_back(slownik[indeks_w_slowniku]->wyraz.at(j));
                }
        blok_wyjscie.push_back(znak);
        if (LZ78_dekom_indeks<LZ78_ilosc_dopuszczalnych_fraz)
                {
                slownik[(LZ78_dekom_indeks-1)]=new slowo(znak,indeks_w_slowniku);
                }
        else
                {
                wyczysc_slownik_dekompresja_LZ78();
                }
        if ((i+5)==blok_wejscie.size())
                {
                short_int_1=blok_wejscie.at(i+3); short_int_2=blok_wejscie.at(i+4);
                indeks_w_slowniku=zamien_char_na_short_int(short_int_1,short_int_2);
                for (unsigned int j=0;j<((slownik[indeks_w_slowniku]->wyraz).size());j++)
                        {
                        blok_wyjscie.push_back(slownik[indeks_w_slowniku]->wyraz.at(j));
                        }
                }
        }
}

void wyczysc_slownik_dekompresja_LZ78()
{
for (unsigned int i=0;i<LZ78_dekom_indeks;i++)
        {
        delete slownik[i];
        }
LZ78_dekom_indeks=0;
slownik[0]=new slowo();
}

//////////////////////////////////////HUFFMAN/////////////////////////////////////////

void zamien_wezly(huff_wezel *pierwszy, huff_wezel *drugi)
{
huff_wezel *syn_lewy_pierwszy=pierwszy->syn_lewy;
huff_wezel *syn_prawy_pierwszy=pierwszy->syn_prawy;
huff_wezel *syn_lewy_drugi=drugi->syn_lewy;
huff_wezel *syn_prawy_drugi=drugi->syn_prawy;
unsigned char tymczasowy;
tymczasowy=pierwszy->znak;
pierwszy->znak=drugi->znak;
drugi->znak=tymczasowy;

pierwszy->syn_lewy=syn_lewy_drugi;
pierwszy->syn_prawy=syn_prawy_drugi;

if (syn_lewy_drugi)
        {
        syn_lewy_drugi->rodzic=pierwszy;
        }
if (syn_prawy_drugi)
        {
        syn_prawy_drugi->rodzic=pierwszy;
        }

drugi->syn_lewy=syn_lewy_pierwszy;
drugi->syn_prawy=syn_prawy_pierwszy;

if (syn_lewy_pierwszy)
        {
        syn_lewy_pierwszy->rodzic=drugi;
        }
if (syn_prawy_pierwszy)
        {
        syn_prawy_pierwszy->rodzic=drugi;
        }
//uaktualnienie spisu wezlow
if (pierwszy->syn_lewy==0)
        {
        (informacja_o_wezle[pierwszy->znak]).wskaznik_do_wezla=pierwszy;
        }
if (drugi->syn_lewy==0)
        {
        (informacja_o_wezle[drugi->znak]).wskaznik_do_wezla=drugi;
        }
}
void powiaz_wezly(huff_wezel *o, huff_wezel *s_p, huff_wezel *s_l)
{
o->waga=s_p->waga+s_l->waga;
s_p->rodzic=o;
s_l->rodzic=o;
o->syn_prawy=s_p;
o->syn_lewy=s_l;
}

void uaktualnij_drzewo(unsigned int i)
{
while ((huff_zbior_wezlow.at(i)->rodzic)!=NULL)
        {
        unsigned int pomoc_i=i;
        while ( ((huff_zbior_wezlow.at(pomoc_i)->waga)==(huff_zbior_wezlow.at(i)->waga)) && ((huff_zbior_wezlow.at(pomoc_i)->numer_wierzcholka)<511) )
                {
                pomoc_i=pomoc_i-1;
                }
        pomoc_i=pomoc_i+1;
        if ( (huff_zbior_wezlow.at(pomoc_i)->numer_wierzcholka!=huff_zbior_wezlow.at(i)->numer_wierzcholka) && (huff_zbior_wezlow.at(i)->rodzic!=huff_zbior_wezlow.at(pomoc_i)) )
                {
                zamien_wezly (huff_zbior_wezlow.at(i),huff_zbior_wezlow.at(pomoc_i));
                i=pomoc_i;
                }
        huff_zbior_wezlow.at(i)->waga=huff_zbior_wezlow.at(i)->waga+1;
        huff_wezel *pomoc=(huff_zbior_wezlow.at(i));
        int z;
        pomoc=pomoc->rodzic;
        z=(511-(pomoc->numer_wierzcholka));
        i=z;
        }
huff_zbior_wezlow.at(i)->waga=(huff_zbior_wezlow.at(i)->syn_lewy->waga)+(huff_zbior_wezlow.at(i)->syn_prawy->waga);
}

void kompresja_Huffman(vector <unsigned char> &blok_wejscie, vector <unsigned char> &blok_wyjscie)
{
if (huff_zbior_wezlow.size()==0)
        {
        huff_zbior_wezlow.push_back(new huff_wezel(0,0));
        }
vector <bool> zakodowane_dane;
unsigned char znak_we;
bool *tab = new bool[8];
for (unsigned int i=0;i<blok_wejscie.size();i++)
        {
        znak_we=blok_wejscie.at(i);
        unsigned int j;
        bool czy_znaleziono=0;
        if ((informacja_o_wezle[znak_we]).czy_jest==1)
                {
                czy_znaleziono=1;
                j=(511-((informacja_o_wezle[znak_we]).wskaznik_do_wezla->numer_wierzcholka));
                }
                
        if (czy_znaleziono==1)
                {
                vector <bool> tymczasowy;
                huff_wezel *tym=huff_zbior_wezlow.at(j);
                while (tym->rodzic!=NULL)    //tworzenie kodu dla danego symbolu
                        {
                        int wierzcholek=tym->numer_wierzcholka;
                        tym=tym->rodzic;
                        if ((tym->syn_lewy->numer_wierzcholka)==wierzcholek)
                                {
                                tymczasowy.push_back(0);
                                }
                        else
                                {
                                tymczasowy.push_back(1);
                                }
                        }
                while (tymczasowy.size()>0)  //umieszczenie kodu na wyjscie
                        {
                        zakodowane_dane.push_back(tymczasowy.back());
                        tymczasowy.pop_back();
                        }
                uaktualnij_drzewo(j);
                }
        else
                {
                vector <bool> tymczasowy;
                huff_wezel *tym=huff_zbior_wezlow.at(huff_zbior_wezlow.size()-1);
                while (tym->rodzic!=NULL)        //wyczytanie kodu NYT-a
                        {
                        unsigned short int wierzcholek=tym->numer_wierzcholka;
                        tym=tym->rodzic;
                        if ((tym->syn_lewy->numer_wierzcholka)==wierzcholek)
                                {
                                tymczasowy.push_back(0);
                                }
                        else
                                {
                                tymczasowy.push_back(1);
                                }
                        }
                while (tymczasowy.size()>0)    //umieszczenie kodu NYT-a na wyjscie
                        {
                        zakodowane_dane.push_back(tymczasowy.back());
                        tymczasowy.pop_back();
                        }
                zamien_char_na_bity(znak_we,tab);
                for (unsigned int a=0;a<8;a++)
                        {
                        zakodowane_dane.push_back(tab[a]);
                        }
                huff_zbior_wezlow.push_back(new huff_wezel (1,znak_we));
                huff_zbior_wezlow.push_back(new huff_wezel (0,0));
                powiaz_wezly(huff_zbior_wezlow.at(huff_zbior_wezlow.size()-3),huff_zbior_wezlow.at(huff_zbior_wezlow.size()-2),huff_zbior_wezlow.at(huff_zbior_wezlow.size()-1));

                (informacja_o_wezle[(huff_zbior_wezlow.at(huff_zbior_wezlow.size()-2))->znak]).czy_jest=1;
                (informacja_o_wezle[(huff_zbior_wezlow.at(huff_zbior_wezlow.size()-2))->znak]).wskaznik_do_wezla=(huff_zbior_wezlow.at(huff_zbior_wezlow.size()-2));

                huff_wezel *pomoc=(huff_zbior_wezlow.at(huff_zbior_wezlow.size()-3));
                if ((pomoc->rodzic)!=NULL)
                        {
                        pomoc=pomoc->rodzic;
                        unsigned int z;
                        z=(511-(pomoc->numer_wierzcholka));
                        uaktualnij_drzewo(z);
                        }
                }
        }
unsigned char ilosc_dobrych_bitow=zakodowane_dane.size()%8;
blok_wyjscie.push_back(ilosc_dobrych_bitow);
unsigned int licznik=0,m=0;
while (licznik<zakodowane_dane.size())
        {
        tab[m]=zakodowane_dane.at(licznik);
        licznik++;
        m++;
        if (m==8)
                {
                blok_wyjscie.push_back(zamien_bity_na_char(tab));
                m=0;
                }
        }
if (m>0)
        {
        blok_wyjscie.push_back(zamien_bity_na_char(tab));
        }
delete [] tab;
}

void dekompresja_Huffman(vector <unsigned char> &blok_wejscie, vector <unsigned char> &blok_wyjscie)
{
if (huff_zbior_wezlow.size()==0)
        {
        huff_zbior_wezlow.push_back(new huff_wezel(0,0));
        }
bool *tab = new bool[8];
vector <bool> zakodowane_dane;
unsigned char ilosc_dobrych_bitow=0;
unsigned char wczytany_znak;
if (blok_wejscie.size()>0)
	{
	ilosc_dobrych_bitow=blok_wejscie.at(0);
	}
unsigned int licznik=1;
while (licznik<blok_wejscie.size())
        {
        wczytany_znak=blok_wejscie.at(licznik);
        zamien_char_na_bity(wczytany_znak,tab);
        for (int i=0;i<8;i++)
                {
                zakodowane_dane.push_back(tab[i]);
                }
        licznik++;
        }
if (ilosc_dobrych_bitow>0)
        {
        for (ilosc_dobrych_bitow;ilosc_dobrych_bitow<8;ilosc_dobrych_bitow++)
                {
                zakodowane_dane.pop_back();
                }
        }

huff_wezel *korzen=huff_zbior_wezlow.at(0);
huff_wezel *temp=korzen;
unsigned int licznik_bitow=0;
while (licznik_bitow<zakodowane_dane.size())
        {
        while (temp->syn_lewy!=0)
                {
                if (zakodowane_dane.at(licznik_bitow))
                        {
                        temp=temp->syn_prawy;
                        licznik_bitow++;
                        }
                else
                        {
                        temp=temp->syn_lewy;
                        licznik_bitow++;
                        }
                }
        if (temp->waga==0)
                {
                for (int s=0;s<8;s++)
                        {
                        tab[s]=zakodowane_dane.at(licznik_bitow);
                        licznik_bitow++;
                        }
                unsigned char symbol;

                symbol=zamien_bity_na_char(tab);
                blok_wyjscie.push_back(symbol);
                huff_zbior_wezlow.push_back(new huff_wezel (1,symbol));
                huff_zbior_wezlow.push_back(new huff_wezel (0,0));
                powiaz_wezly(huff_zbior_wezlow.at(huff_zbior_wezlow.size()-3),huff_zbior_wezlow.at(huff_zbior_wezlow.size()-2),huff_zbior_wezlow.at(huff_zbior_wezlow.size()-1));
                huff_wezel *pomoc=(huff_zbior_wezlow.at(huff_zbior_wezlow.size()-3));
                if ((pomoc->rodzic)!=NULL)
                        {
                        pomoc=pomoc->rodzic;
                        unsigned int z;
                        z=(511-(pomoc->numer_wierzcholka));
                        uaktualnij_drzewo(z);
                        }
                temp=korzen;
                }
        else
                {
                unsigned char symbol;
                symbol=temp->znak;
                blok_wyjscie.push_back(symbol);
                unsigned int j;
                j=(511-(temp->numer_wierzcholka));
                uaktualnij_drzewo(j);
                temp=korzen;
                }
        }
delete [] tab;
}

void usun_drzewo()
{
for (unsigned int i=0;i<huff_zbior_wezlow.size();i++)
       {
       delete huff_zbior_wezlow.at(i);
       }
huff_zbior_wezlow.clear();
numer_wierzch=511;
for (int s=0;s<256;s++)
        {
        informacja_o_wezle[s].czy_jest=0;
        informacja_o_wezle[s].wskaznik_do_wezla=NULL;
        }
}
