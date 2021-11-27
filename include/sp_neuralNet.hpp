#include "sp_Matrices/Matrix.hpp"
#include <random>


namespace sp{ // BEGINING OF NAMESPACE //////////////////////////////////////////////////////////////////


class NNLayer{
public:
	NNLayer(const int inputSize, const int outputSize, const int batchSize, float (*activationFunc)(float), float (*activationFuncDerivative)(float));

	inline void setInputs(const DMatrix<float> *const inputsMatrix) noexcept;

	const inline DMatrix<float> &getOutputs() const noexcept;

	void setRandomWeights(std::uniform_real_distribution<float> &distribution);


	inline void feedForward();

	DMatrix<float> *backPropagate(DMatrix<float> *deltaOutputs);


protected:
// DATA MEMBERS
	DMatrix<float> weights;
	DMatrix<float> biases;
	
	DMatrix<float> sums;
	DMatrix<float> outputs;

	const DMatrix<float> *inputs;

	float (*activationFunction)(float);
	float (*activationDerivative)(float);
public:
	float learningRate;
};








#define CLS NNLayer

CLS::NNLayer(const int inputSize, const int outputSize, const int batchSize, float (*activationFunc)(float), float (*activationFuncDerivative)(float)) :
	weights(outputSize, inputSize), biases(outputSize, 1), sums(outputSize, batchSize), outputs(outputSize, batchSize),
	activationFunction{activationFunc}, activationDerivative{activationFuncDerivative}, learningRate{1.f} {}

inline void CLS::setInputs(const DMatrix<float> *const inputsMatrix) noexcept{
	inputs = inputsMatrix;
}

const inline DMatrix<float> &CLS::getOutputs() const noexcept{
	return outputs;
}

void CLS::setRandomWeights(std::uniform_real_distribution<float> &distribution){
	sp::rand32 rd(clock());

	const float *end = weights.data + weights.size();
	for (float *I=weights.data; I!=end; ++I)
		*I = distribution(rd);

	end = biases.data + biases.size();
	for (float *I=biases.data; I!=end; ++I)
		*I = distribution(rd);
}


void CLS::feedForward(){
	sums.mul(weights, *inputs).add(biases);
	outputs.apply(sums, activationFunction);
}

DMatrix<float> *CLS::backPropagate(DMatrix<float> *deltaOutputs){
	sums.apply(activationDerivative);
	sums.elwiseMul(*deltaOutputs);
	
	deltaOutputs->mul(tr(weights), sums);

	biases.subFromSelf(sums.mul(learningRate));
	weights.subFromSelf(sums.postMul(tr(*inputs)));

	return deltaOutputs;
}


namespace priv__{






}	// END OF NAMESPACE PRIV

}	// END OF NAMESPACE	///////////////////////////////////////////////////////////////////