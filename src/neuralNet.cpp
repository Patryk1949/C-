#define SP_MATRIX_DEBUG_MODE false
#include "sp_neuralNet.hpp"


void printMatrix(sp::DMatrix<float> &A){
	for (uint32_t i=0, j; i<A.rows(); ++i){
		for (j=0; j<A.cols(); ++j)
			printf("%8.2lf", A(i, j));
		putchar('\n');
	}
}


int main(){
	sp::GeneralStorage tempStorage1;
	sp::MatrixTempStorage = &tempStorage1;


	auto ramp = [](float x){
		return x * (x>0);
	};
	auto heaviside = [](float x){
		return (float)(x > 0);
	};
	auto pseudoSigmoid = [](float x){
		return 1.f - 1.f/(x + 2.f);
	};
	auto pseudoSigmoidDerivaive = [](float x){
		const float intermediate = 1.f/(x + 2.f);
		return intermediate*intermediate;
	};


	sp::DMatrix<float> inputs(1, 1);

	sp::NNLayer inputL(2, 30, 1, ramp, heaviside);
	inputL.setInputs(&inputs);

	sp::NNLayer hiddenL1(30, 20, 1, ramp, heaviside);
	hiddenL1.setInputs(&inputL.getOutputs());


	sp::NNLayer outputL(20, 1, 1, tanh, [](float x){ const float y=tanh(x); return 1.f-y*y; });
	outputL.setInputs(&hiddenL1.getOutputs());


	std::uniform_real_distribution<float> initDistribution(-1.f, 1.f);
	const float learningRate = 0.1f;
	
	
	inputL.setRandomWeights(initDistribution);
	hiddenL1.setRandomWeights(initDistribution);
//	hiddenL2.setRandomWeights(initDistribution);
	outputL.setRandomWeights(initDistribution);

	inputL.learningRate = learningRate;
	hiddenL1.learningRate = learningRate;
//	hiddenL2.learningRate = learningRate;
	outputL.learningRate = learningRate;



	sp::DMatrix<float> gradients(1, 1);


	sp::rand32 rd(clock());
	std::uniform_real_distribution<float> inputRange(0, 10.f*M_PI);

	for (uint32_t i=0; i<100000; ++i){
		const int a = rd() & 1;
		const int b = rd() & 1;
		const float correctOutput = a & b;

		inputs(0, 0) = a;
		inputs(1, 0) = b;

		inputL.feedForward();
		hiddenL1.feedForward();
	//	hiddenL2.feedForward();
		outputL.feedForward();

		const float predictedOutput = outputL.getOutputs()(0, 0);
		gradients.resize(2, 1);
		gradients(0, 0) = predictedOutput - correctOutput;
		gradients(1, 0) = predictedOutput - correctOutput;

	//	printf("pred: %10.4f\tcorr: %10.4f\n", predictedOutput, correctOutput);

		outputL.backPropagate(&gradients);
	//	hiddenL2.backPropagate(&gradients);
		hiddenL1.backPropagate(&gradients);
		inputL.backPropagate(&gradients);
	}

	puts("Learning is finished.\n");

	while (true){
		scanf("%f", &inputs(0, 0));

		inputL.feedForward();
		hiddenL1.feedForward();
	//	hiddenL2.feedForward();
		outputL.feedForward();

		printf("= %10.4f\n\n", outputL.getOutputs()(0, 0));
	}



	return 0;
}