#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "includes.h"


// Functions to generate NK fitness landscapes based on our given parameters

Landscape newLandscape(int geneLength, int interactions)
{
	Landscape landscape;
	landscape.geneLength = geneLength;
	landscape.interactions = exp2(interactions+1);

	double **landscapeArray = (double**)malloc(geneLength * sizeof(double*));


	for (int i=0; i < geneLength; i++) {
		landscapeArray[i] = (double*)malloc(landscape.interactions * sizeof(double));
	}

	landscape.matrix = landscapeArray;

	return landscape;
}




void destroyLandscape(Landscape landscape)
{
  for (int i = 0; i < landscape.geneLength; i++) {
    free(landscape.matrix[i]);
  }
  
  free(landscape.matrix);
}




Landscape generateLandscape(int N, int K)
{
	Landscape landscape =  newLandscape(N, K);

	for (int i=0; i < landscape.geneLength; i++) {
		for (int k=0; k < landscape.interactions; k++) {
			landscape.matrix[i][k] = randomReal();
		}
	}

	return landscape;
}
