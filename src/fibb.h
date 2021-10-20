#include <chrono>
#include <future>
#include <thread>
#include <unistd.h>

enum class Algorithm {
  CXX, 
  OPENMP, 
  SERIAL, 
};

class RecursiveFibonacci {
  long long int n_; //fibonacci number of calculate
  long long int val_; //value of n_'th fibonacci number
  double elapsed_; //time elapsed during calculation  

  Algorithm algorithm_; //algorithm to use
  int openmp_threads_; //number of threads to use for OpenMP algorithm
  
public:
  //-- constructors and destructors --//
  RecursiveFibonacci(long long int n, Algorithm algorithm=Algorithm::CXX,
    int openmp_threads=4) 
  : n_(n), val_(0), elapsed_(0.0), algorithm_(algorithm), 
    openmp_threads_(openmp_threads) { }
  
  ~RecursiveFibonacci() { };

  //-- setters and getters --//
  void set_n(long long int n) { n_ = n; }
  long long int n() { return n_; }
  const long long int n() const { return n_; }

  long long int val() { return val_; }
  const long long int val() const { return val_; }

  long long int elapsed() { return elapsed_; }
  const long long int elapsed() const { return elapsed_; }
 
  void set_algorithm(Algorithm algorithm) { algorithm_ = algorithm; }
  Algorithm algorithm() { return algorithm_; }
  const Algorithm algorithm() const { return algorithm_; }

  void set_openmp_threads(int openmp_threads) { 
    openmp_threads_ = openmp_threads; 
  }
  int openmp_threads() { return openmp_threads_; }
  const int openmp_threads() const { return openmp_threads_; }

  //-- compute nth fibonacci number --//
  void run() {
    auto start_time = std::chrono::system_clock::now();
    switch(algorithm_) {
      case Algorithm::CXX: 
        val_ = fibb_cxx(n_); 
        break;
      case Algorithm::OPENMP:
        #pragma omp parallel num_threads(openmp_threads_) 
        {
          #pragma omp single nowait
          {
            val_ = fibo_openmp(n_); 
          }
        }
        break;
      case Algorithm::SERIAL: 
        val_ = fibo_serial(n_); 
        break;
      default: throw std::invalid_argument("Specified algorithm does not exist!"); break;
    }
    auto end_time = std::chrono::system_clock::now();
    
    elapsed_ = std::chrono::duration_cast<std::chrono::milliseconds>(end_time 
      - start_time).count();
  }

private:
  static long long int fibb_cxx(long long int n) {
	  //sleep(rand()%3+1);
	  int tmp = work_function(100);
    if(n <= 1) { 
		  return n + tmp - tmp; 
	  } else {
		  auto tmpn1 = std::async(fibb_cxx, n-1); 
		  auto tmpn2 = std::async(fibb_cxx, n-2); 
		  return tmpn1.get() + tmpn2.get() + tmp - tmp;
  	}
  }

  static long long int fibo_openmp(long long int n) {
	  int tmp = work_function(100);
    if(n <= 1) {
      return n + tmp - tmp;
    } else {
      long long int tmp1, tmp2;
      #pragma omp task shared(tmp1)
      {
        tmp1 = fibo_openmp(n-1);
      } 
      #pragma omp task shared(tmp2)
      {
        tmp2 = fibo_openmp(n-2);
      }
      #pragma omp taskwait

      return tmp1 + tmp2 + tmp - tmp;
    }
  }

  static long long int fibo_serial(long long int n) {
	  int tmp = work_function(100);
    if(n <= 1) {
      return n + tmp - tmp;
    } else {
      return fibo_serial(n-1) + fibo_serial(n-2) + tmp - tmp;
    }
  }
  
  static long long int work_function(int loop) {
    long long int tmp = 0;
    for (int iloop = 1; iloop <= loop; ++iloop) {
      for (int jloop = 1; jloop <= loop; ++jloop) {
        for (int kloop = 1; kloop <= loop; ++kloop) {
          for (int lloop = 1; lloop <= loop; ++lloop) {
            tmp /= rand()%iloop + 1;
            tmp += rand()%jloop;
            tmp += rand()%kloop;
            tmp -= rand()%lloop;
          }
        }
      }
    }

    return tmp;
  }
};

