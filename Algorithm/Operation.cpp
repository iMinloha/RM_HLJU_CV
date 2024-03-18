#include "Operation.hpp"
#include "thread"

template <typename T, typename R>
void operation(Func func, T *args, R *result){
#if MultiThread == ON
    std::thread t(func, args, result);
    t.join();
#endif
}