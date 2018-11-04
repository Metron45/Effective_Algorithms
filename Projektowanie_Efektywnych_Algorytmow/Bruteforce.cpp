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
	final_res = distance_shortest;
	final_route = new int[get_size() + 1];
	for (int i = 0; i <= distance_table_size; ++i) {
		final_route[i] = route_shortest[i];
	}
	return distance_shortest;
}

std::string Bruteforce::get_route()
{
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

int Bruteforce::get_final_distance()
{
	return final_res;
}

void Bruteforce::write_results()
{
	bruteforce();
	std::cout << "Lowest travel value: " << get_final_distance() << std::endl;
	std::cout << "Lowest travel route: " << get_route() << std::endl;
}
