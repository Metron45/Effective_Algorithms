// Projektowanie_Efektywnych_Algorytmow.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Distance_Graph.h"

int main()
{
	Distance_Graph sd;
	sd.load_from_file();
	sd.draw_distance_table();
	int useless;
	std::cin >> useless;
}

