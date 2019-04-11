#include "includes.h"

// Generate scores for solutions given parameters of our NK fitness landscape

int main(int argc, char *argv[])
{

	srand(time(NULL));

	FILE* outputFile = fopen(argv[1], "w");
	int N = strtol(argv[2], NULL, 10);
	int K = strtol(argv[3], NULL, 10);
	int numberOfLandscapes = strtol(argv[4], NULL, 10);

	if (outputFile == NULL) {
		printf("Error opening score table file '%s'", argv[1]);
		exit(1);
	}

	Landscape landscape;
	ScoreTable scoreTable;

	for (int i=0; i < numberOfLandscapes; i++) {
		landscape = generateLandscape(N, K);
		scoreTable = createScoreTable(landscape, K);

		for (int k=0; k<scoreTable.size; k++) {
			fprintf(outputFile, "%f\n", scoreTable.array[k]);
		}
	}

	fclose(outputFile);

	return 0;

}
