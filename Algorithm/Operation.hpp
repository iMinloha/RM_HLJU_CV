#ifndef RMARMOR_OPERATION_HPP
#define RMARMOR_OPERATION_HPP


typedef void (*Func)();

// T是参数结构体,R是返回值类型
template <typename T, typename R>
void operation(Func func, T *args, R *result){
    func();
}






#endif //RMARMOR_OPERATION_HPP
