#include "WOA.h"
#include "BA.h"
#include <time.h>


double calcul(const std::vector<double>& solution) {
    double s = 0;
    for (int i = 0; i < solution.size(); i++) {
        s += pow(solution[i], 2);
    }
    return s;
}

void testWOA() {
    std::vector<double> lb = { -10, -15, -4, -2, -8 };
    std::vector<double> ub = { 10, 15, 12, 8, 20 };

    OriginalWOA* test = new OriginalWOA(1000, 50);

    std::vector<double> res = test->solve(lb, ub, calcul);

    std::cout << "Solution:";
    for (int i = 0; i < res.size() - 1; i++)
        std::cout << res[i] << "|";
    std::cout << std::endl << "Valeurs :" << res[res.size() - 1];
}

void BA() {
    OriginalBA* originalBa = new OriginalBA();

    originalBa->generate_population();
    originalBa->search_best_sol();
    originalBa->bat_algo();
}


int main()
{
        BA();

        return 0;
}

