# ifndef OPTIMIZE_FUNC_H
# define OPTIMIZE_FUNC_H
# include "initial.h"

int f_dimension(void);
double f_value(const double x[], SampleSet *data);
void f_gradient(const double x[], double g[], SampleSet *data);

#endif