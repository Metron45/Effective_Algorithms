#include "stdafx.h"
#include "Dynamic.h"


Dynamic::Dynamic()
{

}


Dynamic::~Dynamic()
{
	delete[] route_table;
	route_table = NULL;
}

void Dynamic::initialize_route_table() 
{
	route_table = new int *[distance_table_size-1];
	for (int i = 0; i < distance_table_size-1; i++) {
		route_table[i] = new int[distance_table_size];
	}
	initialize_route_table_distance();
}

void Dynamic::initialize_route_table_distance()
{
	for (int i = 0; i < distance_table_size - 1; i++) {
		route_table[i][1] = i+1;
		route_table[i][0] = get_distance(0, i + 1);
		for (int y = 2; y < distance_table_size; y++) {
			route_table[i][y] = -1;
		}
	}
}

bool Dynamic::check_visited(int city, int route) {
	int route_position = 1;
	while (route_position < distance_table_size ) {
		if (city == route_table[route][route_position]) {
			return false;
		} 
		else if (route_table[route][route_position] <= 0) {
			return true;
		}
		route_position++;
	}
	return true;
}

void Dynamic::redo_routes(int * new_route, int route_iteration) {
	int ** new_route_table = new int *[distance_table_size - 1];
	for (int line = 0; line < distance_table_size - 1; line++) {
		new_route_table[line] = new int[distance_table_size-1];
		if (route_table[line][0] > 0) {
			for (int column = 0; column < distance_table_size - 1; column++) {
				new_route_table[line][column] = route_table[new_route[line]][column + 1];
			}
			new_route_table[line][route_iteration - 1] = line + 1;
		}
	}

	for (int line = 0; line < distance_table_size - 1; line++) {
		if (route_table[line][0] > 0) {
			for (int column = 0; column < distance_table_size - 1; column++) {
				route_table[line][column + 1] = new_route_table[line][column];
			}
		}
	}
}

int Dynamic::dynamic()
{
	//for S only having 2 elements
	initialize_route_table();
	draw_route_table();
	//for S having over 2 elements 
	int *new_distance, *new_route;
	for (int route_iteration = 2; route_iteration < distance_table_size; route_iteration++) {
		new_distance =	new int[distance_table_size - 1];
		new_route =		new int[distance_table_size - 1];
		for (int route = 0; route < distance_table_size - 1; route++) {
			if (route_table[route][0] > 0) {
				new_distance[route] = 0;
				//znalezienie min
				for (int route_min = 0; route_min < distance_table_size - 1; route_min++) {
					if (check_visited(route + 1, route_min) && route_table[route_min][0] > 0) {
						if (new_distance[route] <= 0) {
							new_distance[route] = get_distance(route_table[route_min][route_iteration - 1], route + 1);
							new_route[route] = route_min;
						}
						else if (route_table[route_min][0] + get_distance(route_table[route_min][route_iteration - 1], route + 1) < new_distance[route]) {
							new_distance[route] = get_distance(route_table[route_min][route_iteration - 1], route + 1);
							new_route[route] = route_min;
						}
					}
				}
				if (new_distance[route] == 0) {
					route_table[route][0] = -1;
				}
			}
			else {
				new_route[route] = -1;
			}
		}
		draw_route_table();
		for (int route = 0; route < distance_table_size - 1; route++) {
			if (route_table[route][0] > 0) {
				route_table[route][0] += new_distance[route];
			}
		}
		redo_routes(new_route, route_iteration);
	}
	return 0;
}

void Dynamic::draw_route_table() {
	std::cout <<"Route Table for dynamic programming" << std::endl;
	for (int line = 0; line < distance_table_size-1; line++) {
		std::cout << line << ": " ;
		for (int column = 0; column < distance_table_size; column++) {
			std::cout << std::setw(4) << route_table[line][column];
		}
		std::cout << std::endl;
	}
}


int Dynamic::dynamic(int * S, int sizeS, int i)
{
	return 0;
}
