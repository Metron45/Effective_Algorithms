#include "stdafx.h"
#include "Test_Zad3.h"
#include "Genetic.h"


Test_Zad3::Test_Zad3()
{
}


Test_Zad3::~Test_Zad3()
{
}

void Test_Zad3::set_amount_of_tests(int step1, int step2, int test_amount, int test_time)
{
	number_of_steps1 = step1;
	number_of_steps2 = step2;
	number_of_tests = test_amount;
	time_of_tests = test_time;
}

void Test_Zad3::test_population(std::string file, float population, float jump)
{
	Genetic matrix;
	matrix.load_from_file(file);

	std::ofstream file_error;
	file_error.open("resultsError.txt", std::fstream::app);

	srand(time(NULL));

	for (int k = 0; k < number_of_steps1; k++)
	{
		file_error << population + jump*k << ",";
	}
	file_error << "\n";
	std::cout << "Starting Tests" << std::endl;
	for (int k = 0; k < number_of_steps1; k++)
	{
		std::cout << " Starting Tests for: " << k << " out of "<< number_of_steps1;

		float avarage_error = 0;
		for (int j = 0; j < number_of_tests; j++) {
			matrix.Initialize(population + jump * k, 4, 0.75, 0.1);
			matrix.reset();
			matrix.Calculate(time_of_tests);
			avarage_error += matrix.error_rate(file);
		}
		avarage_error /= number_of_tests;
		file_error << avarage_error << ",";
		std::cout << " Ended Tests for: " << population + jump * k << std::endl;
	}
	file_error.close();
}

void Test_Zad3::test_mating_pool(std::string file, float mating_size, float jump)
{
	Genetic matrix;
	matrix.load_from_file(file);

	std::ofstream file_error;
	file_error.open("resultsError.txt", std::fstream::app);

	srand(time(NULL));
	

	for (int k = 0; k < number_of_steps1; k++)
	{
		file_error << mating_size + jump * k << ",";
	}
	file_error << "\n";
	std::cout << "Starting Tests" << std::endl;
	for (int k = 0; k < number_of_steps1; k++)
	{
		std::cout << " Starting Tests for: " << k << " out of " << number_of_steps1;
		matrix.Initialize(150, mating_size + jump * k, 0.75, 0.1);
		float avarage_error = 0;
		for (int j = 0; j < number_of_tests; j++) {
			matrix.reset();
			matrix.Calculate(time_of_tests);
			avarage_error += matrix.error_rate(file);
		}
		avarage_error /= number_of_tests;
		file_error << avarage_error << ",";
		std::cout << " Ended Tests for: " << mating_size + jump * k << std::endl;
	}
	file_error.close();
}

void Test_Zad3::test_tournament(std::string file, float tournament_part, float jump)
{
	Genetic matrix;
	matrix.load_from_file(file);

	std::ofstream file_error;
	file_error.open("resultsError.txt", std::fstream::app);

	srand(time(NULL));


	for (int k = 0; k < number_of_steps1; k++)
	{
		file_error << tournament_part + jump * k << ",";
	}
	file_error << "\n";

	std::cout << "Starting Tests" << std::endl;
	for (int k = 0; k < number_of_steps1; k++)
	{
		std::cout << " Starting Tests for: " << k << " out of " << number_of_steps1;
		matrix.Initialize(150, 5, tournament_part + jump * k, 0.1);
		float avarage_error = 0;
		for (int j = 0; j < number_of_tests; j++) {
			matrix.reset();
			matrix.Calculate(time_of_tests);
			avarage_error += matrix.error_rate(file);
		}
		avarage_error /= number_of_tests;
		file_error << avarage_error << ",";
		std::cout << " Ended Tests for: " << tournament_part + jump * k << std::endl;
	}
	file_error.close();
}

void Test_Zad3::test_mutation(std::string file, float mutation_rate, float jump)
{
	Genetic matrix;
	matrix.load_from_file(file);

	std::ofstream file_error;
	file_error.open("resultsError.txt", std::fstream::app);

	srand(time(NULL));


	for (int k = 0; k < number_of_steps1; k++)
	{
		file_error << mutation_rate + jump * k << ",";
	}
	file_error << "\n";

	std::cout << "Starting Tests" << std::endl;
	for (int k = 0; k < number_of_steps1; k++)
	{
		std::cout << " Starting Tests for: " << k << " out of " << number_of_steps1;
		matrix.Initialize(150, 5, 0.75, mutation_rate + jump * k);
		float avarage_error = 0;
		for (int j = 0; j < number_of_tests; j++) {
			matrix.reset();
			matrix.Calculate(time_of_tests);
			avarage_error += matrix.error_rate(file);
		}
		avarage_error /= number_of_tests;
		file_error << avarage_error << ",";
		std::cout << " Ended Tests for: " << mutation_rate + jump * k << std::endl;
	}
	file_error.close();
}

void Test_Zad3::Mass_test_population(float population, float jump) {

	std::ofstream file_error;
	file_error.open("resultsError.txt");
	for (int k = 0; k < number_of_steps1; k++)
	{
		file_error << population + jump * k << ",";
	}
	file_error.close();

	test_population("gr17.tsp", population, jump);
	test_population("gr21.tsp", population, jump);
	test_population("gr24.tsp", population, jump);
	test_population("gr120.tsp", population, jump);
	test_population("si175.tsp", population, jump);
	test_population("si535.tsp", population, jump);
	test_population("si1032.tsp", population, jump);
	}

void Test_Zad3::Mass_test_Mating(float population, float jump) {

	std::ofstream file_error;
	file_error.open("resultsError.txt");
	for (int k = 0; k < number_of_steps1; k++)
	{
		file_error << population + jump * k << ",";
	}
	file_error.close();

	test_mating_pool("gr17.tsp", population, jump);
	test_mating_pool("gr21.tsp", population, jump);
	test_mating_pool("gr24.tsp", population, jump);
	test_mating_pool("gr120.tsp", population, jump);
	test_mating_pool("si175.tsp", population, jump);
	test_mating_pool("si535.tsp", population, jump);
	test_mating_pool("si1032.tsp", population, jump);
}

void Test_Zad3::Mass_test_Tournament(float tournament_part, float jump) {

	std::ofstream file_error;
	file_error.open("resultsError.txt");
	for (int k = 0; k < number_of_steps1; k++)
	{
		file_error << tournament_part + jump * k << ",";
	}
	file_error.close();

	test_tournament("gr17.tsp", tournament_part, jump);
	test_tournament("gr21.tsp", tournament_part, jump);
	test_tournament("gr24.tsp", tournament_part, jump);
	test_tournament("gr120.tsp", tournament_part, jump);
	test_tournament("si175.tsp", tournament_part, jump);
	test_tournament("si535.tsp", tournament_part, jump);
	test_tournament("si1032.tsp", tournament_part, jump);
}

void Test_Zad3::Mass_test_Mutation(float population, float jump) {

	std::ofstream file_error;
	file_error.open("resultsError.txt");
	for (int k = 0; k < number_of_steps1; k++)
	{
		file_error << population + jump * k << ",";
	}
	file_error.close();

	test_mutation("gr17.tsp", population, jump);
	test_mutation("gr21.tsp", population, jump);
	test_mutation("gr24.tsp", population, jump);
	test_mutation("gr120.tsp", population, jump);
	test_mutation("si175.tsp", population, jump);
	test_mutation("si535.tsp", population, jump);
	test_mutation("si1032.tsp", population, jump);
}

void Test_Zad3::test_final(std::string file)
{
	Genetic matrix;
	matrix.load_from_file(file);

	std::ofstream file_error;
	file_error.open("resultsError.txt", std::fstream::app);

	srand(time(NULL));

	std::cout << "Starting Tests" << std::endl;
	matrix.Initialize(100, 4, 0.5, 0.1);

	float avarage_error = 0;
	
	for (int j = 0; j < number_of_tests; j++) {
		matrix.reset();
		matrix.Calculate(time_of_tests);
		avarage_error += matrix.error_rate(file);
	}
	avarage_error /= number_of_tests;
	file_error << avarage_error << ",";
	
	file_error.close();
	std::cout << "Tests done" << std::endl;
}

void Test_Zad3::Mass_test_Final() {
	set_amount_of_tests(1, 1, 10, 20);
	test_final("gr17.tsp");
	set_amount_of_tests(1, 1, 10, 20);
	test_final("gr21.tsp");
	set_amount_of_tests(1, 1, 10, 25);
	test_final("gr24.tsp");
	set_amount_of_tests(1, 1, 10, 85);
	test_final("gr120.tsp");
	set_amount_of_tests(1, 1, 10, 125);
	test_final("si175.tsp");
	set_amount_of_tests(1, 1, 10, 400);
	test_final("si535.tsp");
	set_amount_of_tests(1, 1, 10, 800);
	test_final("si1032.tsp");
}