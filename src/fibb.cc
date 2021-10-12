#include "fibb.h"

#include <iostream>

int main(int argc, char* argv[]) {
	long long int n = atoll(argv[1]);	
  Algorithm algorithm = Algorithm::OPENMP;	  

  RecursiveFibonacci fibb_eng = RecursiveFibonacci(n, algorithm);
  fibb_eng.run();
 
  std::cout << "The " << n <<"th number in the Fibonacci series is " << fibb_eng.val() << std::endl;
}
