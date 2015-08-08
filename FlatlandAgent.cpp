#include <vcl.h>
#include <fstream.h>
#pragma hdrstop
#include "math.h"
#include <vector.h>
#include <cassert>
#include "FlatlandAgent.h"
#include "TNet.h"
#include "TPlottingRoutine.h"
#include "TGenotype.h"
#include "TGeneticOperators.h"
#include "TSelectionMechanisms.h"
#include "TSelectionProtocols.h"
#include "TEnviroment.h"
#include "Tifo.h"
#include "TMyAgent.h"
#include "TTool.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1 *Form1;
TGenotype **Adult;// **Child;
TGeneticOperators GA_Operator;
TSelectionMechanisms SelectionMechanism;
TPlottingRoutine GrphTool;
TSelectionProtocols SelectionProtocol;
////////
TTool tool_2;
////////
TShape *myPlatform[5];
TShape *myIfo[6];
TShape *Boundary;
bool trained = false; unsigned interval;
int click_count = 0;
int w = 30;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{   interval = 15;
    TrackBar1->Position = interval;
    turn_right = false; turn_left = false; steps_per_time = 1;
    steps = Edit9 -> Text.ToInt();
    weight_bits = 8;// num_Weights = 21;//33;
    DoubleBuffered = true;          Label2->Caption=26%13;
    SelectionMechanismNr = 1;
    Label3->Caption = "Fitnes = ";
    Label4->Caption = "Scenario no. ";
}
//---------------------------------------------------------------------------
void saveWeights(const vector<double> &Vector, unsigned type){
    std::ofstream myStream;
    if(type == 0)  myStream.open( "Weights.txt", std::ios::out );
    else if(type == 1)   myStream.open( "Gains.txt", std::ios::out );
    else if(type == 2)   myStream.open( "T_const.txt", std::ios::out );
    else   MessageBox( NULL, "This file does not exist!", "EA_Basic", MB_OK);

    if( myStream.good() == true ){
        myStream << Vector.size() << "\n";
        for(unsigned i = 0; i < Vector.size(); ++i)
            myStream << Vector[i] << "\n";
    }
}
//---------------------------------------------------------------------------
void loadWeights(const vector<double> &Vector, unsigned type){
    Vector.clear();
    std::ifstream myStream;
    if(type == 0)  myStream.open( "Weights.txt", std::ios::in );
    else if(type == 1)   myStream.open( "Gains.txt", std::ios::in );
    else if(type == 2)   myStream.open( "T_const.txt", std::ios::in );
    else   MessageBox( NULL, "This file does not exist!", "EA_Basic", MB_OK);

    if( myStream.good() == true ){
        unsigned size;
        myStream >> size;
        double value;
        for(unsigned i = 0; i < size; ++i){
            myStream >> value;
            Vector.push_back(value);
        }
    }
}
//---------------------------------------------------------------------------
void AgentDef(TShape **myShapes, TMyAgent platform){
    for(int i = 0; i < platform.GetWidth(); ++i){
        myShapes[i]->SendToBack();
        myShapes[i]->Brush->Color = clWhite;
        myShapes[i]->Pen->Color = clRed;  myShapes[i]->Pen->Width = 2;
        myShapes[i]->Top = 620;
        myShapes[i]->Left = w + 5 + platform.GetCoordinates(i) * w;
        myShapes[i]->Width = w;
        myShapes[i]->Height = w;
        myShapes[i]->Shape = stRectangle;
        Boundary->SendToBack();
    }
}
//---------------------------------------------------------------------------
void ObjectDef(TShape **myShapes, Tifo ifo){
    for(int i = 0; i < ifo.GetWidth(); ++i){
        myShapes[i]->SendToBack();
        myShapes[i]->Brush->Color = clWhite;
        myShapes[i]->Pen->Color = clBlue;   myShapes[i]->Pen->Width = 2;
        myShapes[i]->Top = 200 + ifo.GetPosition_y() * w;
        myShapes[i]->Left = w + 5 + ifo.GetCoordinates(i) * w;
        myShapes[i]->Width = w;
        myShapes[i]->Height = w;
        myShapes[i]->Shape = stRectangle;
        Boundary->SendToBack();
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
    steps = Edit9 -> Text.ToInt();
    Label3->Caption= "Fitnes = 0";
    TEnviroment enviroment;
    TMyAgent platform;
    Tifo ifo;
    float overall_performance = 0;
    //****Net****
    vector<unsigned> topology;
    topology.push_back(5);
    topology.push_back(2);
    topology.push_back(2);
    TNet myNet(topology);
    vector<double> Weights;  vector<double> Gains; vector<double> T_const;
    loadWeights(Weights, 0); loadWeights(Gains, 1); loadWeights(T_const, 2);
    myNet.setWeights(Weights);
    myNet.setGains(Gains);
    myNet.setTime_const(T_const);

    vector<double> inputVals;
    vector<double> resultVals;
    //***********
    if(click_count){
        for(int i = 0; i < temp_size; ++i) delete myIfo[i];
        for(int i = 0; i < 5; ++i) delete myPlatform[i];
        delete Boundary;
    }
    click_count ++;

    int previous_x[5];
    for(int i = 0; i < platform.GetWidth(); ++i)  previous_x[i] = platform.GetCoordinates(i);
    int previous_y = ifo.GetPosition_y();
    //***Boundaries***
    Boundary = new TShape(this);
    Boundary->Parent=Form1;
    Boundary->Visible=true;            Boundary->SendToBack();
    Boundary->Pen->Color = clBlack;    Boundary->Pen->Width = w;
    Boundary->Top = 170;               Boundary->Left = 5 ;
    Boundary->Width = 960;             Boundary->Height = 510;
    Boundary->Shape = stRectangle;

    //******Agent******
    for (int i = 0; i < 5; i++) {
        myPlatform[i] = new TShape(this);
        myPlatform[i]->Parent = Form1;
        myPlatform[i]->Visible = true;
    }
    AgentDef(myPlatform, platform);
    //*****object*****
        temp_size = ifo.GetWidth();
    for (int i = 0; i < temp_size; i++) {
        myIfo[i] = new TShape(this);
        myIfo[i]->Parent = Form1;
        myIfo[i]->Visible = true;
    }
    ObjectDef(myIfo, ifo);
    for(int i = 0; i < 13 + (steps - 1) * 14; ++i){
        if(i <= 14 && i%13==0)  Label4->Caption = "Run no. " + IntToStr(i/13);
        else if ((i+1)%14==0) Label4->Caption = "Run no. " + IntToStr((i+1)/14);
        tool_2.setInputValues(inputVals, platform, ifo);
        myNet.feedForward(inputVals);
        myNet.getResults(resultVals);
        //for(int t = 0; t < resultVals.size(); ++t)
          //  StringGrid1->Cells[1 + t][1 + i] = resultVals[t];
        tool_2.output(resultVals, turn_left, turn_right, steps_per_time);
        platform.Move(enviroment, turn_left, turn_right, steps_per_time);
        ifo.Move(enviroment);
        //********shadows********
        for(unsigned i = 0; i < platform.GetWidth(); ++i){
            unsigned shade = 0;
            for(unsigned j = 0; j < ifo.GetWidth() ; ++j)
                if(platform.GetCoordinates(i) == ifo.GetCoordinates(j))  shade += 1;
            if(shade > 0) myPlatform[i]->Brush->Color = clGray;
            else myPlatform[i]->Brush->Color = clWhite;
        }
        //*******************************************
       // for(int t = 0; t < 5; ++t)
         //   StringGrid1->Cells[t + 1][i + 1] = inputVals[t];
        //************* New falling oject ******************
        if(ifo.GetPosition_y() == 0){
            for(int no = 0; no < temp_size; ++no)
                delete myIfo[no];
            previous_y = 0;
            temp_size = ifo.GetWidth();
            for(int no = 0; no < temp_size; ++no){
                myIfo[no] = new TShape(this);
                myIfo[no]->Parent = Form1;
                myIfo[no]->Visible = true;
            }
            ObjectDef(myIfo, ifo);
        }
        //*********** Fitness update ****************
        if(ifo.GetPosition_y() == 13){
            platform.FitnessUpdate(ifo);
            Label3->Caption= "Fitnes = " + FloatToStr(platform.GetFitness());
        }
        //*******************************************
        for(int k = 0; k < w; ++k){
            for(int j = 0; j < platform.GetWidth(); ++j){
                //********** 1st condition **********
                if((previous_x[j] - platform.GetCoordinates(j)) > 4)
                    if(k*(4) < (29 - previous_x[j]) * w)
                        myPlatform[j]->Left = w + 5 + previous_x[j]*w + (29-previous_x[j]+platform.GetCoordinates(j)+1) * k;
                    else
                        myPlatform[j]->Left = w + 5 - (29-previous_x[j])*w + (29-previous_x[j]+platform.GetCoordinates(j)+1) * k;
                //********** 2nd condition **********
                else if((platform.GetCoordinates(j) - previous_x[j] > 4))
                    if(k*(4) < (previous_x[j])*w)
                        myPlatform[j]->Left = w + 5 + previous_x[j]*w - (29-platform.GetCoordinates(j) + previous_x[j] + 1) * k;
                    else
                        myPlatform[j]->Left=935+previous_x[j]*w-(29-platform.GetCoordinates(j) + previous_x[j] + 1) * k;
                //********** 3rd condition **********
                else myPlatform[j]->Left = w + 5 + previous_x[j]*w+(platform.GetCoordinates(j)-previous_x[j])*k;
            }
            for(int j= 0; j < ifo.GetWidth(); ++j)
                myIfo[j]->Top = 200 +  previous_y*w+(ifo.GetPosition_y()-previous_y)*k; 
            Sleep(interval);
            Application->ProcessMessages();
        }                                                                       
        for(int j = 0; j < platform.GetWidth(); ++j) previous_x[j] = platform.GetCoordinates(j);
        previous_y = ifo.GetPosition_y();
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{    
    Randomize();
    population = Edit2 -> Text.ToInt();
    if(population % 2 )   MessageBox( NULL, "Type in even number of population!", "EA_Basic", MB_OK);
    else if((population < 4))   MessageBox( NULL, "Type in at least 4", "EA_Basic", MB_OK);
    else{
        population = Edit2 -> Text.ToInt();
        steps = Edit9 -> Text.ToInt();
        generations = Edit8->Text.ToInt();
        cross_probability = 100 * Edit3 -> Text.ToDouble();
        mut_probability = 100 * Edit4 -> Text.ToDouble();
        max = new float[ generations];
        average = new float[ generations];
        st_dew = new float[ generations];

        TEnviroment enviroment;
        TMyAgent platform;
        Tifo ifo;
        //****Net Beigin*****
        num_Weights = 22;  //
        vector<unsigned> topology;
        topology.push_back(5);
        topology.push_back(2);
        topology.push_back(2);
        TNet myNet(topology);
        //****Net End*****
        num_Neurons = 0;
        //for(unsigned i = 0; i < topology.size(); ++i)
            num_Neurons = 9;//+= int(topology[i]);
        best_genotype = new TGenotype(weight_bits, num_Weights, num_Neurons, myNet, enviroment, platform, tool_2, ifo);
        Adult = new TGenotype*[population];
        for(int i = 0; i < population; i ++)
            Adult[ i] = new TGenotype(weight_bits, num_Weights, num_Neurons, myNet, enviroment, platform, tool_2, ifo);
        GrphTool.Record_Data(Adult, population, 0, myNet, enviroment, platform, tool_2, ifo);

        if(RadioButton6 -> Checked == true){
            SelectionProtocol.FullGenerationalReplacement(Adult, population, generations,
                             cross_probability, mut_probability, SelectionMechanismNr,
                             myNet, enviroment, platform, tool_2, ifo);
        }
        else if(RadioButton7 -> Checked == true){
            SelectionProtocol.OverProduction(Adult, population, generations, cross_probability,
                                             mut_probability, SelectionMechanismNr, myNet, enviroment, platform, tool_2, ifo);
        } //*/
        //********** Save Weights **********
        vector<double> Weights;
        for(unsigned i = 0; i < best_genotype->Get_weights_num(); ++i)
            Weights.push_back(best_genotype->Get_Phenotype(i));
        saveWeights(Weights, 0);
        //********** Save Gains **********
        vector<double> Gains;
        for(unsigned i = 0; i < best_genotype->Get_neurons_num(); ++i)
            Gains.push_back(best_genotype->Get_Phenotype_Gain(i));
        saveWeights(Gains, 1);
        //********** T_const **********
        vector<double> T_const;
        for(unsigned i = 0; i < best_genotype->Get_neurons_num(); ++i)
            T_const.push_back(best_genotype->Get_Phenotype_T(i));
        saveWeights(T_const, 2);
        //***************************
        Button5->Enabled=true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button5Click(TObject *Sender)
{
    GrphTool.Plot(generations);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RadioButton2Click(TObject *Sender)
{
    Edit5 -> Enabled = false;
    SelectionMechanismNr = 1;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RadioButton3Click(TObject *Sender)
{
    Edit5 -> Enabled = true;
    SelectionMechanismNr = 2;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RadioButton4Click(TObject *Sender)
{
    Edit5 -> Enabled = false;
    SelectionMechanismNr = 3;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RadioButton1Click(TObject *Sender)
{
    Edit5 -> Enabled = false;
    SelectionMechanismNr = 10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TrackBar1Change(TObject *Sender)
{
    interval = TrackBar1->Position;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button1Click(TObject *Sender){

    vector<unsigned> topology;
    topology.push_back(5);
    topology.push_back(2);
    topology.push_back(2);
    TNet myNet(topology);
    vector<double> inputVals;
    vector<double> resultVals;
    for(int i = 0; i < 5; ++i)
        inputVals.push_back(1.);
    for(int i = 0; i < 20; ++i)
        myNet.feedForward(inputVals);
    myNet.getResults(resultVals);
    vector<double> Weights;
    for(int i = 0; i < 22; ++i) Weights.push_back(i);
   // myNet.setWeights(Weights);
    vector<double> W;
    myNet.getWeights(W);
    for(int i = 0; i < W.size(); ++i){
        StringGrid1->Cells[1][1 + i] = Weights[i];
        StringGrid1->Cells[2][1 + i] = W[i];
    }

    /*vector<double> Gains; vector<double> T;
    for(int i = 0; i < 9; ++i){ Gains.push_back(22); T.push_back(44);}
    myNet.setGains(Gains); myNet.setTime_const(T);
    loadWeights(Weights, 0); //loadWeights(Gains, 1); loadWeights(T, 2);
    myNet.getGains(Gains);
    for(int i=0; i<Weights.size(); ++i)  StringGrid1->Cells[1][1+i] = Weights[i];
    for(int i=0; i<Gains.size(); ++i)  StringGrid1->Cells[2][1+i] = Gains[i];
    for(int i=0; i<T.size(); ++i)  StringGrid1->Cells[3][1+i] = T[i];  //*/


    //StringGrid1->Cells[1][1] = resultVals[0]; StringGrid1->Cells[1][2] = resultVals[1];
    //StringGrid1->Cells[1][0] = Weights.size();
    //for(int i = 0; i < Weights.size() ; ++i)
      //  StringGrid1->Cells[1][i+1] = Weights[i];
     /*
    vector<double> T;
    for(int i = 0; i < 9; ++i)
        T.push_back(i);
    //myNet.setTime_const(T);
    vector<double> T_2;
    myNet.getTime_const(T_2);
    for(int t = 0; t < T.size() ; ++t){
        StringGrid1->Cells[1][2 + t] = T[t];
        StringGrid1->Cells[2][2 + t] = T_2[t];
    }
    StringGrid1->Cells[1][1 ] = T.size();  StringGrid1->Cells[2][1] = T_2.size();    //*/

}
//---------------------------------------------------------------------------

