#include "AimLock.hpp"

using namespace cv;

int Check(){
#if CUDA == ON && CPU == OFF
    using namespace cv::cuda;
    cuda::printCudaDeviceInfo(cuda::getDevice());
    int count = getCudaEnabledDeviceCount();
    cout << "Supporting " << count << " CUDA cores" << endl;
    return count;
#endif
}

// �˷�������Multi thread
void NMS(vector<Rect> &srcRect, float thresh){
    vector<int> res;
    vector<float> areas;
    for (int i = 0; i < srcRect.size(); i++){
        areas.push_back(srcRect[i].width * srcRect[i].height);
    }
    for (int i = 0; i < srcRect.size(); i++)
        for (int j = i + 1; j < srcRect.size(); j++){
            int x1 = max(srcRect[i].x, srcRect[j].x);
            int y1 = max(srcRect[i].y, srcRect[j].y);
            int x2 = min(srcRect[i].x + srcRect[i].width, srcRect[j].x + srcRect[j].width);
            int y2 = min(srcRect[i].y + srcRect[i].height, srcRect[j].y + srcRect[j].height);
            int w = max(0, x2 - x1);
            int h = max(0, y2 - y1);
            float overlap = w * h / (areas[i] + areas[j] - w * h);
            if (overlap > thresh){
                if (areas[i] > areas[j]){
                    res.push_back(j);
                }else{
                    res.push_back(i);
                }
            }
        }

    sort(res.begin(), res.end());
    res.erase(unique(res.begin(), res.end()), res.end());
    vector<Rect> result;
    for (int i = 0; i < srcRect.size(); i++){
        if (find(res.begin(), res.end(), i) == res.end()){
            result.push_back(srcRect[i]);
        }
    }
    srcRect = result;
}

// ѵ��SVM
/*
 * @param trainData ѵ�����ݼ�(ͨ��generate_dataset����)
 * @param labels ��ǩ(ͨ��generate_dataset����)
 * @param path ����·��
 * */
void TrainSVM(Mat trainData, Mat labels, string path){
    Ptr<cv::ml::SVM> svm = cv::ml::SVM::create();
    Mat data, label;
    svm->setGamma(5.383);
    svm->setKernel(cv::ml::SVM::LINEAR);
    svm->setC(2.67);
    svm->setType(cv::ml::SVM::C_SVC);
    svm->train(trainData, cv::ml::ROW_SAMPLE, labels);
    svm->save(path);
}

/*
 * @param image ͼ��
 * @param desc HOG������
 * @note �÷������ڻ�ȡ����ǰ��HOG������(��Ҫ��SVMȥԤ��)
 * */
void get_hog_descripor(Mat &image, vector<float> &desc) {
    HOGDescriptor hog;
    int h = image.rows;
    int w = image.cols;
    float rate = 64.0 / w;
    Mat img, gray;
    resize(image, img, Size(64, int(rate * h)));
    cvtColor(img, gray, COLOR_BGR2GRAY);
    Mat result = Mat::zeros(Size(64, 128), CV_8UC1);
    result = Scalar(127);
    Rect roi;
    roi.x = 0;
    roi.width = 64;
    roi.y = (128 - gray.rows) / 2;
    roi.height = gray.rows;
    gray.copyTo(result(roi));
    hog.compute(result, desc, Size(8, 8), Size(0, 0));
}

/*
 * @param svm SVMģ��
 * @note �÷������ڻ�ȡSVM�ļ����
 * */
vector<float> get_svm_detector(const Ptr<cv::ml::SVM>& svm){
    // get the support vectors
    Mat sv = svm->getSupportVectors();
    const int sv_total = sv.rows;
    // get the decision function
    Mat alpha, svidx;
    double rho = svm->getDecisionFunction(0, alpha, svidx);

    CV_Assert(alpha.total() == 1 && svidx.total() == 1 && sv_total == 1);
    CV_Assert((alpha.type() == CV_64F && alpha.at<double>(0) == 1.) ||
              (alpha.type() == CV_32F && alpha.at<float>(0) == 1.f));
    CV_Assert(sv.type() == CV_32F);

    vector< float > hog_detector(sv.cols + 1);
    memcpy(&hog_detector[0], sv.ptr(), sv.cols * sizeof(hog_detector[0]));
    hog_detector[sv.cols] = (float)-rho;
    return hog_detector;
}

// ѵ����������
/*
 * @param trainData ѵ������(��)
 * @param labels ��ǩ(��)
 * @param positive_dir ������·��(�������ú��ͼƬ����ѵ��)
 * @param negative_dir ������·��(������������ͼƬ����ѵ��)
 * @note �������к������������ӵ�ͼƬ������ѵ������
 * */
void generate_dataset(Mat &trainData, Mat &labels, string positive_dir, string negative_dir){
    vector<string> images;
    vector<vector<float>> vecDec;
    vector<float> fv;
    glob(positive_dir, images);
    int posNum = images.size();
    for (int i = 0; i < posNum; i++){
        Mat image = imread(images[i].c_str());
        vector<float> fv;
        get_hog_descripor(image, fv);
        printf("image path : %s, feature data length: %d \n", images[i].c_str(), fv.size());
        vecDec.push_back(fv);
    }
    images.clear();
    glob(negative_dir, images);

    int negNum = images.size();
    for (int i = 0; i < negNum; i++){
        fv.clear();
        Mat image = imread(images[i].c_str());
        get_hog_descripor(image, fv);
        printf("image path : %s, feature data length: %d \n", images[i].c_str(), fv.size());
        vecDec.push_back(fv);
    }
    int trainDataNum = posNum + negNum;
    int trainDataLen = fv.size();


    Mat trainDataTemp(trainDataNum, trainDataLen, CV_32FC1);
    Mat trainLabel(trainDataNum, 1, CV_32SC1);


    for (int i = 0; i < trainDataNum; i++){
        for (int j = 0; j < trainDataLen; j++){
            trainDataTemp.at<float>(i, j) = vecDec[i][j];
        }
        if (i < posNum) trainLabel.at<int>(i) = 1;
        else trainLabel.at<int>(i) = -1;
    }
    trainData = trainDataTemp.clone();
    labels = trainLabel.clone();
    return;
}

enum YoloOutput{B1, B2, B3, B4, B5, BO, BS, R1, R2, R3, R4, R5, RO, RS};

// ���з���
vector<Point_t> getBoard(Mat img, AimColor color
#if ONNX == ON && TensorRT == OFF
, const string& onnxPath
#endif
){
    vector<Point_t> result;
#if SVM_Mode == ON && DNN_Mode == OFF
    Ptr<cv::ml::SVM> svm;
    // ��ȡSVMģ��
    if (color == Blue)
        svm = cv::ml::SVM::load("Blue.xml");
    else svm = cv::ml::SVM::load("Red.xml");
    // ��ȡSVM�����
    vector<float> hog_detector = get_svm_detector(svm);
    HOGDescriptor hog;
    hog.setSVMDetector(hog_detector);
    vector<Rect> found, found_filtered;
    vector<Point_t> result;
    hog.detectMultiScale(img, found, 0, Size(8, 8), Size(32, 32), 1.05, 2);
    NMS(found, 0.3);
    for (int i = 0; i < found.size(); i++){
        rectangle(img, found[i], Scalar(0, 255, 0), 2);
        result.push_back(new TPoint(found[i].x, found[i].y));
    }

    return result;
#elif CUDA == ON && CPU == OFF
    // �ж���ONNX����TensorRT, ȡ���������ļ�
    #if ONNX == ON && TensorRT == OFF
        // ONNXģ��
        cv::dnn::Net net = cv::dnn::readNetFromONNX(onnxPath);
        cv::Size size = cv::Size(1024, 1024);
        // ��������ߴ�
        net.setInput(cv::dnn::blobFromImage(img, 1.0, size, cv::Scalar(), true, false));
        std::vector<cv::String> output_layer_names = net.getUnconnectedOutLayersNames();
        Mat output;
        net.forward(output, output_layer_names);
        // ���NMS
        Mat labels, scores, boxes;
        for (int i = 0; i < output.rows; i++){
            float* data = output.ptr<float>(i);
            int index = (int)data[0];
            float score = data[1];
            float x = data[2] * img.cols;
            float y = data[3] * img.rows;
            float w = data[4] * img.cols;
            float h = data[5] * img.rows;
            Rect rect(x - w / 2, y - h / 2, w, h);
            result.push_back(new TPoint(rect.x, rect.y));
        }
        return result;

    #elif ONNX == OFF && TensorRT == ON
        // TensorRTģ��
        Logger logger;
        logger.out("TensorRTģ��");
        return NULL;
    #else
        Logger logger;
        logger.out("Error: CUDAģ��δ����");
        return NULL;
    #endif
#else
    Logger logger;
    logger.out("Error: ģʽδ����");
    return NULL;
#endif
    return result;
}