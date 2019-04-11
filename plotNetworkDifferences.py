import sys
import os
import numpy as np
import matplotlib.pyplot as plt
from typing import *


def findResult(fileName: str) -> float:
  previousLine = ""

  try:
    file = open(fileName, 'r')
  except FileNotFoundError:
    print("File " + fileName + " not fonud.")
    exit()

  for line in file:
    if line == "AVERAGE BEST FITNESS\n":
      return float(previousLine)
    previousLine = line



def singleDifference(directory: str) -> float:

  if directory[-1] != "/":
    directory += "/"

  for file in os.listdir(directory):
    if "LOCAL4" in file:
      localResult = findResult(directory + file)
    if "GLOBAL" in file:
      globalResult = findResult(directory + file)


  difference = localResult - globalResult

  return difference



def sortFolders(folders: List[str]) -> List[str]:
  folderNumbers = []

  for folder in folders:
    folderNumbers.append((folder, int(folder[1:])))

  folderNumbers.sort(key=lambda x: x[1])
  folders = []

  for folder in folderNumbers:
    folders.append(folder[0])

  return folders


def differences(directory: str) -> List[float]:

  result = []

  if directory[-1] != "/":
    directory += "/"

  subDirectories = sortFolders(os.listdir(directory))

  for subDirectory in subDirectories:
    result.append(singleDifference(directory + subDirectory))

  return result


def makePlot(directories: List[str]):

  results = []
  legend = []

  for directory in directories:
    legend.append(directory)

    if directory[-1] != "/":
      directory += "/"

    results.append(differences(directory))

  x = [1,2,3,4,5,6,7]

  for result in results:
    plt.plot(x, result)

  plt.ylabel("Score Differences")
  plt.xlabel("K Values")
  plt.xticks(x, ["2", "4", "6", "8", "10", "12", "14"])

  legend = [x[:-1] for x in legend]

  plt.legend(legend)

  plt.show()


if __name__ == "__main__":
  if len(sys.argv) == 1:
    print("This script must be given at least one directory as an argument.")
    exit()

  makePlot(sys.argv[1:])