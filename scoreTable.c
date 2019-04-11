#include "includes.h"

// Create a hash table for solutions on our NK fitness landscape for fast access

ScoreTable newScoreTable (unsigned int size)
{
	ScoreTable scoreTable;
	scoreTable.size = size;

	scoreTable.array = (double*)malloc(size * sizeof(double));

	return scoreTable;
}




void destroyScoreTable(ScoreTable scoreTable)
{
  free(scoreTable.array);
}




ScoreTable createScoreTable(Landscape landscape, int K)
{
	int numScores = exp2(landscape.geneLength);
	ScoreTable scoreTable = newScoreTable(numScores);

	double maxFitness = 0.0;
	double fitness = 0.0;
	int indexTracker;
	int nextInteraction;
	int scorePosition = 1;

	for (int i = 0; i < numScores; i++) {
		fitness = 0.0;
		for (int n = 0; n < landscape.geneLength; n++) {
			indexTracker = 0;
			for (int k = 0; k < (K + 1); k++) {
				nextInteraction = (n + k) % landscape.geneLength;
				if ((i & (scorePosition << nextInteraction)) != 0) {
					indexTracker += (1 << k);
				}

				}

			fitness += landscape.matrix[n][indexTracker];
			}

			if (fitness > maxFitness) {
				maxFitness = fitness;
		}
		scoreTable.array[i] = fitness;

	}

	for (int i = 0; i < scoreTable.size; i++) {
		scoreTable.array[i] = pow(scoreTable.array[i]/maxFitness, 8);
	}

	return scoreTable;
}



ScoreTable scoreTableFromFile(int N, FILE* scoreTableFile)
{
	int index;
	char buffer[255];
	ScoreTable scoreTable = newScoreTable(exp2(N));

	for (int i=0; i<exp2(N); i++) {
		getNext(buffer, &index, scoreTableFile);
		scoreTable.array[i] = strtof(buffer, NULL);
	}

	return scoreTable;
}
