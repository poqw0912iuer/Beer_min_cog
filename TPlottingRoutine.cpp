#pragma hdrstop
#include <vcl.h>
#include <math.h>
#include "Unit2.h"
#include "TPlottingRoutine.h"
#include "TGenotype.h"
#include "FlatlandAgent.h"
#include "TNet.h"
#include "TEnviroment.h"
#include "TMyAgent.h"
#include "TTool.h"
#include "Tifo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
void TPlottingRoutine::Record_Data(TGenotype **object, int population, int generation,
                                   TNet myNet, TEnviroment enviroment, TMyAgent platform, TTool tool, Tifo ifo){
    float sum = 0;
    for(int i = 0; i < population; i ++)
        sum += object[ i] -> Get_Fitnes();
    Form1->average[ generation] = (float)sum / (float)population;
    Form1->st_dew[ generation] = 0;
    for(int i = 0; i < population; i ++)
        Form1->st_dew[ generation] += pow((object[ i] -> Get_Fitnes() - (float)Form1->average[ generation]), 2);
    Form1->st_dew[ generation] = pow(Form1->st_dew[ generation] / (population - 1), 0.5);

    Form1->max[ generation] = -1e6;
    for(int i = 0; i < population; i ++){
        if(object[ i]->Get_Fitnes() > Form1->max[ generation]){
            Form1->max[ generation] = object[ i] -> Get_Fitnes();
            if(Form1->max[ generation] > Form1->max[ generation - 1]){
                for(int n = 0; n < object[ 0]->Get_weights_num() * object[ 0]->Get_bits_num() ; n ++)
                    Form1->best_genotype->Put_Gen(n, object[ i]->Get_Gen(n));
                for(int n = 0; n < object[ 0]->Get_neurons_num() * object[ 0]->Get_bits_num() ; n ++){
                    Form1->best_genotype->Put_Gen_Gain(n, object[ i]->Get_Gen_Gain(n));
                    Form1->best_genotype->Put_Gen_T(n, object[ i]->Get_Gen_T(n));
                }
                Form1->generation = generation;
            }
            Form1->best_genotype->FitnessEvaluation(myNet, enviroment, platform, tool, ifo);
        }
    }
    for(int i = 1; i < population; i ++)
        if(Form1->max[ generation - 1] > Form1->max[ generation])
            Form1->max[ generation] = Form1->max[ generation - 1];
}
//---------------------------------------------------------------------------
void TPlottingRoutine::Plot(int generations){
    Form2->Show();
    int width = Form2->PaintBox1->Width;
    int height = Form2->PaintBox1->Height;
    Form2 -> PaintBox1 -> Canvas -> Brush -> Color = clWhite;
    Form2 -> PaintBox1 -> Canvas -> Rectangle(0, 0, width, height);
    float peak = -1e6;
    for(int i = 0; i < generations; i ++)
        if(Form1->max[ i] > peak)
            peak = Form1->max[ i];
    Form2->PaintBox1->Canvas->MoveTo(0, height-40);  Form2->PaintBox1->Canvas->LineTo(width, height-40);
    Form2->PaintBox1->Canvas->MoveTo(40, height);    Form2->PaintBox1->Canvas->LineTo(40, 0);
    Form2->PaintBox1->Canvas->Pen->Style = psDot;
    Form2->PaintBox1->Canvas->Pen->Color = cl3DDkShadow;
    Form2->PaintBox1->Canvas->MoveTo(40+(width-30)*Form1->generation/generations, height-40);
    Form2->PaintBox1->Canvas->LineTo(40+(width-30)*Form1->generation/generations, (height-40)-Form1->max[ generations - 1]*(height-40)/(1.1*peak));
    Form2->PaintBox1->Canvas->MoveTo(40, (height-40)-Form1->max[ generations - 1]*(height-40)/(1.1*peak));
    Form2->PaintBox1->Canvas->LineTo(width, (height-40)-Form1->max[ generations - 1]*(height-40)/(1.1*peak));
    Form2->PaintBox1->Canvas->Pen->Style = psSolid;
    Form2->PaintBox1->Canvas->MoveTo(40, (height-40)-Form1->max[ 0]*(height-40)/(1.1*peak));
    Form2->PaintBox1->Canvas -> Pen -> Color = clBlue;
    for(int i = 1; i < generations; i ++)
        Form2->PaintBox1->Canvas->LineTo(40+i*(width-40)/(generations-1), (height-40)-Form1->max[ i]*(height-40)/(1.1*peak));
    Form2->PaintBox1->Canvas->MoveTo(40, (height-40)-Form1->average[ 0]*(height-40)/(1.1*peak));
    Form2->PaintBox1->Canvas -> Pen -> Color = clLime;
    for(int i = 1; i < generations; i ++)
        Form2->PaintBox1->Canvas->LineTo(40+i*(width-40)/(generations-1), (height-40)-Form1->average[ i]*(height-40)/(1.1*peak));
    Form2->PaintBox1->Canvas->MoveTo(40, (height-40)-Form1->st_dew[ 0]*(height-40)/(1.1*peak));
    Form2->PaintBox1->Canvas -> Pen -> Color = clRed;
    for(int i = 1; i < generations; i ++)
        Form2->PaintBox1->Canvas->LineTo(40+i*(width-40)/(generations-1), (height-40)-Form1->st_dew[i]*(height-40)/(1.1*peak));
    Form2->PaintBox1->Canvas -> Pen -> Color = clBlack;
    Form2->PaintBox1->Canvas->Font->Name = "Arial";
    Form2->PaintBox1->Canvas->Font->Size = 10;
    Form2->PaintBox1->Canvas->TextOut(40+(width-30)*Form1->generation/generations, height - 60, AnsiString(Form1->generation));
    Form2->PaintBox1->Canvas->TextOut( 45, 5, "Fitnes");
    Form2->PaintBox1->Canvas->TextOut( 20, 24, AnsiString(Form1->max[generations - 1]));
    Form2->PaintBox1->Canvas->TextOut( width / 2, height - 30, "Generation");
    Form2->PaintBox1->Canvas->TextOut( 45, height - 35, 0);
    Form2->PaintBox1->Canvas->TextOut( 30, height - 60, 0);
    Form2->PaintBox1->Canvas->TextOut( 0.95*width, height - 35, generations);
    Form2->PaintBox1->Canvas->Rectangle(0.86*width, height - 303, 0.99*width, height - 240);
    Form2->PaintBox1->Canvas -> Pen -> Color = clBlue;
    Form2->PaintBox1->Canvas->MoveTo(0.88*width, height - 290);
    Form2->PaintBox1->Canvas->LineTo(0.92*width, height - 290);
    Form2->PaintBox1->Canvas -> Pen -> Color = clLime;
    Form2->PaintBox1->Canvas->MoveTo(0.88*width, height - 270);
    Form2->PaintBox1->Canvas->LineTo(0.92*width, height - 270);
    Form2->PaintBox1->Canvas -> Pen -> Color = clRed;
    Form2->PaintBox1->Canvas->MoveTo(0.88*width, height - 250);
    Form2->PaintBox1->Canvas->LineTo(0.92*width, height - 250);
    Form2->PaintBox1->Canvas->TextOut( 0.93*width, height - 300, "Max");
    Form2->PaintBox1->Canvas->TextOut( 0.93*width, height - 280, "Avg");
    Form2->PaintBox1->Canvas->TextOut( 0.93*width, height - 260, "StDev");
    Form2->PaintBox1->Canvas->Font->Style = TFontStyles()<< fsBold;
    Form2->PaintBox1->Canvas->TextOut( 0.44 * width, 5, "Fitness Progression");
    Form2->PaintBox1->Canvas -> Pen -> Color = clBlack;
    Form2->PaintBox1->Canvas->Font->Style = TFontStyles()>> fsBold;
}
//---------------------------------------------------------------------------