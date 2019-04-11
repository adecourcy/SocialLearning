typedef struct results_tag {
  int experiments;
  int populations;
  int populationSize;
  int generations;
  double* averageBestFitness;
  double* averageFitness;
  double*** matrix;
} Results;

Results newResultsMatrix (int numberOfExperiments, int numberOfPopulations, int numberOfGenerations, int populationSize);
void destroyResults(Results results);
void writeResults(Results results, char* experimentName);