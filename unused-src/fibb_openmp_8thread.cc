#include <iostream>
#include <unistd.h>

long long int fibo(long long int n) {
	sleep(rand()%3+1);
	if(n <= 1) { 
		return n; 
	} else { 
		long long int tmp1, tmp2;
		#pragma omp task shared(tmp1) 
		{
			tmp1 = fibo(n-2);
		}
		#pragma omp task shared(tmp2) 
		{
			tmp2 = fibo(n-1);
		}
		#pragma omp taskwait

		return tmp1 + tmp2;
	}
}

int main() {
	#pragma omp parallel num_threads(8)
	{
		#pragma omp single nowait
		{
			long long int n = 10;	
			std::cout << "The " << n <<"th number in the Fibonacci serries is " << fibo(n) << std::endl;
		}
	}
}
