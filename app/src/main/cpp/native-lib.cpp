#include <jni.h>
#include <string>
#include "log/AndroidLog.h"
#include <math.h>
#include <vector>
#include "NURBS.h"


extern "C" JNIEXPORT jstring JNICALL
Java_tongji_lzt_nurbs_1fit_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jfloatArray JNICALL
Java_tongji_lzt_nurbs_1fit_MainActivity_NURBS_1fit(JNIEnv *env, jobject thiz, jfloatArray pdata) {
    jsize len = env->GetArrayLength(pdata);
    jboolean isCopy;
    std::vector<float> dataVector;
    dataVector.reserve(len);
    float * dataArr=(float *)env->GetFloatArrayElements(pdata,&isCopy);
    for (int i=0; i<len; i++)
    {
        dataVector.push_back(dataArr[i]);
    }
    if (isCopy == JNI_TRUE)
    {
        env->ReleaseFloatArrayElements(pdata, dataArr, JNI_ABORT);
    }
//    LOGE("width %d", data_length);
    InputData inputData;
    inputData.data=dataVector;
    inputData.pNum=len/2;
    inputData.k=3;
    inputData.ctrPNum=13;
    inputData.w=(int* )NURBS::ones(inputData.ctrPNum);
    inputData.xNum=100;
    inputData.x=NURBS::linspace(0,1,inputData.xNum);
    inputData.dataPara= NURBS::parametrizationCM(inputData);
    inputData.knots=NURBS::getKnotsUAVG(inputData);
    //fit the curve
    inputData.data=NURBS::invCtrP(inputData);
    inputData.dataPara= NURBS::parametrizationCM(inputData);
    inputData.knots=NURBS::getKnotsUAVG(inputData);
    std::vector<float> Q=NURBS::fitP(inputData);

//    jfloatArray dataPara = env->NewFloatArray(inputData.ctrPNum);
//    env->SetFloatArrayRegion(dataPara, 0, inputData.ctrPNum, inputData.dataPara);
//    jfloatArray dataPara = env->NewFloatArray(inputData.ctrPNum + inputData.k + 1);
//    env->SetFloatArrayRegion(dataPara, 0, inputData.ctrPNum + inputData.k + 1, inputData.knots);
//    jfloatArray dataPara = env->NewFloatArray(len);
//    env->SetFloatArrayRegion(dataPara, 0, len, inputData.data.data());
    jfloatArray dataPara = env->NewFloatArray(inputData.xNum*2);
    env->SetFloatArrayRegion(dataPara, 0, inputData.xNum*2, Q.data());

    return dataPara;

}