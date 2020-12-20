# include <stdio.h>
# include <stdlib.h>
# include "initial.h"
# include "func1.h"

int f_dimension(void)
{
    return 2;
}

double f_value(const double x[], SampleSet *data)
{
    double f_val = 0.0;
    for (int i = 0; i < data->number; ++i)
        f_val += (data->sample[i].temp - x[0] * data->sample[i].alt - x[1]) * (data->sample[i].temp - x[0] * data->sample[i].alt - x[1]);

    return f_val;
}

void f_gradient(const double x[], double g[], SampleSet *data)
{
    g[0] = 0.0;
    g[1] = 0.0;
    for (int i = 0; i < data->number; ++i)
    {
        g[0] += 2 * data->sample[i].alt * (x[0] * data->sample[i].alt + x[1] - data->sample[i].temp);
        g[1] += 2 * (x[0] * data->sample[i].alt + x[1] - data->sample[i].temp);
    }
}