#include "common.h"

using namespace std;

int main() {

    srand((unsigned)time(0));
    cout << endl;

    // ========== //

        NeuralNetwork nn ({
            Layer(2, "none"),
            Layer(2, "sigmoid"),
            Layer(1, "sigmoid"),
        });
        nn.printNN();

    // ========== //

    cout << endl;
    cout << " | ";
    system("pause");
    return 0;

}