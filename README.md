# Purpose

In brief, this is a social learning simulation. In more detail, a set of homogenous simple agents are trying to find the optimal solution to a given problem. These agents can share information about their current solutions among their immeadiate neighbors. This simulation tests whether different network topologies affect the quality of the final solution.

Put in a more simple sense: say you had fifty engineers trying to come up with a simple problem. What is the best way to team up these engineers to find the best solution to this problem? It might seem intuitively obviously to just have all the engineers communicate with other, but previous research suggests that this is actually sub-optimal. In this case, once a solution is found that is "good enough", all members of the team tend to imitate this solution rather than innovating on their own. If the engineers can only communicate locally (think of the engineers as standing in a circle, with each engineer only able to communicate with their immediate neighbors), and information spreads throughout the group more slowly, all enginners might not immeadiately be exposed to the "good enough" solution. This may force the engineers to innovate on their own to find better solutions to their problem.

This program searches for optimal network topologies (i.e., modes of communication) through the use of a genetic algorithm. It creates "problems" for the agents to solve through the use of NK-landscapes. The simulation goes through a series of time steps, and in each time step the agents have the ability to either adopt a neighbors current solution or to "innovate" on their own.

The main function is located in "calculation.C"
