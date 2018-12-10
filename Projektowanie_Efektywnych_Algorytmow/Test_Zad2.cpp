#include "stdafx.h"
#include "Test_Zad2.h"
#include "Simulated_Annealing.h"

Test_Zad2::Test_Zad2()
{
}


Test_Zad2::~Test_Zad2()
{
	
}



void Test_Zad2::Set_number_of_tests(int iter, int temp, int tests)
{
	number_of_iter_steps = iter;
	number_of_temp_steps = temp;
	number_of_tests = tests;
}

void Test_Zad2::Test_Simulated_Annealing(std::string problem_name, float max_temp, float cooling_rate, float temp_jump, float cooling_jump)
{
	Simulated_Annealing matrix;
	matrix.load_from_file(problem_name);
	matrix.Set_route_size();

	std::chrono::high_resolution_clock::time_point clock;
	std::chrono::nanoseconds diff;
	int fitness;
	float error;

	std::ofstream file_time, file_error;
	file_time.open("resultsTime.txt");
	file_error.open("resultsError.txt");

	float temperature = max_temp;
	float rate = cooling_rate;

	srand(time(NULL));

	for (int k = 0; k < number_of_iter_steps; k++)
	{
		rate = cooling_rate;
		for (int i = 0; i < number_of_temp_steps; i++) {
			error_time average_results, current_results;
			average_results.error = 0;
			average_results.time = 0;
			for (int j = 0; j < number_of_tests; j++) {
				
				matrix.Set_temperature(temperature, rate);
				clock = std::chrono::high_resolution_clock::now();
				fitness = matrix.Calculate();
				diff = std::chrono::high_resolution_clock::now() - clock;
				error = error_rate(problem_name, fitness);
				average_results.error += error;
				average_results.time += diff.count() / 1000;

			}
			average_results.error /= number_of_tests;
			average_results.time /= number_of_tests;
			file_time  << average_results.time   << "," ;
			file_error << average_results.error << ",";
			rate += cooling_jump;
			std::cout << "Temp: " << i + 1 << " out of : " << number_of_temp_steps << " DONE" << std::endl;
		}
		file_time << "\n";
		file_error << "\n";
		temperature += temp_jump;
		std::cout << "Iteratrion: " << k + 1 << " out of : " << number_of_iter_steps << " Finished" << std::endl;
		
	}
	file_time.close();
	file_error.close();
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

