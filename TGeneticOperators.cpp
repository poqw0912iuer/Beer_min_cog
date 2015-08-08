#pragma hdrstop
#include <vcl.h>
#include "TGeneticOperators.h"
#include "TGenotype.h"
#include "TNet.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
void TGeneticOperators::Crossover(TGenotype **object, int probability, int population, TNet myNet){
    unsigned bits = object[0]->Get_bits_num();
    for(int i = 0; i < population; i += 2){
        for(int j = 0; j < object[0] -> Get_weights_num(); ++j){
            if(random(100) < probability){
                int cross_point = random(bits - 1);
                int temp;
                for(int k = 0; k <= cross_point; ++k){
                    temp = object[ i] -> Get_Gen(j * bits + k);
                    object[ i] -> Put_Gen(j * bits + k, object[ i + 1] -> Get_Gen(j * bits + k));
                    object[ i + 1] -> Put_Gen(j * bits + k, temp);
                }
            }
        }
    }
//*************** gains *******************
    for(int i = 0; i < population; i += 2){
        for(int j = 0; j < object[0] -> Get_neurons_num(); ++j){
            if(random(100) < probability){
                int cross_point = random(bits - 1);
                int temp;
                for(int k = 0; k <= cross_point; ++k){
                    temp = object[ i] -> Get_Gen_Gain(j * bits + k);
                    object[ i] -> Put_Gen_Gain(j * bits + k, object[ i + 1] -> Get_Gen_Gain(j * bits + k));
                    object[ i + 1] -> Put_Gen_Gain(j * bits + k, temp);
                }
            }
        }
    }
//*************** T constants *******************
    for(int i = 0; i < population; i += 2){
        for(int j = 0; j < object[0] -> Get_neurons_num(); ++j){
            if(random(100) < probability){
                int cross_point = random(bits - 1);
                int temp;
                for(int k = 0; k <= cross_point; ++k){
                    temp = object[ i] -> Get_Gen_T(j * bits + k);
                    object[ i] -> Put_Gen_T(j * bits + k, object[ i + 1] -> Get_Gen_T(j * bits + k));
                    object[ i + 1] -> Put_Gen_T(j * bits + k, temp);
                }
            }
        }
    }
}
//---------------------------------------------------------------------------
void TGeneticOperators::Mutation(TGenotype **object, int probability, int population, TNet myNet){
    unsigned bits = object[0]->Get_bits_num();
    for(int i = 0; i < population; i ++){
        for(int j = 0; j < object[0] -> Get_weights_num(); ++j){
            if(random(100) < probability){
                int mut_point = random(bits);
                switch(object[ i] -> Get_Gen(j * bits + mut_point)){
                    case 0:
                        object[ i] -> Put_Gen(mut_point, 1);
                        break;
                    case 1:
                        object[ i] -> Put_Gen(mut_point, 0);
                        break;
                }
            }
        }
    }
}
//---------------------------------------------------------------------------
