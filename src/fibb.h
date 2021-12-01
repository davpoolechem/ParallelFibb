#include <chrono>
#include <future>
#include <memory>
#include <thread>
#include <unistd.h>

#include "algs.h"

class RecursiveFibonacci {
  long long int n_; //fibonacci number of calculate
  long long int val_; //value of n_'th fibonacci number
  double elapsed_; //time elapsed during calculation  

  std::unique_ptr<RecursiveFibonacciAlgorithm> algorithm_; //pointer to algorithm functor
  
public:
  //-- constructors and destructors --//
  RecursiveFibonacci(long long int n, Algorithm algorithm=Algorithm::CXX) 
  : n_(n), val_(0), elapsed_(0.0), algorithm_(nullptr) 
  {
    switch(algorithm) {
      case Algorithm::CXX: 
    	algorithm_ = std::unique_ptr<CxxAlgorithm>(new CxxAlgorithm());  
        break;
      case Algorithm::OPENMP:
    	algorithm_ = std::unique_ptr<OpenMPAlgorithm>(new OpenMPAlgorithm());  
        break;
      case Algorithm::SERIAL: 
    	algorithm_ = std::unique_ptr<SerialAlgorithm>(new SerialAlgorithm());  
        break;
      default: throw std::invalid_argument("Specified algorithm does not exist!"); break;
    }
  }

  /*
  RecursiveFibonacci(long long int n, int omp_num_threads) 
  : n_(n), val_(0), elapsed_(0.0) 
  {
    algorithm_ = std::make_unique<RecursiveFibonacciAlgorithm>(new OpenMPAlgorithm(omp_num_threads));  
  }
  */

  ~RecursiveFibonacci() { };

  //-- setters and getters --//
  void set_n(long long int n) { n_ = n; }
  long long int n() { return n_; }
  const long long int n() const { return n_; }

  long long int val() { return val_; }
  const long long int val() const { return val_; }

  long long int elapsed() { return elapsed_; }
  const long long int elapsed() const { return elapsed_; }
 
  Algorithm algorithm() { return algorithm_->algorithm(); }
  const Algorithm algorithm() const { return algorithm_->algorithm(); }

  //-- compute nth fibonacci number --//
  void run() {
    auto start_time = std::chrono::system_clock::now();
    val_ = algorithm_->compute_fibb(n_); 
    auto end_time = std::chrono::system_clock::now();
    
    elapsed_ = std::chrono::duration_cast<std::chrono::milliseconds>(end_time 
      - start_time).count();
  }
};

