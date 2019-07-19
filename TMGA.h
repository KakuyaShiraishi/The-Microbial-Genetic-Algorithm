#ifndef TMGA_TMGA_h
#define TMGA_TMGA_h
#include <vector>
extern "C" {
#include "dSFMT.h"
}


using namespace std;

typedef vector<unsigned int> genotype;

class objectiveFunctionEvaluator {
public:
    virtual float evaluate(genotype &a) = 0;
};

class TMGA {
public:
    enum fitnessComparisonTypes {
        HIGHSCOREISBEST, LOWSCOREISBEST
    } fitnessComparisonType;
    TMGA(unsigned int populationSize, unsigned int demeSize, unsigned int geneSize, float recombinationRate, float mutationRate,
                objectiveFunctionEvaluator *evaluator, fitnessComparisonTypes comparisonType, int reportEvery);
    ~TMGA();
    void evolve(unsigned int numIterations);
    void evolveUntil(float threshold);
    genotype& getFittestIndividual();
    static void genotypeToFloat(genotype &g, vector<float> &floatdata);
private:
    void prepareToEvolve();
    unsigned int populationSize, demeSize, geneSize;
    float recombinationRate, mutationRate;
    vector<genotype> population;
    objectiveFunctionEvaluator *evaluator;
    unsigned int geneCharSize;
    
    void microbialTournament();
    inline unsigned char bitwiseInfectAndMutate(const unsigned char a, const unsigned char b);
    
    float smoothedFitness, bestFitness;
    unsigned int bestFitnessIndex;
    int reportPeriod;
    
    dsfmt_t *mtRand;
    
    inline float randUF() {
//        return (float)rand() / (float) RAND_MAX;
        return dsfmt_genrand_close_open(mtRand);
    }

};

#endif
