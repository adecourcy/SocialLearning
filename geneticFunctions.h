Population recombinationSFI(Population population,
                            ScoreTable scoreTable,
                            Network network,
                            int selectionTries,
                            int N,
                            double recombinationRate);
unsigned int mutateSFI(unsigned int agent,
                       ScoreTable scoreTable,
                       int N);


Population recombinationAllSame(Population population,
                                ScoreTable scoreTable,
                                Network network,
                                int selectionTries,
                                int N,
                                double recombinationRate);
Population mutateAllSame(Population agent,
                         ScoreTable scoreTable,
                         int N,
                         double mutationRate);

Population recombinationHyper(Population population,
                              ScoreTable scoreTable,
                              Network network,
                              int N,
                              double recombinationRate);

unsigned int mutateHyper(unsigned int agent, ScoreTable scoreTable, int N);

Population recombinationHyper2(Population population,
                              ScoreTable scoreTable,
                              Network network,
                              int N,
                              double recombinationRate);

Population mutateHyper2(Population agent, ScoreTable scoreTable, int N);


Population recombinationConformity(Population population,
                                   ScoreTable scoreTable,
                                   Network network,
                                   int selectionTries,
                                   int N,
                                   double recombinationRate);
