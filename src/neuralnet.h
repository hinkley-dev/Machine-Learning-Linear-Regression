#ifndef NEURALNET_H
#define NEURALNET_H

#include "vec.h"
#include "matrix.h"
#include "layer.h"
#include "layerlinear.h"
#include <vector>
#include "supervised.h"

using namespace std;

class NeuralNet : public SupervisedLearner
{

private:
  Vec layerWeights;
  vector<LayerLinear> layers;

public:
  NeuralNet();
  ~NeuralNet();
  virtual void train(const Matrix& features, const Matrix& labels);
	virtual const Vec& predict(const Vec& in);
  virtual const char* name();

};



#endif
