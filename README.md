# Genetic Algorithm in C++

This C++ project implements a Genetic Algorithm (GA) as part of the COS110 first year course at the University of Pretoria. The goal of the assignment was to use a GA to evolve a population of chromosomes to contain only 1s. The project demonstrates proficiency in C++ programming, dynamic memory management, and class design.

## Implementation Details
#### RandomGenerator
- Responsible for generating random numbers used in the algorithm.

- Initialized with a seed value for reproducibility.

- Provides a method to generate random boolean values.

#### Chromosome

- Represents an individual in the population.

- Supports various constructors for initialization.

- Implements functions for crossover, mutation, fitness calculation, and string representation.

- Demonstrates proper use of dynamic memory allocation and deallocation.
#### FitnessFunction

- Calculates the fitness of a chromosome based on the number of 1s in its genes.
- Ensures that the fitness function avoids integer division.
  
#### GA (Genetic Algorithm)

- Manages the population, selection, crossover, mutation, and running generations.
- Uses classes like Chromosome and RandomGenerator to create a complete GA.
- Ensures proper memory management throughout the algorithm.
- Provides functions to calculate average fitness, standard deviation, and variance of the population.
