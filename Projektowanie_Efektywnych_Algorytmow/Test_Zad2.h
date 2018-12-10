#pragma once

struct error_time {
	long float time;
	float error;
};

class Test_Zad2
{
public:
	
	Test_Zad2();
	~Test_Zad2();

	void Set_number_of_tests(int iter, int temp, int tests);
	void Test_Simulated_Annealing(std::string file, float max_temp, float cool_rate, float temp_jump, float cool_jump);

	int number_of_iter_steps;
	int number_of_temp_steps;
	int number_of_tests;

	float error_rate(std::string problem_name, int fitness_result);

};

