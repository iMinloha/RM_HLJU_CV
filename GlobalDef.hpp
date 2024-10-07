/*
 * @author: Minloha
 * @blog: https://blog.minloha.cn
 * @file: ȫ�ֺ궨��,���ڿ�������
 */

#ifndef RMARMOR_GLOBALDEF_HPP
#define RMARMOR_GLOBALDEF_HPP

#define ON true
#define OFF false

// ����ģʽ(ֵΪ1ʱ�����Ϣ)
#define DEBUG ON
// ����ͨ���豸
#define SerialPort "/dev/ttyS0"
// --------------[��ѡһΪON]---------------
// ˫Ŀ���
#define DoubleEye OFF
// ��Ŀ���
#define Monocular ON
// ------------------------------
// �����ʹ��yolo����������ȥ���Ŀ��ʶ�𣬵���Ϊ���ٶȿ��ǣ�ģ�����Ҫ����
// CPUģʽ(��GPU��ѡһ����, �������cuda��cudnn, ������������̫����)
#define CPU OFF
// CUDAģʽ
#define CUDA ON
// ONNXģ�͡�TensorRTģ���������(�����ʹ��Yolo������ģʽ, ���Ը���ȷ)
// ================[����GPUģʽʹ��]===================
#define ONNX ON
#define TensorRT OFF
// ==================================================
// CPU�Ķ��߳�
#define MultiThread ON
// Ŀ��ʶ��ʽ(��ӦCPU��GPU)
#define SVM_Mode OFF // ����CPU��һ��Ҫ����SVM
#define DNN_Mode ON // ����GPU��һ��Ҫ����DNN(ע�⣬������ָ�����磬��û��дʹ��cuda���ٵĴ�ͳ�Ӿ��㷨)
// ������ɫ
enum AimColor{
    Red,
    Blue
};

// ������ɫ
// ����ÿ�η����ʱ�򣬲�ͬ��ɫ�ĵ��˷ֿ�
#define EnemyColor Red

#endif
