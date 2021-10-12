#include "fibb.h"

#include <iostream>
#include <string>
#include <unordered_map> 

int main(int argc, char* argv[]) {
	long long int n = atoll(argv[1]);	

  std::unordered_map<Algorithm, std::string> algorithms; 
  algorithms[Algorithm::CXX] = "CXX";
  algorithms[Algorithm::OPENMP] = "OPENMP";
  
  RecursiveFibonacci fibb_eng = RecursiveFibonacci(n-1);
  for (auto algorithm : algorithms) {
    fibb_eng.set_algorithm(algorithm.first);
    fibb_eng.run();
   
    std::cout << "The " << n << "th number of the Fibonacci series using the "
      << algorithm.second << " algorithm is: " << fibb_eng.val() << std::endl;
    std::cout << "The time it took to complete algorithm " << algorithm.second 
      << " is: " << fibb_eng.elapsed()/1000.0 << " s." << std::endl;
  }
}
