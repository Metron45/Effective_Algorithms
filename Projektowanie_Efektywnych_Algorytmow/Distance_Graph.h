#pragma once
class Distance_Graph
{
private:
	int ** distance_table;
	int distance_table_size;
	std::string matrix_type;
	void set_matrix_sizeof(int size);
	void instert_line_lower_diagram(std::string line);

public:
	Distance_Graph();
	~Distance_Graph();
	
	void load_from_file();
	void draw_distance_table();
};

