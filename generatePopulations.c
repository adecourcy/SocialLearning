#include "includes.h"

// Generate a random starting solution for each member of our population

int main(int argc, char *argv[])
{

	srand(time(NULL));
	
	FILE* outputFile = fopen(argv[1], "w");
	int N = strtol(argv[2], NULL, 10);
	int populationSize = strtol(argv[3], NULL, 10);
	int numberOfPopulations = strtol(argv[4], NULL, 10);

	if (outputFile == NULL) {
		printf("Error opening population file '%s'", argv[1]);
		exit(1);
	}

	Population population;

	for (int i=0; i < numberOfPopulations; i++) {
		population = generatePopulation(populationSize, N);

		for (int k=0; k<populationSize; k++) {
			fprintf(outputFile, "%d\n", population.population[k]);
		}
	}

	fclose(outputFile);

	return 0;

}
