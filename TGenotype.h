#ifndef TGenotypeH
#define TGenotypeH
#include <vector.h>
//---------------------------------------------------------------------------
class TGenotype{
friend class TForm1;
friend class TNet;
friend class TTool;
friend class TEnviroment;
friend class TMyAgent;
friend class Tifo;
private:
    int *gens; int *gens_gain; int *gens_time_const;
    double *phenotypes;  double *phenotypes_gain;  double *phenotypes_time_const;
    int weight_bits, num_Weights, num_Neurons;
    float fitnes, fitnes_temp;
public:
    TGenotype(unsigned bits, unsigned weights, unsigned neurons, TNet myNet, TEnviroment enviroment, TMyAgent platform, TTool tool, Tifo ifo);
    void PhenotypeConvertion();
    double Get_Phenotype(int index);
    double Get_Phenotype_Gain(int index);
    double Get_Phenotype_T(int index);
    int Get_Gen(int index);
    int Get_Gen_Gain(int index);
    int Get_Gen_T(int index);
    void Put_Gen(int index, int value);
    void Put_Gen_Gain(int index, int value);
    void Put_Gen_T(int index, int value);
    void FitnessEvaluation(TNet myNet, TEnviroment enviroment, TMyAgent platofrm, TTool tool, Tifo ifo);
    float Get_Fitnes();
    float Get_Fitnes_temp();
    void Scale_Fitnes(float value);
    int Get_weights_num();
    int Get_neurons_num();
    int Get_bits_num();
};
#endif