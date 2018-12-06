#pragma once
#include "Distance_Graph.h"

struct tour {
	int * route;
	int fitness;
};

class Simulated_Annealing : 
	public Distance_Graph
{
public:
	Simulated_Annealing();
	~Simulated_Annealing();
	

	
	void Set_temperature(float max, float rate, float min, int iterations);
	int Calculate();

//private:
	float max_temperature;
	float cooling_rate;
	float min_temperature;
	int max_iterations;

	int calculate_tour_cost(tour x);
	bool calculate_probability(tour x, tour y, float temp);
	int change_in_cost(tour x, tour y);
	
};

