#include "layer.h"

Layer::Layer(size_t inputs, size_t outputs) :
  activation(outputs)
{

}

Layer::~Layer()
{

}

Vec Layer::getActivation()
{
  return activation;
}
