#pragma once
#include "Distance_Graph.h"
class Bruteforce :
	public Distance_Graph
{
private:
	int * final_route;
	int final_res;
public:
	Bruteforce();
	~Bruteforce();
	int bruteforce();
	std::string get_route();
	int get_final_distance();
	void write_results();
};

