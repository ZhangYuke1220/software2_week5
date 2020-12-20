# ifndef OPTIMIZE_OPTIMIZE_H
# define OPTIMIZE_OPTIMIZE_H
# include "initial.h"
# include "func1.h"


int optimize(const double alpha, const int dim, double x[], SampleSet *data,
             void (*calc_grad)(const double[], double[], SampleSet *));

#endif
