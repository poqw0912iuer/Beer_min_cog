#pragma hdrstop
#include "Tifo.h"
#include <vcl.h>
#include "TEnviroment.h"
#include "FlatlandAgent.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

Tifo::Tifo(){
    width = random(6) + 1;
    steps_per_time_vertical = 1;
    steps_per_time_horizontal = 0;
    index = 0;
    position_y = 0;
    coordinates = new int[width];
    coordinates[0] = random(30);
    for(unsigned x = 1; x < width; ++x)
        if(coordinates[x - 1] >= 29) coordinates[x] = coordinates[x - 1] - 29;
        else coordinates[x] = coordinates[x - 1] + 1;
}
//---------------------------------------------------------------------------
void Tifo::setInitialConditions(){
    width = random(6) + 1;
    position_y = 0;
    coordinates[0] = random(30);
    for(unsigned x = 1; x < width; ++x)
        if(coordinates[x - 1] >= 29) coordinates[x] = coordinates[x - 1] - 29;
        else coordinates[x] = coordinates[x - 1] + 1;
    index += 1;
}
//---------------------------------------------------------------------------
void Tifo::Move(TEnviroment enviroment){
    if(position_y < 13){
        position_y += steps_per_time_vertical;
        //for(unsigned x = 0; x < width; ++x)
          //  coordinates[x] += steps_per_time_horizontal;
    }
    else setInitialConditions();
    //WrapAround(enviroment);
}
//---------------------------------------------------------------------------
void Tifo::WrapAround(TEnviroment enviroment){

    for(unsigned x = 0; x < width; ++x){
        if(coordinates[x] < 0)
            coordinates[x] = enviroment.GetWidth() - coordinates[x];
        else if(coordinates[width - x - 1] > enviroment.GetWidth() - 1)
            coordinates[width - x - 1] = coordinates[width - x - 1] - (enviroment.GetWidth() - 1) - 1;
    }
}
//---------------------------------------------------------------------------
int Tifo::GetCoordinates(int index){
    return coordinates[index];
}
//---------------------------------------------------------------------------
int Tifo::GetPosition_y(){
    return position_y;
}
//---------------------------------------------------------------------------
int Tifo::GetWidth(){
    return width;
}
//---------------------------------------------------------------------------
int Tifo::GrtIndex(){
    return index;
}
//---------------------------------------------------------------------------
int Tifo::GetVerticalSpeed(){
    return steps_per_time_vertical;
}
//---------------------------------------------------------------------------
int Tifo::GetHorizontalSpeed(){
    return steps_per_time_horizontal;
}
//---------------------------------------------------------------------------
