#include "stdafx.h"
#include "Test.h"


Test::Test()
{
}


Test::~Test()
{
}

void Test::test_menu() {
	int menu = 0;
	do{
		std::cout << "Select what test you want to do:" << std::endl;
		std::cout << "1: Time test" << std::endl;
		std::cout << "2: Test using TSPLIB file" << std::endl;
		std::cout << "3: Test using random distances" << std::endl;
		std::cout << "0: Exit" << std::endl;
		std::cin >> menu;
		switch (menu) {
		case 1: 
			test_time();
			break;
		case 2:
			test_correctness();
			break;
		case 3:
			test_random();
			break;
		default:
			menu = 3;
			break;
		}
	} while (menu != 0);
}

void Test::test_time() {
	int menu = 0, size;
	do {
		std::cout << "Select what test you want to do:" << std::endl;
		std::cout << "1: Bruteforce" << std::endl;
		std::cout << "2: Dynamic" << std::endl;
		std::cout << "3: Bnb" << std::endl;
		std::cout << "0: Back" << std::endl;
		std::cin >> menu;
		system("CLS");
		if (menu != 0) {
			std::cout << "Select size: ";
			std::cin >> size;
		}
		switch (menu) {
		case 1:
			test_time_bruteforce(size,100);
			break;
		case 2:
			test_time_dynamic(size,100);
			break;
		case 3:
			test_time_bnb(size,100);
			break;
		default:
			break;
		}
	} while (menu != 0);
}

void Test::test_correctness() {
	int menu = 0;
	do {
		std::cout << "Select what algorithms you want to use:" << std::endl;
		std::cout << "1: Bruteforce" << std::endl;
		std::cout << "2: Dynamic" << std::endl;
		std::cout << "3: Bnb" << std::endl;
		std::cout << "0: Back" << std::endl;
		std::cin >> menu;
		system("CLS");
		switch (menu) {
		case 1:
			test_correctness_bruteforce();
			break;
		case 2:
			test_correctness_dynamic();
			break;
		case 3:
			test_correctness_bnb();
			break;
		default:
			break;
		}
	} while (menu != 0);
}

void Test::test_random() {
	int menu = 0;
	int size;
	do {
		std::cout << "Select what algorithms you want to use:" << std::endl;
		std::cout << "1: Bruteforce" << std::endl;
		std::cout << "2: Dynamic" << std::endl;
		std::cout << "3: Bnb" << std::endl;
		std::cout << "0: Back" << std::endl;
		std::cin >> menu;
		system("CLS");
		if (menu != 0) {
			std::cout << "Select size: ";
			std::cin >> size;
		}
		switch (menu) {
		case 1:
			test_random_bruteforce(size);
			break;
		case 2:
			test_random_dynamic(size);
			break;
		case 3:
			test_random_bnb(size);
			break;
		default:
			break;
		}
	} while (menu != 0);

}

void Test::test_time_bruteforce(int size, int amount)
{
	Bruteforce matrix;
	std::ofstream file;
	file.open("results.txt");
	std::chrono::high_resolution_clock::time_point clock;
	std::chrono::nanoseconds diff;
	matrix.generate_random(size);
	file <<  size << "\n";
	for (int i = 0; i < amount; i++) {
		clock = std::chrono::high_resolution_clock::now();
		matrix.bruteforce();
		diff = std::chrono::high_resolution_clock::now() - clock;
		if (matrix.getFinalDistance() > matrix.get_size() * 8) {
			std::cout << std::endl << "Algorithm has failed" << std::endl;
			break;
		}
		file << diff.count() << "\n";
		matrix.generate_next_random();
	}
	file.close();
	std::cout << "test finished check results file" << std::endl << std::endl;
}

void Test::test_time_dynamic(int size, int amount)
{
	Dynamic matrix;
	std::ofstream file;
	file.open("results.txt");
	std::chrono::high_resolution_clock::time_point clock;
	std::chrono::nanoseconds diff;
	matrix.generate_random(size);
	file << size << "\n";
	for (int i = 0; i < amount; i++) {
		clock = std::chrono::high_resolution_clock::now();
		matrix.dynamic();
		diff = std::chrono::high_resolution_clock::now() - clock;
		if (matrix.getFinalDistance() > matrix.get_size() * 8) {
			std::cout << std::endl << "Algorithm has failed" << std::endl;
			break;
		}
		file << diff.count() << "\n";
		matrix.generate_next_random();
	}
	file.close();
	std::cout << "test finished check results file" << std::endl << std::endl;
}

void Test::test_time_bnb(int size, int amount)
{
	Bound_And_Branch matrix;
	std::ofstream file;
	file.open("results.txt");
	std::chrono::high_resolution_clock::time_point clock;
	std::chrono::nanoseconds diff;
	matrix.generate_random(size);
	file << size << "\n";
	for (int i = 0; i < amount; i++) {
		clock = std::chrono::high_resolution_clock::now();
		matrix.bnb();
		diff = std::chrono::high_resolution_clock::now() - clock;
		if (matrix.getFinalDistance() > matrix.get_size() * 8) {
			std::cout << std::endl << "Algorithm has failed" << std::endl;
			break;
		}
		file << diff.count() << "\n";
		matrix.generate_next_random();
	}
	file.close();
	std::cout << "test finished check results file" << std::endl << std::endl;
}

void Test::test_correctness_bruteforce()
{
	Bruteforce matrix;
	if (matrix.load_from_file()) {
		matrix.draw_distance_table();
		matrix.write_results();
		std::cout << std::endl;
	}
}

void Test::test_correctness_dynamic()
{
	Dynamic matrix;
	if (matrix.load_from_file()) {
		matrix.draw_distance_table();
		matrix.write_results();
		std::cout << std::endl;
	}
}

void Test::test_correctness_bnb()
{
	Bound_And_Branch matrix;
	if (matrix.load_from_file()) {
		matrix.draw_distance_table();
		matrix.write_results();
		std::cout << std::endl;
	}
}

void Test::test_random_bruteforce(int size)
{
	Bruteforce matrix;
	matrix.generate_random(size);
	matrix.draw_distance_table();
	matrix.write_results();
	if (matrix.getFinalDistance() > matrix.get_size() * 8) {
		std::cout << std::endl << "Algorithm has failed" << std::endl;
	}
	std::cout << std::endl;
}

void Test::test_random_dynamic(int size)
{
	Dynamic matrix;
	matrix.generate_random(size);
	matrix.draw_distance_table();
	matrix.write_results();
	if (matrix.getFinalDistance() > matrix.get_size() * 8) {
		std::cout << std::endl << "Algorithm has failed" << std::endl;
	}
	std::cout << std::endl;
}

void Test::test_random_bnb(int size)
{
	Bound_And_Branch matrix;
	matrix.generate_random(size);
	matrix.draw_distance_table();
	matrix.write_results();
	if (matrix.getFinalDistance() > matrix.get_size() * 8) {
		std::cout << std::endl << "Algorithm has failed" << std::endl;
	}
	std::cout << std::endl;
}

