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
	std::string getFinalRoute();
	int getFinalDistance();
	void write_results();
};

