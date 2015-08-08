#ifndef TSelectionMechanismsH
#define TSelectionMechanismsH
//---------------------------------------------------------------------------
class TSelectionMechanisms{
friend class TGenotype;
friend class TNet;
friend class TEnviroment;
friend class TMyAgent;
friend class TTool;
friend class Tifo;

private:
public:
    void FitnessProportionate(TGenotype **object, int population,
                              TNet myNet, TEnviroment enviroment, TMyAgent platform, TTool tool, Tifo ifo);
    void SigmaScaling(TGenotype **object, int population,
                      TNet myNet, TEnviroment enviroment, TMyAgent platform, TTool tool, Tifo ifo);
    void BoltzmannScaling(TGenotype **object, int population, double T,
                          TNet myNet, TEnviroment enviroment, TMyAgent platform, TTool tool, Tifo ifo);
    void RankSelection(TGenotype **object, int population, float Min,
                       TNet myNet, TEnviroment enviroment, TMyAgent platform, TTool tool, Tifo ifo);
    void Sort( TGenotype **object, int population);
    void RuletteWheel(TGenotype **object, int population,
                      TNet myNet, TEnviroment enviroment, TMyAgent platform, TTool tool, Tifo ifo);
};
#endif