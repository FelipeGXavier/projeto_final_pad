std::vector <long long> sequentialPrimeFactor(long long number) {
	long long squareRoot = sqrtl(number);
	std::vector <long long> primeFactors;
	for(int divisor = 1; divisor < squareRoot; divisor++) {
		// 1 2 3 4 5 6 7 8 9
		if(number % divisor != 0) {
			continue;
		}
		// 1 & 100/1 -> 100
		// 2 & 100/2 -> 50
		// 4 & 100/4 -> 25
		// 5 & 100/5 -> 20
		primeFactors.push_back(divisor);
		primeFactors.push_back(number / divisor);
	}
	// Tratativa para número com raiz quadrada sendo um número inteiro
	// Evitar de inserir novamente na lista de fatoração
	if(number % squareRoot == 0) {
		primeFactors.push_back(squareRoot);
		if(squareRoot * squareRoot != number) {
			primeFactors.push_back(number / squareRoot);
		}
	}
	sort(primeFactors.begin(), primeFactors.end());
	return primeFactors;
}