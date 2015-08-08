#ifndef TifoH
#define TifoH
//---------------------------------------------------------------------------
#endif

class Tifo{
friend class TEnviroment;
private:
    int *coordinates;
    int position_y;
    int width;
    int steps_per_time_vertical, steps_per_time_horizontal;
    int index;
public:
    Tifo();
    void Move(TEnviroment enviroment);
    void WrapAround(TEnviroment enviroment);
    void setInitialConditions();
    int GetCoordinates(int index);
    int GetPosition_y();
    int GetWidth();
    int GrtIndex();
    int GetVerticalSpeed();
    int GetHorizontalSpeed();
};