// Projektowanie_Efektywnych_Algorytmow.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Distance_Graph.h"
#include "Bruteforce.h"
#include "Dynamic.h"

int main()
{
	Dynamic matrix;
	matrix.load_from_file("test8.tsp");
	matrix.draw_distance_table();
	matrix.dynamic();

	int useless;
	std::cin >> useless;
}

