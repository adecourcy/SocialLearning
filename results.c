#include "includes.h"

// A data structure for tracking our population scores, to be written later

Results newResultsMatrix (int numberOfExperiments,
                          int numberOfPopulations,
                          int numberOfGenerations,
                          int populationSize)
{
  Results results;
  results.experiments = numberOfExperiments;
  results.populations = numberOfPopulations;
  results.generations = numberOfGenerations;
  results.populationSize = populationSize;
  
  double ***matrix = (double***)malloc(numberOfExperiments * sizeof(double**));
  
  for (int i = 0; i < numberOfExperiments; i++) {
    matrix[i] = (double**)malloc(numberOfPopulations * sizeof(double*));
    for (int k = 0; k < numberOfPopulations; k++) {
      matrix[i][k] = (double*)malloc(populationSize * sizeof(double));
    }
  }
  
  double *averageFitness = (double*) malloc(numberOfGenerations * sizeof(double));
  double *averageBestFitness = (double*) malloc(numberOfGenerations * sizeof(double));
  
  results.matrix = matrix;
  results.averageFitness = averageFitness;
  results.averageBestFitness = averageBestFitness;

  for (int i = 0; i < numberOfGenerations; i++) {
  	results.averageFitness[i] = 0;
  }

  for (int i = 0; i < numberOfGenerations; i++) {
    results.averageBestFitness[i] = 0;
  }
  
  return results;
}




void destroyResults(Results results)
{
  for (int i = 0; i < results.experiments; i++) {
    for (int k = 0; k < results.populations; k++) {
      free(results.matrix[i][k]);
    }
  }
  
  for (int i = 0; i < results.experiments; i++) {
    free(results.matrix[i]);
  }
  
  free(results.matrix);
  free(results.averageFitness);
  free(results.averageBestFitness);
}




void writeResults(Results results, char* experimentName)
{
  
  FILE* file = fopen(experimentName, "w");

  fprintf(file, "AVERAGE FITNESS\n");
  for (int i = 0; i < results.generations; i++) {
    fprintf(file, "%f\n", results.averageFitness[i]);
  }

  fprintf(file, "AVERAGE BEST FITNESS\n");
  for (int i = 0; i < results.generations; i++) {
    fprintf(file, "%f\n", results.averageBestFitness[i]);
  }

  fprintf(file, "FINAL GENERATION\n");

  for (int i = 0; i < results.experiments; i++) {
    for (int k = 0; k < results.populations; k++) {
      for (int m = 0; m < results.populationSize; m++) {
        fprintf(file, "%f ", results.matrix[i][k][m]);
      }
      fprintf(file, "\n");
    }
  }
    
  fclose(file);

}
