#pragma once
#include "Distance_Graph.h"
class Dynamic :
	public Distance_Graph
{
private:
	int ** route_table;
public:
	Dynamic();
	~Dynamic();
	void initialize_route_table();
	void initialize_route_table_distance();
	int dynamic();
	int dynamic(int * S, int sizeS, int i);
};

