#include "stdafx.h"
#include "Distance_Graph.h"


Distance_Graph::Distance_Graph()
{
	distance_table_size = 0;
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

	while (line.back() == ' ') {
		line = line.substr(0, line.size() - 1);
	}
	//test
	while (line.front() == ' ') {
		line = line.substr(1, line.size());
	}
	position = line.find(' ');
	if (position < 0 && std::stoi(line) == 0) {
		return;
	}
	//finding uninitiated distance table space
	while (distance_table[position_line][position_column] != 0) {
		position_column++;
		if (position_column >= position_line) {
			position_line++;
			position_column = 0;
		}
	}
	//writing line into a matrix
	
	while (line.size() > 0) {
		while (line.front() == ' ') {
			line = line.substr(1, line.size() - 1);
		}
		position = line.find(' ');
		if (position == -1) {
			number = std::stoi(line);
			line ="";
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

void Distance_Graph::instert_line_full_diagram(std::string line, int position_line) {
	int position, position_column = 0, number;
	while (line.back() == ' ') {
		line = line.substr(0, line.size() - 1);
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
		distance_table[position_line][position_column] = number;
		position_column++;
	}
}

void Distance_Graph::instert_line_upper_diagram(std::string line)
{
	int position;
	while (line.back() == ' ') {
		line = line.substr(0, line.size() - 1);
	}
	while (line.front() == ' ') {
		line = line.substr(1, line.size());
	}
	position = line.find(' ');
	if (position < 0 && std::stoi(line) == 0) {
		return;
	}
	//finding uninitiated distance table space
	int position_line = 0, position_column = 1, number;
	while (distance_table[position_line][position_column] != 0) {
		position_column++;
		if (position_column >= get_size()) {
			position_line++;
			position_column = position_line + 1;
		}
		
	}
	//writing line into a matrix
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
			if (position_column >= get_size()) {
				position_line++;
				position_column = position_line + 1;
			}
		}
	}

}

void Distance_Graph::initialize_table_INTMAX()
{
	srand(time(NULL));
	int random;

	for (int line = 0; line < get_size(); line++) {
		for(int column = 0;column <= line ;column++){
			if (column == line) {
				distance_table[line][column] = 0;
			}
			else {
				random = 8 + rand() % 256;
				distance_table[line][column] = random;
				distance_table[column][line] = random;
			}
		}
	}
}

void Distance_Graph::insert_shortest_INTMIN()
{
	distance_table[0][curr_min_route[0]] = 8;
	distance_table[curr_min_route[0]][0] = 8;
	for (int edge = 0; edge < get_size()-2; edge++) {
		distance_table[curr_min_route[edge]][curr_min_route[edge + 1]] = 8;
		distance_table[curr_min_route[edge + 1]][curr_min_route[edge]] = 8;
	}
	distance_table[curr_min_route[get_size() - 2]][0] = 8;
	distance_table[0][curr_min_route[get_size() - 2]] = 8;
}

void Distance_Graph::lower_to_full()
{
	for (int line = 0; line < get_size(); line++) {
		for (int column = 0; column < line; column++) {
			distance_table[column][line] = distance_table[line][column];
		}
	}
	matrix_type = "FULL_MATRIX";
}

void Distance_Graph::upper_to_full()
{
	for (int line = 0; line < get_size(); line++) {
		for (int column = line + 1; column < get_size(); column++) {
			distance_table[column][line] = distance_table[line][column];
		}
	}
	matrix_type = "FULL_MATRIX";
}

bool Distance_Graph::load_from_file()
{
	std::string filename;
	std::cout << "Problem name :";
	std::cin >> filename;
	filename += ".tsp";
	return load_from_file(filename);
}

bool Distance_Graph::load_from_file(std::string filename)
{
	std::string data;
	std::fstream file;
	std::size_t position;
	int number_of_towns;
	file.open(filename, std::ios::in);
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
			//std::cout << std::setw(25) << "Comment to a problem: " << data.substr(position + 1) << std::endl;
			//DIMENSION :
			getline(file, data);
			position = data.find(':');
			//std::cout << std::setw(25) << "Number of towns: " << data.substr(position + 1) << std::endl;
			set_matrix_sizeof(std::stoi(data.substr(position + 1)));
			//EDGE_WEIGHT_TYPE : EXPLICIT
			getline(file, data);
			position = data.find("EXPLICIT");
			if (position > 0 && position < data.size()) {
				//std::cout << std::setw(25) << "Edge Weight Type: " << data.substr(position) << std::endl;
				if (position > 0) {
					//EDGE_WEIGHT_FORMAT : LOWER_DIAG_ROW
					getline(file, data);
					position = data.find("LOWER_DIAG_ROW");
					if (position > 0 && position < data.size()) {
						//std::cout << std::setw(25) << "Matrix Type: " << data.substr(position) << std::endl;
						getline(file, data);
						matrix_type = "LOWER_DIAG_ROW";
						getline(file, data);
						do {
							instert_line_lower_diagram(data);
							getline(file, data);
							position = data.find("EOF");
							if (position == -1) {
								position = data.find("DISPLAY_DATA_SECTION");
							}
						} while (position == -1);
						lower_to_full();
					}
					position = data.find("FULL_MATRIX");
					if (position > 0 && position < data.size()) {
						//std::cout << std::setw(25) << "Matrix Type: " << data.substr(position) << std::endl;
						matrix_type = "FULL_MATRIX";
						getline(file, data); //DISPLAY_DATA_TYPE: TWOD_DISPLAY	
						getline(file, data); //EDGE_WEIGHT_SECTION
						getline(file, data); 
						int line = 0;
						do {
							instert_line_full_diagram(data, line);
							line++;
							getline(file, data);
							position = data.find("DISPLAY_DATA_SECTION");
						} while (position == -1);
					}
					position = data.find("UPPER_DIAG_ROW");
					if (position > 0 && position < data.size()) {
						//std::cout << std::setw(25) << "Matrix Type: " << data.substr(position) << std::endl;
						matrix_type = "UPPER_DIAG_ROW";
						getline(file, data); //DISPLAY_DATA_TYPE: NO_DISPLAY
						getline(file, data); //EDGE_WEIGHT_SECTION
						getline(file, data);
						do {
							instert_line_upper_diagram(data);
							getline(file, data);
							position = data.find("EOF");
							if (position == -1) {
								position = data.find("DISPLAY_DATA_SECTION");
							}
						} while (position == -1);
						upper_to_full();
					}
				}
				else {
					std::cout << "Program doesn't work with non-explicit distances" << std::endl;
				}
			}
		}
		else {
			std::cout << "Problem is not TSP" << std::endl;
			return false;
		}
	}
	else {
		std::cout << "No such problem file";
		return false;
	}
	return true;
}

void Distance_Graph::draw_distance_table()
{
	std::cout << std::setw(4) << " ";
	for (int i = 0; i < distance_table_size; i++) {
		std::cout << std::setw(4) << i;
	}
	std::cout << std::endl;

	for (int line = 0; line < distance_table_size; line++) {
		std::cout << std::setw(4) << line;
		for (int column = 0; column < distance_table_size; column++) {
			std::cout << std::setw(4) << distance_table[line][column];
		}
		std::cout << std::endl;
	}

}

int Distance_Graph::get_distance(int line, int column) {
	return distance_table[line][column];
}

int Distance_Graph::get_size()
{
	return distance_table_size;
}

void Distance_Graph::generate_random(int size)
{
	set_matrix_sizeof(size);
	initialize_table_INTMAX();
	curr_min_route = new int[get_size()-1];
	for (int i = 1; i < get_size(); i++) {
		curr_min_route[i-1] = i;
	}
	std::random_shuffle(curr_min_route, curr_min_route + get_size() - 1);
	insert_shortest_INTMIN();
	matrix_type = "FULL_MATRIX";
}

void Distance_Graph::generate_next_random()
{
	std::random_shuffle(curr_min_route, curr_min_route + get_size() - 1);
	initialize_table_INTMAX();
	insert_shortest_INTMIN();
}
