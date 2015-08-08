#include <vcl.h>
#pragma hdrstop
#include "Unit2.h"
#include "TPlottingRoutine.h"
#include "FlatlandAgent.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPlottingRoutine GrphTool;
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::PaintBox1Paint(TObject *Sender)
{
    GrphTool.Plot(Form1->generations);
}
//---------------------------------------------------------------------------

