#include "stdafx.h"
#include "Bruteforce.h"


Bruteforce::Bruteforce()
{
}


Bruteforce::~Bruteforce()
{
}

int Bruteforce::bruteforce()
{
	int * route, distance, * route_shortest, distance_shortest;
	//initialization of Routes
	route_shortest = new int[distance_table_size + 1];
	route =			 new int[distance_table_size + 1];
	for (int i = 0; i <= distance_table_size; ++i) {
		route_shortest[i] = i;
		route[i] = i;
	}
	route_shortest[distance_table_size] = 0;
	route[distance_table_size] = 0;
	//initialization of distance
	distance_shortest = 0;
	for (int i = 0; i < distance_table_size; ++i) {
		distance_shortest += get_distance(route_shortest[i], route_shortest[i + 1]);
	}
	//complete review of all routes
	std::sort(route, route + distance_table_size - 1);
	do{
		distance = 0;
		for (int i = 0; i < distance_table_size; ++i) {
			distance += get_distance(route[i], route[i+1]);
		}
		if (distance_shortest > distance) {
			distance_shortest = distance;
			for (int i = 1; i <= distance_table_size; ++i) {
				route_shortest[i] = route[i];
			}
		}
	} while (std::next_permutation(route + 1, route + distance_table_size));
	std::cout << "Lowest travel value: " << distance_shortest << std::endl;
	std::cout << "Lowest travel route: " << std::endl;
	for (int i = 0; i <= distance_table_size; ++i) {
		std::cout << std::setw(3) << route_shortest[i];
	}
	return distance_shortest;
}