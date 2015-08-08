#pragma hdrstop
#include <vcl.h>
#include <math.h>
#include "TSelectionMechanisms.h"
#include "TGenotype.h"
#include "TNet.h"
#include "TEnviroment.h"
#include "TMyAgent.h"
#include "TTool.h"
#include "Tifo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
void TSelectionMechanisms::FitnessProportionate(TGenotype **object, int population,
                                                TNet myNet, TEnviroment enviroment, TMyAgent platform, TTool tool, Tifo ifo){
    RuletteWheel(object, population, myNet, enviroment, platform, tool, ifo);
}
//---------------------------------------------------------------------------
void TSelectionMechanisms::SigmaScaling(TGenotype **object, int population,
                                        TNet myNet, TEnviroment enviroment, TMyAgent platform, TTool tool, Tifo ifo){
    float sum = 0;
    for(int i = 0; i < population; i ++)
        sum += object[ i] -> Get_Fitnes();
    float average = (float)sum / (float)population;
    float st_dew = 0;
    for(int i = 0; i < population; i ++)
        st_dew += pow((object[ i] -> Get_Fitnes() - (float)average), 2);
    st_dew = pow(st_dew / (population - 1), 0.5);
   
    float ExpVal;
    if(st_dew)
        for(int i = 0; i < population; i ++){
            ExpVal = 1. + (object[i] -> Get_Fitnes() - (float)average) / ( 2 * st_dew);
            if(ExpVal <= 0) object[ i] -> Scale_Fitnes(0);
            else object[ i] -> Scale_Fitnes(ExpVal);
        }
    RuletteWheel(object, population,  myNet, enviroment, platform, tool, ifo);
}
//---------------------------------------------------------------------------
void TSelectionMechanisms::BoltzmannScaling(TGenotype **object, int population, double T,
                                            TNet myNet, TEnviroment enviroment, TMyAgent platform, TTool tool, Tifo ifo){
    float sum = 0;
    for(int i = 0; i < population; i++)
        sum += exp(object[ i] -> Get_Fitnes() / T);
    float average = sum / population;
    float ExpVal;
    for(int i = 0; i < population; i ++){
        ExpVal = exp(object[ i] -> Get_Fitnes() / T) / average;
        object[ i] -> Scale_Fitnes(ExpVal);
    }
    RuletteWheel(object, population, myNet, enviroment, platform, tool, ifo);
}
//---------------------------------------------------------------------------
void TSelectionMechanisms::RankSelection(TGenotype **object, int population, float Min,
                                         TNet myNet, TEnviroment enviroment, TMyAgent platform, TTool tool, Tifo ifo){
    float Max = 2 - Min;
    Sort(object, population);
    float ExpVal;
    for(int i = 0; i < population; i ++){
        ExpVal = Min + (Max - Min) * ((i + 1) - 1) / (population - 1);
        object[ i] -> Scale_Fitnes(ExpVal);
    }
    RuletteWheel(object, population, myNet, enviroment, platform, tool, ifo);
}
//---------------------------------------------------------------------------
void TSelectionMechanisms::Sort( TGenotype **object, int population){
    for(int i = 1; i < population; i ++){
        int j = i;
        TGenotype *temp = object[j];
        int temp_fitnes_value = object[j]->Get_Fitnes();
        while(( j > 0) && ( object[ j - 1]-> Get_Fitnes() > temp_fitnes_value)){
            object[ j] = object[ j - 1];
            j --;
        }
        object[ j] = temp;
    }
}
//---------------------------------------------------------------------------
void TSelectionMechanisms::RuletteWheel(TGenotype **object, int population,
                                        TNet myNet, TEnviroment enviroment, TMyAgent platform, TTool tool, Tifo ifo){
    float sum = 0;
    for(int i = 0; i < population; i++)
        sum += object[ i] -> Get_Fitnes_temp();
    float *treshold = new float[ population];
    treshold[ 0] = object[ 0] -> Get_Fitnes_temp();
    for(int i = 1; i < population; i ++)
        treshold[ i] = treshold[ i - 1] + object[ i] -> Get_Fitnes_temp();
    float rand;
    int *rank = new int[population];
    for(int i = 0; i < population; i ++){
        rand = random(sum * 1000) / 1000.;
        if(rand <= treshold[ 0])
            rank[ i] = 0;
        else for(int j = 1; j < population; j ++)
            if(rand > treshold[ j - 1] && rand <= treshold[ j])
                rank[ i] = j;
    }
    TGenotype **supplementary_pool = new TGenotype*[population];
    for(int i = 0; i < population; i ++){
        supplementary_pool[ i] = new TGenotype(object[ 0] -> Get_bits_num(), object[ 0]->Get_weights_num(), object[0]->Get_neurons_num() , myNet, enviroment, platform, tool, ifo);
        for(int j = 0; j < object[ 0] -> Get_weights_num() * object[ 0] -> Get_bits_num(); j ++)
            supplementary_pool[ i] -> Put_Gen(j, object[ i] -> Get_Gen(j));
    }
    for(int i = 0; i < population; i ++){
        for(int j = 0; j < object[ 0] -> Get_weights_num() * object[ 0] -> Get_bits_num(); j ++)
            object[ i]->Put_Gen(j, supplementary_pool[rank[ i]]->Get_Gen(j) );
    }
    //for(int i = 0; i < population; i ++)
      //  object[ i] -> FitnessEvaluation(myNet, enviroment, platform, tool, ifo);
}
//---------------------------------------------------------------------------