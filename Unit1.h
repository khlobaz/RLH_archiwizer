//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <fstream.h>
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "trayicon.h"
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TKompresor : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *menu_ik;
        TMenuItem *zakoncz;
        TMenuItem *Pomoc1;
        TMemo *konsola;
        TOpenDialog *otworz_ik;
        TSaveDialog *zapisz_ik;
        TButton *otworz;
        TButton *zapisz;
        TEdit *o_edycja;
        TEdit *z_edycja;
        TButton *start;
        TGroupBox *s_kompresji;
        TCheckBox *rle_zaznacz;
        TCheckBox *lz78_zaznacz;
        TCheckBox *huff_zaznacz;
        TLabel *lz78;
        TLabel *rle;
        TLabel *huff;
        TGroupBox *operacja;
        TRadioButton *kompresja;
        TRadioButton *dekompresja;
        TTimer *Timer1;
        void __fastcall dekompresjaClick(TObject *Sender);
        void __fastcall kompresjaClick(TObject *Sender);
        void __fastcall otworzClick(TObject *Sender);
        void __fastcall startClick(TObject *Sender);
        void __fastcall zapiszClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall OnTimerTimer(TObject *Sender);
        void __fastcall zakonczClick(TObject *Sender);
        void __fastcall Pomoc1Click(TObject *Sender);
private:	// User declarations


public:		// User declarations
        AnsiString sciezka_otworz,sciezka_katalogu_otworz,nazwa_pliku_otworz,rozszerzenie_otworz;//do odczytu i zapisu plikow
        AnsiString rozszerzenie_zapisz,nazwa_pliku_zapisz,sciezka_zapisz;
        int W_ID_1;
        int anuluj;
        int licz_czas;
        void czyszczenie_struktur();
        unsigned int W_PD;
        __fastcall TKompresor(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TKompresor *Kompresor;
//---------------------------------------------------------------------------
#endif
