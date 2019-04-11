Network returnNetwork(char* netName, int populationSize, int demeSize);
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
                       FILE* populationFile);
