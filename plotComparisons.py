import sys
import os
import numpy as np
import matplotlib.pyplot as plt

def extractDataHelper(file):
  data = []

  for line in file:
    line = line.strip()
    try:
      data.append(float(line))
    except ValueError:
      return data


def extractData(fileName, triggerLine):
  try:
    dataFile = open(fileName, 'r')
  except FileNotFoundError:
    print("File " + fileName + " not found.")
    exit()

  for line in dataFile:
    line = line.strip()
    if triggerLine == line:
      data = extractDataHelper(dataFile)
      dataFile.close()
      return data


def plotAverageComparison(directory):
  extractAverages = lambda x: extractData(x, "AVERAGE FITNESS") 
  plotDirectory(directory, "Averages.png", extractAverages)


def plotBestComparison(directory):
  extractAverages = lambda x: extractData(x, "AVERAGE BEST FITNESS") 
  plotDirectory(directory, "Best.png", extractAverages)


def plotDirectory(directory, plotName, plotFunction):
  if directory[-1] != "/":
    directory += "/"
  
  plotPath = directory + plotName

  legend = []

  x = [1,2,3,4,5,6,7]

  for file in os.listdir(directory):
    if ".png" not in file:
      filePath = directory + file
      result = plotFunction(filePath)
      plt.plot(x, result)
      legend.append(file)

  plt.ylabel("Score")
  plt.xlabel("K Values")
  plt.xticks(x, ["2", "4", "6", "8", "10", "12", "14"])

  plt.legend(legend)
  plt.savefig(plotPath)
  plt.clf()



def createPlots(directory):
  plotAverageComparison(directory)
  plotBestComparison(directory)

def plotAllDirectories(directory):
  if directory[-1] != "/":
    directory += "/"

  for subDirectory in os.listdir(directory):
    createPlots(directory + subDirectory)

if __name__ == "__main__":
  if len(sys.argv) != 2:
    print("This script takes exactly 1 directory as an argument.")
    exit()

  plotAllDirectories(sys.argv[1])