#include "stdafx.h"
#include "Distance_Graph.h"


struct Candidate {
	int * chromosome;
	int fitness;
};


class Genetic : 
	public Distance_Graph
{
public:
	Genetic();
	~Genetic();

	void Initialize(int size, int mating_pool_part, float tournament_pool_part, float mutation_chance);
	int Calculate(int solution_time);

	Candidate *mating_pool;
	Candidate *population;
	bool * participating;
	Candidate * tournament;

	int population_size;
	int mating_pool_size;
	int tournament_pool_size;
	float mutation_chance;

	Candidate best_solution;

	void set_initial_population();
	void initialize_chromosome();
	
	void mutate();

	void cross_population_OX();
	void reset_population();
	void cross_population_cross_section(int parent1, int parent2, int children_index, int k1, int k2);
	void cross_population_rest(int parent, int children_index, int k1, int k2);

	void tournament_selection();
	void tournament_participants();
	void tournament_sort();

	void show_population();
	void show_mating_pool();

	void show_best_solution();

	void calc_fitness();

	Candidate find_best_candidate(Candidate *  candidates, int size);
	void set_best_candidate();
	int calculate_tour_cost(Candidate x);

	float error_rate(std::string problem_name);

	void reset();

	void Test(std::string problem_name);


};
