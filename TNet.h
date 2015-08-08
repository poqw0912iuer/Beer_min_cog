#ifndef TNetH
#define TNetH
#include <vector.h>
//---------------------------------------------------------------------------
#endif

struct Connection{
    double weight;
    double weight_recursive;
};


class Neuron;

typedef vector<Neuron> Layer;

//******************* class Neuron *******************
class Neuron{
private:
	//double transferFunction(double x);
	static double randomWeight(){ return 10 * rand()/double(RAND_MAX) - 5;}
        static double randomGain(){return 4 * rand()/double(RAND_MAX) + 1;}
        static double randomT(){return rand()/double(RAND_MAX) + 1;}
	double m_outputVal, m_outputVal_past;
	vector<Connection> m_outputWeights;
	unsigned m_myIndex, num_Outputs;
        double gain;
        double time_const;
        double y, dy, y_past;
public:
	Neuron (unsigned numOutputs, unsigned myIndex, unsigned neuronsInLayer);
	void setOutputVal(double val){ m_outputVal = val;}
        void setOutputValCRNN(double val);
        void setY_past(){y_past = y;}
        void set_m_outputVal_past(){m_outputVal_past = m_outputVal;}
        double transferFunction(double x);
        double get_m_outputVal_past(){return m_outputVal_past;}
	double getOutputVal() const { return m_outputVal;}
        double getY_past() const { return y_past;}
        double getGain() const { return gain;}
        double getTime_const() const { return time_const;}
	void feedForward(const Layer &prevLayer, const Layer &thisLayer);
        void getWeights(unsigned neuronsInLayer, vector<double> &Weights) const;
        void setWeights(unsigned &ind, unsigned neuronsInLayer, const vector<double> &Weights);
        void setGains(unsigned &ind, const vector<double> &Gains);
        void setTime_const(unsigned &ind, const vector<double> &Time_const);
};

//******************* class Net *******************
class TNet{
private:
	vector<Layer> m_layers;  //m_layers[layerNum][neuronNum]
public:
	TNet(const vector<unsigned> &topology);
	void feedForward(const vector<double> &inputVals);
	void getResults(vector<double> &resultVals) const;
        void getWeights(vector<double> &Weights) const;
        void getGains(vector<double> &Gains) const;
        void getTime_const(vector<double> &Time_const) const;
        void setWeights(const vector<double> &Weights);
        void setGains(const vector<double> &Gains);
        void setTime_const(const vector<double> &Time_const);
};
