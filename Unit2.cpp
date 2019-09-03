//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#include "Unit1.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

Tpasek *pasek;
//---------------------------------------------------------------------------
__fastcall Tpasek::Tpasek(TComponent* Owner)   
        : TForm(Owner)
{
}

//---------------------------------------------------------------------------

void __fastcall Tpasek::anulujClick(TObject *Sender)
{
Kompresor->anuluj=1;
pasek->anuluj->Enabled=false;
}
//---------------------------------------------------------------------------



