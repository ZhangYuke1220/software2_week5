# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "initial.h"

void print_sample_set(SampleSet *data)
{
    for (int i = 0; i < data->number; ++i)
    {
        printf("loc = %s, ", data->sample[i].loc);
        printf("alt = %3.2lf, ", data->sample[i].alt);
        printf("temp = %3.2lf\n", data->sample[i].temp);
    }
}

int comp_alt(const void *x0, const void *x1)
{
    const Sample *p0 = (Sample *)x0;
    const Sample *p1 = (Sample *)x1;
    const double *y0 = (const double *)&p0->alt;
    const double *y1 = (const double *)&p1->alt;
	if(*y0 > *y1)
        return 1;
	if(*y0 < *y1)
        return -1;
	return 0;
}

SampleSet *load_sample_set(const char *filename)
{
    FILE *fp = NULL;
    unsigned int count = 0;
    unsigned int bufsize = 100;
    char buf_loc[bufsize];
    double altit, tempre;
    Sample samp_buf[bufsize];

    fp = fopen(filename, "r");
    if (fp == NULL)
        exit(-1);
    while (fscanf(fp, "%[^,]%*[^0-9]%lf%*[^0-9]%lf\n", buf_loc, &altit, &tempre) > 0)
    {
        samp_buf[count].loc = (char *)malloc(sizeof(char) * strlen(buf_loc));
        strcpy(samp_buf[count].loc, buf_loc);
        samp_buf[count].alt = altit;
        samp_buf[count].temp = tempre;
        ++count;
    }
    fclose(fp);

    SampleSet *data = (SampleSet *)malloc(sizeof(SampleSet));
    Sample *sample = (Sample *)malloc(sizeof(Sample) * count);
    for (int i = 0; i < count; ++i)
        sample[i] = (Sample)samp_buf[i];
    *data = (SampleSet){.number = count, .sample = sample};

    return data;
}