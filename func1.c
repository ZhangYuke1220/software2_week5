#include <stdio.h>
#include <stdlib.h>

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


int f_dimension()
{
    return 2;
}

SampleSet *load_sample_set(const char *filename)
{
    FILE *fp = NULL;
    unsigned int count = 0;
    unsigned int bufsize = 1000;
    Sample *buf = (Sample *)malloc(sizeof(Sample) * bufsize);

    fp = fopen(filename, "r");
    if (fp == NULL)
        exit(-1);
    else
        while(count < bufsize &&
            fscanf(fp, "%s%*[^0-9]%lf%*[^0-9]%lf", buf[count].loc, &buf[count].alt, &buf[count].temp) > 0)
            ++count;
    fclose(fp);
    
    SampleSet *data = (SampleSet *)malloc(sizeof(SampleSet));
    Sample *sample = (Sample *)malloc(sizeof(Sample) * count);
    for (int i=0; i<=count; ++i)
        sample[i] = (Sample)buf[i];
    *data = (SampleSet){.number = count+1, .sample = sample};

    free(buf);
    return data;
}

double f_value(const double x[], SampleSet *data)
{
    double f_val = 0.0;
    for (int i=0; i<data->number; ++i)
        f_val += (data->sample[i].temp - x[0] * data->sample[i].alt - x[1]) * (data->sample[i].temp - x[0] * data->sample[i].alt - x[1]);

    return f_val;
}

void f_gradient(const double x[], double g[], SampleSet *data)
{
    g[0] = 0.0;
    g[1] = 0.0;
    for (int i=0; i<data->number; ++i)
    {
        g[0] += 2 * data->sample[i].alt * (x[0] * data->sample[i].alt + x[1] - data->sample[i].temp);
        g[1] += 2 * (x[0] * data->sample[i].alt + x[1] - data->sample[i].temp);
    }
}