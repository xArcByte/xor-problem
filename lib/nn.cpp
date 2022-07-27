#include <iostream>
#include <Windows.h>


auto sigmoid = [] (float x) { return (1 / (1 + std::exp(-x))); };

struct Layer {

    int neurons;
    std::string activationFunction;

    Layer(int neurons, const std::string& activationFunction) {

        this->neurons = neurons;
        this->activationFunction = activationFunction;

    }
    
};

class NeuralNetwork {

    public:

        std::vector<Layer> layers;
        std::vector<Matrix> weights;
        std::vector<Matrix> biases;

        NeuralNetwork(std::vector<Layer> layers) {

            this->layers = layers;

            for (int i = 0; i < layers.size() - 1; i++) {

                weights.push_back(Matrix({layers[i].neurons, layers[i + 1].neurons}));
                weights[i].randomize();

                biases.push_back(Matrix({layers[i + 1].neurons, 1}));
                biases[i].randomize();

            } 

        }

        Matrix feedForward(Matrix inputMatrix) {

            Matrix outputMatrix(inputMatrix.data);

                for (int i = 0; i < layers.size() - 1; i++) {

                    outputMatrix = Matrix::matMul(Matrix::transpose(weights[i]), outputMatrix);
                    outputMatrix = Matrix::add(outputMatrix, biases[i]);
                    // outputMatrix = Matrix::map(outputMatrix, sigmoid);

                    outputMatrix.printData();
                    std::cout << std::endl;

                }

            return outputMatrix;

        }

        void printNN() {

            std::vector<std::string> myCMD;
            myCMD.resize(2);

                std::vector<std::vector<std::string>> help;
                help.resize(layers.size());

                for (int i = 0; i < help.size(); i++) {

                    for (int j = 0; j < layers[i].neurons; j++) {
                        help[i].push_back(" [ ? ] ");
                    }

                }

            for (int i = 0; i < myCMD.size(); i++) std::cout << " |" << myCMD[i] << std::endl;

        }

    //

};