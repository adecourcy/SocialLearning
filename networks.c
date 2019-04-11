#include "includes.h"

// File including necessary functions for handling Network data structures

Network newNetwork(int size)
{
	Network network;
	network.size = size;

	Connections *networkMatrix = (Connections*)malloc(size * sizeof(Connections));

	network.matrix = networkMatrix;

	return network;
}




void destroyNetwork(Network network)
{
  for (int i = 0; i < network.size; i++) {
    free(network.matrix[i].connections);
  }
  
  free(network.matrix);
}



Connections newConnections(int size)
{
  Connections connections;
  connections.size = size;

  unsigned int *connectionsArray = (unsigned int*)malloc(size * sizeof(unsigned int));

  connections.connections = connectionsArray;
  return connections;
}





Network createLocalNetwork(int demeSize, int populationSize)
{
	Network network = newNetwork(populationSize);

  if (demeSize % 2 != 0) {
    demeSize += 1;
  }

  for (int i = 0; i < populationSize; i++) {
    network.matrix[i] = newConnections(demeSize);
  }

  for (int i = 0; i < populationSize; i++) {
    int currentNode = 0;

    for (int k = 1; k < ((demeSize/2) + 1); k++) {
      network.matrix[i].connections[currentNode] = wraparound((i - k), populationSize);
      currentNode++;
      network.matrix[i].connections[currentNode] = wraparound((i + k), populationSize);
      currentNode++;
    }

  }

	return network;

}


Network createGlobalNetwork(int populationSize)
{
  Network network = newNetwork(populationSize);

  for (int i = 0; i < populationSize; i++) {
    network.matrix[i] = newConnections(populationSize);
  }

  for (int i = 0; i < populationSize; i++) {
    for (int k = 0; k < populationSize; k++) {
      network.matrix[i].connections[k] = k;
    }
  }
  
  return network;
}


Network networkFromFile(FILE* file, int populationSize)
{
  int numConnections;
  int connection;
  int index;
  char buffer[255];
  Network network = newNetwork(populationSize);

  for (int i=0; i < populationSize; i++) {
    getNext(buffer, &index, file);
    numConnections = (int) strtol(buffer, NULL, 10);
    network.matrix[i] = newConnections(numConnections);
    for (int k=0; k < numConnections; k++) {
      getNext(buffer, &index, file);
      connection = (int) strtol(buffer, NULL, 10);
      network.matrix[i].connections[k] = connection;
    }
  }

  return network;
}
