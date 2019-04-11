typedef struct landscape_tag {
	int geneLength;
	int interactions;
	double **matrix;
} Landscape;

Landscape newLandscape(int geneLength, int interactions);
void destroyLandscape(Landscape landscape);
Landscape generateLandscape(int N, int K);
