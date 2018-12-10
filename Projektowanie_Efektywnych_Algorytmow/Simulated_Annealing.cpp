#include "stdafx.h"
#include "Simulated_Annealing.h"


Simulated_Annealing::Simulated_Annealing()
{
}


Simulated_Annealing::~Simulated_Annealing()
{
	delete[] current.route;
	delete[] next.route;
}

void Simulated_Annealing::Set_route_size()
{
	current.route = new int[get_size()];
	next.route = new int[get_size()];
}

void Simulated_Annealing::Set_temperature(float max, float rate)
{
	max_temperature = max;
	cooling_rate = rate;

}



int Simulated_Annealing::Calculate()
{
	float temperature = max_temperature;
	//initialization
	for (int i = 0; i < get_size(); i++) {
		current.route[i] = i;
	}
	for (int i = 0; i < get_size(); i++) {
		int random_point = rand() % get_size();
		std::swap(next.route[i], next.route[random_point]);
	}
	current.fitness = calculate_tour_cost(current);

	//iterations
	while (temperature > 0.1) {
		//redo route for next
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

		//check if worth checking
		if (next.fitness < current.fitness) {
			for (int i = 0; i < get_size(); i++) {
				current.route[i] = next.route[i];
			}
			current.fitness = next.fitness;
		}
		else if (calculate_probability(current, next, temperature)) {
			for (int i = 0; i < get_size(); i++) {
				current.route[i] = next.route[i];
			}
			current.fitness = next.fitness;
		}

		//cool down and increase iteration
		temperature *= cooling_rate;
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
	double acceptance, random;
	acceptance = 1 / (1 + exp(change_in_cost(y, x) / temp)) / 2;
	random = (double)rand() / (1.0*RAND_MAX);

	if (random < acceptance) {
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
