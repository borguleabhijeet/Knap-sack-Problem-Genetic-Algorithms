# Knap-sack-Problem-Genetic-Algorithms
is report represents a 0-1 knapsack problem using Genetic Algorithms. The knapsack problem is an NP hard optimization problem. The genetic algorithm maximizes the benefit in a knapsack with limiting the capacity of the knapsack. The Knap sack implementation has 3 parts with two different selection procedure as shown in homework.

1) The first GA consists of the roulette wheel selection, 3-point crossover, and bit-wise mutation. 
2) The second GA consists of the (pair-wise) strict tournament selection, 3-point crossover, and bit-wise mutation.

In our problem we have given population size 100, crossover probability 0.90 and mutation probability 0.01. We have solved this problem by considering all the population. The GA consist of following steps:

1. Initialize population: Generate chromosomes
A. Chromosomes size is equal to the items size 500. It encodes the problem as select as 1 and reject as 0 in binary form.
B. The randomly selected chromosomes of size 500 are generated 100 times since we have population of 100.
2. Check the Fitness: Check the fitness of the generated population
3. Selection of population: Selection procedure is Roulette wheel selection and Tournament selection
A. We first select the population by rotating our wheel 100th times and the new population is then processed for the cross over step.
B. The second GA selects the population based on the pair wise tournament selection a randomly selected population has been compared with all the population. The fitness is then processed for the cross over step. 
4. Cross Over: 3-point crossover
A. After the selection step 2, we create the new crossover 50 times to generate the 100 new population.
5. Check the Fitness: Check the fitness of the population
6. Evaluation: We compare the old population fitness and newly generated population fitness.
A. If the fitness of new population is greater than new old population we continue for the Roulette wheel selection procedure.
B. If a selected population exceeds the weight limit we set up the fitness to 0.
7. Stop:
A. We stop our iteration after the 100th iteration as store the best maximum fitness and average fitness to plot the graph.
