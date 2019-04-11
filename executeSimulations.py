from networkFunctions import *
import os, sys

def malformedFile():
  print('malformed input file')
  exit()

def executeSimulations(file):

  for line in file:
    if line == "BEGIN LANDS\n":
      createLandscapes(file)
    elif line == "BEGIN POPS\n":
      createPopulations(file)
    elif line == "BEGIN EXPS\n":
      executeExperiment(file)


def createLandscapes(file):

  # parameter order: FILE N K NUM

  for line in file:
    if line == "END LANDS\n" or line == "END LANDS":
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


def createPopulations(file):

  # parameter order: FILE N POPSIZE NUM

  for line in file:
    if line == "END POPS\n" or line == "END POPS":
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


def executeExperiment(file):

  # parameter order:
  # N K POPSIZE SELTRIES NUMGENS NUMPOPS NUMLANDS
  # RECRATE NETTYPE DEMESIZE LFILE PFILE EXPNAME

  for line in file:
    if line == "END EXPS\n" or line == "END EXPS":
      break
    else:
      parameters = line.split()

      if len(parameters) != 15:
        print("Not all experiment parameters are specified")
        exit()
      
      createNetwork(int(parameters[2]),
                    parameters[9],
                    int(parameters[10]),
                    parameters[11])

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
                                             parameters[11],
                                             parameters[12],
                                             parameters[13],
                                             parameters[14]))


if __name__ == "__main__":

  if not os.path.isfile("./generatePopulations"):
    os.system("gcc -o generatePopulations generatePopulations.c supportFunctions.c population.c -lm")
  if not os.path.isfile("./generateScoreTables"):
    os.system("gcc -o generateScoreTables generateScoreTables.c supportFunctions.c landscapes.c scoreTable.c -lm")
  if not os.path.isfile("./simulate"):
    os.system("gcc -o simulate calculation.c geneticFunctions.c landscapes.c networks.c population.c results.c scoreTable.c supportFunctions.c -lm")

  try:
    parametersFile = open(sys.argv[1], 'r')
  except FileNotFoundError:
    print("Could not open input file\n")
    exit()

  executeSimulations(parametersFile)