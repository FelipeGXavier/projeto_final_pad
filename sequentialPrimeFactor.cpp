std::vector <long long> sequentialPrimeFactor(long long number) {
	long long squareRoot = sqrtl(number);
	std::vector <long long> primeFactors;
	for(int divisor = 1; divisor < squareRoot; divisor++) {
		if(number % divisor != 0) {
			continue;
		}
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