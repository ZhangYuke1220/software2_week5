# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "initial.h"
# include "optimize.h"
# include "func1.h"

int main(const int argc, const char **argv)
{
    if (argc < 2)
    {
        printf("usage : <number><filename>");
        return EXIT_FAILURE;
    }
    const double alpha = atof(argv[1]);
    const char *filename = (argc == 3) ? argv[2] : "data.csv";
    SampleSet *data = load_sample_set(filename);
    const int dim = f_dimension();

    printf("Before :\n");
    print_sample_set(data);
    qsort(data->sample, data->number, sizeof(Sample), comp_alt);
    printf("After :\n");
    print_sample_set(data);

    double *x = malloc(dim * sizeof(double));
    for (int i = 0; i < dim; i++)
        x[i] = 0;

    const int iter = optimize(alpha, dim, x, data, f_gradient);
    printf("number of iterations = %d\n", iter);

    double mtfuji_alt = 3.776;
    double mtfuji_temp = x[0] * mtfuji_alt + x[1];
    printf("the altitude of mountain fuji ：%3.3lf km\n", mtfuji_alt);
    printf("the temperature of mountain fuji : %3.3lf celsius\n", mtfuji_temp);

    free(x);
    return 0;
}
