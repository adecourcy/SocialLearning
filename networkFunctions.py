from random import randint

def popSizeToNumConnections(popSize):
    popSize -= 1
    return (popSize * (popSize + 1)) // 2

def createNetwork(popSize, type, demeSize, filename):
    # Just create a random network for now
    network = generateRandomNetworks(popSizeToNumConnections(popSize), 1)
    listFormat = binaryNetworkToList(popSize, network[0])
    networkToFile(listFormat, filename)

def generateRandomNetworks(numConnections, numNetworks):
    networks = []

    for i in range(numNetworks):
        binaryNetwork = 0
        for k in range(numConnections):
            if randint(0, 1) == 1:
                binaryNetwork += (1 << k)
        networks.append(binaryNetwork)
    
    return networks


def binaryNetworkToList(popSize, binaryNetwork):
    networkConnections = []

    for i in range(popSize):
        networkConnections.append([])

    bitPosition = 0

    for i in range(popSize-1):
        for k in range(i+1, popSize):
            if (binaryNetwork & (1 << bitPosition)) != 0:
                networkConnections[i].append(str(k))
                networkConnections[k].append(str(i))
            bitPosition += 1
    
    return networkConnections

def allBinaryNetworksToList(popSize, allNetworks):
    networkLists = []

    for binNet in allNetworks:
        networkLists.append(binaryNetworkToList(popSize, binNet))
    
    return networkLists

def networkToFile(network, filename):
    file = open(filename, "w")
    #file = filename
    for connections in network:
        connectionString = " ".join(connections)
        file.write(str(len(connections)) + " " + connectionString + "\n")
    file.close()

if __name__ == "__main__":
    a = generateRandomNetworks(10, 1)
    b = binaryNetworkToList(10, a[0])
    networkToFile(b, "testNetwork")