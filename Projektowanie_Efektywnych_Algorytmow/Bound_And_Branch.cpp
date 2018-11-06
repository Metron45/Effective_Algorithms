#include "stdafx.h"
#include "Bound_And_Branch.h"


Bound_And_Branch::Bound_And_Branch()
{
	final_value = INT_MAX;
}

Bound_And_Branch::~Bound_And_Branch()
{
	delete[] final_route;
	final_route = NULL;
}

int Bound_And_Branch::minLine(int vertex, int pass, int ** matrix)
{
	int minimum = INT_MAX;
	for (int i = 0; i < get_size(); i++) {
			if (matrix[vertex][i] < minimum && i != pass) {
				minimum = matrix[vertex][i];
			}
	}
	if (minimum < INT_MAX) {
		return minimum;
	}
	else {
		return 0;
	}
}

int Bound_And_Branch::minColumn(int vertex, int pass, int ** matrix)
{
	int minimum = INT_MAX;
	for (int i = 0; i < get_size(); i++) {
			if (matrix[i][vertex] < minimum && i != pass) {
				minimum = matrix[i][vertex];
			}
	}
	if (minimum < INT_MAX) {
		return minimum;
	}
	else {
		return 0;
	}
}

int Bound_And_Branch::reduceMatrixCost(int x, int y, int ** matrix){

	int reduction = 0;
	int temp = matrix[y][x];

	matrix[y][x] = INT_MAX;

	//reduction of lines
	for (int i = 0; i < get_size(); i++) {
		if (i != x ) {
			reduction += minLine(i, y, matrix);
		}
	}
	//reduction of columnt
	for (int i = 0; i < get_size(); i++) {
		if (i != y) {
			reduction += minColumn(i, x, matrix);
		}
	}
	matrix[y][x] = temp;

	return reduction;
}

Node Bound_And_Branch::copyNode(Node node)
{
	Node newNode;

	newNode.curr_bound = node.curr_bound;
	newNode.level = node.level;

	newNode.curr_route = new int [get_size()];
	newNode.matrix = new int *[get_size()];

	for (int i = 0; i < get_size(); i++) {
		newNode.curr_route[i] = node.curr_route[i];
		newNode.matrix[i] = new int [get_size()];
		for (int j = 0; j < get_size(); j++) {
			newNode.matrix[i][j] = node.matrix[i][j];
		}
	}

	return newNode;
}

void Bound_And_Branch::temp_to_final(int * temp)
{
	final_route = new int[get_size() + 1];
	for (int i = 0; i < get_size(); i++) {
		final_route[i] = temp[i];
	}
	final_route[get_size()] = 0;
}

std::string Bound_And_Branch::getFinalRoute() {
	std::string route;
	for (int i = 0; i < get_size() + 1; i++) {
		route += " ";
		if (final_route[i] >= 10) {
			route += (final_route[i] - (final_route[i] % 10)) / 10 + '0';
			route += (final_route[i] % 10) + '0';
		}
		else {
			route += final_route[i] + '0';
		}
	}

	return route;
}

int Bound_And_Branch::getFinalDistance(){
	return final_value;
}

void Bound_And_Branch::write_results()
{
	bnb();
	std::cout << "Lowest travel value: " << getFinalDistance() << std::endl;
	std::cout << "Lowest travel route: " << getFinalRoute() << std::endl;
}



void Bound_And_Branch::bnb(Node node) {
	
	if (node.level == get_size())
	{
		temp_to_final(node.curr_route);
		final_value = node.curr_bound;
	}
	else {
		//dodanie nowych node
		int bound = INT_MAX;
		for (int i = 0; i < get_size(); i++)
		{
			if (node.matrix[node.curr_route[node.level - 1]][i] != INT_MAX)
			{
				//calculating next bound
				int temp_bound ;
				temp_bound = node.matrix[node.curr_route[node.level - 1]][i];
				temp_bound += node.curr_bound;
				temp_bound += reduceMatrixCost(node.curr_route[node.level - 1], i, node.matrix);
				//creating next node
				Node nextNode;
				nextNode = copyNode(node);
				nextNode.curr_route[nextNode.level] = i;
				nextNode.curr_bound = temp_bound;
				
				//setting correct rows to INF
				for (int i = 0; i < get_size(); i++) {
					nextNode.matrix[nextNode.curr_route[nextNode.level - 1]][i] = INT_MAX;
					nextNode.matrix[i][nextNode.curr_route[nextNode.level]] = INT_MAX;
				}
				nextNode.matrix[nextNode.curr_route[nextNode.level]][0] = INT_MAX;
				//reduction of lines
				for (int i = 0; i < get_size(); i++) {
					int min = minLine(i, -1, nextNode.matrix);
					for (int j = 0; j < get_size(); j++) {
						if (nextNode.matrix[i][j] != INT_MAX) {
							nextNode.matrix[i][j] -= min;
						}
					}
				}
				//reduction of columns
				for (int i = 0; i < get_size(); i++) {
					int min = minColumn(i, -1, nextNode.matrix);
					for (int j = 0; j < get_size(); j++) {
						if (nextNode.matrix[j][i] != INT_MAX) {
							nextNode.matrix[j][i] -= min;
						}

					}
				}
				nextNode.level++;
				//adding node to node table
				nodeTable.push_back(nextNode);
			}
		}
		//finding next minimal node and earasing it from the list
		Node next = copyNode(nodeTable[0]);
		int iteration=0, i = 0;
		for (std::vector<Node>::iterator it = nodeTable.begin(); it != nodeTable.end(); ++it) {
			if (it->curr_bound < next.curr_bound) {
				next = copyNode(*it);
				iteration = i;
			}
			//std::cout << std::endl << "Node   Table: ";
			//std::cout << "Bound:" << it->curr_bound;
			//std::cout << " Next City:" << it->curr_route[it->level - 1];
			//std::cout << " Level:" << it->level << std::endl;
			i++;
		}
		nodeTable.erase(nodeTable.begin() + iteration);
		//std::cout << std::endl << "Choosen Node: ";
		//std::cout << "Bound:" << next.curr_bound;
		//std::cout << " Next City:" << next.curr_route[next.level - 1];
		//std::cout << " Level:" << next.level << std::endl;

		bnb(next);
	}
}

void Bound_And_Branch::debug_draw(int ** matrix) {
	std::cout <<  "debug:" <<std::endl;
	for (int i = 0; i < get_size(); i++) {
		for (int j = 0; j < get_size(); j++) {
			if (matrix[i][j] == INT_MAX) {
				std::cout << " INF";
			}
			else
			{
				std::cout << std::setw(4) << matrix[i][j];
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Bound_And_Branch::bnb() {
	final_value = INT_MAX;
	
	final_route = new int[get_size() + 1];

	int * curr_route;
	curr_route = new int[get_size() + 1];
	for (int i = 0; i < get_size() + 1; i++) {
		curr_route[i] = -1;
	}

	int **matrix;
	matrix = new int * [get_size()];
	for (int i = 0; i < get_size(); i++) {
		matrix[i] = new int[get_size()];
		for (int j = 0; j < get_size(); j++) {
			if (i == j) {
				matrix[i][j] = INT_MAX;
			}
			else {
				matrix[i][j] = get_distance(i, j);
			}
		}
	}

	int curr_bound = 0;
	//reduction of lines
	for (int i = 0; i < get_size(); i++) {
		int min = minLine(i, -1,  matrix);
		curr_bound += min;
		for (int j = 0; j < get_size(); j++) {
			if (matrix[i][j] != INT_MAX) {
				matrix[i][j] -= min;
			}
		}
	}
	//reduction of columnt
	for (int i = 0; i < get_size(); i++) {
		int min = minColumn(i, -1, matrix);
		curr_bound += min;
		for (int j = 0; j < get_size(); j++) {
			if (matrix[j][i] != INT_MAX) {
				matrix[j][i] -= min;
			}
			
		}
	}

	curr_route[0] = 0;

	Node firstNode;
	firstNode.curr_bound = curr_bound;
	firstNode.curr_route = curr_route;
	firstNode.level = 1;
	firstNode.matrix = matrix;

	bnb(firstNode);
}

