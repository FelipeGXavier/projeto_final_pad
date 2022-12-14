
#include <chrono>
#include <algorithm>		
#include <vector>		
#include <string>
#include <fstream>
#include <streambuf>
#include <iostream>		
#include <math.h>		
#include <omp.h>		

#include "parallelPrimeFactor.cpp"
#include "sequentialPrimeFactor.cpp"

void printBenchmark(long long number) {
	// Serial
	std::chrono::steady_clock::time_point beginSequential = std::chrono::steady_clock::now();
	sequentialPrimeFactor(number);
	std::chrono::steady_clock::time_point endSequential = std::chrono::steady_clock::now();
	auto elapsedTimeSequential = std::chrono::duration_cast<std::chrono::milliseconds>(endSequential - beginSequential).count();
	// Paralelo
	std::chrono::steady_clock::time_point beginParallel = std::chrono::steady_clock::now();
	std::vector <long long> primeFactors = parallelPrimeFactor(number);
	std::chrono::steady_clock::time_point endParallel = std::chrono::steady_clock::now();
	auto elapsedTimeParallel = std::chrono::duration_cast<std::chrono::milliseconds>(endParallel - beginParallel).count();
	std::cout << number << " | Seq. " << elapsedTimeSequential << " | Par. " << elapsedTimeParallel << "\n";
}

void printPrimeFactorization(long long number, std::vector <long long> &primeFactorsList)
{
	std::cout << number << " = ";
	for(int i = 0; i + 1 < primeFactorsList.size(); i++) {
		std::cout << primeFactorsList[i] << " * ";
	}
	std::cout << primeFactorsList.back() << "\n";
}

int main(int argc, char **argv)
{
	std::ifstream in("input.txt");
	std::string str;
	std::vector<std::string> inputNumbers;
    while (std::getline(in, str)) {
    	if(str.size() > 0) {
			inputNumbers.push_back(str);
			const char * c = str.c_str();
			long long number = atoll(c);
			printBenchmark(number);
		}
	}
}