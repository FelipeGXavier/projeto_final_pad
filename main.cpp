
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

std::vector <long long> factorization(long long number, std::vector <long long> &divisors) {
	std::vector <long long> result;
	for(auto divisor: divisors) {
		// Não altera o produto
		if(divisor == 1) {
			continue;
		}
		// 2 4 5 10 20 25 50 100
		// 2 2 5 5
		while (number % divisor == 0) {
			result.push_back(divisor);
			number = number/divisor;
		}
	}
	if(number != 1) {
		result.push_back(number);
	}
	return result;
}

void printFactorization(long long number, std::vector <long long> &factors)
{
	std::cout << number << " = ";
	for(int i = 0; i + 1 < factors.size(); i++) {
		std::cout << factors[i] << " * ";
	}
	std::cout << factors.back() << "\n";
}

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



int main(int argc, char **argv)
{
	std::ifstream in("input.txt");
	std::string str;
	std::vector<std::string> inputNumbers;
    while (std::getline(in, str)) {
    	if (str.size() > 0) {
			inputNumbers.push_back(str);
			const char * c = str.c_str();
			long long number = atoll(c);
			printBenchmark(number);
		}
	}
	//Teste
	// long long n = 100;
	// std::vector <long long> primeFactorsList = sequentialPrimeFactor(n);
	// std::vector <long long> result = factorization(n, primeFactorsList);
	//printFactorization(n, result);
}