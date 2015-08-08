#pragma hdrstop
#include <vcl.h>
#include "TMyAgent.h"
#include "TEnviroment.h"
#include "Tifo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

TMyAgent::TMyAgent(){
    width = 5;
    coordinates = new int[width];
    coordinates[0] = 0 + 1;
    for(unsigned x = 1; x < width; ++x)
        if(coordinates[x - 1] >= 29) coordinates[x] = coordinates[x - 1] - 29;
        else coordinates[x] = coordinates[x - 1] + 1;
    fitness = 0;
}
//---------------------------------------------------------------------------
void TMyAgent::setInitialConditions(){
    coordinates[0] = 0 + 1;
    for(unsigned x = 1; x < width; ++x)
        if(coordinates[x - 1] >= 29) coordinates[x] = coordinates[x - 1] - 29;
        else coordinates[x] = coordinates[x - 1] + 1;  //*/
    fitness = 0;
}
//---------------------------------------------------------------------------
void TMyAgent::Move(TEnviroment enviroment, bool go_left, bool go_right, int steps_per_time){
    if(go_left)
        for(int x = 0; x < width; ++x)
            coordinates[x] -= steps_per_time;
    else if(go_right)
        for(int x = 0; x < width; ++x)
            coordinates[x] += steps_per_time;
    else if(!go_left && !go_right)
        return;

    WrapAround(enviroment);
}
//---------------------------------------------------------------------------
void TMyAgent::WrapAround(TEnviroment enviroment){
    for(int x = 0; x < width; ++x){
        if(coordinates[x] < 0)
            coordinates[x] = enviroment.GetWidth() + coordinates[x];
        else if(coordinates[width - x - 1] > enviroment.GetWidth() - 1)
            coordinates[width - x - 1] = coordinates[width - x - 1] - (enviroment.GetWidth() - 1) - 1;
    }
}
//---------------------------------------------------------------------------
void TMyAgent::FitnessUpdate(Tifo object){
    if((object.GetWidth() < width) && (coordinates[0] <= object.GetCoordinates(0)) && (coordinates[width-1] >= object.GetCoordinates(object.GetWidth()-1)))
        fitness += 4.0;
    else if ((object.GetWidth() >= width) || (coordinates[0]<=object.GetCoordinates(object.GetWidth()-1))
             &&  (coordinates[width-1]>=object.GetCoordinates(0)))
        fitness -= 3.0;
    if(fitness < 0) fitness = 0.0;

    /*float plus = 4.0;
    float mins = 1.0;
    //*********** Sucess ************
    if((coordinates[0] < object.GetCoordinates(0)) && (coordinates[width-1] >= object.GetCoordinates(object.GetWidth()-1)))
        fitness += plus;
    else if((coordinates[0] <= object.GetCoordinates(0)) && (coordinates[width-1] > object.GetCoordinates(object.GetWidth()-1)))
        fitness += plus;
    //*********** Failure ***********
    else if ((object.GetWidth() >= width) && (coordinates[0]<=object.GetCoordinates(object.GetWidth()-1))
                                          && (coordinates[width-1]>=object.GetCoordinates(0)))
        fitness += mins;
    else if ((object.GetWidth() >= width) && (coordinates[0] > coordinates[width - 1])
                                          && (object.GetCoordinates(0) <= coordinates[width - 1]))
        fitness += mins;
    else if ((object.GetWidth() >= width) && (coordinates[0] > coordinates[width - 1])
                                          && (object.GetCoordinates(width - 1) >= coordinates[0]))
        fitness += mins;
    else if ((object.GetWidth() >= width) && (object.GetCoordinates(0) > object.GetCoordinates(width - 1))
                                          && (object.GetCoordinates(0) <= coordinates[width - 1]))
        fitness += mins;
    else if ((object.GetWidth() >= width) && (object.GetCoordinates(0) > object.GetCoordinates(width - 1))
                                          && (object.GetCoordinates(width - 1) >= coordinates[0]))   
        fitness += mins;  
    //*******************************
    if(fitness < 0) fitness = 0.0; //*/
}
//---------------------------------------------------------------------------
int TMyAgent::GetCoordinates(int index){
    return coordinates[index];
}
//---------------------------------------------------------------------------
float TMyAgent::GetFitness(){
    return fitness;
}
//---------------------------------------------------------------------------
int TMyAgent::GetWidth(){
    return width;
}
//---------------------------------------------------------------------------