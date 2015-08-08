#ifndef TSelectionProtocolsH
#define TSelectionProtocolsH
//---------------------------------------------------------------------------
class TSelectionProtocols{
friend class TGenotype;
friend class TNet;
friend class TEnviroment;
friend class TMyAgent;
friend class TTool;
friend class Tifo;
public:
    void FullGenerationalReplacement(TGenotype **object, int populationint, int generations,
                                     int cross_probability, int mut_probability, int SelectionMechanismNr,
                                     TNet myNet, TEnviroment enviroment, TMyAgent platform, TTool tool, Tifo ifo);
    void OverProduction(TGenotype **object, int population, int generations, int cross_probability,
                                     int mut_probability, int SelectionMechanismNr,
                                     TNet myNet, TEnviroment enviroment, TMyAgent platform, TTool tool, Tifo ifo);
    void ChooseSelectionMechanism(int number, TGenotype **object, int population,
                                  TNet myNet, TEnviroment enviroment, TMyAgent platform, TTool tool, Tifo ifo);
};
#endif