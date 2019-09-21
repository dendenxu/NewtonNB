#include "Matrix.h"
void InitializeMatrixLibrary();
void TerminateMatrixLibrary();
void TransposeMatrix(double *output, double *input, int rows, int cols);
void InverseMatrix(double *output, double *input, int rows, int cols);
void AddMatrix(double *output, double *input1, double *input2, int rows, int cols);
void SubstractMatrix(double *output, double *input1, double *input2, int rows, int cols);
void MultiplyMatrix(double *output, double *input1, double *input2, int rows1, int cols1, int rows2, int cols2);
void Derivative(double *output, double *input, int mainxindex, int rows, int cols);
void ComputeValue(double *value, double *function, double *x, int rows, int cols);
