#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "solve.h"
#include "NewtonNB.h"

int main(void)
{
	InitializeMatrixLibrary();
	int cnt;
	double *ans;
	Formula *set = Read(&cnt, &ans);

	int i, j;
	for (i = 0; i < cnt; i++)
	{
		for(j = 0 ; j < (cnt + 1) * set[i].terms; j++)
			printf("%.1lf ",set[i].function[j]);
		puts("");
	}
	/*Read the equation set, store them clone first*/

	printf("%d\n", Newton(&ans, set, cnt, 1E-3));
//	system("pause");
//
	for (i = 0; i < cnt; i++)
	{
		printf("%.2lf ", ans[i]);
		free(set[i].function);
	}
	free(ans);
	free(set);
	TerminateMatrixLibrary();
	return 0;
}

int Newton(double **approximation, Formula *formula, int cnt, double EPS)
{
	const double ZERO = 1E-7;
	int i, j, N = 10, flag = 0;
	/* N - the maxium calculate times
	 * flag - whether there a accurate solve
	 */

	double *pre = (double*)malloc(cnt * sizeof(double));
	double *f = (double*)malloc(cnt * sizeof(double));
	double *u = (double*)malloc(cnt * cnt * sizeof(double));
	/*
	 * pre - last result
	 * f - F(x) with cnt rows and 1 column
	 * u - F'(x) with cnt rows and cnt colume
	 */

	Derivation *differention = (Derivation*)malloc(cnt * sizeof(Derivation));
	for (i = 0; i < cnt; i++)
	{
		int terms = formula[i].terms;
		differention[i].terms = terms;
		differention[i].formulas = (Formula*)malloc(cnt * sizeof(Formula));
		for (j = 0; j < cnt; j++)
		{
			differention[i].formulas[j].terms = terms;
			differention[i].formulas[j].function = (double*)malloc((cnt + 1) * terms * sizeof(double));
/*			differention[i].formulas[j].function[0] = 1.0;
			printf("%lf" , differention[i].formulas[j].function[0]);
			system("pause");
*/
			Derivative(differention[i].formulas[j].function,
				formula[i].function, j + 1, cnt + 1, terms);
		}
	}
//------------------- Newton's method -----------------------------
	do {
		N--;
		for (i = 0; i < cnt; i++)
		{
			pre[i] = (*approximation)[i];
		}
		for (i = 0; i < cnt; i++)
		{
			ComputeValue(f + i, formula[i].function, pre, cnt + 1, formula[i].terms);
			/*calculate F(x)*/
		}
		for (i = 0; i < cnt; i++)
		{
			if (fabs(f[i]) > 0)
				break;
			flag = 1;
		}
		if (flag)
			break;

		for (i = 0; i < cnt; i++)
		{
			for (j = 0; j < cnt; j++)
			{
				ComputeValue(&u[i + j * cnt], differention[i].formulas[j].function,
					pre, cnt + 1, differention[i].terms);
				/*calculate F'(x)*/
			}
		}

		InverseMatrix(u, u, cnt, cnt);
		MultiplyMatrix(f, u, f, cnt, cnt, cnt, 1);
		SubstractMatrix(*approximation, *approximation, f, cnt, 1);
		/* *approximation = pre - F'(x)^-1 * F(x) */
		/* (n*1) = (n*1) - (n*n)*(n*1)*/

		for (i = 0; i < cnt; i++)
		{
			if (fabs((*approximation)[i] - pre[i]) > EPS)
				break;
			flag = 1;
		}
	} while (!flag && N);
//-----------------------------------------------------------------
	for(i = 0; i < cnt; i++)
	{
		for (j = 0; j < cnt; j++)
		{
			free(differention[i].formulas[j].function);
		}
		free(differention[i].formulas);
	}
	free(differention);
	free(u);
	free(pre);
	free(f);

	return flag;
}

Formula * Read(int *cnt, double **ans)
{
	puts("Input the number of equation");
	scanf("%d", cnt);
	*ans = (double*)malloc(*cnt * sizeof(double));
	Formula *formula = (Formula*)malloc(*cnt * sizeof(Formula));
	int i, j, k;
	for (i = 0; i < *cnt; i++)
	{
		printf("Input the number of terms in equation%d\n", i + 1);
		scanf("%d", &formula[i].terms);
		formula[i].function = (double*)malloc((*cnt + 1) * formula[i].terms * sizeof(double));
		for (j = 0; j <= *cnt; j++)
		{
			printf("Input the exponential of varies%d in equation%d\n", j, i + 1);
			for (k = 0; k < formula[i].terms; k++)
				scanf("%lf", &formula[i].function[j + k * *cnt + k]);
		}
	}
	puts("Input the approximation of answer");
	for (i = 0; i < *cnt; i++)
		scanf("%lf", &((*ans)[i]));
	return formula;
}
