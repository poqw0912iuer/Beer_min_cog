#ifndef TMyAgentH
#define TMyAgentH
//---------------------------------------------------------------------------
#endif

class TMyAgent{
friend class TEnviroment;
friend class Tifo;
private:
    int *coordinates;
    int width;
    float fitness;
public:
    TMyAgent();
    void setInitialConditions();
    void Move(TEnviroment enviroment, bool go_left, bool go_right, int steps_per_time);
    void WrapAround(TEnviroment enviroment);
    void FitnessUpdate(Tifo object);
    int GetCoordinates(int index);
    float GetFitness();
    int GetWidth();
};
