#include "stdafx.h"
#include "Bound_And_Branch.h"


Bound_And_Branch::Bound_And_Branch()
{
	final_res = -1;
	visited = 0;
}

Bound_And_Branch::~Bound_And_Branch()
{
	delete[] final_route;
	final_route = NULL;
}

int Bound_And_Branch::minimal_edge(int vertex)
{
	int minimum = -1;
	for (int i = 0; i < get_size(); i++) {
		if (vertex == i) {
			continue;
		}
		if (minimum == -1 || get_distance(vertex, i) < minimum) {
			minimum = get_distance(vertex, i);
		}
	}
	return minimum;
}

int Bound_And_Branch::minimal_second_edge(int vertex)
{
	int first = -1, second = -1;
	for (int i = 0; i < get_size(); i++)
	{
		if (vertex == i) {
			continue;
		}
		if(get_distance(vertex, i) <= first || first == -1 ) {
			second = first;
			first = get_distance(vertex, i);
		}
		else if (get_distance(vertex, i) <= second && get_distance(vertex, i) != first || second == -1) {
			second = get_distance(vertex, i);
		}
	}
	return second;
}

void Bound_And_Branch::temp_to_final(int * temp)
{
	final_route = new int[get_size() + 1];
	for (int i = 0; i < get_size(); i++) {
		final_route[i] = temp[i];
	}
	final_route[get_size()] = 0;
}

std::string Bound_And_Branch::get_route() {
	std::string route;
	for (int i = 0; i < get_size() + 1; i++) {
		route += " ";
		if (final_route[i] >= 10) {
			route += (final_route[i] - (final_route[i] % 10)) / 10 + '0';
			route += (final_route[i] % 10) + '0';
		}
		else {
			route += final_route[i] + '0';
		}
	}

	return route;
}

int Bound_And_Branch::get_final_distance(){
	return final_res;
}

void Bound_And_Branch::write_results()
{
	bnb();
	std::cout << "Lowest travel value: " << get_final_distance() << std::endl;
	std::cout << "Lowest travel route: " << get_route() << std::endl;
}

void Bound_And_Branch::bnb(int curr_bound, int curr_weight, int level, int * curr_route) {
	if (level == get_size()) {
		if (get_distance(curr_route[level - 1], curr_route[0]) != 0)
		{
			int curr_res = curr_weight + get_distance(curr_route[level - 1],curr_route[0]);
			if (curr_res < final_res || final_res == -1){
				temp_to_final(curr_route);
				final_res = curr_res;
			}
		}
	}
	else {
		for (int i = 0; i<get_size(); i++){
			if (get_distance(curr_route[level - 1], i) != 0 && ((visited&(1 << i)) == 0)){
				int temp = curr_bound;
				curr_weight += get_distance(curr_route[level - 1], i);
				curr_bound = calculate_bound(curr_bound, i, level, curr_route);
				if (curr_bound + curr_weight < final_res || final_res == -1)
				{
					curr_route[level] = i;
					visited += 1 << i;
					bnb(curr_bound, curr_weight, level + 1, curr_route);
				}
				curr_weight -= get_distance(curr_route[level - 1],i);
				curr_bound = temp;
				visited = 0;
				for (int j = 0; j < level; j++) {
					visited += (1 << curr_route[j]);
				}
			}
		}
	}
}

int Bound_And_Branch::calculate_bound(int bound, int city, int level, int * route)
{
	int edge_first, edge_second;
	if (level == 1) {
		edge_first = minimal_edge(route[level - 1]);
		edge_second = minimal_edge(city);
		//bound -= ((minimal_edge(route[level - 1]) + minimal_edge(city)) / 2);
	}
	else {
		edge_first = minimal_second_edge(route[level - 1]);
		edge_second = minimal_edge(city);
		//bound -= ((minimal_second_edge(route[level - 1]) + minimal_edge(city)) / 2);
	}
	int temp = edge_first + edge_second;
	temp = (temp & 1 == 1) ? temp / 2 + 1 : temp / 2;
	bound -= temp;
	return bound;
}

void Bound_And_Branch::bnb() {
	int * curr_route, curr_bound = 0; 
	curr_route = new int[get_size() + 1];
	for (int i = 0; i < get_size() + 1; i++) {
		curr_route[i] = -1;
	}
	for (int i = 0; i < get_size(); i++) {
		curr_bound += (minimal_edge(i) + minimal_second_edge(i));
	}
	curr_bound = (curr_bound & 1 == 1) ? curr_bound / 2 + 1 : curr_bound / 2;
	visited = 1;
	curr_route[0] = 0;
	bnb(curr_bound, 0, 1, curr_route);
}