#ifndef TGeneticOperatorsH
#define TGeneticOperatorsH
//---------------------------------------------------------------------------
class TGeneticOperators{
friend class TGenotype;
friend class TNet;
public:
    void Crossover(TGenotype **object,  int probability, int population, TNet myNet);
    void Mutation(TGenotype **object, int probability, int population, TNet myNet);
};
#endif
