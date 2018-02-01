#ifndef LAYERLINEAR_H
#define LAYERLINEAR_H

#include <vector>
#include "vec.h"
#include "matrix.h"


class LayerLinear : public Layer
{
  size_t m_inputs;
  size_t m_outputs;

private:
  Matrix createOriginCentered(const Matrix& m);
  Matrix calculateCentroidVals(const Matrix& m);
  Matrix buildRandom(int rows, int cols);
  Vec buildRandom(size_t size);
  bool isNoiseTolerable(Vec& computed, Vec& original);
  void addNoise(Matrix& M);



public:
	LayerLinear(size_t inputs, size_t outputs);

	~LayerLinear();

	virtual void activate(const Vec& weights,const Vec& x);

  void ordinary_least_squares(const Matrix& X,const Matrix& Y, Vec& weights);
  void ordinary_least_squares_test();
};



#endif
