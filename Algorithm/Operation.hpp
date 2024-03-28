#ifndef RMARMOR_OPERATION_HPP
#define RMARMOR_OPERATION_HPP

#include "../GlobalDef.hpp"



typedef void (*Func)(void* args, void* result);

// T是参数结构体,R是返回值类型
template <typename T, typename R>
void operation(Func func, T *args, R *result);

void ReceiveData(void* result, int length);

void SendData(void* args, int length);




#endif //RMARMOR_OPERATION_HPP
