//
// Created by Administrator on 2021/9/7.
//

#include "NURBS.h"
#include "log/AndroidLog.h"

float *NURBS::parametrizationCM(InputData inputData) {
    float *data = inputData.data.data();
    int n = inputData.pNum;
    float *dataPara = (float *) zeros(n);
    double *L = GetTwoPointsDis(data, n, 1 / 2);
    double sum1 = std::accumulate(L, L + n, 0);
    for (int i = 1; i < n - 1; i++) {
        double sum2 = std::accumulate(L, L + i - 1, 1);
        dataPara[i] = sum2 / sum1;
    }
    dataPara[n - 1] = 1.0f;
    return dataPara;
}


double *NURBS::GetTwoPointsDis(float *data, int length, float p) {
    int n = length;
    double *Dis = zeros(n - 1);
    for (int i = 0; i < n - 1; i++) {
        int i1 = 2 * i;
        int i2 = 2 * (i + 1);
        double A = norm2(data[i1] - data[i2], data[i1 + 1] - data[i2 + 1]);
        Dis[i] = pow(A, p);
    }
    return Dis;
}

double NURBS::norm2(double a, double b) {
    return sqrt(a * a + b * b);
}

double *NURBS::ones(int n) {
    double *Array = (double *) malloc(n * sizeof(double));    // 在堆中申请内存
    memset(Array, 1, n * sizeof(double));            // 初始化数组全为 0
    return Array;
}

double *NURBS::zeros(int n) {
    double *Array = (double *) malloc(n * sizeof(double));    // 在堆中申请内存
    memset(Array, 0, n * sizeof(double));            // 初始化数组全为 0
    return Array;
}

double *NURBS::linspace(double begin, double finish, int n) {
    int j;
    double interval = (finish - begin) / (n - 1);
    double *data = (double *) malloc(n * sizeof(double));    // 在堆中申请内存
    memset(data, 0, n * sizeof(double));            // 初始化数组全为 0
    for (j = 0; j < n; j++)
        data[j] = begin + j * interval;
    return data;
}

double *NURBS::getKnotsUAVG(InputData inputData) {
    int m = inputData.pNum;
    int n = inputData.ctrPNum;
    float *u = inputData.dataPara;
    int kn = inputData.k;
    double *knot = zeros(n + kn + 1);
    for (int i = n; i < n + kn + 1; i++) {
        knot[i] = 1.0;
    }
    for (int j = 1; j < n - kn; j++) {
        double sum1 = 0.0;
        for (int jj = 0; jj < kn + m - n; jj++) {
            sum1 += u[j + jj];
        }
        knot[j + kn] = sum1 / (kn + m - n);
    }
    return knot;
}

std::vector<float> NURBS::invCtrP(InputData inputData) {
    std::vector<float> data_f = inputData.data;
    std::vector<double> data(data_f.begin(), data_f.end());
    float *dataPara = inputData.dataPara;
    int k = inputData.k;
    int n = inputData.ctrPNum;
    int m = inputData.pNum;
    double *knots = inputData.knots;
    // r
    Eigen::MatrixXd r(n - 2, 2);
    for (int i = 1; i < m - 1; i++) {
        double basisFcn1 = getBasisFcn(dataPara[i], knots, 0, k);
        double basisFcn2 = getBasisFcn(dataPara[i], knots, n - 1, k);
        r(i - 1, 0) = data[2 * i]
                      - data[0] * basisFcn1
                      - data[2 * m - 2] * basisFcn2;
        r(i - 1, 1) = data[2 * i + 1]
                      - data[1] * basisFcn1
                      - data[2 * m - 1] * basisFcn2;
    }
//    for (int i = 0; i < r.rows(); i++) {
//        for (int j = 0; j < r.cols(); j++) {
//            LOGE("r[%d][%d]: %lf", i, j, r(i, j));
//        }
//    }

    // N
    Eigen::MatrixXd N(m - 2, n - 2);
    for (int j = 1; j < m - 1; j++) {
        double *x = zeros(n - 2);
        for (int i = 1; i < n - 1; i++) {
            x[i - 1] = getBasisFcn(dataPara[j], knots, i - 1, k);
        }
        for (int it = 0; it < n - 2; it++) {
            N(j - 1, it) = x[it];
        }
    }
//    for (int i = 0; i < N.rows(); i++) {
//        for (int j = 0; j < N.cols(); j++) {
//            LOGE("N[%d][%d]: %lf", i, j, N(i, j));
//        }
//    }
    Eigen::MatrixXd R = N.transpose() * r;
    Eigen::MatrixXd NN =  N.transpose()*N;
    Eigen::MatrixXd NNR =  NN.inverse()*R;


    float * ctrP =new float[m*2];
    ctrP[0]=data[0];
    ctrP[1]=data[1];
    for (int i = 0; i < NNR.rows(); i++) {
        for (int j = 0; j < NNR.cols(); j++) {
            ctrP[(i+1)*2+j]= NNR(i, j);
//            LOGE("R[%d][%d]: %lf", i, j, NNR(i, j));
        }
    }
    ctrP[2*m-2]=data[2*m-2];
    ctrP[2*m-1]=data[2*m-1];
    std::vector<float> ctrP_vector {ctrP, ctrP + 2*m};

    return ctrP_vector;
}

double NURBS::getBasisFcn(double x, double *knot, int i, int k) {
    double *knots = knot;
    double res = 0.0;
    if (k == 0) {
        if (x >= knots[i + 1] && x < knots[i + 2]) {
            res = 1.0;
        } else {
            res = 0.0;
        }
    } else {
        double A = getBasisFcn(x, knots, i, k - 1);
        double B = getBasisFcn(x, knots, i + 1, k - 1);
        double w1 = 0.0;
        double w2 = 0.0;
        if (A == 0) {
            // 防止迭代过程中,出现分母为0情况
            w1 = 0.0;
        } else {
            w1 = (x - knots[i + 1]) / (knots[i + k + 1] - knots[i + 1]);
//            LOGE("x : %lf", x);
//            LOGE("w1 : %lf",    x - knots[i + 1]);
        }
        if (B == 0) {
            w2 = 0.0;
        } else {
            w2 = (knots[i + k + 2] - x) / (knots[i + k + 2] - knots[i + 2]);
        }
        res = w1 * A + w2 * B;
    }
    return res;
}

std::vector<float> NURBS::fitP(InputData inputData) {
    std::vector<float> data = inputData.data;
    double * x=inputData.x;
    double * knots=inputData.knots;
    int k =inputData.k;
    int ctrPNum=inputData.ctrPNum;
    int * w =inputData.w;
    int xNum=inputData.xNum;
    // N
    Eigen::MatrixXd N(xNum, ctrPNum);
    for(int i=0;i<xNum;i++){
        for(int j=0;j<ctrPNum;j++){
            N(i,j)=getBasisFcn(x[i],knots,j-1,k);
        }
    }

//    Eigen::MatrixXd wm(1, ctrPNum);
//    Eigen::MatrixXd wn1(xNum, 1);
    Eigen::MatrixXd ctrPM(ctrPNum, 2);
//    for(int i=0;i<ctrPNum;i++){
//        wm(0,i)=w[i];
//    }
//    wn1=N*wm.transpose();
    for(int i=0;i<ctrPNum;i++){
//        for(int j=0;j<xNum;j++){
//            LOGE("N[%d][%d]: %lf", j, i, N(j, i));
//        }
        ctrPM(i,0) = data[2*i];
        ctrPM(i,1) =  data[2*i+1];
    }
    Eigen::MatrixXd Q(xNum, 2);
    Q=N*ctrPM;
    std::vector<float> Q_vector;
    for (int i = 0; i < Q.rows(); i++) {
        for (int j = 0; j < Q.cols(); j++) {
//            LOGE("Q[%d][%d]: %lf", i, j, Q(i, j));
        Q_vector.push_back((float)Q(i,j));
        }
    }

    return Q_vector;
}


