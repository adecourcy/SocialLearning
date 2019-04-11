#include "includes.h"

Population generatePopulation(int populationSize, int N)
{
	Population population;
	population.populationSize = populationSize;

	population.population = (unsigned int*)malloc(populationSize * sizeof(int));

	int representationMax = exp2(N) - 1;

	for (int i = 0; i < populationSize; i++) {
		population.population[i] = randInt(0, representationMax);
	}

	return population;

}




void destroyPopulation(Population population)
{
  free(population.population);
}




Population populationFromFile(FILE* file,
                              int populationSize,
                              int N)
{
  int index;
  char buffer[255];
  Population population = generatePopulation(populationSize, N);

  for (int i=0; i < population.populationSize; i++) {
    getNext(buffer, &index, file);
    population.population[i] = (int) strtol(buffer, NULL, 10);
  }

  return population;
}