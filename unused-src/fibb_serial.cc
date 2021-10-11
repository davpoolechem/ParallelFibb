#include <iostream>
#include <unistd.h>

int fibo(int n) {
	sleep(rand()%3+1); 
	if(n <= 1) { 
		return n; 
	} else { 
		return fibo(n - 1) + fibo(n - 2); 
	}
}

int main() {
	int n = 10; 
	std::cout << "The " << n <<"th number in the Fibonacci serries is " << fibo(n) << std::endl;
}
