#pragma once
#include "Distance_Graph.h"
class Bruteforce :
	public Distance_Graph
{
private:

public:
	Bruteforce();
	~Bruteforce();
	int bruteforce();
	void write_results();
};

