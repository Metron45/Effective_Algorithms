#pragma once
#include "Distance_Graph.h"
class Bound_And_Branch :
	public Distance_Graph
{
private:
	int * final_route;
	int final_res;
	int visited;

	int minimal_edge(int vertex);
	int minimal_second_edge(int vertex);
	void temp_to_final(int * temp);
	void bnb(int curr_bound, int current_weight, int level, int * current_path);
	int calculate_bound(int curr_bound, int city, int level, int * route);
public:
	Bound_And_Branch();
	~Bound_And_Branch();
	void bnb();
	std::string get_route();
	int get_final_distance();
	void write_results();
	
};

	