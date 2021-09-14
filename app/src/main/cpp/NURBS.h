//
// Created by Administrator on 2021/9/7.
//

#ifndef NURBS_FIT_NURBS_H
#define NURBS_FIT_NURBS_H
#include <math.h>
#include <numeric>
#include <vector>
#include "Eigen/Eigen/Dense"
#include "Eigen/Eigen/Core"

struct InputData
{
    std::vector<float> data;
    int pNum;
    int k;
    int ctrPNum;
    int * w;
    int xNum;
    double * x;
    float * dataPara;
    double * knots;
};

class NURBS {
public:
    static double * ones(int n);
    static double * zeros(int n);
    static double *linspace(double begin, double finish, int number);
    /**
     * Centripetal Method
     * @param inputData
     * @return
     */
    static float* parametrizationCM(InputData inputData);
    /**
     *
     * @param inputData
     * @return
     */
    static double * getKnotsUAVG(InputData inputData);
    /**
     *
     * @param data
     * @return
     */
    static std::vector<float> invCtrP(InputData inputData);

    static double getBasisFcn(double x, double * knots, int i, int k);

    static std::vector<float> fitP(InputData inputData);

private:
    /**
     *
     * @param data control points (n*2)
     * @param p pow number (chord length=1/2 Centripetal)
     * @return
     */
    static double * GetTwoPointsDis(float * data, int length, float p);

    static double norm2(double a, double b);


};


#endif //NURBS_FIT_NURBS_H
