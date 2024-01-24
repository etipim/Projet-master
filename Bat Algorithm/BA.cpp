//
// Created by etipi on 09/01/2024.
//

#include "BA.h"
#include "Agent.h"
#include <random>

OriginalBA::OriginalBA(int epoch, int popSize, double loudness, double pulse_rate, double pfMin, double pfMax, int dimention, int fit_function)
{
    this->epoch = epoch;
    this->popSize = popSize;
    this->loudness = loudness;
    this->pulse_rate = pulse_rate;
    this->pfMin = pfMin;
    this->pfMax = pfMax;

    this->fit_function = fit_function;

    this->Lb = -10;
    this->Ub = 10;

    // dimention
    this->dimention = dimention;
}

// générer la population
void OriginalBA::generate_population()
{
    //std::vector<std::vector<int>> pop;
    //std::vector<int> fitness;

    for (int i = 0; i < this->popSize; ++i) {
        this->pop.push_back(init_bat());
        this->fitness.push_back(init_fitness(pop[i]));
    }

    this->best_fitness = this->fitness[0];
}

// avoir la meilleur solution
void OriginalBA::search_best_sol()
{
    this->g_best = this->pop[index_best_fitness()];
}

// Algo global
void OriginalBA::bat_algo()
{
    int t = 0;
    while (t < this->epoch)
    {

        std::vector<Agent*> pop_new;
        for (int idx = 0; idx < this->popSize; ++idx) {
            // init agent
            Agent* agent = new Agent();
            agent->solution = this->pop[idx]->solution;
            agent->velocity = this->pop[idx]->velocity;
            double pulse_frequency = this->pfMin + (this->pfMax - this->pfMin) * random(0., 1.); // Eq. 2

            // change pulse frequency
            //std::uniform_real_distribution<double> distributionPf(this->pfMin, this->pfMax);
            //agent->pulse_frequency = distributionPf(this->generator);


            Agent* x_new = new Agent();
            x_new->solution = this->pop[idx]->solution;
            for (int i = 0; i < this->dimention; ++i) {
                // change velocity
                agent->velocity[i] = agent->velocity[i] + pulse_frequency * (this->pop[idx]->solution[i] - this->g_best->solution[i]);  // Eq. 3
                // change solution
                if (this->pop[idx]->solution[i] + agent->velocity[i] > this->Ub){
                    x_new->solution[i] = this->Ub;
                } if (this->pop[idx]->solution[i] + agent->velocity[i] < this->Lb){
                    x_new->solution[i] = this->Lb;
                } else {
                    x_new->solution[i] = this->pop[idx]->solution[i] + agent->velocity[i];  // Eq. 4
                }


                // search around g_best position
                //if (random(0, 1) > this->pulse_rate){
                //    x_new->solution[i] = this->g_best->solution[i] + 0.001 * random(0, this->dimention);
                //}
            }

            agent->solution = x_new->solution;

            pop_new.push_back(agent);
        }


        std::vector<int> pop_child_index;
        std::vector<Agent*> pop_child;
        for (int idx = 0; idx < this->popSize; ++idx) {
            //if (this->fitness[idx] > init_fitness(pop_new[idx]) && random(0, 1) < this->loudness){
            if (this->fitness[idx] > init_fitness(pop_new[idx])) {
                this->pop[idx] = pop_new[idx];
                this->fitness[idx] = init_fitness(pop_new[idx]);
            } else {
                if (random(0, 1) < this->pulse_rate) {
                    Agent* agent = new Agent();
                    agent->solution = this->pop[idx]->solution;
                    agent->velocity = this->pop[idx]->velocity;
                    for (int i = 0; i < this->dimention; ++i) {
                        double new_sol = new double();
                                this->g_best->solution[i] + 0.01 * random(this->Lb, this->Ub);
                        if (new_sol > this->Ub){
                            agent->solution[i] = this->Ub;
                        } if (new_sol < this->Lb){
                            agent->solution[i] = this->Lb;
                        } else {
                            agent->solution[i] = new_sol;  // Eq. 4
                        }
                    }
                    pop_child_index.push_back(idx);
                    pop_child.push_back(agent);
                }
            }
        }

        for (int idx = 0; idx < pop_child_index.size(); ++idx) {
//            if (init_fitness(pop_new[pop_child_index[idx]]) > init_fitness(pop_child[idx])) {
//                pop_new[pop_child_index[idx]] = pop_child[idx];
//                //this->fitness[pop_child_index[idx]] = init_fitness(pop_child[idx]);
//            }

            if (this->fitness[pop_child_index[idx]] > init_fitness(pop_child[idx])) {
                this->pop[pop_child_index[idx]] = pop_child[idx];
                this->fitness[pop_child_index[idx]] = init_fitness(pop_child[idx]);
            }
        }

        //this->pop = pop_new;
        for (int idx = 0; idx < this->popSize; ++idx) {
            this->fitness[idx] = init_fitness(this->pop[idx]);
            if (this->fitness[idx] < this->best_fitness){
                this->best_fitness = this->fitness[idx];
            }
        }


        //this->loudness = 0.97 * this->loudness;
        //pulse_rate = 1 - std::exp(-0.1 * t);
        search_best_sol();

        t +=1;
    }
}

Agent* OriginalBA::init_bat()
{
    // Génération d'un nombre aléatoire selon une distribution uniforme
    std::uniform_real_distribution<double> distribution(this->Lb, this->Ub);
    //std::uniform_real_distribution<double> distributionVelo(-50.0, 50.0);
    std::uniform_real_distribution<double> distributionFrequency(this->pfMin, this->pfMax);

    Agent* bats = new Agent();

    bats->pulse_frequency = distributionFrequency(generator);

    for (int i = 0; i < this->dimention; ++i) {
        bats->solution.push_back(distribution(this->generator));
        bats->velocity.push_back(0);
    }

    return bats;
}

double OriginalBA::init_fitness(Agent* bat)
{
    double sum = 0.0;
    for (int i = 0; i < bat->solution.size(); ++i) {

        // Sphère
        if (fit_function == 1) {
            sum += bat->solution[i]*bat->solution[i]; // (bat->solution[i] - 2) * (bat->solution[i] - 2);
        }

            // Rastrigin
        else if (fit_function == 2) {
            sum += bat->solution[i] * bat->solution[i] - 10.0 * std::cos(2.0 * M_PI * bat->solution[i]) + 10.0;
        }

            // Rosenbrock
        else if (fit_function == 3) {
            if (i < bat->solution.size() - 1) {
                sum += 100.0 * std::pow((bat->solution[i + 1] - std::pow(bat->solution[i], 2)), 2) +
                       std::pow((bat->solution[i] - 1.0), 2);
            }
        }

            // Ackley
        else if (fit_function == 4) {
            double term1 = -20.0 * std::exp(-0.2 * std::sqrt(0.5 * (std::pow(bat->solution[i], 2) + std::pow(bat->solution[i + 1], 2))));
            double term2 = -std::exp(0.5 * (std::cos(2.0 * M_PI * bat->solution[i]) + std::cos(2.0 * M_PI * bat->solution[i + 1])));
            sum += term1 + term2 + 20.0 + std::exp(1.0);
            i++; // Because Ackley function is typically defined for two dimensions, we increment i again.
        }
    }
    return sum;
}

int OriginalBA::index_best_fitness()
{
    int min = this->fitness[0];
    int best_index = 0;
    for (int i = 1; i < this->fitness.size(); ++i) {
        if (this->fitness[i] < min){
            min = this->fitness[i];
            best_index = i;
        }
    }

    return best_index;
}

double OriginalBA::random(double min, double max)
{
    std::random_device rd;  // Utilisé pour obtenir une seed pour le générateur
    std::mt19937 gen(rd() + static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count())); // Générateur Mersenne Twister

    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(gen);
}

double OriginalBA::mean_loudness()
{
    double sum = 0.0;

    for (int i = 0; i < this->popSize; ++i) {
       // sum += this->pop[i]->loudness;
    }

    return sum / this->popSize;
}