#include "GA.h"
using namespace std;

GA::GA(int populationSize, RandomGenerator *rand, int numGenes, int selectionSize)
{
    GA::populationSize = populationSize;
    GA::selectionSize = selectionSize;
    population = new Chromosome *[GA::populationSize];
    for (int i = 0; i < GA::populationSize; i++)
    {
        GA::population[i] = new Chromosome(numGenes, rand);
    }
}

GA::GA(GA *geneticAlgorithm)
{
    GA::populationSize = geneticAlgorithm->populationSize;
    GA::selectionSize = geneticAlgorithm->selectionSize;
    GA::population = new Chromosome *[GA::populationSize];
    for (int i = 0; i < GA::populationSize; i++)
    {
        GA::population[i] = new Chromosome(geneticAlgorithm->population[i]);
    }
}

GA::~GA()
{
    
    if((population != NULL)){
        for(int i = 0; i < populationSize; i++){
            if((population[i] != NULL)){
                delete population[i];
            }
        }
        delete[] population;
        population = NULL;
    }
    
}

Chromosome **GA::selection(FitnessFunction *fitnessFunction)
{
    double *fitArr = new double[populationSize];
    int *numArr = new int[populationSize];
    Chromosome** pop = new Chromosome*[populationSize];

    for(int i = 0; i < populationSize; i++){
        pop[i] = population[i];
    }

    for (int i = 0; i < populationSize; i++)
    {
        fitArr[i] = fitnessFunction->calculateFitness(pop[i], pop[i]->getNumGenes());
        numArr[i] = i;
    }

    for (int i = 0; i < populationSize-1; i++)
    {
        for (int j = i+1; j < populationSize; j++)
        {
            if (fitArr[i] < fitArr[j])
            {
                Chromosome *temp = pop[i];
                pop[i] = pop[j];
                pop[j] = temp;

                double temp1 = fitArr[i];
                fitArr[i] = fitArr[j];
                fitArr[j] = temp1;

                int temp2 = numArr[i];
                numArr[i] = numArr[j];
                numArr[j] = temp2;
            }
        }
    }

    for (int i = 0; i < populationSize-1; i++)
    {
        for (int j = i+1; j < populationSize; j++)
        {
            if (fitArr[i] == fitArr[j])
            {
                if (numArr[i] > numArr[j])
                {
                    Chromosome *temp = pop[i];
                    pop[i] = pop[j];
                    pop[j] = temp;

                    int temp2 = numArr[i];
                    numArr[i] = numArr[j];
                    numArr[j] = temp2;

                }
            }
        }
    }
    
    delete [] numArr;
    numArr = NULL;
    delete [] fitArr;
    fitArr = NULL;

    return pop;
} 

Chromosome **GA::inverseSelection(FitnessFunction *fitnessFunction)
{
    double *fitArr = new double[populationSize];
    int *numArr = new int[populationSize];

    Chromosome** popu = new Chromosome*[populationSize];

    for(int i = 0; i < populationSize; i++){
        popu[i] = population[i];
    }

    for (int i = 0; i < populationSize; i++)
    {
        fitArr[i] = fitnessFunction->calculateFitness(popu[i], popu[i]->getNumGenes());
        numArr[i] = i;
    }

    for (int i = 0; i < populationSize-1; i++)
    {
        for (int j = i+1; j < populationSize; j++)
        {
            if (fitArr[j] < fitArr[i])
            {
                Chromosome *temp = popu[i];
                popu[i] = popu[j];
                popu[j] = temp;

                double temp1 = fitArr[i];
                fitArr[i] = fitArr[j];
                fitArr[j] = temp1;

                int temp2 = numArr[i];
                numArr[i] = numArr[j];
                numArr[j] = temp2;
            }
        }
    }

    
    for (int i = 0; i < populationSize-1; i++)
    {
        for (int j = i+1; j < populationSize; j++)
        {
            if (fitArr[i] == fitArr[j])
            {
                if (numArr[i] < numArr[j])
                {
                    Chromosome *temp = popu[i];
                    popu[i] = popu[j];
                    popu[j] = temp;

                    int temp2 = numArr[i];
                    numArr[i] = numArr[j];
                    numArr[j] = temp2;

                }
            }
        }
    }
    
    delete [] numArr;
    numArr = NULL;
    delete [] fitArr;
    fitArr = NULL;
    
    return popu;
}

Chromosome **GA::crossOver(Chromosome *c1, Chromosome *c2)
{
    Chromosome** arr = new Chromosome*[2];
    arr[0] = c1->crossOver(c2);
    arr[1] = c2->crossOver(c1);
    return arr;
}

Chromosome *GA::mutate(Chromosome *c1)
{
    return c1->mutate();
}

double GA::calculateAvgAccuracy(FitnessFunction *fitnessFunction)
{
    double tot = 0;
    for(int i = 0; i < populationSize; i++){
        double val = fitnessFunction->calculateFitness(population[i], population[i]->getNumGenes());
        tot += val;
    }
    double ave = tot/(1.0*populationSize);
    return ave;
}

double GA::calculateStd(FitnessFunction *fitnessFunction)
{
    double sumproduct = 0;
    double ave = calculateAvgAccuracy(fitnessFunction);
    for(int i = 0; i < populationSize; i++){
        double fit = fitnessFunction->calculateFitness(population[i], population[i]->getNumGenes());
        double diff = (fit-ave);
        sumproduct += pow(diff,2);
    }

    double brac = (sumproduct/(populationSize));
    double std = sqrt(brac);
    return std;
}

double GA::calculateVariance()
{
    double numU = 0.0;
    for(int i = 0; i < populationSize; i++){
        int j;
        for(j = 0; j < i; j++){
            if(population[i]->toString() == population[j]->toString()){
                break;
            }
        }
        if(i == j){
            numU += 1.0;
        }
    }
    
    double var = numU/populationSize;
    return var;
}

void GA::setPopulation(Chromosome **p)
{
    for(int i = 0; i < populationSize; i++){
        population[i] = new Chromosome(p[i]);
    }
}

Chromosome **GA::run(FitnessFunction* fitnessFunction)
{
    Chromosome** winners = selection(fitnessFunction);
    Chromosome** losers = inverseSelection(fitnessFunction);
    Chromosome** offsprings = new Chromosome* [3*selectionSize];
    Chromosome** P = new Chromosome* [populationSize];

    for(int i = 0; i < (2*selectionSize);i++){
        Chromosome** nChromosome = crossOver(winners[i], winners[i+1]);
        offsprings[i] = nChromosome[0];
        offsprings[i+1] = nChromosome[1];
        i++;
        delete[] nChromosome;
        nChromosome = NULL;
        
    }

    for(int i = 0; i < selectionSize;i++){
        offsprings[i+2*selectionSize] = mutate(winners[i+2*selectionSize]);
    }

    //P = new Chromosome*[populationSize];

    for(int i = 0; i < populationSize; i++){
        P[i] = population[i];
    }

    for(int i = 0; i < 3*selectionSize; i++){
        Chromosome* dyingChromosome = losers[i];
        int u;
        for(int j = 0; j < populationSize; j++){
            if(P[j] == dyingChromosome){
                u = j;
                break;
            }
        }
        P[u] = offsprings[i];
    }

    delete[] offsprings;
    offsprings = NULL;
    
    delete[] winners;
    winners = NULL;
    
    delete[] losers;
    losers = NULL;

    return P;
}

double **GA::run(FitnessFunction *fitnessFunction, int numGenerations)
{

    double** results = new double* [numGenerations]; 
    for(int i = 0; i < numGenerations; i++){
        results[i] = new double [3];
    }
    
    for(int i = 0; i < numGenerations; i++){
        Chromosome** P = run(fitnessFunction);
        population = P;
        results[i][0] = calculateAvgAccuracy(fitnessFunction);
        results[i][1] = calculateStd(fitnessFunction);
        results[i][2] = calculateVariance();
        
        
    }

    return results;
}


