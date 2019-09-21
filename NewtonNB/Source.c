#include "NewtonNB.h"
// Make sure you've got Matrix.h Matrix.dll Matrix.lib Source.c NewtonNB.h in your current working directory

// Sample main entry point
// Delete this main function when you write your own code
int main()
{
    // You'll have to initialize the matrix lib when you're gonna use it some time soon
    // This takes a little time (When initializing itself, the matrix lib handles some exception)
    // So don't terminate it unless you're not gonna use it anymore in your program flow
    // If you call a function in the lib before initializing the lib, you may crash badly
    InitializeMatrixLibrary();

    // Using double array to represent matrix, columns first, for example:
    // 1 2
    // 3 4
    // is 1 3 2 4
    double data1[] = {1, 1, 2, 2};
    double data2[] = {2, 2, 1, 1};
    // Reserve enough space for every matrix
    double *out = malloc(sizeof(double) * 16);
    // This for loop proves that the time consuming part is initialization but the real computation
    for (int i = 1; i < 10000; i++) {
        MultiplyMatrix(out, data1, data2, 4, 1, 1, 4);
    }
    for (int i = 0; i < 16; i++) {
        printf("%f\n", out[i]);
    }
    double function[5][5] = {{5, -6, 1, 1, 1}, {3, 2, 1, 0, 0}, {2, 0, 3, 1, 0}, {3, 1, 1, 0, 1}, {2, 0, 0, 3, 2}};
    double x[4] = {1, 2, 3, 4};
    double *tempFunction = malloc(sizeof(double) * 5 * 5);
    TransposeMatrix(tempFunction, function, 5, 5);
    double result;
    ComputeValue(&result, tempFunction, x, 5, 5);
    printf("%f", result);
    free(out);
    free(tempFunction);
    TerminateMatrixLibrary();
}

void Derivative(double *output, double *input, int mainxindex, int rows, int cols)
{
    mxArray *matrix = mxCreateDoubleMatrix(rows, cols, 0);
    mxArray *result = mxCreateDoubleMatrix(rows, cols, 0);
    mxSetDoubles(matrix, input);
    mlfDerivative(1, &result, matrix, mainxindex);
    memcpy(output, mxGetDoubles(result), sizeof(double) * rows * cols);
}

void ComputeValue(double *value, double *function, double *x, int rows, int cols)
{
    mxArray *matrix1 = mxCreateDoubleMatrix(rows, cols, 0);
    mxArray *matrix2 = mxCreateDoubleMatrix(rows - 1, 1, 0);
    mxArray *result = mxCreateDoubleMatrix(1, 1, 0);
    mxSetDoubles(matrix1, function);
    mxSetDoubles(matrix2, x);
    mlfComputeValue(1, &result, matrix1, matrix2);
    memcpy(value, mxGetDoubles(result), sizeof(double));
}

// Those functions are quite self-explainary, so I didn't write any comment in NewtonNB.h
// Make sure the rows and cols match matrix multiplication's prerequisite
void MultiplyMatrix(double *output, double *input1, double *input2, int rows1, int cols1, int rows2, int cols2)
{
    mxArray *matrix1 = mxCreateDoubleMatrix(rows1, cols1, 0);
    mxArray *matrix2 = mxCreateDoubleMatrix(rows2, cols2, 0);
    mxArray *result = mxCreateDoubleMatrix(rows1, cols2, 0);
    mxSetDoubles(matrix1, input1);
    mxSetDoubles(matrix2, input2);
    mlfMultiply(1, &result, matrix1, matrix2);
    memcpy(output, mxGetDoubles(result), sizeof(double) * rows1 * cols2);
}

void AddMatrix(double *output, double *input1, double *input2, int rows, int cols)
{
    mxArray *matrix1 = mxCreateDoubleMatrix(rows, cols, 0);
    mxArray *matrix2 = mxCreateDoubleMatrix(rows, cols, 0);
    mxArray *result = mxCreateDoubleMatrix(rows, cols, 0);
    mxSetDoubles(matrix1, input1);
    mxSetDoubles(matrix2, input2);
    mlfAdd(1, &result, matrix1, matrix2);
    memcpy(output, mxGetDoubles(result), sizeof(double) * rows * cols);
}
// Substract input2 from input1
void SubstractMatrix(double *output, double *input1, double *input2, int rows, int cols)
{
    mxArray *matrix1 = mxCreateDoubleMatrix(rows, cols, 0);
    mxArray *matrix2 = mxCreateDoubleMatrix(rows, cols, 0);
    mxArray *result = mxCreateDoubleMatrix(rows, cols, 0);
    mxSetDoubles(matrix1, input1);
    mxSetDoubles(matrix2, input2);
    mlfSubstract(1, output, &result, input1, input2);
    memcpy(output, mxGetDoubles(result), sizeof(double) * rows * cols);
}

void InverseMatrix(double *output, double *input, int rows, int cols)
{
    mxArray *matrix = mxCreateDoubleMatrix(rows, cols, 0);
    mxArray *result = mxCreateDoubleMatrix(rows, cols, 0);
    mxSetDoubles(matrix, input);
    mlfInverse(1, &result, matrix);
    memcpy(output, mxGetDoubles(result), sizeof(double) * rows * cols);
}

void TransposeMatrix(double *output, double *input, int rows, int cols)
{
    mxArray *matrix = mxCreateDoubleMatrix(rows, cols, 0);
    mxArray *result = mxCreateDoubleMatrix(rows, cols, 0);
    mxSetDoubles(matrix, input);
    mlfTranspose(1, &result, matrix);
    memcpy(output, mxGetDoubles(result), sizeof(double) * rows * cols);
}

void InitializeMatrixLibrary()
{
    if (isInitialized)
        return;
    if (!mclInitializeApplication(NULL, 0)) {
        fprintf(stderr, "Could not initialize the application.\n");
        return -1;
    }
    if (!MatrixInitialize()) {
        fprintf(stderr, "Could not initialize the library.\n");
        return -1;
    }
    isInitialized = 1;
}

void TerminateMatrixLibrary()
{
    if (isInitialized)
        MatrixTerminate();
    isInitialized = 0;
}