# ga-tsp
This is old code. Most is from 2004-2007. 

## Compile
Compile on Ubuntu/Debian:
Make sure build-essential is installed:
```
sudo apt install build-essential
```
Then, in a folder, holding all the cpp-files, compile like this:
```
g++ *.cpp -o ga-tsp -O2
```
Or create a makefile if you wish. There isn't a lot of code, so not a whole lot can be gained in compilations speed from using make. 

Run the compiled executable like this:
```
./ga-tsp
```
## GA stuff implemented
This GA is implements parent and child populations, elitism, selection pressure, PMX crossovers, mutations, solution evaluation, fixed alphabet, fixed length integer sequence solutions.

### Abstract base class problem
The GA takes a pointer to a abstract base class problem. TSP is a specialization of the abstract problem base class. It is possible to create other specializations of problem for other types of problems and that way reuse the most of the other code unchanged.

A problem class specialization must implement the following member methods:

#### Encode
Creates a valid random solution. This is used to create the initial random population.
##### Mutate
Introduces a small scramble of a solution that results in another valid, slightly changed solution or possibly (re-)introduce missing "genetic material". This may help prevent ending up in a local minimum in the search volume.
#### Crossover
Recombines two parent solutions to create two new valid child solutions, based on the parent solution sequences. A optimized version of PMX (Partially Mixed Crossover) is used. PMX is a crossover method that allows two solutions to be recombined without disturbing the existing partial sequences too much. Nice for fixed length, fixed alphabet solutions.
#### Evaluate
Calculates the fitness/cost for a solution. Makes it possible to compare solutions. Elitism (making the best solution s "immortal") and selection pressure (creating a bias in selecting solutions for crossovers) ensures that the best solutions are used more often when generating child solutions for the next generation. And that makes it more likely that child solutions better than the parent solutions are created.

More description to follow...
