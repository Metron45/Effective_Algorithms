#pragma once
#include "Distance_Graph.h"
class Dynamic :
	public Distance_Graph
{
private:
	unsigned *** route_table;
	int visited_all;
	int * final_route;
	int final_res;
	int dynamic(int mask, int position);
	void initialize_route_table();
	int size=0;
public:
	Dynamic();
	~Dynamic();
	int dynamic();
	void draw_route_table(int info_type);
	std::string getFinalRoute();
	int getFinalDistance();
	void write_results();
};

