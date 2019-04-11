typedef struct connections_tag {
  int size;
  unsigned int *connections;
} Connections;

typedef struct network_tag {
	int size;
	Connections *matrix;
} Network;

Network newNetwork(int size);
void destroyNetwork(Network network);
Connections newConnections(int size);
Network createLocalNetwork(int demeSize, int populationSize);
Network createGlobalNetwork(int populationSize);
Network networkFromFile(FILE* file, int populationSize);