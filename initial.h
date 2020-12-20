#ifndef OPTIMIZE_INIT_H
#define OPTIMIZE_INIT_H

typedef struct
{
    char *loc;   // location name
    double alt;  // altitude (km)
    double temp; // temperature (centigrade)
} Sample;

typedef struct
{
    unsigned int number;
    Sample *sample;
} SampleSet;

void print_sample_set(SampleSet *data);
int comp_alt(const void *x0, const void *x1);
SampleSet *load_sample_set(const char *filename);
void free_sample_set(SampleSet *data);
SampleSet *add_sample(SampleSet *data, char *loc, double alt, double temp);

#endif