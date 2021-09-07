#include <jni.h>
#include <string>
#include "log/AndroidLog.h"
#include <math.h>
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
    float* data=(float *)env->GetFloatArrayElements(pdata,0);
    int data_length=env->GetArrayLength(pdata);
//    LOGE("width %d", data_length);
    InputData inputData;
    inputData.p=data;
    inputData.knotsNum=3;
    inputData.ctrPNum=13;
//    int* wdata;
//    for(int i=0;i<inputData.ctrPNum;i++){
//        wdata
//    }
    inputData.w=(int* )NURBS::ones(inputData.ctrPNum);
    inputData.x=NURBS::linspace(0,1,100);
    inputData.dataPara= NURBS::ParametrizationCM(inputData);

    jfloatArray dataPara = env->NewFloatArray(inputData.ctrPNum);

    env->SetFloatArrayRegion(dataPara, 0, inputData.ctrPNum, inputData.dataPara);
    return dataPara;

}