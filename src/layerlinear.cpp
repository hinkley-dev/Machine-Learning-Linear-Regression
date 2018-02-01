#include "layer.h"
#include "layerlinear.h"
#include "matrix.h"
#include "vec.h"

#include <cmath>

LayerLinear::LayerLinear(size_t inputs, size_t outputs) :
 Layer(inputs, outputs)
{
  m_inputs = inputs;
  m_outputs = outputs;

}

LayerLinear::~LayerLinear()
{

}

void LayerLinear::activate(const Vec& weights,const Vec& x)
{

  //b will be first "outputs" values in weights
   VecWrapper b(*(Vec*)&weights, 0, m_outputs);

   Matrix M(m_outputs, m_inputs);


  size_t matrixIndex = m_outputs -1;

  //Matricies will read the weights by rows
  for(size_t i = 0; i < m_outputs; ++i)
  {
    for(size_t j = 0; j < m_inputs; ++j)
    {
      matrixIndex++;
      M[i][j] = weights[matrixIndex];
    }
  }

  //making x into a matrix to test it out
  Matrix X(m_inputs,1);
  for(size_t i = 0; i < m_inputs; ++i)
  {
    X[i][0] = x[i];
  }


  Vec& Mx = Matrix::multiply(M,X, false,false)->transpose()->row(0);
  Vec y = Mx + b;
  activation.copy(y);


}


void LayerLinear::ordinary_least_squares(const Matrix& X,const Matrix& Y, Vec& weights)
{

    if(X.cols() != m_inputs) throw Ex("Invalid X matrix for input size");
    if(Y.cols() != m_outputs) throw Ex("Invalid Y Matrix for output size");

    Matrix X_originCentered = createOriginCentered(X);
    Matrix Y_originCentered = createOriginCentered(Y);

    //OLS calculation for M
    Matrix* term1 = Matrix::multiply(Y_originCentered, X_originCentered, true, false);

    Matrix* term2 = Matrix::multiply(X_originCentered, X_originCentered, true, false)->pseudoInverse();

    Matrix* M = Matrix::multiply(*term1, *term2, false, false);


    //b calculation...very specific to single features
    Matrix Y_centroids = calculateCentroidVals(Y);
    Matrix X_centroids = calculateCentroidVals(X);

    Matrix* Mx = Matrix::multiply(*M, X_centroids, false, true);

    Vec b = Y_centroids.row(0) - Mx->row(0);

    weights.resize(b.size() + M->row(0).size());
    for(size_t i = 0; i < b.size(); ++i)
    {
      weights[i] = b[i];
    }
    for(size_t i = b.size(), j = 0; i < weights.size(); ++i,++j )
    {
      weights[i] = M->row(0)[j];
    }

    term1->~Matrix();
    term2->~Matrix();
    M->~Matrix();
    Mx->~Matrix();


}

void LayerLinear::ordinary_least_squares_test()
{


    Matrix X = buildRandom(100,13);
    Vec weights = buildRandom(14);

    //calculate y values with activate
    Matrix Y(100,1);
    for(size_t i = 0; i < Y.rows(); ++i)
    {
      activate(weights, X.row(i));
      for(size_t j = 0; j < activation.size(); ++j)
      {
        Y[i][j] = activation[j];
      }
    }

    addNoise(Y);

    Vec olsWeights;
    ordinary_least_squares(X,Y,olsWeights);

    if(!isNoiseTolerable(weights, olsWeights))
      throw Ex("Claculated and original weights differ too much when noise is added.");

}

void LayerLinear::addNoise(Matrix& M)
{
  Rand r(12);
  double noise_deviation = 0.1;

  for(size_t i = 0; i < M.rows(); ++i)
  {
    for(size_t j = 0; j < activation.size(); ++j)
    {
      M[i][j] += noise_deviation * r.normal();
    }
  }
}

bool LayerLinear::isNoiseTolerable(Vec& computed, Vec& original)
{
  if(computed.size() != original.size()) throw Ex("Cannot check noise tolerance of different sized Vectors");

  double tolerance = 0.05;
  for(size_t i = 0; i < computed.size(); ++i)
  {
    if(abs(computed[i] - original[i]) > tolerance)
      return false;
  }
  return true;
}

Matrix LayerLinear::buildRandom(int rows, int cols)
{
  Matrix m(rows,cols);
  Rand random(23);
  for(size_t r = 0; r < m.rows(); ++r)
  {
    for(size_t c = 0; c < m.cols(); ++c)
    {

      m[r][c] = random.normal();
    }
  }
  return m;
}

Vec LayerLinear::buildRandom(size_t size)
{
  Vec v(size);
  Rand r(14);
  for(size_t i = 0; i < size; ++i)
  {
    v[i] = r.normal();
  }
  return v;
}


Matrix LayerLinear::createOriginCentered(const Matrix& m)
{

  Matrix originCentered(m.rows(), m.cols());

  Matrix centroidVals = calculateCentroidVals(m);

  //mi - avg(m) to fill matrix
  for(size_t i = 0; i < originCentered.rows(); ++i)
  {
    for(size_t j = 0; j < originCentered.cols(); ++j)
    {
      originCentered[i][j] = m[i][j] - centroidVals[0][j];
    }
  }


  return originCentered;
}

Matrix LayerLinear::calculateCentroidVals(const Matrix& m)
{
  Matrix centroidVals(1, m.cols());
  for(size_t i = 0; i < m.cols(); ++i)
  {
    centroidVals[0][i] = m.columnMean(i);
  }
  return centroidVals;
}



















//hello
