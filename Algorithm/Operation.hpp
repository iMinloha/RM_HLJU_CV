#ifndef RMARMOR_OPERATION_HPP
#define RMARMOR_OPERATION_HPP


typedef void (*Func)();

// T�ǲ����ṹ��,R�Ƿ���ֵ����
template <typename T, typename R>
void operation(Func func, T *args, R *result){
    func();
}






#endif //RMARMOR_OPERATION_HPP
