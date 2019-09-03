//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include <fstream.h>
#include <iostream.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
#include <vector.h>
#include "Biblioteki\pomocnicze.h"
#include "Biblioteki\metody.h"
//---------------------------------------------------------------------------

const int BLOK=128000;

//----------------------------------------------------------------------------
TKompresor *Kompresor;

int __fastcall akcja(Pointer Parameter)    //Watek kompresji i dekompresji
{
Kompresor->anuluj=0;
pasek->anuluj->Enabled=false;
char *plik_odczytu=Kompresor->sciezka_otworz.c_str();
char *plik_zapisu=Kompresor->sciezka_zapisz.c_str();        //odczyt i zapis pliku
TSearchRec Plik_odczyt;
FindFirst(Kompresor->sciezka_otworz, faAnyFile, Plik_odczyt);   //do odczytania rozmiaru pliku
double rozmiar_pliku_odczytu=Plik_odczyt.Size;


ifstream wejscie(plik_odczytu,ios::binary);
ofstream wyjscie(plik_zapisu,ios::binary);

vector <unsigned char> blok_danych_wejsciowych;
vector <unsigned char> blok_danych_wyjsciowych;

if (Kompresor->kompresja->Checked==true)
        {
        Kompresor->Timer1->Enabled=true;
        //BUDOWA NAGLOWKA
        wyjscie.put('R');wyjscie.put('L'); wyjscie.put('H');
        for (int i=0;i<4;i++) //przygotowanie miejsca na rozmiar pliku
                {
                wyjscie.put(char(0));
                }
        wyjscie.put(Kompresor->nazwa_pliku_otworz.Length());
        char *nazwa_pliku=Kompresor->nazwa_pliku_otworz.c_str();
        wyjscie.write(nazwa_pliku,Kompresor->nazwa_pliku_otworz.Length());
        unsigned char metody=0;
        if (Kompresor->rle_zaznacz->Checked==true)
                {
                metody=metody+128;
                }
        if (Kompresor->lz78_zaznacz->Checked==true)
                {
                metody=metody+64;
                }
        if (Kompresor->huff_zaznacz->Checked==true)
                {
                metody=metody+32;
                }
        wyjscie.put(metody);
        //KONIEC NAGLOWKA

        pasek->c_zadanie->Caption="Proces kompresji w toku...";
        int dane_wejsciowe_rozmiar=0;
        double wspolczynnik;
        pasek->anuluj->Enabled=true;
        while (wejscie!=NULL)
                {
                wczytaj_blok_danych (blok_danych_wejsciowych,wejscie,BLOK);
                vector <unsigned char> blok_tymczasowy;
                blok_tymczasowy=blok_danych_wejsciowych;
                if (blok_tymczasowy.size()>0)
                        {
                        if (Kompresor->rle_zaznacz->Checked==true)
                                {
                                kompresja_rle(blok_tymczasowy,blok_danych_wyjsciowych);
                                blok_tymczasowy.clear();
                                blok_tymczasowy=blok_danych_wyjsciowych;
                                blok_danych_wyjsciowych.clear();
                                }
                        if (Kompresor->lz78_zaznacz->Checked==true)
                                {
                                kompresja_LZ78(blok_tymczasowy,blok_danych_wyjsciowych);
                                blok_tymczasowy.clear();
                                blok_tymczasowy=blok_danych_wyjsciowych;
                                blok_danych_wyjsciowych.clear();
                                }
                        if (Kompresor->huff_zaznacz->Checked==true)
                                {
                                kompresja_Huffman(blok_tymczasowy,blok_danych_wyjsciowych);
                                blok_tymczasowy.clear();
                                blok_tymczasowy=blok_danych_wyjsciowych;
                                blok_danych_wyjsciowych.clear();
                                }
                        blok_danych_wyjsciowych=blok_tymczasowy;
                        unsigned int rozmiar_wyjscia=blok_danych_wyjsciowych.size();
                        unsigned char znak1,znak2,znak3,znak4;
                        zamien_int_na_char(rozmiar_wyjscia,znak1,znak2,znak3,znak4);
                        wyjscie.put(znak1); wyjscie.put(znak2);
                        wyjscie.put(znak3); wyjscie.put(znak4);  //zapis 4 znakow aby
                        zapisz_blok_danych (blok_danych_wyjsciowych,wyjscie);  // dekompresor wiedzial ile wyczytac

                        dane_wejsciowe_rozmiar=dane_wejsciowe_rozmiar+blok_danych_wejsciowych.size();
                        double wynik=dane_wejsciowe_rozmiar/rozmiar_pliku_odczytu;
                        wynik=wynik*100.0;
                        pasek->pasek_1->Position=int(wynik);  //pasek postepu - aktualizacja

                        wynik=(wynik/100.0);
                        int calkowity_czas=(double(Kompresor->licz_czas)/wynik);  //za ile koniec
                        AnsiString tym2=(calkowity_czas-(Kompresor->licz_czas));
                        pasek->koniec_z->Caption=(tym2+" s");

                        wspolczynnik=(double(dane_wejsciowe_rozmiar-wyjscie.tellp())/double(dane_wejsciowe_rozmiar))*100; //wspolczynnik
                        AnsiString tym1=int(wspolczynnik);
                        pasek->wspolczynnik->Caption=(tym1+"%");

                        blok_danych_wejsciowych.clear(); blok_danych_wyjsciowych.clear();
                        }

                if (Kompresor->anuluj==1)
                        {
                        Kompresor->czyszczenie_struktur();
                        Kompresor->licz_czas=0;
                        pasek->pasek_1->Position=0;    //czyszczenie zmiennych
                        pasek->uplynel->Caption=0;
                        pasek->koniec_z->Caption=0;
                        pasek->wspolczynnik->Caption=("-");
                        Kompresor->Timer1->Enabled=false;
                        Kompresor->o_edycja->Text="";
                        Kompresor->z_edycja->Text="";
                        wejscie.close();
                        wyjscie.close();
                        char *plik_do_usuniecia=Kompresor->sciezka_zapisz.c_str();
                        DeleteFile(plik_do_usuniecia);
                        pasek->Close();
                        EndThread(0); //przerwanie watka
                        }

                }
        pasek->anuluj->Enabled=false;
        Kompresor->czyszczenie_struktur();   //jezeli korzystano z tych metod trzeba wyczyscic pamiec

        unsigned int rozmiar_pliku_zapisu=wyjscie.tellp();
        wyjscie.seekp(3);
        unsigned char znak1,znak2,znak3,znak4;
        zamien_int_na_char(rozmiar_pliku_zapisu,znak1,znak2,znak3,znak4);   //dopisanie rozmiaru wyjscia do pliku wyjsciowego
        wyjscie.put(znak1); wyjscie.put(znak2);
        wyjscie.put(znak3); wyjscie.put(znak4);

        Kompresor->Timer1->Enabled=false;
        pasek->Close();

        Kompresor->konsola->Lines->Insert(0,"----------------------------------------------------------------");
        AnsiString czas_tym=Kompresor->licz_czas;
        Kompresor->konsola->Lines->Insert(0,"Czas kompresji: "+czas_tym+" s");
        AnsiString wspolczynnik_tym=int(wspolczynnik);
        Kompresor->konsola->Lines->Insert(0,"Wspolczynnik kompresji: "+wspolczynnik_tym+"%");
        Kompresor->konsola->Lines->Insert(0,"Nazwa archiwum: "+Kompresor->nazwa_pliku_zapisz);
        Kompresor->konsola->Lines->Insert(0,"Skompresowano: "+Kompresor->nazwa_pliku_otworz);

        }

else
        {
        pasek->anuluj->Enabled=false;
        Kompresor->Timer1->Enabled=true;
        char znak1,znak2,znak3,znak4;
        wejscie.get(znak1); wejscie.get(znak2); wejscie.get(znak3);
        if ( (znak1=='R') && (znak2=='L') && (znak3=='H') )
                {
                wejscie.get(znak1); wejscie.get(znak2);
                wejscie.get(znak3); wejscie.get(znak4);
                int rozmiar_z_naglowka=zamien_char_na_int(znak1,znak2,znak3,znak4);
                if (rozmiar_pliku_odczytu==rozmiar_z_naglowka)
                        {
                        wejscie.get(znak1);
                        int dlugosc_nazwy=int(znak1);
                        wejscie.seekg(wejscie.tellg()+dlugosc_nazwy);
                        pasek->c_zadanie->Caption="Proces dekompresji w toku...";

                        wejscie.get(znak1);
                        unsigned char rle=0,lz78=0,huffman=0;
                        unsigned char pomoc=znak1;
                        rle=pomoc>>7;
                        lz78=pomoc; lz78=lz78<<1; lz78=lz78>>7;
                        huffman=pomoc; huffman=huffman<<2; huffman=huffman>>7;
                        pasek->anuluj->Enabled=true;
                        while (wejscie!=NULL)
                                {
                                wejscie.get(znak1); wejscie.get(znak2);
                                wejscie.get(znak3); wejscie.get(znak4);
                                unsigned int rozmiar_wejscia=zamien_char_na_int(znak1,znak2,znak3,znak4);
                                wczytaj_blok_danych (blok_danych_wejsciowych,wejscie,rozmiar_wejscia);
                                if (blok_danych_wejsciowych.size()>0)
                                        {
                                        vector <unsigned char> blok_tymczasowy;
                                        blok_tymczasowy=blok_danych_wejsciowych;
                                        if (huffman==1)
                                                {
                                                dekompresja_Huffman(blok_tymczasowy,blok_danych_wyjsciowych);
                                                blok_tymczasowy.clear();
                                                blok_tymczasowy=blok_danych_wyjsciowych;
                                                blok_danych_wyjsciowych.clear();
                                                }

                                        if (lz78==1)
                                                {
                                                dekompresja_LZ78(blok_tymczasowy,blok_danych_wyjsciowych);
                                                blok_tymczasowy.clear();
                                                blok_tymczasowy=blok_danych_wyjsciowych;
                                                blok_danych_wyjsciowych.clear();
                                                }

                                        if (rle==1)
                                                {
                                                dekompresja_rle(blok_tymczasowy,blok_danych_wyjsciowych);
                                                blok_tymczasowy.clear();
                                                blok_tymczasowy=blok_danych_wyjsciowych;
                                                blok_danych_wyjsciowych.clear();
                                                }
                                        blok_danych_wyjsciowych=blok_tymczasowy;
                                        zapisz_blok_danych (blok_danych_wyjsciowych,wyjscie);
                                        blok_danych_wejsciowych.clear(); blok_danych_wyjsciowych.clear();
                                        }

                                double wynik=wejscie.tellg()/rozmiar_pliku_odczytu;
                                wynik=wynik*100.0;
                                pasek->pasek_1->Position=int(wynik);       //pasek postepu - aktualizacja

                                wynik=(wynik/100.0);
                                int calkowity_czas=(double(Kompresor->licz_czas)/wynik);     //za ile koniec
                                AnsiString tym2=(calkowity_czas-(Kompresor->licz_czas));
                                pasek->koniec_z->Caption=(tym2+" s");

                                if (Kompresor->anuluj==1)     //sprawdza czy wcisnieto przycisk anuluj
                                        {
                                        Kompresor->czyszczenie_struktur();
                                        Kompresor->licz_czas=0;
                                        pasek->pasek_1->Position=0;    //czyszczenie zmiennych
                                        pasek->uplynel->Caption=0;
                                        pasek->koniec_z->Caption=0;
                                        pasek->wspolczynnik->Caption=("-");
                                        Kompresor->Timer1->Enabled=false;
                                        Kompresor->o_edycja->Text="";
                                        Kompresor->z_edycja->Text="";
                                        wejscie.close();
                                        wyjscie.close();
                                        char *plik_do_usuniecia=Kompresor->sciezka_zapisz.c_str();
                                        DeleteFile(plik_do_usuniecia);
                                        pasek->Close();
                                        EndThread(0); //przerwanie watka
                                        }

                               }
                        pasek->anuluj->Enabled=false;
                        Kompresor->czyszczenie_struktur();

                        Kompresor->Timer1->Enabled=false;
                        pasek->Close();

                        Kompresor->konsola->Lines->Insert(0,"----------------------------------------------------------------");
                        AnsiString czas_tym=Kompresor->licz_czas;
                        Kompresor->konsola->Lines->Insert(0,"Czas dekompresji: "+czas_tym+" s");
                        Kompresor->konsola->Lines->Insert(0,"Utworzono: "+Kompresor->nazwa_pliku_zapisz);
                        Kompresor->konsola->Lines->Insert(0,"Zdekompresowano: "+Kompresor->nazwa_pliku_otworz);

                        }
                }
        }

Kompresor->licz_czas=0;
pasek->pasek_1->Position=0;    //czyszczenie zmiennych
pasek->uplynel->Caption=0;
pasek->koniec_z->Caption=0;
pasek->wspolczynnik->Caption=("-");
Kompresor->Timer1->Enabled=false;

MessageBeep(MB_ICONEXCLAMATION);    //Dzwiek
Kompresor->o_edycja->Text="";
Kompresor->z_edycja->Text="";
wejscie.close();
wyjscie.close();
return 0;
}

//---------------------------------------------------------------------------
__fastcall TKompresor::TKompresor(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TKompresor::zakonczClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------


void __fastcall TKompresor::Pomoc1Click(TObject *Sender)
{
MessageBox(Handle,
"Aby przeprowadziæ kompresjê wybranego pliku nale¿y:\n"
"1.     zaznaczyæ opcjê ''Kompresja'' z panelu ''Operacja'',\n"
"2.     wybraæ kompresowany plik przy pomocy ''Otwórz'',\n"
"3.     wybraæ metody kompresji z panelu ''Metody kompresji'',\n"
"4.     nacisn¹æ przycisk ''Start''.\n\n"

"Aby przeprowadziæ dekompresjê archiwum nale¿y:\n"
"1.     zaznaczyæ opcjê ''Dekompresja'' z panelu ''Operacja'',\n"
"2.     wybraæ plik archiwum przy pomocy ''Otwórz'',\n"
"3.     nacisn¹æ przycisk ''Start''.\n\n"

"Opis algorytmów:\n\n"
"1.    metoda RLE - polega na wyszukiwaniu w plikach ci¹gów takich samych znaków, jej skutecznoœæ\n"
"       ogranicza siê w zasadzie do kompresji plików graficznych o ma³ej iloœci kolorów. Zalet¹ tej\n"
"       metody jest bardzo du¿a szybkoœæ dzia³ania oraz znikome zapotrzebowanie na pamiêæ komputera.\n\n"
"2.    metoda LZ78 - polega na wyszukiwaniu i kodowaniu fraz, które ju¿ wczeœniej wyst¹pi³y \n"
"       w zbiorze - najlepsza do kompresji plików tekstowych. Wad¹ LZ78 jest bardzo du¿e\n"
"       zapotrzebowaniena pamiêæ.\n\n"
"3.    metoda Huffmana (algorytm FGK) - zamienia kolejne znaki ze zbioru na ró¿nej d³ugoœci kod binarny. \n"
"       Du¿y wspó³czynnik kompresji uzyska siê w plikach  charakteryzuj¹cych siê ma³¹ ró¿norodnoœci¹\n"
"       symboli, a tak¿e du¿¹ rozbie¿noœci¹ w czêstotliwoœci ich wystêpowania. Generalnie daje dobre\n"
"       efekty w przypadku ró¿nych typów plików. Charakteryzuje siê niedu¿ym zapotrzebowaniem na pamiêæ\n"
"       oraz bardzo ma³¹ szybkoœci¹ dzia³ania."

,"Pomoc",MB_OK | MB_ICONINFORMATION);

}
//---------------------------------------------------------------------------


void __fastcall TKompresor::dekompresjaClick(TObject *Sender)
{
rle_zaznacz->Enabled=false;
lz78_zaznacz->Enabled=false;
huff_zaznacz->Enabled=false;
rle->Enabled=false;
lz78->Enabled=false;
huff->Enabled=false;
Kompresor->o_edycja->Text="";
Kompresor->z_edycja->Text="";
}
//---------------------------------------------------------------------------

void __fastcall TKompresor::kompresjaClick(TObject *Sender)
{
rle_zaznacz->Enabled=true;
lz78_zaznacz->Enabled=true;
huff_zaznacz->Enabled=true;
rle->Enabled=true;
lz78->Enabled=true;
huff->Enabled=true;
Kompresor->o_edycja->Text="";
Kompresor->z_edycja->Text="";
}
//---------------------------------------------------------------------------

void __fastcall TKompresor::otworzClick(TObject *Sender)
{
if (otworz_ik->Execute())
        {
        if (kompresja->Checked==true)
                {
                o_edycja->Text=otworz_ik->FileName;
                sciezka_otworz=o_edycja->Text;
                sciezka_katalogu_otworz=ExtractFilePath(sciezka_otworz);
                nazwa_pliku_otworz=ExtractFileName(sciezka_otworz);
                rozszerzenie_otworz=ExtractFileExt(sciezka_otworz);
                rozszerzenie_zapisz=".rlh";

                nazwa_pliku_zapisz=nazwa_pliku_otworz;
                nazwa_pliku_zapisz.Delete((nazwa_pliku_otworz.Length()-rozszerzenie_otworz.Length()+1),rozszerzenie_otworz.Length());
                nazwa_pliku_zapisz=nazwa_pliku_zapisz+rozszerzenie_zapisz;
                sciezka_zapisz=sciezka_katalogu_otworz+nazwa_pliku_zapisz;
                z_edycja->Text=sciezka_zapisz;
                if (o_edycja->Text==z_edycja->Text)
                        {
                        z_edycja->Text="";
                        }

                }
        else    //czyli dekompresja
                {
                o_edycja->Text=otworz_ik->FileName;
                sciezka_otworz=o_edycja->Text;
                sciezka_katalogu_otworz=ExtractFilePath(sciezka_otworz);
                nazwa_pliku_otworz=ExtractFileName(sciezka_otworz);
                char *sciezka=sciezka_otworz.c_str();
                ifstream strumien (sciezka,ios::binary);
                TSearchRec plik;
                FindFirst(sciezka_otworz, faAnyFile,plik);
                double wielkosc_pliku=plik.Size;

                char znak1,znak2,znak3,znak4;
                strumien.get(znak1);strumien.get(znak2); strumien.get(znak3);
                if ( (znak1=='R') && (znak2=='L') && (znak3=='H') )
                        {
                        strumien.get(znak1);strumien.get(znak2); strumien.get(znak3); strumien.get(znak4);
                        int rozmiar_z_naglowka=zamien_char_na_int(znak1,znak2,znak3,znak4);
                        if (wielkosc_pliku==rozmiar_z_naglowka)
                                {
                                strumien.get(znak1);
                                int dlugosc_nazwy=int(znak1);
                                unsigned char rle=0,lz78=0,huffman=0;
                                AnsiString nazwa_pliku;
                                for (int a=0;a<dlugosc_nazwy;a++)
                                        {
                                        strumien.get(znak1);
                                        nazwa_pliku=nazwa_pliku+AnsiString(znak1);
                                        }
                                strumien.get(znak1);
                                unsigned char pomoc=znak1;
                                rle=pomoc>>7;
                                lz78=pomoc; lz78=lz78<<1; lz78=lz78>>7;
                                huffman=pomoc; huffman=huffman<<2; huffman=huffman>>7;

                                nazwa_pliku_zapisz=nazwa_pliku;
                                sciezka_zapisz=sciezka_katalogu_otworz+nazwa_pliku_zapisz;
                                z_edycja->Text=sciezka_zapisz;

                                AnsiString r,l,h;
                                if (rle==1) {r="RLE";}
                                if (lz78==1) {l="LZ78";}
                                if (huffman==1) {h="HUFFMAN";}
                                Kompresor->konsola->Lines->Insert(0,"----------------------------------------------------------------");
                                Kompresor->konsola->Lines->Insert(0,"U¿yte metody: "+r+" "+l+" "+h);
                                Kompresor->konsola->Lines->Insert(0,"Archiwum: "+nazwa_pliku_otworz);
                                }
                        else
                                {
                                MessageBox(Handle, "Uszkodzone archiwum!", "B³¹d",MB_OK |MB_ICONSTOP);
                                o_edycja->Text="";
                                }
                        }
                else
                        {
                        AnsiString pomoc="Plik "+nazwa_pliku_otworz+" nie jest archiwum RLH archiwizera";
                        char *wpis=pomoc.c_str();
                        MessageBox(Handle,wpis, "B³¹d",MB_OK |MB_ICONSTOP);
                        o_edycja->Text="";
                        }

                strumien.close();
                }

        }
}
//---------------------------------------------------------------------------
void __fastcall TKompresor::zapiszClick(TObject *Sender)
{
if(zapisz_ik->Execute())
      {
      z_edycja->Text=zapisz_ik->FileName;
      sciezka_zapisz=z_edycja->Text;
      rozszerzenie_zapisz=ExtractFileExt(sciezka_zapisz);
      nazwa_pliku_zapisz=ExtractFileName(sciezka_zapisz);
      }

}

//---------------------------------------------------------------------------

void __fastcall TKompresor::startClick(TObject *Sender)
{

if ( (z_edycja->Text=="") || (o_edycja->Text=="") )
        {
        MessageBox(Handle, "Brak scie¿ki odczytu/zapisu!", "B³¹d",MB_OK |MB_ICONSTOP);
        }
else
        {
        if (o_edycja->Text==z_edycja->Text)
                {
                MessageBox(Handle, "Œcie¿ki odczytu i zapisu s¹ identyczne!", "B³¹d",MB_OK |MB_ICONSTOP);
                }
        else
                {
                if ((kompresja->Checked)==true)
                        {
                        if ((rle_zaznacz->Checked==false)&&(lz78_zaznacz->Checked==false)&&
                           (huff_zaznacz->Checked==false))
                                {
                                MessageBox(Handle, "Nie wybano ¿adnej z metod kompresji!", "B³¹d",MB_OK |MB_ICONSTOP);
                                }
                        else
                                {
                                if (FileExists(nazwa_pliku_zapisz))
                                        {
                                        AnsiString tym="Plik "+nazwa_pliku_zapisz+" juz istnieje i zostanie nadpisany!\n Czy na pewno kontynuowac?";
                                        char *wpis=tym.c_str();
                                        int wybor=MessageBox(Handle,wpis,"Uwaga",MB_YESNO|MB_ICONEXCLAMATION|MB_SYSTEMMODAL|MB_DEFBUTTON1);
                                        if(wybor==ID_YES)
                                                {
                                                W_ID_1 = BeginThread(NULL, 0,akcja, this, 0, W_PD);
                                                pasek->ShowModal();
                                                }
                                        }
                                else
                                        {
                                        W_ID_1 = BeginThread(NULL, 0,akcja, this, 0, W_PD);
                                        pasek->ShowModal();
                                        }
                                 }
                        }
                else     //dekompresja
                        {
                        if (FileExists(nazwa_pliku_zapisz))
                                {
                                AnsiString tym="Plik "+nazwa_pliku_zapisz+" juz istnieje i zostanie nadpisany!\n Czy na pewno kontynuowac?";
                                char *wpis=tym.c_str();
                                int wybor=MessageBox(Handle,wpis,"Uwaga",MB_YESNO|MB_ICONEXCLAMATION|MB_SYSTEMMODAL|MB_DEFBUTTON1);
                                if(wybor==ID_YES)
                                        {
                                        W_ID_1 = BeginThread(NULL, 0,akcja, this, 0, W_PD);
                                        pasek->ShowModal();
                                        }
                                }
                        else
                                {
                                W_ID_1 = BeginThread(NULL, 0,akcja, this, 0, W_PD);
                                pasek->ShowModal();
                                }
                        }

                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TKompresor::Timer1Timer(TObject *Sender)
{
licz_czas=0;
}
//---------------------------------------------------------------------------

void __fastcall TKompresor::OnTimerTimer(TObject *Sender)
{
licz_czas++;
AnsiString czas=licz_czas;
AnsiString tym=(czas+" s");
pasek->uplynel->Caption=tym;
}

//---------------------------------------------------------------------------

void TKompresor::czyszczenie_struktur()
{
if (kompresja->Checked==true)
        {
        wyczysc_slownik_kompresja_LZ78();
        usun_drzewo();
        }
else
        {
        wyczysc_slownik_dekompresja_LZ78();
        usun_drzewo();
        }
}



