#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <functional>

auto _add = [] (float A, float B) { return A + B; };
auto _mul = [] (float A, float B) { return A * B; };
auto _sub = [] (float A, float B) { return A - B; };
auto _div = [] (float A, float B) { return A / B; };

float operate(float A, float B, std::function<float(float, float)> func) { return func(A, B); };

class Matrix {

    public:

        std::vector<int> dim = { 0, 0 }; // shape of the matrix
        std::vector<std::vector<float>> data;
        int rows;
        int cols;

        // constructor without type or data (creates a zero matrix)
        Matrix(std::vector<int> dim) {

            this->dim = dim; rows = dim[0]; cols = dim[1];
            data.resize(rows, std::vector<float>(cols));

        }

        // constructor with type without data (options: "random") 
        // if invalid type is given, creates a zero matrix
        // disabled for now since there's only one redundant type
        /* Matrix(std::vector<int> dimention, const std::string& type) {

            dim = dimention; rows = dim[0], cols = dim[1];
            data.resize(rows, std::vector<float>(cols));

            if (type == "random") {

                srand((unsigned)time(0));

                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++)
                        data[i][j] = (float)rand() / RAND_MAX;
                }

            }

        } */

        // constructor with 2D data (specify the datatype while constructing this way 
        // cuz it gets confused for some reason)
        Matrix(std::vector<std::vector<float>> data) {

            this->data = data;
            this->dim[0] = data.size();
            this->dim[1] = data[0].size();

            rows = dim[0];
            cols = dim[1];

        }

        // randomize a the current matrix to numbers between 0 and 1
        void randomize() {

            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++)
                    data[i][j] = (float)rand() / RAND_MAX;
            }

        }

        // print the data to external console
        void printData() {

            for (int i = 0; i < rows; i++) {
                std::cout << " | [ ";

                for (int j = 0; j < cols; j++) {
                    printf(" %.2f", data[i][j]);
                    std::cout << " ";
                }

                std::cout << " ] ";
                std::cout << std::endl;
            }

            std::cout << " | shape: " << rows << "x" << cols << " " << std::endl;

        }

        // loops over the given matrices and applies the given operation to their
        // respective indices
        static Matrix loopOver(Matrix A, Matrix B, std::function<float(float, float)> operation) {

            if (A.rows != B.rows || A.cols != B.cols)
                std::cout << "\a | ERROR: the shape of both matrices should be equal for this operation " << std::endl;

            Matrix C({A.rows, A.cols});

                for (int i = 0; i < A.rows; i++) {
                    for (int j = 0; j < A.cols; j++)
                        C.data[i][j] = operate(A.data[i][j], B.data[i][j], operation);
                }

            return C;

        }

        // loops over the given matrix and applies the given operation to its
        // respective index
        static Matrix loopOver(Matrix A, float B, std::function<float(float, float)> operation) {

            Matrix C({A.rows, A.cols});

                for (int i = 0; i < A.rows; i++) {
                    for (int j = 0; j < A.cols; j++)
                        C.data[i][j] = operate(A.data[i][j], B, operation);
                }

            return C;

        }

        // operations
        static Matrix add(Matrix A, Matrix B) { return loopOver(A, B, _add); };
        static Matrix add(Matrix A, float B) { return loopOver(A, B, _add); };

        static Matrix mul(Matrix A, Matrix B) { return loopOver(A, B, _mul); };
        static Matrix mul(Matrix A, float B) { return loopOver(A, B, _mul); };

        static Matrix sub(Matrix A, Matrix B) { return loopOver(A, B, _sub); };
        static Matrix sub(Matrix A, float B) { return loopOver(A, B, _sub); };

        static Matrix div(Matrix A, Matrix B) { return loopOver(A, B, _div); };
        static Matrix div(Matrix A, float B) { return loopOver(A, B, _div); };

        // matrix multiplication
        static Matrix matMul(Matrix A, Matrix B) {

            if (A.cols != B.rows)
                std::cout << "\a | ERROR: cols of A must be equal to rows of B for matMul " << std::endl;

            Matrix C({A.rows, B.cols});

                for (int i = 0; i < A.rows; i++) {
                    for (int j = 0; j < B.cols; j++) {

                        float sum = 0;
                        for (int k = 0; k < A.cols; k++)
                            sum += A.data[i][k] * B.data[k][j];
                        C.data[i][j] = sum;

                    }
                }

            return C;

        }

        static Matrix transpose(Matrix A) {

            Matrix C({A.cols, A.rows});

                for (int i = 0; i < A.cols; i++) {
                    for (int j = 0; j < A.rows; j++)
                        C.data[i][j] = A.data[j][i];
                }
            
            return C;

        }

        static Matrix map(Matrix A, std::function<float(float)> func) {

            Matrix C({A.rows, A.cols});

                for (int i = 0; i < C.rows; i++) {
                    for (int j = 0; j < C.cols; j++)
                        C.data[i][j] = func(C.data[i][j]);
                }

            return C;

        }

    //

};