#include "stdafx.h"
#include "Distance_Graph.h"


Distance_Graph::Distance_Graph()
{
}


Distance_Graph::~Distance_Graph()
{
	delete [] distance_table;
	distance_table = NULL;
}

void Distance_Graph::set_matrix_sizeof(int size) {
	distance_table_size = size;
	distance_table = new int*[size];
	for (int i = 0; i < size; i++) {
		distance_table[i] = new int[size];
		for (int column = 0; column < size; column++) {
			distance_table[i][column] = 0;
		}
	}
}

void Distance_Graph::load_from_file()
{
	std::string name, data;
	std::fstream file;
	std::size_t position;
	int number_of_towns;

	std::cout << "Problem name :";
	std::cin >> name;
	name += ".tsp";

	file.open(name, std::ios::in);

	if (file.is_open()) {
		//NAME :
		getline(file, data);

		//TYPE :
		getline(file, data);
		position = data.find('TSP');
		if (position > 0) {
			//COMMENT :
			getline(file, data);
			position = data.find(':');
			std::cout << "Comment to a problem :\n" << data.substr(position+1) << std::endl;

			//DIMENSION :
			getline(file, data);
			position = data.find(':');
			std::cout << "Number of towns :\n" << data.substr(position+1) << std::endl;
			number_of_towns = std::stoi(data.substr(position + 1));

			//EDGE_WEIGHT_TYPE : EXPLICIT
			getline(file, data);
			position = data.find("EXPLICIT");
			if (position > 0) {
				//EDGE_WEIGHT_FORMAT : LOWER_DIAG_ROW
				getline(file, data);
				position = data.find("LOWER_DIAG_ROW");
				if (position > 0) {
					//Adding the LOWER_DIAG_ROW into a matrix
					matrix_type = "LOWER_DIAG_ROW";
					set_matrix_sizeof(number_of_towns);


				}
			}
			else {
				std::cout << "Program doesn't work with non-explicit distances" << std::endl;
			}
		}
		else {
			std::cout << "Problem is not TSP" << std::endl;
		}
	}
	else {
		std::cout << "Program has not found such TPS problem";
	}

}
