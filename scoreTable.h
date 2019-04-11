typedef struct score_tag {
	unsigned int size;
	double *array;
} ScoreTable;

ScoreTable newScoreTable (unsigned int size);
void destroyScoreTable(ScoreTable scoreTable);
ScoreTable createScoreTable(Landscape landscape, int K);
ScoreTable scoreTableFromFile(int populationSize, FILE* scoreTableFile);