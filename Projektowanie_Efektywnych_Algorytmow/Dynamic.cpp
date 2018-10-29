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
	route_table = new int *[distance_table_size - 1];
	for (int i = 0; i < distance_table_size - 1; i++) {
		route_table[i] = new int[distance_table_size];
	}
}

void Dynamic::initialize_route_table_distance()
{
	for (int i = 0; i < distance_table_size - 1; i++) {
		distance_table[i][1] = i+1;
		distance_table[i][0] = get_distance(0, i + 1);
	}
}

int Dynamic::dynamic()
{
	initialize_route_table();
	initialize_route_table_distance();
	for (int i = 2; i < distance_table_size; i++) {

	}

	return 0;
}

int Dynamic::dynamic(int * S, int sizeS, int i)
{
	return 0;
}
