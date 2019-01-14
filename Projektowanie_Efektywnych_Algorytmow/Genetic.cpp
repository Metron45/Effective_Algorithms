#include "stdafx.h"
#include "Genetic.h"


Genetic::Genetic()
{
	population = new Candidate[1];
	Initialize(1,1,1, 1);
	
}

Genetic::~Genetic()
{
}

void Genetic::Initialize(int size, int mating_pool_part, float tournament_pool_part, float mutation_ch)
{
	population_size = size;
	mating_pool_size = mating_pool_part;
	tournament_pool_size = population_size * tournament_pool_part;
	
	mating_pool = new Candidate[mating_pool_size];
	for (int i = 0; i < mating_pool_size; i++) {
		mating_pool[i].chromosome = new int[get_size()];
	}
	participating = new bool[population_size];
	tournament = new Candidate[tournament_pool_size];

	best_solution.chromosome = new int[get_size()];

	mutation_chance = mutation_ch;

	population = new Candidate[population_size];
	for (int i = 0; i < population_size; i++) {
		population[i].chromosome = new int[get_size()];
	}

	reset();
}

int Genetic::Calculate(int solution_time)
{	
	//srand(time(NULL));
	//For multiple tests you need to start random outside the Calculate function.
	set_initial_population();

	int curr_time = 0;
	std::chrono::steady_clock::time_point clock_start = std::chrono::steady_clock::now();
	while (curr_time < solution_time) {
		tournament_selection();
		cross_population_OX();
		mutate();
		calc_fitness();
		set_best_candidate();
		curr_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - clock_start).count();
	}

	//best_solution = find_best_candidate(population, population_size);
	//checking for best candidate each round resulted in much better solutions
	return best_solution.fitness;
}

void Genetic::set_initial_population()
{
	initialize_chromosome();
}

void Genetic::initialize_chromosome() {
	for (int i = 0; i < population_size; i++) {
		for (int j = 0; j < get_size(); j++) {
			population[i].chromosome[j] = j;
		}
		for (int j = 0; j < get_size(); j++) {
			int random_point = rand() % get_size();
			std::swap(population[i].chromosome[j], population[i].chromosome[random_point]);
		}
		population[i].fitness = calculate_tour_cost(population[i]);
	}
}

void Genetic::mutate()
{
	for (int i = 0; i < population_size; i++) {
		if (((rand() % 1000) / 1000) < mutation_chance) {
			int k1 = rand() % get_size();
			int k2;
			do {
				k2 = rand() % get_size();
			} while (k1 == k2);

			int temp = population[i].chromosome[k1];
			population[i].chromosome[k1] = population[i].chromosome[k2];
			population[i].chromosome[k2] = temp;
		}
	}
}

void Genetic::cross_population_OX() {
	int parent1, parent2;
	int k1, k2;
	int number_of_breeds = population_size / 2;

	reset_population();
	for (int i = 0; i < number_of_breeds; i++)
	{
	
		parent1 = rand() % mating_pool_size;
		do{
			parent2 = rand() % mating_pool_size;
		} while (parent1 == parent2);

		k1 = rand() % get_size();
		do {
			k2 = rand() % get_size();
		} while (k1 == k2);

		if (k2 < k1) {
			int temp = k1;
			k1 = k2;
			k2 = temp;
		}
		
		cross_population_cross_section(parent1, parent2, i * 2, k1, k2);
		
		cross_population_rest(parent2, i * 2, k1, k2);
		cross_population_rest(parent1, i * 2 + 1, k1, k2);
	}
}

void Genetic::reset_population() {
	for (int i = 0; i < population_size; i++) {
		for (int j = 0; j < get_size(); j++) {
			population[i].chromosome[j] = -1;
		}
	}
}

void Genetic::cross_population_cross_section(int parent1, int parent2, int children_index, int k1, int k2) {
	
	for (int j = k1; j < k2; j++) {
		population[children_index].chromosome[j]	 = mating_pool[parent1].chromosome[j];
		population[children_index + 1].chromosome[j] = mating_pool[parent2].chromosome[j];
	}


}

void Genetic::cross_population_rest(int parent, int children_index, int k1, int k2) {

	int chromosome_parent = k2;
	bool conflict = false;

	for (int i = k2; i <get_size(); i++) {
		conflict = true;
		while (conflict == true) {
			conflict = false;
			for (int j = 0; j < get_size(); j++) {
				if (population[children_index].chromosome[j] == mating_pool[parent].chromosome[chromosome_parent]) {
					conflict = true;
					break;
				}
			}
			if (conflict == false) {
				population[children_index].chromosome[i] = mating_pool[parent].chromosome[chromosome_parent];
			}
			else {
				chromosome_parent++;
				if (chromosome_parent >= get_size()) {
					chromosome_parent = 0;
				}
			}
		}
	}

	for (int i = 0; i < k1; i++) {
		conflict = true;
		while (conflict == true) {
			conflict = false;
			for (int j = 0; j < get_size(); j++) {
				if (population[children_index].chromosome[j] == mating_pool[parent].chromosome[chromosome_parent]) {
					conflict = true;
					break;
				}
			}
			if (conflict == false) {
				population[children_index].chromosome[i] = mating_pool[parent].chromosome[chromosome_parent];
			}
			else {
				chromosome_parent++;
				if (chromosome_parent >= get_size()) {
					chromosome_parent = 0;
				}
			}
		}
	}

}

void Genetic::tournament_selection() {

	for (int i = 0; i < mating_pool_size; i++) {
		tournament_participants();
		Candidate winner = find_best_candidate(tournament, tournament_pool_size);
		for (int j = 0; j < get_size(); j++) {
			mating_pool[i].chromosome[j] = winner.chromosome[j];
		}
		mating_pool[i].fitness = winner.fitness;
	}
}

void Genetic::tournament_participants() {

	for (int i = 0; i < population_size; i++) {
		participating[i] = false;
	}

	for (int i = 0; i < tournament_pool_size; i++) {
		int random_candidate = rand() % population_size;
		while (participating[random_candidate] == true) {
			random_candidate = rand() % population_size;
		}
		tournament[i] = population[random_candidate];
		participating[random_candidate] = true;
	}

}

void Genetic::tournament_sort() {
	//there is no need for sort in my current version of the algorithm
	//it can be used to randomly choose one of the first of the the tournament participants
	//instead I just use the best participant
	for (int i = 0; i < mating_pool_size - 1; i++) {
		for (int j = 0; j < mating_pool_size - 1 - i; j++) {
			if (mating_pool[j].fitness > mating_pool[j + 1].fitness) {
				Candidate temp;
				temp = mating_pool[j];
				mating_pool[j] = mating_pool[j + 1];
				mating_pool[j + 1] = temp;
			}
		}
	}
}

void Genetic::show_population()
{
	std::cout << std::endl;
	std::cout << std::endl;
	for (int i = 0; i < population_size; i++) {
		std::cout << "Population: " << i << " Fit: " << population[i].fitness << " Route: ";
		for (int j = 0; j < get_size(); j++) {
			std::cout << population[i].chromosome[j] << " ";
		}
		std::cout << std::endl;
	}
}

void Genetic::show_mating_pool()
{
	std::cout << std::endl;
	std::cout << std::endl;
	for (int i = 0; i < mating_pool_size; i++) {
		std::cout << "Mates: " << i << " Fit: " << mating_pool[i].fitness << " Route: ";
		for (int j = 0; j < get_size(); j++) {
			std::cout << mating_pool[i].chromosome[j] << " ";
		}
		std::cout << std::endl;
	}
}

void Genetic::show_best_solution() {
	std::cout << "Best: " << " Fit: " << best_solution.fitness << " Route: ";
	for (int j = 0; j < get_size(); j++) {
		std::cout << best_solution.chromosome[j] << " ";
	}
	std::cout << std::endl;
}

void Genetic::calc_fitness() {
	for (int i = 0; i < population_size; i++) {
		population[i].fitness = calculate_tour_cost(population[i]);
	}
}

Candidate Genetic::find_best_candidate(Candidate * candidates, int size) {
	int best = 0;
	int best_fitness = candidates[0].fitness;
	for (int i = 1; i < size; i++) {
		if (candidates[i].fitness < best_fitness) {
			best_fitness = candidates[i].fitness;
			best = i;
		}
	}

	return candidates[best];
}

void Genetic::set_best_candidate() {
	Candidate best_candidate = find_best_candidate(population,population_size);
	if (best_candidate.fitness < best_solution.fitness) {
		best_solution.fitness = best_candidate.fitness;
		for (int i = 0; i < get_size(); i++) {
			best_solution.chromosome[i] = best_candidate.chromosome[i];
		}
	}
}

int Genetic::calculate_tour_cost(Candidate candidate) {
	int tour_cost = 0;
	for (int i = 1; i < get_size(); i++)
	{
		tour_cost += get_distance(candidate.chromosome[i - 1], candidate.chromosome[i]);
	}
	tour_cost += get_distance(candidate.chromosome[get_size() - 1], candidate.chromosome[0]);
	return tour_cost;
}

float Genetic::error_rate(std::string problem_name)
{
	std::ifstream file("solutions.txt");
	std::string line, name, distance;
	float result;

	if (file.is_open())
	{
		int position;
		while (name + ".tsp" != problem_name)
		{
			std::getline(file, line);
			position = line.find(' ');
			name = line.substr(0, position);
		}
		position += 3;
		distance = line.substr(position, line.size() - 1);

		result = best_solution.fitness - std::stof(distance);
		file.close();
		return result / std::stoi(distance);
	}
	else
	{
		std::cout << "there is not solutions.txt file" << std::endl; \
			return -1;
	}
}

void Genetic::reset() {
	reset_population();
	for (int i = 0; i < mating_pool_size; i++) {
		for (int j = 0; j < get_size(); j++) {
			mating_pool[i].chromosome[j] = -1;
		}
		mating_pool[i].fitness = INT_MAX;
	}
	for (int j = 0; j < get_size(); j++) {
		best_solution.chromosome[j] = -1;
	}
	best_solution.fitness = INT_MAX;
}