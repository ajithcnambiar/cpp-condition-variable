#ifndef _ZERO_EVEN_ODD_H_
#define _ZERO_EVEN_ODD_H_
#include <functional>
#include <condition_variable>
#include <mutex>
#include <iostream>
class ZeroOddEven{
    // input integer, generates until n
    int n;
    // counter counts upto n
    int counter;
    // condition variable, helps to realize unblock a thread until a condition is met.
    std::condition_variable cv;
    // used part of condition to generate "0"
    bool generate0;
    // used part of condition to signal to end worker thread
    bool done;
    // mutex used to synchronize changes on shared variables n, counter, generate0 and done
    // used side by side with condition variable
    std::mutex m;
    // stores result
    std::string result;
    void togglegenerate0(){
        generate0 = !generate0;
    }
    void incCounter(){
        counter++;
    }
public:
    ZeroOddEven(int n): n(n), counter(1), generate0(true),done(false),result(""){}

    // Generating methods wait on condition variable until lambda returns true.
    // lambda is different for each method to generate intended number
    // Condition variable uses mutex to synchronize changes on shared variables
    // notify_all is used instead of notify_one b/c multiple threads will be waiting on condition at same time.
    void zero(std::function<void(std::string&, int)>);
    void odd(std::function<void(std::string&, int)>);
    void even(std::function<void(std::string&, int)>);
    std::string get_result(){return result;}
};
#endif
