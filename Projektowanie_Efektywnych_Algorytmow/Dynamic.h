#pragma once
#include "Distance_Graph.h"
class Dynamic :
	public Distance_Graph
{
private:
	long long *** route_table;
	int visited_all;
public:
	Dynamic();
	~Dynamic();
	void initialize_route_table();
	int dynamic();
	int dynamic(int mask, int position);
	void draw_route_table(int info_type);
	std::string get_route();
	void write_results();
};

