#include "zeroevenodd.h"
#include <gtest/gtest.h>
#include <thread>
using namespace std;

class store_result{
public:
    void operator()(std::string& out, int i){
        out += std::to_string(i);
    }
};

TEST(ZeroEvenOdd, Positive){
    ZeroOddEven object(10);
    function<void(string&, int)> fp = store_result();
    std::thread t1(&ZeroOddEven::zero, &object, fp);
    std::thread t2(&ZeroOddEven::even, &object, fp);
    std::thread t3(&ZeroOddEven::odd, &object, fp);

    t1.join();
    t2.join();
    t3.join();

    ASSERT_EQ(object.get_result(), "010203040506070809010");
}
