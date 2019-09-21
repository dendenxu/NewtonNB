#ifndef SOLVE_H
#define SOLVE_H
typedef struct
{
    int terms;
    double *function;
} Formula;

typedef struct
{
    int terms;
    Formula *formulas;
} Derivation;

int Newton(double **approximation, Formula *formula, int cnt, double EPS);

Formula *Read(int *cnt, double **ans);

#endif // !SOLVE_H
