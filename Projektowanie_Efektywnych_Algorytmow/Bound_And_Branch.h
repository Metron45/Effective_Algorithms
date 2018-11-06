#pragma once
#include "Distance_Graph.h"

struct Node {
	int curr_bound;
	int * curr_route;
	int level;
	int ** matrix;
};

class Bound_And_Branch :
	public Distance_Graph
{
private:


	std::vector<Node> nodeTable;

	int * final_route;
	int final_value;
	Node copyNode(Node node);
	void temp_to_final(int * temp);
	int minLine(int vertex, int pass, int ** matrix);
	int minColumn(int vertex, int pass, int ** matrix);
	int reduceMatrixCost(int x, int y, int ** matrix);
	void bnb(Node node);


public:
	void debug_draw(int ** matrix);
	Bound_And_Branch();
	~Bound_And_Branch();
	void bnb();
	std::string getFinalRoute();
	int getFinalDistance();
	void write_results();
	
};

	