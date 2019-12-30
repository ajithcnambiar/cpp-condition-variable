#include "zeroevenodd.h"
using namespace std;

void ZeroOddEven::zero(function<void(string&, int)> store_result){
    while(true){
        unique_lock<mutex> lk(m);
        // cout << "zero waiting " << "\n";
        cv.wait(lk, [this]{ return generate0 || done;});
        if (counter == n+1) {done = true; togglegenerate0();lk.unlock(); cv.notify_all();return;}
        // cout << "zero " ;
        store_result(result,0);
        togglegenerate0();
        // cout << "\n";
        lk.unlock();
        cv.notify_all();
    }
}

void ZeroOddEven::odd(function<void(string&, int)> store_result){
    while(true){
        unique_lock<mutex> lk(m);
        // cout << "odd waiting " << "\n";
        cv.wait(lk, [this]{ return (generate0 == false && counter %2 == 1) || done;});
        if (counter == n+1) {done = true; togglegenerate0();lk.unlock(); cv.notify_all();return;}
        // cout << "odd " ;
        store_result(result, counter);
        togglegenerate0();
        incCounter();
        // cout << "\n";
        lk.unlock();
        cv.notify_all();
    }
}

void ZeroOddEven::even(function<void(string&, int)> store_result){
    while(true){
        unique_lock<mutex> lk(m);
        // cout << "even waiting " << "\n";
        cv.wait(lk, [this]{ return (generate0 == false && counter %2 == 0) || done;});
        if (counter == n+1) {done = true;togglegenerate0();lk.unlock(); cv.notify_all();return;}
        // cout << "even " ;
        store_result(result, counter);
        togglegenerate0();
        incCounter();
        // cout << "\n";
        lk.unlock();
        cv.notify_all();
    }
}
