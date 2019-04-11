#!/usr/bin/env python3

from random import *
from networkFunctions import *
import os
from sys import argv


def createLandscapes(i, fileArgs):

  # parameter order: FILE N K NUM

  while(True):
    line = fileArgs[i]
    i += 1
    if "END" in line:
      break
    else:
      parameters = line.split()
      if len(parameters) != 4:
        print("Not all landscape parameters are specified\n")
        exit()

      os.system("./generateScoreTables {} {} {} {}".format(parameters[0],
                                                           parameters[1],
                                                           parameters[2],
                                                           parameters[3]))


def createPopulations(i, fileArgs):

  # parameter order: FILE N POPSIZE NUM

  while(True):
    line = fileArgs[i]
    i += 1
    if "END" in line:
      break
    else:
      parameters = line.split()

      if len(parameters) != 4:
          print("Not all population parameters are specified")
          exit()

      os.system("./generatePopulations {} {} {} {}".format(parameters[0],
                                                           parameters[1],
                                                           parameters[2],
                                                           parameters[3]))


def getNetworkScores(network,
                     networkScores,
                     parameters,
                     networkFileName,
                     resultsFileName):

  if network in networkScores:
    return networkScores[network]

  popSize = int(parameters[2])
  listRep = binaryNetworkToList(popSize, network)
  networkToFile(listRep, networkFileName)

  finished = \
    os.system("./simulate {} {} {} {} {} \
                          {} {} {} {} {} \
                          {} {} {}".format(parameters[0],
                                           parameters[1],
                                           parameters[2],
                                           parameters[3],
                                           parameters[4],
                                           parameters[5],
                                           parameters[6],
                                           parameters[7],
                                           parameters[8],
                                           networkFileName,
                                           parameters[9],
                                           parameters[10],
                                           resultsFileName))

  if finished != 0:
    exit()


  try:
    networkFile = open(networkFileName, 'r+')
  except:
    print("Cannot open network file for temporary storage.\nTerminating...")
    exit()

  try:
    resultsFile = open(resultsFileName, 'r+')
  except:
    print("Cannot open results file for temporary storage.\nTerminating...")
    exit()


  oldLine = ''
  for line in resultsFile:
    #print(line)
    if 'FINAL GENERATION' in line:
      score = float(oldLine.strip())
      break
    else:
      oldLine = line

  resultsFile.seek(0)
  resultsFile.truncate()
  resultsFile.close()

  networkFile.seek(0)
  networkFile.truncate()
  networkFile.close()

  return score


def executeTournament(fileName,
                      numNetworks,
                      numGenerations,
                      recombinationRate,
                      mutationRate,
                      outputFile):

  networkFileName = "tempNetworkRepresentationFile"
  resultsFileName = "tempNKResultsFile"

  try:
    output = open(outputFile, 'w')
  except:
    print("Cannot open file " + outputFile + " for output.\nTerminating...")
    exit()

  try:
    genOutput = open(outputFile + ".generations", 'w')
  except:
    print("Cannot open file " + outputFile + ".generations" + " for output.\nTerminating...")
    exit()


  # Make sure we can actually write to these files before we do a bunch of
  # failed computations

  try:
    networkFile = open(networkFileName, 'w')
  except:
    print("Cannot open network file for temporary storage.\nTerminating...")
    exit()

  try:
    resultsFile = open(resultsFileName, 'w')
  except:
    print("Cannot open results file for temporary storage.\nTerminating...")
    exit()

  networkFile.close()
  resultsFile.close()

  if not os.path.isfile("./generatePopulations"):
    os.system("gcc -o generatePopulations generatePopulations.c supportFunctions.c population.c -lm")
  if not os.path.isfile("./generateScoreTables"):
    os.system("gcc -o generateScoreTables generateScoreTables.c supportFunctions.c landscapes.c scoreTable.c -lm")
  if not os.path.isfile("./simulate"):
    os.system("gcc -o simulate calculation.c geneticFunctions.c landscapes.c networks.c population.c results.c scoreTable.c supportFunctions.c -lm")

  with open(fileName) as f:
    fileParameters = f.read()
  fileParameters = fileParameters.split("\n")

  for i in range(0, len(fileParameters)):
    if fileParameters[i] == "BEGIN LANDS":
      createLandscapes(i+1, fileParameters)
    elif fileParameters[i] == "BEGIN POPS":
      createPopulations(i+1, fileParameters)
    elif fileParameters[i] == "BEGIN EXPS":
      startExperiments = i+1
      break

  parameters = fileParameters[startExperiments]
  parameters = parameters.split()
  startExperiments += 1

  parameters[0] = int(parameters[0])
  parameters[1] = int(parameters[1])
  parameters[2] = int(parameters[2])
  parameters[3] = int(parameters[3])
  parameters[4] = int(parameters[4])
  parameters[5] = int(parameters[5])
  parameters[6] = int(parameters[6])
  parameters[7] = float(parameters[7])
  parameters[8] = float(parameters[8])

  numConnections = popSizeToNumConnections(parameters[2])
  networks = generateRandomNetworks(numConnections, numNetworks)
  networkScores = {}
  networkIndices = [x for x in range(numNetworks)]

  generationScore = []


  for i in range(numGenerations):
    currentGenerationScores = []

    for network in networks:
      score = getNetworkScores(network,
                               networkScores,
                               parameters,
                               networkFileName,
                               resultsFileName)
      networkScores[network] = score
      currentGenerationScores.append(score)

    generationScore.append(currentGenerationScores)

    for k in range(numNetworks):
      cmprIndices = sample(networkIndices, 2)
      score1  = getNetworkScores(networks[cmprIndices[0]],
                                 networkScores,
                                 parameters,
                                 networkFileName,
                                 resultsFileName)

      score2  = getNetworkScores(networks[cmprIndices[1]],
                                 networkScores,
                                 parameters,
                                 networkFileName,
                                 resultsFileName)

      if score1 > score2:
        greater = 0
        lesser = 1
      elif score1 < score2:
        greater = 1
        lesser = 0
      else:
        continue

      newSolution = recombination(networks[cmprIndices[greater]],
                                  networks[cmprIndices[lesser]],
                                  recombinationRate,
                                  numConnections)
      newSolution = mutation(newSolution, mutationRate, numConnections)

      newScore = getNetworkScores(newSolution,
                            networkScores,
                            parameters,
                            networkFileName,
                            resultsFileName)

      networks[cmprIndices[lesser]] = newSolution

      newScore = getNetworkScores(newSolution,
                                  networkScores,
                                  parameters,
                                  networkFileName,
                                  resultsFileName)

      networkScores[newSolution] = newScore

      # print(score1)
      # print(score2)

      # print(cmprIndices[greater])
      # print(cmprIndices[lesser])

      # print(networkScores[networks[cmprIndices[greater]]])
      # print(networkScores[networks[cmprIndices[lesser]]])
      # input()


  solutions = []

  for network in networks:
    solutions.append((network, getNetworkScores(network,
                                                networkScores,
                                                parameters,
                                                networkFileName,
                                                resultsFileName)))

  solutions.sort(key=lambda x: x[1], reverse=True)

  for solution in solutions:
    output.write(str(solution[0]) + " " + str(solution[1]) + "\n")

  for i in range(0, len(generationScore)):
    genOutput.write("GENERATION " + str(i) + "\n")
    for score in generationScore[i]:
      genOutput.write(str(score) + "\n")



def recombination(greaterSolution,
                  lesserSolution,
                  recombinationRate,
                  numConnections):

  for i in range(numConnections):
    if uniform(0, 1) < recombinationRate:
      lesserSolution = lesserSolution & ~(1 << i)
      replacementBit = greaterSolution & (1 << i)
      lesserSolution = lesserSolution | replacementBit
    
  return lesserSolution


def mutation(solution, mutationRate, numConnections):
  # roll to mutate between 0-25 genes and generate numbers of which bits to flip
  # use uniform distribution
  for i in range(numConnections):
    if uniform(0, 1) < mutationRate:
      solution = solution ^ (1 << i)
    
  return solution


if __name__ == "__main__":
  fileName = argv[1]
  numNetworks = int(argv[2])
  numGenerations = int(argv[3])
  recombinationRate = float(argv[4])
  mutationRate = float(argv[5])
  outputFile = argv[6]

  executeTournament(fileName,
                    numNetworks,
                    numGenerations,
                    recombinationRate,
                    mutationRate,
                    outputFile)