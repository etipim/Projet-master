//
// Created by etipi on 09/01/2024.
//

#ifndef BAT_ALGORITHM_BA_H
#define BAT_ALGORITHM_BA_H

#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include <functional>
#include <algorithm>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <chrono>

#include "Agent.h"


class OriginalBA {
public:
    OriginalBA(int epoch = 1000, int popSize = 50, double loudness = 0.8, double pulse_rate = 0.95, double pfMin = 0., double pfMax = 10, int dimention = 30, int fit_function = 1);
    Agent solve();
    void generate_population();
    void search_best_sol();
    void bat_algo();
private:
    Agent* init_bat(); //std::vector<int> init_bat();
    double init_fitness(Agent* bat);
    int index_best_fitness();
    double random(double min, double max);
    double mean_loudness();


    Agent generateEmptyAgent(int solution);
    void evolve();



    std::vector<Agent*> pop;  //std::vector<std::vector<int>> pop;
    std::vector<double> fitness;

    Agent* g_best;
    double best_fitness;
    int fit_function;

    int epoch;
    int popSize;
    double loudness;
    double pulse_rate;
    double pfMin;
    double pfMax;
    int dimention;

    double Lb; //lower bounds
    double Ub; //Upper bounds

    // Déclaration et initialisation du générateur de nombres aléatoires
    std::default_random_engine generator;
};

#endif //BAT_ALGORITHM_BA_H
