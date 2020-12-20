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

void free_sample_set(SampleSet *data)
{
    for (int i=0; i<data->number; ++i)
        free(data->sample[i].loc);
    free(data->sample);
    free(data);
}

SampleSet *add_sample(SampleSet *data, char *loc, double alt, double temp)
{
    SampleSet *data_set_new = (SampleSet *)malloc(sizeof(SampleSet));
    data_set_new->number = data->number + 1;

    Sample *data_new = (Sample *)malloc(sizeof(Sample) * (data_set_new->number + 1));
    for (int i=0; i<data->number; ++i)
    {
        data_new[i].loc = (char *)malloc(sizeof(char) * strlen(data->sample[i].loc));
        strcpy(data_new[i].loc, data->sample[i].loc);
        data_new[i].alt = data->sample[i].alt;
        data_new[i].temp = data->sample[i].temp;
    }

    data_new[data_set_new->number-1] = (Sample){.loc = NULL, .alt = alt, .temp = temp};
    data_new[data_set_new->number-1].loc = (char *)malloc(sizeof(char) * strlen(loc));
    strcpy(data_new[data_set_new->number-1].loc, loc);

    data_set_new->sample = data_new;

    return data_set_new;
}