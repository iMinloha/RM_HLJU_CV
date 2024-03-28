#ifndef RMARMOR_OPERATION_HPP
#define RMARMOR_OPERATION_HPP

#include "../GlobalDef.hpp"



typedef void (*Func)(void* args, void* result);

// T�ǲ����ṹ��,R�Ƿ���ֵ����
template <typename T, typename R>
void operation(Func func, T *args, R *result);

void ReceiveData(void* result, int length);

void SendData(void* args, int length);




#endif //RMARMOR_OPERATION_HPP
