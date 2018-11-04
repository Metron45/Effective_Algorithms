#pragma once
#include "Bruteforce.h"
#include "Dynamic.h"
#include "Bound_And_Branch.h"

class Test
{
public:
	Test();
	~Test();
	void test_menu();
	void test_time();
	void test_correctness();
	void test_random();

private:
	void test_time_bruteforce(int size, int amount);
	void test_time_dynamic(int size, int amount);
	void test_time_bnb(int size, int amount);
	void test_correctness_bruteforce();
	void test_correctness_dynamic();
	void test_correctness_bnb();
	void test_random_bruteforce(int size);
	void test_random_dynamic(int size);
	void test_random_bnb(int size);

};

