#pragma once
#include "jVector.h"
#include <utility>

namespace jGraphic {

    class jPlane {
    public:
        jPlane(float A, float B, float C, float D) : A_(A), B_(B), C_(C), D_(D) {}
        jPlane(const jPoint3D &x1, const jPoint3D &x2, const jPoint3D &x3){
            A_ = x1[1] * (x2[2] - x3[2]) + x2[1] * (x3[2] - x1[2]) + x3[1] * (x1[2] - x2[2]);
            B_ = x1[2] * (x2[0] - x3[0]) + x2[2] * (x3[0] - x1[0]) + x3[2] * (x1[0] - x2[0]);
            C_ = x1[0] * (x2[1] - x3[1]) + x2[0] * (x3[1] - x1[1]) + x3[0] * (x1[1] - x2[1]);
            D_ = -x1[0] * (x2[1] * x3[2] - x3[1] * x2[2]) - x2[0] * (x3[1] * x1[2] - x1[1] * x3[2]) - x3[0] * (x1[1] * x2[2] - x2[1] * x1[2]);
        }
        const jVec_3<float> Normal() {
            jVec_3<float> ret = jVec_3<float>{A_, B_, C_};
            return std::move(ret);
        }
    private:
        float A_, B_, C_, D_;       // A plane can be described as Ax + By + Cz + D = 0;
    };

}