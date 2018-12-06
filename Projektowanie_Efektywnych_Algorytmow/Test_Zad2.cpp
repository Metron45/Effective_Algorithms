#include "stdafx.h"
#include "Test_Zad2.h"
#include "Simulated_Annealing.h"

Test_Zad2::Test_Zad2()
{
}


Test_Zad2::~Test_Zad2()
{
}



void Test_Zad2::Test_Simulated_Annealing(std::string problem_name, float max_temp, float cooling_rate, float min_temp, int max_iter, float temp_jump, int iter_jump, float cooling_jump)
{
	std::ofstream file;
	file.open("results.txt");
	float temperature = max_temp;
	int iterations = max_iter;
	float rate = cooling_rate;
	srand(time(NULL));

	for (int k = 0; k < number_of_steps; k++)
	{
		temperature = max_temp;
		rate = cooling_rate;
		for (int i = 0; i < number_of_steps; i++) {
			error_time average_results, current_results;
			average_results.error = 0;
			average_results.time = 0;
			for (int j = 0; j < 100; j++) {
				current_results = time_test_Simulated_Annealing(problem_name, temperature, cooling_rate, min_temp, iterations);
				average_results.error += current_results.error;
				average_results.time += current_results.time;
			}
			average_results.error /= 100;
			average_results.time /= 100;
			file << average_results.time << "'" << average_results.error << "'";
			temperature += temp_jump;
			rate += cooling_jump;
		}
		file << "\n";
		iterations += iter_jump;
	}
}

void Test_Zad2::Test_Simulated_Annealing_grid(float max_temp, int max_iter, float temp_jump, int iter_jump)
{
	std::ofstream file;
	file.open("grid.txt");
	int temperature = max_temp;
	int iterations = max_iter;
	temperature = max_temp;
	//first line with example max temp and max iterations
	for (int k = 0; k < number_of_steps; k++)
	{
		for (int i = 0; i < number_of_steps; i++) {
			file << temperature << "," << iterations << ",";
			temperature += temp_jump;
		}
	file << "\n";
	iterations += iter_jump;
	}
}


float Test_Zad2::error_rate(std::string problem_name, int fitness_result)
{
	std::ifstream file ("solutions.txt");
	std::string line, name, distance;
	float result;
	
	if (file.is_open())
	{
		int position;
		while (name + ".tsp" != problem_name)
		{
			std::getline(file, line);
			position = line.find(' ');
			name = line.substr(0, position);
		}
		position += 3;
		distance = line.substr(position, line.size() - 1);

		result = fitness_result - std::stof(distance);
		file.close();
		return result / std::stoi(distance);
	}
	else
	{
		std::cout << "there is not solutions.txt file" << std::endl; \
		return -1;
	}
}

error_time Test_Zad2::time_test_Simulated_Annealing(std::string file, float max, float rate, float min, int iterations)
{
	Simulated_Annealing matrix;

	matrix.load_from_file(file);
	matrix.Set_temperature(max,rate,min,iterations);

	std::chrono::high_resolution_clock::time_point clock;
	std::chrono::nanoseconds diff;
	int fitness;

	clock = std::chrono::high_resolution_clock::now();
	fitness = matrix.Calculate();
	diff = std::chrono::high_resolution_clock::now() - clock;

	error_time results;
	results.error = error_rate(file, fitness);
	results.time = diff.count();
	return results;
}

std::string Test_Zad2::get_problem_name(int id)
{
	std::string name;

	switch (id) {
	case 0:
		name = "gr17.tps";
		break;
	case 1:
		name = "gr21.tps";
		break;
	case 2:
		name = "gr24.tps";
		break;
	case 3:
		name = "fr26.tps";
		break;
	case 4:
		name = "bays29.tps";
		break;
	case 5:
		name = "dantzig42.tps";
		break;
	case 6:
		name = "gr48.tps";
		break;
	case 7:
		name = "brazil58.tps";
		break;
	case 8:
		name = "gr120.tps";
		break;
	case 9:
		name = "si175.tps";
		break;
	case 10:
		name = "a280.tps";
		break;
	case 11:
		name = "gr535.tps";
		break;
	case 12:
		name = "si1032.tps";
		break;
	}

	return name;
}

