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
	bool check_visited(int city, int route);
	void redo_routes(int * new_route, int route_iteration);
	int dynamic();
	void draw_route_table();
	int dynamic(int * S, int sizeS, int i);
};

