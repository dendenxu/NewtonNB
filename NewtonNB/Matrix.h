/*
 * MATLAB Compiler: 7.1 (R2019b)
 * Date: Sat Sep 21 20:52:47 2019
 * Arguments:
 * "-B""macro_default""-W""lib:Matrix,version=1.0""-T""link:lib""-d""D:\Document
 * s\MATLAB\Matrix\for_testing""-v""D:\Documents\MATLAB\Add.m""D:\Documents\MATL
 * AB\ComputeValue.m""D:\Documents\MATLAB\Derivative.m""D:\Documents\MATLAB\Inve
 * rse.m""D:\Documents\MATLAB\Multiply.m""D:\Documents\MATLAB\Substract.m""D:\Do
 * cuments\MATLAB\Transpose.m"
 */

#ifndef Matrix_h
#define Matrix_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#ifdef __cplusplus
extern "C" { // sbcheck:ok:extern_c
#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_Matrix_C_API 
#define LIB_Matrix_C_API /* No special import/export declaration */
#endif

/* GENERAL LIBRARY FUNCTIONS -- START */

extern LIB_Matrix_C_API 
bool MW_CALL_CONV MatrixInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_Matrix_C_API 
bool MW_CALL_CONV MatrixInitialize(void);

extern LIB_Matrix_C_API 
void MW_CALL_CONV MatrixTerminate(void);

extern LIB_Matrix_C_API 
void MW_CALL_CONV MatrixPrintStackTrace(void);

/* GENERAL LIBRARY FUNCTIONS -- END */

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

extern LIB_Matrix_C_API 
bool MW_CALL_CONV mlxAdd(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_Matrix_C_API 
bool MW_CALL_CONV mlxComputeValue(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_Matrix_C_API 
bool MW_CALL_CONV mlxDerivative(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_Matrix_C_API 
bool MW_CALL_CONV mlxInverse(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_Matrix_C_API 
bool MW_CALL_CONV mlxMultiply(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_Matrix_C_API 
bool MW_CALL_CONV mlxSubstract(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_Matrix_C_API 
bool MW_CALL_CONV mlxTranspose(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */

/* C INTERFACE -- MLF WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

extern LIB_Matrix_C_API bool MW_CALL_CONV mlfAdd(int nargout, mxArray** c, mxArray* a, mxArray* b);

extern LIB_Matrix_C_API bool MW_CALL_CONV mlfComputeValue(int nargout, mxArray** value, mxArray* mat, mxArray* x);

extern LIB_Matrix_C_API bool MW_CALL_CONV mlfDerivative(int nargout, mxArray** mat, mxArray* mat_in1, mxArray* mainxindex);

extern LIB_Matrix_C_API bool MW_CALL_CONV mlfInverse(int nargout, mxArray** a, mxArray* a_in1);

extern LIB_Matrix_C_API bool MW_CALL_CONV mlfMultiply(int nargout, mxArray** c, mxArray* a, mxArray* b);

extern LIB_Matrix_C_API bool MW_CALL_CONV mlfSubstract(int nargout, mxArray** c, mxArray* a, mxArray* b);

extern LIB_Matrix_C_API bool MW_CALL_CONV mlfTranspose(int nargout, mxArray** a, mxArray* a_in1);

#ifdef __cplusplus
}
#endif
/* C INTERFACE -- MLF WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */

#endif
