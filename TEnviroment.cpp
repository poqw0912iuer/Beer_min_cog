#pragma hdrstop
#include <vcl.h>
#include "TEnviroment.h"
#include "TMyAgent.h"
#include "Tifo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
                       
TEnviroment::TEnviroment(){
    width = 30;
    height = 15;
    /*grid = new int*[width];
    for(int i = 0; i < width; i ++)
        grid[i] = new int[height];//*/
}
//---------------------------------------------------------------------------
/*void TEnviroment::GridUpdate(TMyAgent agent, Tifo object){
    for(int x = 0; x < width; ++x)
        for(int y = 0; y < height; ++y)
            grid[x][y] = 0;
    for(int x = object.GetCoordinates(0); x < object.GetCoordinates(0) + object.GetWidth(); ++x)
        grid[x][x] = 2;
    for(int x = agent.GetCoordinates(0); x < agent.GetCoordinates(0) + agent.GetWidth(); ++x)
        grid[x][x]=1;  
}  //*/
//---------------------------------------------------------------------------
/*int TEnviroment::GetItem(int x, int y){
    return grid[x][y];
} //*/
//---------------------------------------------------------------------------
int TEnviroment::GetWidth(){
    return width;
}
//---------------------------------------------------------------------------
int TEnviroment::GetHeight(){
    return height;
}                                                     
//---------------------------------------------------------------------------     */