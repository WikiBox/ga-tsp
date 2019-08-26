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
Or create a makefile if you wish. There is not much code, so not a lot to gain in compilations speed. 

Run the executable like this:
```
./ga-tsp
```
## GA stuff implemented
This GA is implements parent and child populations, elitism, selection pressure, PMX crossovers, mutations, solution evaluation, integer sequence solutions.

### Abstract base class problem
The GA takes a pointer to a abstract base class problem. TSP is a problem. It is possible to create other specializations of problem for other types of problems and reuse the other code unchanged.

A problem class specialisation must provide the following member methods:

#### Encode
Create a valid random solution.
##### Mutate
Introduce a small scramble of a solution that results in another valid, slightly changed solution or possibly (re-)introduce missing "genetic material".
#### Crossover
Recombine two parent solutions to create two new valid child solutions, based on the parents. PMX (Partially Mixed Crossover) is used. That is a crossover method that allows two solutions to be recombined without disturbing the existing partial sequences too much. Good for fixed "alphabet" solutions consisting of integer sequences.
#### Evaluate
Calculate fitness/cost for a solution. Elitism and selection pressure ensures that the best solutions are used more often when generating child solutions for the next generation. 

More description to follow...
