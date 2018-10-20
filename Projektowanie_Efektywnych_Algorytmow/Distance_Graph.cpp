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

void Distance_Graph::instert_line_lower_diagram(std::string line) {
	int position, position_line = 1, position_column = 0,number;

	while (distance_table[position_line][position_column] != 0) {
		position_column++;
		if (position_column >= position_line) {
			position_line++;
			position_column = 0;
		}
	}
	while (line.back() == ' ') {
		line = line.substr(0, line.size() - 2);
	}
	while (line.size() > 0) {
		while (line.front() == ' ') {
			line = line.substr(1, line.size() - 1);
		}
		position = line.find(' ');
		if (position == -1) {
			number = std::stoi(line);
			line = "";
		}
		else {
			number = std::stoi(line.substr(0, position));
			line = line.substr(position, line.size() - 1);
		}
		if (number != 0) {
			distance_table[position_line][position_column] = number;
			position_column++;
			if (position_column >= position_line) {
				position_line++;
				position_column = 0;
			}
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
			std::cout << std::setw(25) << "Comment to a problem: " << data.substr(position+1) << std::endl;
			//DIMENSION :
			getline(file, data);
			position = data.find(':');
			std::cout << std::setw(25) << "Number of towns: " << data.substr(position+1) << std::endl;
			number_of_towns = std::stoi(data.substr(position + 1));
			//EDGE_WEIGHT_TYPE : EXPLICIT
			getline(file, data);
			position = data.find("EXPLICIT");
			std::cout << std::setw(25) << "Edge Weight Type: " << data.substr(position) << std::endl;
			if (position > 0) {
				//EDGE_WEIGHT_FORMAT : LOWER_DIAG_ROW
				getline(file, data);
				position = data.find("LOWER_DIAG_ROW");
				std::cout << std::setw(25) << "Matrix Type: " << data.substr(position) << std::endl;
				getline(file, data);
				if (position > 0) {
					matrix_type = "LOWER_DIAG_ROW";
					set_matrix_sizeof(number_of_towns);
					getline(file, data);
					do {
						instert_line_lower_diagram(data);
						getline(file, data);
						position = data.find("EOF");
					} while (position == -1);
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
		std::cout << "Bo such problem file";
	}

}

void Distance_Graph::draw_distance_table()
{
	for (int line = 0; line < distance_table_size; line++) {
		for (int column = 0; column < distance_table_size; column++) {
			std::cout << std::setw(4) << distance_table[line][column];
		}
		std::cout << std::endl;
	}

}
