#include "FitnessFunction.h"
using namespace std;

double FitnessFunction::calculateFitness(Chromosome* chromosome, int numGenes){
    double count = 0.0;
    //bool* gPtr = chromosome->getGenes();
    
    for(int i = 0; i < numGenes; i++){
        if(chromosome->getGenes()[i] == true){ 
            count += 1.0;
        }
    }
    double m = count;
    double n = (1.0*numGenes);
    double fitness = m/n;
    return fitness;
}

