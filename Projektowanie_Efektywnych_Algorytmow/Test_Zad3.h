#pragma once
class Test_Zad3
{
public:
	Test_Zad3();
	~Test_Zad3();

	int number_of_steps1;
	int number_of_steps2;
	int number_of_tests;
	int time_of_tests;

	void set_amount_of_tests(int step1, int step2, int test_amount, int test_time);
	void test_population(std::string file, float population, float jump);
	void test_mating_pool(std::string file, float mating_size, float jump);
	void test_tournament(std::string file, float tournament_part, float jump);
	void test_mutation(std::string file, float mutation_rate, float jump);

	void Mass_test_population(float population, float jump);
	void Mass_test_Mating(float population, float jump);
	void Mass_test_Tournament(float population, float jump);
	void Mass_test_Mutation(float population, float jump);
	void test_final(std::string file);
	void Mass_test_Final();
};

