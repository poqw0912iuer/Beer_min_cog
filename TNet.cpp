#pragma hdrstop
#include "TNet.h"
#include <math.h>
#include <vector.h>
#include <cassert>

//---------------------------------------------------------------------------
#pragma package(smart_init)

//******************* class Neuron *******************
Neuron::Neuron(unsigned numOutputs, unsigned myIndex, unsigned neuronsInLayer){
    // Sum the previous layer's outputs (which are our inputs)
    // Include the bias node from the prevoius layer
    for(unsigned c = 0; c < numOutputs; c ++){
        m_outputWeights.push_back(Connection());
        m_outputWeights.back().weight = myIndex + c;//randomWeight();//
    }
    for( unsigned c = 0; c < neuronsInLayer; ++c){
        m_outputWeights.push_back(Connection());
        m_outputWeights.back().weight_recursive = 10 + c;//randomWeight(); //
    }
    m_myIndex = myIndex;
    num_Outputs = numOutputs;
    m_outputVal_past = 0;
    y_past = 0;
    time_const = randomT();
    gain = randomGain();
}   
//---------------------------------------------------------------------------
double Neuron::transferFunction(double x){
    if(x > 100) return 1; // preven overflows
    else return 1/(1+exp(-gain * x));
}
//---------------------------------------------------------------------------
void Neuron::setOutputValCRNN(double val){
    dy = (-y_past + val) / time_const;
    y = y_past + dy;
    m_outputVal = transferFunction(y);
}
//---------------------------------------------------------------------------
void Neuron::feedForward(const Layer &prevLayer, const Layer &thisLayer){
    double sum = 0.0;
    for(unsigned n = 0; n < prevLayer.size(); ++n){
	sum += prevLayer[n].getOutputVal() * prevLayer[n].m_outputWeights[m_myIndex].weight;
    }
    for(unsigned n = 0; n < thisLayer.size()-1; ++n){
	sum += thisLayer[n].get_m_outputVal_past() * thisLayer[n].m_outputWeights[m_myIndex + 2 ].weight;// weight_recursive;
    }
    setOutputValCRNN(sum);
}
//---------------------------------------------------------------------------
void Neuron::getWeights(unsigned neuronsInLayer, vector<double> &Weights) const{
    /*for(unsigned n = 0; n < prevLayer.size(); ++n){
        Weights.push_back(prevLayer[n].m_outputWeights[m_myIndex].weight);
    } */

    for(unsigned n = 0; n < num_Outputs; ++n)
        Weights.push_back(m_outputWeights[n].weight);
    for(unsigned n = 0; n < neuronsInLayer; ++n)
        Weights.push_back(m_outputWeights[n].weight_recursive);
}
//---------------------------------------------------------------------------
void Neuron::setWeights(unsigned &ind, unsigned neuronsInLayer, const vector<double> &Weights){
    m_outputWeights.clear();
    for(unsigned n = 0; n < num_Outputs; ++n){
        m_outputWeights.push_back(Connection());
        m_outputWeights.back().weight = Weights[ind];
        ind += 1;
    }
    for(unsigned n = 0; n < neuronsInLayer; ++n){
        m_outputWeights.push_back(Connection());
        m_outputWeights.back().weight_recursive = Weights[ind];
        ind += 1;
    }
}
//---------------------------------------------------------------------------
void Neuron::setGains(unsigned &ind, const vector<double> &Gains){
    gain = Gains[ind];
    ind += 1;
}
//---------------------------------------------------------------------------
void Neuron::setTime_const(unsigned &ind, const vector<double> &Time_const){
    time_const = Time_const[ind];
    ind += 1;
}
//---------------------------------------------------------------------------

//******************* class Net *******************
TNet::TNet(const vector<unsigned> &topology){
    unsigned numLayers = topology.size();
    for(unsigned layerNum = 0; layerNum < numLayers; ++layerNum){
        m_layers.push_back(Layer());
        unsigned numOutputs = layerNum == topology.size() -1 ? 0: topology[layerNum + 1];
        // We have new layer, now fill it with neurons , and
        // add a bias neuron in each layer.
        for(unsigned neuronNum = 0; neuronNum < topology[layerNum]; ++ neuronNum){
            if(layerNum == 0 || layerNum == 1)
                m_layers.back().push_back(Neuron(numOutputs, neuronNum, 0));
            else
                m_layers.back().push_back(Neuron(numOutputs, neuronNum, topology[layerNum]));  }
        unsigned neuronNum = topology[layerNum];
        m_layers.back().push_back(Neuron(numOutputs, neuronNum, 0));
        m_layers.back().back().setOutputVal(2.0);
    }
}
//---------------------------------------------------------------------------
void TNet::getResults(vector<double> &resultVals)const{
    resultVals.clear();
    for(unsigned n = 0; n < m_layers.back().size() - 1; ++n)
        resultVals.push_back(m_layers.back()[n].getOutputVal());
}
//---------------------------------------------------------------------------
void TNet::feedForward(const vector<double> &inputVals){
    assert(inputVals.size() == m_layers[0].size() - 1);

    //Assign the input values into the input neurons
    for(unsigned i = 0; i < inputVals.size(); ++i){
        m_layers[0][i].setOutputValCRNN(inputVals[i]);
        m_layers[0][i].setY_past();
        m_layers[0][i].set_m_outputVal_past();
    }

    //Forward propagate
    for(unsigned layerNum = 1; layerNum < m_layers.size(); ++layerNum){
        Layer &prevLayer = m_layers[layerNum - 1];
        Layer &thisLayer = m_layers[layerNum];
        for(unsigned n = 0; n < m_layers[layerNum].size() - 1; ++n){
            m_layers[layerNum][n].feedForward(prevLayer, thisLayer);
        }
        for(unsigned n = 0; n < m_layers[layerNum].size() - 1; ++n){
            m_layers[layerNum][n].setY_past();
            m_layers[layerNum][n].set_m_outputVal_past();
        }
    }
}
//---------------------------------------------------------------------------
void TNet::getWeights(vector<double> &Weights) const{
    Weights.clear();
    for(unsigned n = 0; n < m_layers[0].size(); ++n)
            m_layers[0][n].getWeights(0, Weights);

    for(unsigned layerNum = 1; layerNum < m_layers.size(); ++layerNum){
        for(unsigned n = 0; n < m_layers[layerNum].size()-1; ++n) {
            if(layerNum == 1)
                m_layers[layerNum][n].getWeights(0, Weights);
            else
                m_layers[layerNum][n].getWeights(m_layers[layerNum].size()-1, Weights);
        }
        unsigned n = m_layers[layerNum].size()-1;
            m_layers[layerNum][n].getWeights(0, Weights);
    }
}
//---------------------------------------------------------------------------
void TNet::getGains(vector<double> &Gains) const{
    Gains.clear();
    for(unsigned layerNum = 0; layerNum < m_layers.size(); ++layerNum)
        for(unsigned n = 0; n < m_layers[layerNum].size() - 1; ++n)
            Gains.push_back(m_layers[layerNum][n].getGain());
}
//---------------------------------------------------------------------------
void TNet::getTime_const(vector<double> &Time_const) const{
    Time_const.clear();
    for(unsigned layerNum = 0; layerNum < m_layers.size(); ++layerNum)
        for(unsigned n = 0; n < m_layers[layerNum].size() - 1; ++n)
            Time_const.push_back(m_layers[layerNum][n].getTime_const());
}
//---------------------------------------------------------------------------
void TNet::setWeights(const vector<double> &Weights){
    unsigned ind = 0;
    /*for(unsigned layerNum = 0; layerNum < m_layers.size() - 1; ++layerNum){
        for(unsigned n = 0; n < m_layers[layerNum].size(); ++n)
            m_layers[layerNum][n].setWeights(ind, Weights);
    } //*/

    for(unsigned n = 0; n < m_layers[0].size(); ++n)
            m_layers[0][n].setWeights(ind, 0, Weights);

    for(unsigned layerNum = 1; layerNum < m_layers.size(); ++layerNum){
        for(unsigned n = 0; n < m_layers[layerNum].size()-1; ++n){
            if(layerNum == 1)
                m_layers[layerNum][n].setWeights(ind, 0, Weights);
            else
                m_layers[layerNum][n].setWeights(ind, m_layers[layerNum].size()-1, Weights);
        }
        unsigned n = m_layers[layerNum].size()-1;
            m_layers[layerNum][n].setWeights(ind, 0, Weights);
    }//*/
}
//---------------------------------------------------------------------------
void TNet::setGains(const vector<double> &Gains){
    unsigned ind = 0;
    for(unsigned layerNum = 0; layerNum < m_layers.size(); ++layerNum){
        for(unsigned n = 0; n < m_layers[layerNum].size() - 1; ++n)
            m_layers[layerNum][n].setGains(ind, Gains);
    }
}
//---------------------------------------------------------------------------
void TNet::setTime_const(const vector<double> &Time_const){
    unsigned ind = 0;
    for(unsigned layerNum = 0; layerNum < m_layers.size(); ++layerNum){
        for(unsigned n = 0; n < m_layers[layerNum].size() - 1; ++n)
            m_layers[layerNum][n].setTime_const(ind, Time_const);
    }
}
//---------------------------------------------------------------------------
