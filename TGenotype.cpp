#pragma hdrstop
#include <vcl.h>
#include <fstream.h>
#include <vector.h>
#include "math.h"
#include "TGenotype.h"
#include "FlatlandAgent.h"
#include "TNet.h"
#include "TMyAgent.h"
#include "TTool.h"
#include "TEnviroment.h"
#include "Tifo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
TGenotype::TGenotype(unsigned bits, unsigned weights, unsigned neurons, TNet myNet,  TEnviroment enviroment, TMyAgent platform, TTool tool, Tifo ifo){
    weight_bits = bits;
    num_Weights = weights;
    num_Neurons = neurons;
    gens = new int[ num_Weights * bits];
    gens_gain = new int[ num_Neurons * bits];
    gens_time_const = new int[ num_Neurons * bits];

    phenotypes = new double [ num_Weights];
    phenotypes_gain = new double [ num_Neurons];
    phenotypes_time_const = new double [ num_Neurons];
    for(int i = 0; i < weight_bits * num_Weights; i ++)
        gens[ i] = random(2);
    for(int i = 0; i < weight_bits * num_Neurons; i ++){
        gens_gain[ i] = random(2);
        gens_time_const[ i] = random(2);
    } 
    PhenotypeConvertion();
    FitnessEvaluation( myNet, enviroment, platform, tool, ifo);
}
//---------------------------------------------------------------------------
void TGenotype::PhenotypeConvertion(){
    double divisor, divisor1, divisor2;
    divisor = 0;

    for(unsigned i = 0; i < weight_bits; ++i)
        divisor += pow(2., i);
    divisor1 = divisor/10;
    divisor2 = divisor/4;
    for(int i = 0; i < num_Weights; ++i){
        phenotypes[ i] = 0;
        for(unsigned j = 0; j < weight_bits; ++j){
            phenotypes[ i] += double(gens[ i * weight_bits + j]) * pow(2., j);
        }
        phenotypes[ i] = phenotypes[ i] / divisor1 - 5;
    }
    for(int i = 0; i < num_Neurons; ++i){
        phenotypes_gain[ i] = 0;
        phenotypes_time_const[ i] = 0;
        for(unsigned j = 0; j < weight_bits; ++j){
            phenotypes_gain[ i] += double(gens_gain[ i * weight_bits + j]) * pow(2., j);
            phenotypes_time_const[ i] += double(gens_time_const[ i * weight_bits + j]) * pow(2., j);
        }
        phenotypes_gain[ i] = phenotypes_gain[ i] / divisor2 + 1;
        phenotypes_time_const[ i] = phenotypes_time_const[ i] / divisor + 1;
    }
}
//---------------------------------------------------------------------------
double TGenotype::Get_Phenotype(int index){
    return phenotypes[ index];
}
//---------------------------------------------------------------------------
double TGenotype::Get_Phenotype_Gain(int index){
    return phenotypes_gain[ index];
}
//---------------------------------------------------------------------------
double TGenotype::Get_Phenotype_T(int index){
    return phenotypes_time_const[ index];
}
//---------------------------------------------------------------------------
int TGenotype::Get_Gen(int index){
    return gens[index];
}
//---------------------------------------------------------------------------
int TGenotype::Get_Gen_Gain(int index){
    return gens_gain[index];
}
//---------------------------------------------------------------------------
int TGenotype::Get_Gen_T(int index){
    return gens_time_const[index];
}
//---------------------------------------------------------------------------
void TGenotype::Put_Gen(int index, int value){
    gens[ index] = value;
}
//---------------------------------------------------------------------------
void TGenotype::Put_Gen_Gain(int index, int value){
    gens_gain[ index] = value;
}
//---------------------------------------------------------------------------
void TGenotype::Put_Gen_T(int index, int value){
    gens_time_const[ index] = value;
}
//---------------------------------------------------------------------------
void TGenotype::FitnessEvaluation(TNet myNet, TEnviroment enviroment, TMyAgent platform, TTool tool, Tifo ifo){
    fitnes = 0; fitnes_temp = 0;
    int steps_per_time = 1;
    vector<double> inputVals;
    vector<double> resultVals;
    vector<double> Weights;
    vector<double> Gains;
    vector<double> T_consts;
    bool turn_left, turn_right;
    PhenotypeConvertion();
    for(unsigned i = 0; i < num_Weights; ++i)
        Weights.push_back(phenotypes[ i]);
    for(unsigned i = 0; i < num_Neurons; ++i){
        Gains.push_back(phenotypes_gain[ i]);
        T_consts.push_back(phenotypes_time_const[ i]);
    }
    myNet.setWeights(Weights);
    myNet.setGains(Gains);
    myNet.setTime_const(T_consts);
    for(int run = 0; run < (13+14*(Form1->steps-1)); ++run){
        tool.setInputValues(inputVals, platform, ifo);
        myNet.feedForward(inputVals);
        myNet.getResults(resultVals);
        tool.output(resultVals, turn_left, turn_right, steps_per_time);
        platform.Move(enviroment, turn_left, turn_right, steps_per_time);
        ifo.Move(enviroment);
        if(ifo.GetPosition_y() == 13)
            platform.FitnessUpdate(ifo);
    }  fitnes = platform.GetFitness();   fitnes_temp = platform.GetFitness();
    platform.setInitialConditions();
}
//---------------------------------------------------------------------------
float TGenotype::Get_Fitnes(){
    return fitnes;
}
//---------------------------------------------------------------------------
float TGenotype::Get_Fitnes_temp(){
    return fitnes_temp;
}
//---------------------------------------------------------------------------
void TGenotype::Scale_Fitnes(float value){
    fitnes_temp = value;
}
//---------------------------------------------------------------------------
int TGenotype::Get_weights_num(){
    return num_Weights;
}
//---------------------------------------------------------------------------
int TGenotype::Get_neurons_num(){
    return num_Neurons;
}
//---------------------------------------------------------------------------
int TGenotype::Get_bits_num(){
    return weight_bits;
}
//---------------------------------------------------------------------------
