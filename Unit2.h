//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class Tpasek : public TForm
{
__published:	// IDE-managed Components
        TButton *anuluj;
        TStaticText *zadanie;
        TProgressBar *pasek_1;
        TStaticText *c_zadanie;
        TStaticText *uplynelo;
        TStaticText *ratio;
        TLabel *wspolczynnik;
        TLabel *uplynel;
        TStaticText *koniec_za;
        TLabel *koniec_z;
        
        void __fastcall anulujClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall Tpasek(TComponent* Owner); 
};
//---------------------------------------------------------------------------
extern PACKAGE Tpasek *pasek;
//---------------------------------------------------------------------------
#endif
