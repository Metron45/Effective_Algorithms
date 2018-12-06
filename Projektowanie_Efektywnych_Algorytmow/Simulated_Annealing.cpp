#include "stdafx.h"
#include "Simulated_Annealing.h"


Simulated_Annealing::Simulated_Annealing()
{
}


Simulated_Annealing::~Simulated_Annealing()
{
}

void Simulated_Annealing::Set_temperature(float max, float rate, float min, int iterations)
{
	max_temperature = max;
	cooling_rate = rate;
	min_temperature = min;
	max_iterations = iterations;

}

int Simulated_Annealing::Calculate()
{
	float temperature = max_temperature;
	tour current, next;
	//initialization
	current.route = new int[get_size()];
	for (int i = 0; i < get_size(); i++) {
		current.route[i] = i;
	}
	current.fitness = calculate_tour_cost(current);

	
	int iteration = 0;

	//iterations
	while (temperature > min_temperature && iteration < max_iterations) {
		//redo route for next
		next.route = new int[get_size()];
		for (int i = 0; i < get_size(); i++) {
			next.route[i] = current.route[i];
		}
		//swap 2 random cities
		int point_x, point_y;
		point_x = rand() % get_size();
		do {
			point_y = rand() % get_size();
		} while (point_y == point_x);
		std::swap(next.route[point_x], next.route[point_y]);
		//calculate next route fitness

		next.fitness = calculate_tour_cost(next);

		//check if woth checking
		if (next.fitness < current.fitness) {
			current = next;
		}
		else if (calculate_probability(current,next,temperature)) {
			current = next;
		}

		temperature *= cooling_rate;
		iteration++;
	}


	return current.fitness;
}

int Simulated_Annealing::calculate_tour_cost(tour x)
{
	int tour_cost = 0;
	for (int i = 1; i < get_size(); i++)
	{
		tour_cost += get_distance(x.route[i - 1], x.route[i]);
	}
	tour_cost += get_distance(x.route[get_size() - 1], x.route[0]);
	return tour_cost;
}

bool Simulated_Annealing::calculate_probability(tour x, tour y, float temp)
{
	if ((float)rand() / (1.0*RAND_MAX) < exp(-1.0*(change_in_cost(y,x)) / temp)) {
		return true;
	}
	else {
		return false;
	}
}

int Simulated_Annealing::change_in_cost(tour x, tour y)
{
	return x.fitness - y.fitness;
}
