// this file include easy to use random functions

#include <stdio.h>      // NULL, printf, scanf, puts
#include <stdlib.h>     // srand, rand
#include <time.h>       // time





void initRandomFunc (int seed = -1)
{
	if (seed == -1)
	{
		srand(time(NULL));
	}
	else
	{
		srand(seed);
	}
}



int random (int min, int max)
{
	return ( rand() % (max - min + 1) + min );
}



float random (float min, float max)
{
    float r = (float) rand() / RAND_MAX;
    return min + r * (max - min);
}



double random (double min, double max)
{
    double r = (double) rand() / RAND_MAX;
    return min + r * (max - min);
}



long double random (long double min, long double max)
{
    long double r = (long double) rand() / RAND_MAX;
    return min + r * (max - min);
}


































//
