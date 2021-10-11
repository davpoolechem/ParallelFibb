#include <future>
#include <iostream>
#include <thread>
#include <unistd.h>

long long int fibo(long long int n) {
	sleep(rand()%3+1);
	if(n <= 1) { 
		return n; 
	} else {
		auto tmpn1 = std::async(fibo, n-1); 
		auto tmpn2 = std::async(fibo, n-2); 
		return tmpn1.get() + tmpn2.get();
	}
}

int main(int argc, char* argv[]) {
	long long int n = atoll(argv[1]);	
	std::cout << "The " << n <<"th number in the Fibonacci serries is " << fibo(n) << std::endl;
}
