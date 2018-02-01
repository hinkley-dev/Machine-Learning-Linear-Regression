#ifndef LAYER_H
#define LAYER_H

#include <vector>
#include "vec.h"

class Layer
{

protected: Vec activation;

public:

	Layer(size_t inputs, size_t outputs);
	Vec getActivation();

	virtual ~Layer();

	virtual void activate(const Vec& weights,const Vec& x) = 0;
};

#endif
