#ifndef TEnviromentH
#define TEnviromentH
//---------------------------------------------------------------------------
#endif

class TEnviroment{
friend class TMyAgent;
friend class Tifo;
private:
    //int **grid;
    int width, height;
public:
    TEnviroment();
    /*void GridUpdate(TMyAgent agent, Tifo object);
    int GetItem(int x, int y); //*/
    int GetWidth();
    int GetHeight(); 
};