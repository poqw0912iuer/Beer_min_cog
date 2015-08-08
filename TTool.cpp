#pragma hdrstop
#include "TTool.h"
#include <vector.h>
#include "TEnviroment.h"
#include "TMyAgent.h"
#include "Tifo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

void TTool::setInputValues(vector<double> &inputVals, TMyAgent agent, Tifo object)const{
    inputVals.clear();
    for(unsigned i = 0; i < agent.GetWidth(); ++i){
        unsigned shade = 0;
        for(unsigned j = 0; j < object.GetWidth() ; ++j)
            if(agent.GetCoordinates(i) == object.GetCoordinates(j))  shade += 1;
        if(shade > 0) inputVals.push_back(1.);
        else inputVals.push_back(0.);
    }
}
//---------------------------------------------------------------------------
void TTool::output(const vector<double> &resultVals, bool &turn_left, bool &turn_right, int &steps_per_time){
    turn_left = false;
    turn_right = false;
    steps_per_time = 1;
    if(resultVals[0] > 1.02*resultVals[1]){
        turn_left = true;
        if(resultVals[0] > 4*resultVals[1]) steps_per_time = 4;
        else if(resultVals[0] > 3*resultVals[1]) steps_per_time = 3;
        else if(resultVals[0] > 2*resultVals[1]) steps_per_time = 2;
    }
    else if(resultVals[1] > 1.02*resultVals[0]){
        turn_right = true;
        if(resultVals[1] > 4*resultVals[0]) steps_per_time = 4;
        else if(resultVals[1] > 3*resultVals[0]) steps_per_time = 3;
        else if(resultVals[1] > 2*resultVals[0]) steps_per_time = 2;
    }
}
//---------------------------------------------------------------------------