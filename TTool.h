#ifndef TToolH
#define TToolH
#include <vector.h>
//---------------------------------------------------------------------------
#endif

class TTool{
friend class TEnviroment;
friend class TMyAgent;
friend class Tifo;
public:
    void setInputValues(vector<double> &inputVals, TMyAgent agent, Tifo object) const;
    void output(const vector<double> &resultVals, bool &turn_left, bool &turn_right, int &steps_per_time);
};