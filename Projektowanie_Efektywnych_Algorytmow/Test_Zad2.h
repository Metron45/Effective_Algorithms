#pragma once

struct error_time {
	int time;
	float error;
};

class Test_Zad2
{
public:
	
	Test_Zad2();
	~Test_Zad2();

	void Test_Simulated_Annealing(std::string problem_name, float max_temp, float cooling_rate, float min_temp, int max_iter, float temp_jump, int iter_jump, float cooling_jump);
	void Test_Simulated_Annealing_grid(float max_temp, int max_iter, float temp_jump, int iter_jump);

	static const int number_of_steps = 4;// 12;
	float error_rate(std::string problem_name, int fitness_result);
	error_time time_test_Simulated_Annealing(std::string file, float max, float rate, float min, int iterations);
	std::string get_problem_name(int id);
};

