# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include "optimize.h"
# include "initial.h"

double calc_norm(const int dim, double v[])
{
    double tmp = 0;
    for (int i = 0; i < dim; i++)
    {
        tmp += v[i] * v[i];
    }
    tmp = sqrt(tmp);
    return tmp;
}

int optimize(const double alpha, const int dim, double x[], SampleSet *data,
             void (*calc_grad)(const double[], double[], SampleSet *))
{
    double *g = malloc(dim * sizeof(double));
    int iter = 0;

    while (++iter < 10000)
    {
        (*calc_grad)(x, g, data);
        const double norm = calc_norm(dim, g);

        if (norm < 0.0001)
            break;

        for (int i = 0; i < dim; i++)
            x[i] -= alpha * g[i];
    }

    free(g);
    return iter;
}
