#include "includes.h"


/*
 * This file contains multiple recombination and mutation strategies. Function
 * names denote the papers from which they were derived.
 */

Population recombinationSFI(Population population,
                            ScoreTable scoreTable,
                            Network network,
                            int selectionTries,
                            int N,
                            double recombinationRate)
{
  
  float currentAgentScore;
  float currentNeighborScore;
  unsigned int currentNeighbor;
  unsigned int bestNeighbor;
  double bestNeighborScore;

  unsigned int mask = 0;
  unsigned int bestNeighborBits;
  unsigned int maskedCurrentNumber;
  unsigned int recombinationTry;


  // For each agent, find the best scoring neighber and decide whether to
  // recombine with that neighbor
	for (int i = 0; i < population.populationSize; i++) {
	  currentAgentScore = scoreTable.array[population.population[i]];
    bestNeighborScore = 0.0;
	  if (currentAgentScore == 1.0) {
	  	continue;
	  }

    // Don't iterate through all neighbors, only choose a random portion for comparison
		for (int k = 0; k < selectionTries; k++) {

			int neighborSelection = (int) randInt(0, network.matrix[i].size - 1);
			currentNeighbor =
			    population.population[network.matrix[i].connections[neighborSelection]];

			currentNeighborScore = scoreTable.array[currentNeighbor];

			if (currentNeighborScore > bestNeighborScore) {
				bestNeighbor = currentNeighbor;
				bestNeighborScore = currentNeighborScore;
			}
		}

    // Generate a bit mask for recombination
		for (int k = 0; k < N; k++) {
      double randResult = randomReal();
			if (randResult < recombinationRate) {
				mask = mask | (unsigned int) exp2(k);				
			}
		}

    // Recombine, if flagged
    bestNeighborBits = bestNeighbor & mask;
    maskedCurrentNumber = population.population[i] & (~mask);

    recombinationTry = (unsigned int) (maskedCurrentNumber | bestNeighborBits);

    // Mutate if the conditions are met
    if (scoreTable.array[recombinationTry] > currentAgentScore) {
      population.population[i] = recombinationTry;
    } else {

      population.population[i] = mutateSFI(population.population[i],
                                           scoreTable,
                                           N);
    }
              

	}

	return population;

}


unsigned int mutateSFI(unsigned int agent, ScoreTable scoreTable, int N)
{
  unsigned int mutatedAgent = agent;
  int mutatePosition = randInt(0, N-1);
  
  mutatedAgent = mutatedAgent ^ (unsigned int) exp2(mutatePosition);

  if (scoreTable.array[mutatedAgent] > scoreTable.array[agent]) {
    return mutatedAgent;
  } else {
    return agent;
  }
  
}


// The following functions work pretty much the same as above, with variations
// Refer to above comments
Population recombinationAllSame(Population population,
                                ScoreTable scoreTable,
                                Network network,
                                int selectionTries,
                                int N,
                                double recombinationRate)
{
  
  float currentAgentScore;
  float currentNeighborScore;
  int currentNeighbor;
  int bestNeighbor;
  double bestFitNeighbor;
  int numberOfNeighbors;
  int neighborList[network.size];

  unsigned int mask;
  unsigned int bestNeighborBit;
  unsigned int maskedCurrentNumber;

  for (int i = 0; i < population.populationSize; i++) {
    currentAgentScore = scoreTable.array[population.population[i]];
    bestFitNeighbor = currentAgentScore;
    
    for (int k = 0; k < selectionTries; k++) {
      int neighborSelection = (int) randInt(0, network.matrix[i].size - 1);
      currentNeighbor =
          population.population[network.matrix[i].connections[neighborSelection]];
      currentNeighborScore = scoreTable.array[currentNeighbor];
      if (currentNeighborScore > bestFitNeighbor) {
        bestNeighbor = currentNeighbor;
        bestFitNeighbor = currentNeighborScore;
      }
    }

    if (bestFitNeighbor > currentAgentScore) {
      for (int k = 0; k < N; k++) {
        if (randomReal() < recombinationRate) {
          mask = exp2(k);
          bestNeighborBit = bestNeighbor & mask;
          maskedCurrentNumber = population.population[i] & (~mask);
          population.population[i] =
              (unsigned int) maskedCurrentNumber | bestNeighborBit;
        }
      }
    }

  }

  return population;

}

Population mutateAllSame(Population population,
                         ScoreTable scoreTable,
                         int N,
                         double mutationRate)
{
  int mutationAgent;
  
  for (int i = 0; i < population.populationSize; i++) {
    mutationAgent = population.population[i];
    for (int k = 0; k < N; k++) {
      if (randomReal() < 0.1) {
        mutationAgent ^= 1 << k;
       }
    }
    
    if (scoreTable.array[mutationAgent] >
        scoreTable.array[population.population[i]]) {
      population.population[i] = mutationAgent;
    }
  }
  
  return population;
}


Population recombinationHyper(Population population,
                              ScoreTable scoreTable,
                              Network network,
                              int N,
                              double recombinationRate)
{
  
  float currentAgentScore;
  float currentNeighborScore;
  unsigned int currentNeighbor;
  unsigned int bestNeighbor;
  double bestNeighborScore;

  unsigned int mask = 0;
  unsigned int bestNeighborBits;
  unsigned int maskedCurrentNumber;
  unsigned int recombinationTry;


  for (int i = 0; i < population.populationSize; i++) {
    currentAgentScore = scoreTable.array[population.population[i]];
    bestNeighborScore = 0.0;

    if (currentAgentScore == 1.0) {
      continue;
    }


    for (int k = 0; k < network.matrix[i].size; k++) {

      currentNeighbor =
          population.population[network.matrix[i].connections[k]];
      currentNeighborScore = scoreTable.array[currentNeighbor];

      if (currentNeighborScore > bestNeighborScore) {
        bestNeighbor = currentNeighbor;
        bestNeighborScore = currentNeighborScore;
      }
    }
    
    for (int k = 0; k < N; k++) {
      double randResult = randomReal();
      if (randResult < recombinationRate) {
        mask = mask | (unsigned int) exp2(k);       
      }
    }

    bestNeighborBits = bestNeighbor & mask;
    maskedCurrentNumber = population.population[i] & (~mask);

    recombinationTry = (unsigned int) (maskedCurrentNumber | bestNeighborBits);
    

    if (scoreTable.array[bestNeighbor] > currentAgentScore) {
      population.population[i] = recombinationTry;
    } else {
      population.population[i] = mutateHyper(population.population[i],
                                             scoreTable,
                                             N);
    }
              

  }

  return population;

}


unsigned int mutateHyper(unsigned int agent,
                         ScoreTable scoreTable,
                         int N)
{
  unsigned int mutatedAgent = 0;
  int randResult;

  for (int i = 0; i < N; i++) {
    randResult = randInt(1, 0);
    if (randResult == 1) {
        mutatedAgent += (unsigned int) exp2(i);
    }
  }
  
  if (scoreTable.array[mutatedAgent] > scoreTable.array[agent]) {
    return mutatedAgent;
  } else {
    return agent;
  }
  
}


Population recombinationHyper2(Population population,
                               ScoreTable scoreTable,
                               Network network,
                               int N,
                               double recombinationRate)
{
  
  float currentAgentScore;
  float currentNeighborScore;
  unsigned int currentNeighbor;
  unsigned int bestNeighbor;
  double bestNeighborScore;

  unsigned int mask = 0;
  unsigned int bestNeighborBits;
  unsigned int maskedCurrentNumber;
  unsigned int recombinationTry;

  for (int i = 0; i < population.populationSize; i++) {
    currentAgentScore = scoreTable.array[population.population[i]];
    bestNeighborScore = 0.0;

    if (currentAgentScore == 1.0) {
      continue;
    }


    for (int k = 0; k < network.matrix[i].size; k++) {

      currentNeighbor =
          population.population[network.matrix[i].connections[k]];
      currentNeighborScore = scoreTable.array[currentNeighbor];

      if (currentNeighborScore > bestNeighborScore) {
        bestNeighbor = currentNeighbor;
        bestNeighborScore = currentNeighborScore;
      }
    }

    if (scoreTable.array[bestNeighbor] > currentAgentScore) {
      population.population[i] = bestNeighbor;
    }              

  }

  return population;

}


Population mutateHyper2(Population population,
                        ScoreTable scoreTable,
                        int N)
{
  unsigned int mutatedAgent;
  int randResult;

  for (int i = 0; i < N; i++) {
    mutatedAgent = 0;
    for (int k = 0; k < N; k++) {
      randResult = randInt(1, 0);
      if (randResult == 1) {
          mutatedAgent += (unsigned int) exp2(k);
      }
    }
    if (scoreTable.array[mutatedAgent] >
          scoreTable.array[population.population[i]]) {
      population.population[i] = mutatedAgent;
    }
  }

  return population;
  
}


Population recombinationConformity(Population population,
                                   ScoreTable scoreTable,
                                   Network network,
                                   int selectionTries,
                                   int N,
                                   double recombinationRate)
{
  
  float currentAgentScore;
  float currentNeighborScore;
  unsigned int currentNeighbor;
  unsigned int bestNeighbor;
  double bestNeighborScore;
  unsigned int allNeighbors[selectionTries];
  unsigned int allNeighborsCount[selectionTries];
  int recombine = 1;
  unsigned int greatestNeighbor;
  unsigned int greatestNeighborCount = 0;
  int selected[selectionTries];

  unsigned int mask = 0;
  unsigned int bestNeighborBits;
  unsigned int maskedCurrentNumber;
  unsigned int recombinationTry;


  for (int i = 0; i < selectionTries; i++) {
    selected[i] = -1;
  }


  for (int i = 0; i < population.populationSize; i++) {
    currentAgentScore = scoreTable.array[population.population[i]];
    bestNeighborScore = 0.0;

    if (currentAgentScore == 1.0) {
      continue;
    }


    for (int k = 0; k < selectionTries; k++) {

      int neighborSelection = (int) randInt(0, network.matrix[i].size - 1);

      for (int m = 0; m < k; m++) {
        if (neighborSelection == selected[m]) {
          neighborSelection = (int) randInt(0, network.matrix[i].size - 1);
          m = 0;
        }
      }

      selected[k] = neighborSelection;

      currentNeighbor =
          population.population[network.matrix[i].connections[neighborSelection]];
      allNeighbors[k] = currentNeighbor;

    }

    for (int k = 0; k < selectionTries; k++) {
      allNeighborsCount[k] = 1;
      currentNeighbor = allNeighbors[k];
      for (int m = k+1; m < selectionTries; m++) {
        if (allNeighbors[m] == currentNeighbor) {
          allNeighbors[k]++;
        }
      }
    }

    for (int k = 0; k < selectionTries; k++) {
      if (allNeighborsCount[k] > greatestNeighborCount) {
        greatestNeighbor = allNeighbors[k];
        recombine = 1;
      } else if (allNeighborsCount[k] == greatestNeighborCount) {
        recombine = 0;
      }
    }

    bestNeighbor = greatestNeighbor;


    for (int k = 0; k < N; k++) {
      double randResult = randomReal();
      if (randResult < recombinationRate) {
        mask = mask | (unsigned int) exp2(k);       
      }
    }

    bestNeighborBits = bestNeighbor & mask;
    maskedCurrentNumber = population.population[i] & (~mask);

    recombinationTry = (unsigned int) (maskedCurrentNumber | bestNeighborBits);

    if ((scoreTable.array[recombinationTry] > currentAgentScore) && (recombine == 1)) {
      population.population[i] = recombinationTry;
    } else {
      population.population[i] = mutateSFI(population.population[i],
                                           scoreTable,
                                           N);
    }

  }

  return population;

}
