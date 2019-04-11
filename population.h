typedef struct pop_tag {
	int populationSize;
	unsigned int* population;
} Population;

Population generatePopulation(int populationSize, int N);
void destroyPopulation(Population population);
Population populationFromFile(FILE* file, int populationSize, int N);