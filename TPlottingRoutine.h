#ifndef TPlottingRoutineH
#define TPlottingRoutineH
//---------------------------------------------------------------------------
class TPlottingRoutine{
friend class TGenotype;
friend class TForm1;
friend class TNet;
friend class TEnviroment;
friend class TMyAgent;
friend class TTool;
friend class Tifo;

public:
    void Record_Data(TGenotype **object, int population, int generation,
                     TNet myNet, TEnviroment enviroment, TMyAgent platofrm, TTool tool, Tifo ifo);
    void Plot(int generations);
};
#endif