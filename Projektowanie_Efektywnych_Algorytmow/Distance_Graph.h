#pragma once
#define Pi = 3.141592;
class Distance_Graph
{
protected:
	int ** distance_table;
	int distance_table_size;
	std::string matrix_type;

private:
	int * curr_min_route;

	void set_matrix_sizeof(int size);

	void instert_line_lower_diagram(std::string line);
	void instert_line_full_diagram(std::string line, int position_line);
	void instert_line_upper_diagram(std::string line);

	void initialize_table_INTMAX();
	void insert_shortest_INTMIN();

	void lower_to_full();
	void upper_to_full();


public:
	Distance_Graph();
	~Distance_Graph();
	bool load_from_file();
	bool load_from_file(std::string filename);
	
	void draw_distance_table();
	int get_distance(int line, int column);
	int get_size();

	void generate_random(int size);
	void generate_next_random();

};

