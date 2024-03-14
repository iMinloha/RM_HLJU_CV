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
// --------------[��ѡһΪON]---------------
// ˫Ŀ���
#define DoubleEye OFF
// ��Ŀ���
#define Monocular ON
// ------------------------------
// �����ʹ��yolo����������ȥ���Ŀ��ʶ�𣬵���Ϊ���ٶȿ��ǣ�ģ�����Ҫ����
// CPUģʽ(��GPU��ѡһ����, �������cuda��cudnn, ������������̫����)
#define CPU ON
// CUDAģʽ
#define CUDA OFF
// ONNXģ�͡�TensorRTģ���������(�����ʹ��Yolo������ģʽ, ���Ը���ȷ)
// ================[����GPUģʽʹ��]===================
#define ONNX ON
#define TensorRT OFF
// ==================================================
// CPU�Ķ��߳�
#define MultiThread ON
// Ŀ��ʶ��ʽ
#define SVM_Mode ON
#define DNN_Mode OFF
// ������ɫ
enum AimColor{
    Red,
    Blue
};


#endif
