#include "SimulatedAnnealing.hpp"

double acceptance_probability(int energy, int new_energy, double temperature)
{
    if (new_energy < energy)
        return 1.0;

    return exp((energy - new_energy) / temperature);
}

void simulated_annealing()
{
    double temp = 10000;
    double cooling_rate = 0.01;
    int iter = 10000;

   // Schedule current_solution(generate_tree_from_file());
    Schedule current_solution(generate_random_tree(7));

    current_solution.mix_hops();

    Schedule best = current_solution;

    cout << "Rozwiazanie poczatkowe max_delay = "
            << best.get_max_delay() << endl;

    best.to_string_matrix();

  // clock_t start = clock();
   // while ( (clock() - start)/CLOCKS_PER_SEC <= 10) {
    while (iter > 0) {
        Schedule new_solution = current_solution;

        int pos1 = random_num(0, new_solution.size_of_matrix()-1);
        int pos2 = random_num(0, new_solution.size_of_matrix()-1);

        new_solution.replace_hops(pos1, pos2);

        int current_energy = current_solution.get_energy();
        int neighbor_energy = new_solution.get_energy();

        if (acceptance_probability(current_energy, neighbor_energy, temp) >
                                   random_num_real(0, 1)) {

            current_solution = new_solution;
           // current_solution.remove_empty_slots();
        }

        if (current_solution.get_energy() < best.get_energy())
            best = current_solution;

        temp *= 1 - cooling_rate;
        iter--;
    }
    best.remove_empty_slots();
    cout << "Rozwiazanie koncowe max_delay = " << best.get_max_delay() << endl;
    best.to_string_matrix();
}
