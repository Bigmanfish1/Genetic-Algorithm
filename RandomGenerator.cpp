#include "RandomGenerator.h"
using namespace std;

RandomGenerator::RandomGenerator(int seed){
    srand(seed);
    RandomGenerator::seed = seed;
}

bool RandomGenerator::randomBool(){
    int randNum = rand();
    bool val;
    if(randNum%2 == 0){
        val = false;
    }else if(randNum%2 == 1){
        val = true;
    }
    return val;
}