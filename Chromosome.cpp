#include "Chromosome.h"
using namespace std;

Chromosome::Chromosome(int numGenes, RandomGenerator *rand)
{
    

    if (numGenes < 0)
    {
        Chromosome::numGenes = 0;
        genes = new bool[0];
    }
    else if (rand == NULL)
    {
        Chromosome::numGenes = numGenes;
        genes = new bool[Chromosome::numGenes];
        for (int j = 0; j < Chromosome::numGenes; j++)
        {
            genes[j] = false;
        }
    }
    else
    {
        Chromosome::numGenes = numGenes;
        genes = new bool[Chromosome::numGenes];
        for (int i = 0; i < Chromosome::numGenes; i++)
        {
            genes[i] = rand->randomBool(); // array of genes is a chromosome
        }
    }
}

Chromosome::Chromosome(Chromosome *chromosome)
{
    

    if (chromosome == NULL)
    {
        Chromosome::numGenes = 0;
        genes = new bool[0];
    }
    else
    {
        Chromosome::numGenes = chromosome->numGenes;
        genes = new bool[Chromosome::numGenes];
        for (int i = 0; i < Chromosome::numGenes; i++)
        {
            genes[i] = chromosome->genes[i];
        }
    }


}

Chromosome::Chromosome(bool *genes, int numGenes)
{
    

    if (numGenes < 0)
    {
        Chromosome::numGenes = 0;
        Chromosome::genes = new bool[0];
    }
    else if (genes == NULL)
    {
        Chromosome::numGenes = numGenes;
        Chromosome::genes = new bool[Chromosome::numGenes];
        for (int i = 0; i < Chromosome::numGenes; i++)
        {
            Chromosome::genes[i] = false;
        }
    }
    else
    {
        Chromosome::numGenes = numGenes;
        Chromosome::genes = new bool[Chromosome::numGenes];
        for (int i = 0; i < Chromosome::numGenes; i++)
        {
            Chromosome::genes[i] = genes[i];
        }
    }
}

Chromosome::~Chromosome()
{
    if(genes != NULL){
        delete[] genes;
        genes = NULL;
    }
    
}

double Chromosome::fitness(FitnessFunction *fitnessFunction, Chromosome *chromosome, int numGenes)
{
    double fitness;
    if (fitnessFunction == NULL)
    {
        fitness = 0;
    }else if(chromosome == NULL){
        fitness = 0;
    }else if(numGenes <= 0){
        fitness = 0;
    }else{
        fitness = fitnessFunction->calculateFitness(chromosome, chromosome->numGenes);
    }
    return fitness;
}

int Chromosome::getNumGenes()
{
    return Chromosome::numGenes;
}

Chromosome *Chromosome::crossOver(Chromosome *c2)
{ 
    Chromosome *cPtr;
    
    if (c2 == NULL)
    {
        cPtr = new Chromosome(this);
    }
    else
    {
        int crossOverPoint = floor((c2->numGenes/2)); 
        bool *nGenes = new bool[Chromosome::numGenes];
        for (int i = 0; i < crossOverPoint; i++)
        {
            nGenes[i] = this->genes[i];
        }

        for (int k = crossOverPoint; k < Chromosome::numGenes; k++)
        {
            nGenes[k] = c2->genes[k];
        }
        
        cPtr = new Chromosome(nGenes, Chromosome::numGenes);
        
        delete[] nGenes;
        nGenes = NULL;
    }
    

    return cPtr;

}

Chromosome *Chromosome::mutate()
{ 
    bool *nGenes = new bool[Chromosome::numGenes];
    for (int i = 0; i < Chromosome::numGenes; i++)
    {
        if(genes[i] == true){
            nGenes[i] = false;
        }else if(genes[i] == false){
            nGenes[i] = true;
        }
    }
    Chromosome *cPtr = new Chromosome(nGenes, Chromosome::numGenes);
    
    delete[] nGenes;
    nGenes = NULL;
    
    return cPtr;
}

string Chromosome::toString()
{
    string gene;
    if (Chromosome::numGenes == 0)
    {
            gene = "";
    }
    else
    {
        gene = "";
        for (int i = 0; i < Chromosome::numGenes; i++)
        {
            if (genes[i] == true)
            {
                gene += '1';
            }
            else if (genes[i] == false)
            {
                gene += '0';
            }
        }
        
    }
    return gene;
}

bool *Chromosome::getGenes()
{
    return Chromosome::genes;
}
