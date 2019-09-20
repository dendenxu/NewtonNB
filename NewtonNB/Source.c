#include "Matrix.h"
void InitializeMatrixLibrary();
void TerminateMatrixLibrary();
void TransposeMatrix(double *output, double *input, int rows, int cols);
void InverseMatrix(double *output, double *input, int rows, int cols);
void AddMatrix(double *output, double *input1, double *input2, int rows, int cols);
void SubtractMatrix(double *output, double *input1, double *input2, int rows, int cols);
void MultiplyMatrix(double *output, double *input1, double *input2, int rows1, int cols1, int rows2, int cols2);
int isInitialized = 0;

int main()
{
    InitializeMatrixLibrary();

    double data1[] = {1, 1, 2, 2};
    double data2[] = {2, 2, 1, 1};
    double *out = malloc(sizeof(double) * 16);
    for (int i = 1; i < 10000; i++) {
        MultiplyMatrix(out, data1, data2, 4, 1, 1, 4);
    }
    for (int i = 0; i < 16; i++) {
        printf("%f\n", out[i]);
    }

    TerminateMatrixLibrary();
}

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