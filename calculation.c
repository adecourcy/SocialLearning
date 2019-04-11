#include "includes.h"
#include "calculation.h"

int main(int argc, char *argv[])
{
  srand(time(NULL));
  
  // Parse all input

  int N = strtol(argv[1], NULL, 10);
  int K = strtol(argv[2], NULL, 10);
  int populationSize = strtol(argv[3], NULL, 10);
  int selectionTries = strtol(argv[4], NULL, 10);
  int numberOfGenerations = strtol(argv[5], NULL, 10);
  int numberOfPopulations = strtol(argv[6], NULL, 10);
  int experimentRepetitions = strtol(argv[7], NULL, 10);
  double recombinationRate = strtof(argv[8], NULL);
  double mutationRate = strtof(argv[9], NULL);
  FILE* networkFile = fopen(argv[10], "r");
  FILE* scoreTableFile = fopen(argv[11], "r");
  FILE* populationFile = fopen(argv[12], "r");
  char* experimentName = argv[13];

  if (networkFile == NULL) {
    printf("Error opening network file '%s', for reading\n", argv[10]);
    exit(1);
  }

  if (scoreTableFile == NULL) {
    printf("Error opening score table file '%s', for reading\n", argv[11]);
    exit(1);
  }

  if (populationFile == NULL) {
    printf("Error opening population file '%s', for reading\n", argv[12]);
    exit(1);
  }

  // Create a usable network data structure from our file input
  Network network = networkFromFile(networkFile, populationSize);

  Results results;

  results = executeSimulation(N,
                              K,
                              populationSize,
                              selectionTries,
                              numberOfGenerations,
                              numberOfPopulations,
                              experimentRepetitions,
                              recombinationRate,
                              mutationRate,
                              network,
                              scoreTableFile,
                              populationFile);

  writeResults(results, experimentName);
    
  destroyNetwork(network); 
  destroyResults(results);

  return 0;

}

/*
  NO LONGER USED

  This function parses the network specifications from an input file and
  returns an appropriate network
*/
Network returnNetwork(char* netName, int populationSize, int demeSize)
{

  if (strcmp(netName, "GLOBAL") == 0) {
    return createGlobalNetwork(populationSize);

  } else if (strcmp(netName, "LOCAL") == 0) {
    return createLocalNetwork(demeSize, populationSize);

  } else {
    printf("%s is not a proper network name.\n", netName);
    exit(0);
  }
  
}


// Find the member of the population with the best fitness score
double bestFitness(Population population, ScoreTable scoreTable)
{
  double best = 0;
  for (int i = 0; i < population.populationSize; i++) {
    if (population.population[i] > best) {
      best = scoreTable.array[population.population[i]];
    }
  }
  return best;
}

/*
  This is the "driver" function of the experiment. It is basically a skeleton
  outlining the experiment steps, and calling specific experiment functions
  as necessary

  Specific recombination and mutation strategies have been added ad-hoc through
  development. Future improvement includes passing a specific set of functions to
  use, but for now commenting works for selecting the appropriate function.
*/
Results executeSimulation(int N,
                          int K,
                          int populationSize,
                          int selectionTries,
                          int numberOfGenerations,
                          int numberOfPopulations,
                          int experimentRepetitions,
                          double recombinationRate,
                          double mutationRate,
                          Network network,
                          FILE* scoreTableFile,
                          FILE* populationFile)
{

  ScoreTable scoreTable;
  Population population;
  Results results;
  int index = 0;

  results = newResultsMatrix (experimentRepetitions,
                              numberOfPopulations,
                              numberOfGenerations,
                              populationSize);

  // Test multiple randomly-generated landscapes with our specified parameters
  for (int i = 0; i < experimentRepetitions; i++) {

    scoreTable = scoreTableFromFile(N, scoreTableFile);
    
    // For each landscape, we will test multiple randomly generated populations
    for (int k = 0; k < numberOfPopulations; k++) {

      population = populationFromFile(populationFile, populationSize, N);

      for (int m = 0; m < numberOfGenerations; m++) {

        index++;

        /*
        population = recombinationAllSame(population,
                                          scoreTable,
                                          network,
                                          selectionTries,
                                          N,
                                          recombinationRate);

        population = mutateAllSame(population, scoreTable, N, mutationRate);
        */
        
        population = recombinationConformity(population,
                                      scoreTable,
                                      network,
                                      selectionTries,
                                      N,
                                      recombinationRate);
        
        /*
        population = recombinationHyper(population,
                                         scoreTable,
                                         network,
                                         N,
                                         recombinationRate);

        population = mutateHyper2(population,
                                  scoreTable,
                                  N);*/

        double averageFit = 0.0;

        for (int x = 0; x < population.populationSize; x++) {
          averageFit += (double) scoreTable.array[population.population[x]];
        }

        averageFit /= (double) population.populationSize;

        results.averageFitness[m] += averageFit;
        results.averageBestFitness[m] += bestFitness(population, scoreTable);

        }

      // For each landscape and population, record the scores of each agent
      for (int p = 0; p < population.populationSize; p++) {
        results.matrix[i][k][p] = scoreTable.array[population.population[p]];

      }

      destroyPopulation(population);
     
    }

    rewind(populationFile);
    destroyScoreTable(scoreTable);

  }

  double averageDivision = (double) numberOfPopulations * experimentRepetitions;

  for (int i = 0; i < numberOfGenerations; i++) {
    results.averageFitness[i] /= averageDivision;
  }

  for (int i = 0; i < numberOfGenerations; i++) {
    results.averageBestFitness[i] /= averageDivision;
  }

  return results;
}

