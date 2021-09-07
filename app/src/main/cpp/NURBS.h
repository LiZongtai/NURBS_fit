//
// Created by Administrator on 2021/9/7.
//

#ifndef NURBS_FIT_NURBS_H
#define NURBS_FIT_NURBS_H
#include <math.h>
#include <numeric>
struct InputData
{
    float * p;
    int knotsNum;
    int ctrPNum;
    int * w;
    double * x;
    float * dataPara;
    float * knots;
};

class NURBS {
public:
    /**
     * Centripetal Method
     * @param inputData
     * @return
     */
    static float* ParametrizationCM(InputData inputData);
    static double * ones(int n);
    static double * zeros(int n);
    static double *linspace(double begin, double finish, int number);

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
