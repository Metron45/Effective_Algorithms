#pragma once
class Distance_Graph
{
protected:
	int ** distance_table;
	int distance_table_size;
	std::string matrix_type;
private:
	void set_matrix_sizeof(int size);
	void instert_line_lower_diagram(std::string line);
	void instert_line_full_diagram(std::string line, int position_line);
public:
	Distance_Graph();
	~Distance_Graph();
	void load_from_file();
	void load_from_file(std::string filename);
	void draw_distance_table();
	int get_distance(int line, int column);
	int get_size();
};

