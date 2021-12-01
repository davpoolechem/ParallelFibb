#include <chrono>
#include <future>
#include <thread>
#include <unistd.h>

enum class Algorithm {
  CXX, 
  OPENMP, 
  SERIAL, 
};

class RecursiveFibonacciAlgorithm {
protected:
  Algorithm algorithm_; //algorithm to use

public:
  virtual ~RecursiveFibonacciAlgorithm() = default;
  
  virtual long long int compute_fibb(long long int n) = 0; 

  Algorithm algorithm() { return algorithm_; }
  const Algorithm algorithm() const { return algorithm_; }

protected:
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

class CxxAlgorithm : public RecursiveFibonacciAlgorithm {
public:
  CxxAlgorithm() = default;	
  virtual ~CxxAlgorithm() = default;
  CxxAlgorithm(CxxAlgorithm&&) = default;

  virtual long long int compute_fibb(long long int n) override {
    #define IMPL false 
    #if IMPL
    //sleep(rand()%3+1);
    int tmp = work_function(0);
    if(n <= 1) { 
      return n + tmp - tmp;
    } else {
      auto tmpn1 = std::async(compute_fibb, n-1); 
      auto tmpn2 = std::async(compute_fibb, n-2); 
      return tmpn1.get() + tmpn2.get() + tmp - tmp;
    }
    #else
    throw std::runtime_error("CXX algorithm not yet implemented.");	
    #endif
  }   
};

class OpenMPAlgorithm : public RecursiveFibonacciAlgorithm {
  static const int omp_num_threads_ = 4; //number of openmp threads to use
	
public:
  OpenMPAlgorithm() = default;	
  virtual ~OpenMPAlgorithm() = default;
  OpenMPAlgorithm(OpenMPAlgorithm&&) = default;

  /*
  void set_openmp_threads(int omp_num_threads) { 
    omp_num_threads_ = omp_num_threads; 
  }
  */
  int omp_num_threads() { return omp_num_threads_; }
  const int omp_num_threads() const { return omp_num_threads_; }

  virtual long long int compute_fibb(long long int n) override {
    int val;
    #pragma omp parallel num_threads(omp_num_threads_) 
    {
      #pragma omp single nowait
      {
        val = compute_fibb_impl(n); 
      }
    }
    return val;
  }

private:
  long long int compute_fibb_impl(long long int n) {
    int tmp = work_function(0);
    if(n <= 1) {
      return n + tmp - tmp;
    } else {
      long long int tmp1, tmp2;
      #pragma omp task shared(tmp1)
      {
        tmp1 = compute_fibb_impl(n-1);
      } 
      #pragma omp task shared(tmp2)
      {
        tmp2 = compute_fibb_impl(n-2);
      }
      #pragma omp taskwait

      return tmp1 + tmp2 + tmp - tmp;
    }
  }
};

class SerialAlgorithm : public RecursiveFibonacciAlgorithm {
public:
  SerialAlgorithm() = default;	
  virtual ~SerialAlgorithm() = default;
  SerialAlgorithm(SerialAlgorithm&&) = default;

  virtual long long int compute_fibb(long long int n) override {
    int tmp = work_function(0);
    if(n <= 1) {
      return n + tmp - tmp;
    } else {
      return compute_fibb(n-1) + compute_fibb(n-2) + tmp - tmp;
    }
  }
};


