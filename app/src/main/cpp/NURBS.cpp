//
// Created by Administrator on 2021/9/7.
//

#include "NURBS.h"
float *NURBS::ParametrizationCM(InputData inputData) {
    float * data=inputData.p;
    int n = inputData.ctrPNum;
    float * dataPara=(float*)zeros(n);
    double * L= GetTwoPointsDis(data, n, 1/2);
    double sum1 = std::accumulate(L, L + n-1, 0);
    for(int i=1;i<n-1;i++){
        double sum2 = std::accumulate(L, L + i-1, 0);
        dataPara[i]=sum2/sum1;
    }
    dataPara[n-1]=1.0f;
    return dataPara;
}


double *NURBS::GetTwoPointsDis(float *data,int length, float p) {
    int n=length;
    double * Dis =zeros(n-1);
    for (int i=0;i<n-1;i++){
        int i1=2*i;
        int i2=2*(i+1);
        double A=norm2(data[i1]-data[i2],data[i1+1]-data[i2+1]);
        Dis[i]=pow(A,p);
    }
    return Dis;
}

double NURBS::norm2(double a, double b) {
    return sqrt(a*a+b*b);
}

double *NURBS::ones(int n) {
    double * Array = (double *)malloc(n * sizeof(double));	// 在堆中申请内存
    memset(Array, 1, n * sizeof(double));			// 初始化数组全为 0
    return Array;
}

double *NURBS::zeros(int n) {
    double * Array = (double *)malloc(n * sizeof(double));	// 在堆中申请内存
    memset(Array, 0, n * sizeof(double));			// 初始化数组全为 0
    return Array;
}

double * NURBS::linspace(double begin,double finish,int n)
{
    int j;
    double interval = (finish-begin)/(n-1);
    double * data = (double *)malloc(n * sizeof(double));	// 在堆中申请内存
    memset(data, 0, n * sizeof(double));			// 初始化数组全为 0
    for (j=0;j<n;j++)
        data[j]=begin+j*interval;
    return data;
}


