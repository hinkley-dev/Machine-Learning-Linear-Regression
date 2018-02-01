#include "neuralnet.h"
#include "supervised.h"

NeuralNet::NeuralNet()
{

}

NeuralNet::~NeuralNet()
{

}

const char* NeuralNet::name()
{
  return "neural network";
}

void NeuralNet::train(const Matrix& features, const Matrix& labels)
{
  layers.clear();
  LayerLinear l(features.cols(), labels.cols());
  layers.push_back(l);
  for(size_t i = 0; i < layers.size(); ++i)
  {
    layers[0].ordinary_least_squares(features, labels, layerWeights);
  }


}


const Vec& NeuralNet::predict(const Vec& in)
{

      layers[0].activate(layerWeights, in);
      const Vec* prediction = new Vec(layers[0].getActivation());
      return *prediction;

}
