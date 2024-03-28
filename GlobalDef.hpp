/*
 * @author: Minloha
 * @blog: https://blog.minloha.cn
 * @file: 全局宏定义,用于开启功能
 */

#ifndef RMARMOR_GLOBALDEF_HPP
#define RMARMOR_GLOBALDEF_HPP

#define ON true
#define OFF false

// 调试模式(值为1时输出信息)
#define DEBUG ON
// 串口通信设备
#define SerialPort "/dev/ttyS0"
// --------------[二选一为ON]---------------
// 双目相机
#define DoubleEye OFF
// 单目相机
#define Monocular ON
// ------------------------------
// 你可以使用yolo或者神经网络去完成目标识别，但是为了速度考虑，模型最好要量化
// CPU模式(与GPU二选一开启, 务必配置cuda和cudnn, 否则性能牺牲太大了)
#define CPU OFF
// CUDA模式
#define CUDA ON
// ONNX模型、TensorRT模型启用与否(你可以使用Yolo的量化模式, 可以更精确)
// ================[开启GPU模式使用]===================
#define ONNX ON
#define TensorRT OFF
// ==================================================
// CPU的多线程
#define MultiThread ON
// 目标识别方式(对应CPU和GPU)
#define SVM_Mode OFF
#define DNN_Mode ON
// 索敌颜色
enum AimColor{
    Red,
    Blue
};


#endif
