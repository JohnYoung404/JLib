#pragma once
#include <boost/static_assert.hpp>
#include <cmath>
#include "jMath.h"
#include "jMatrix.h"
#include "jVector.h"

namespace jLib{
namespace jGraphic{

    inline const jVec4f transform(const jVec2f &pointToProj, const jMat4f &projMat) 
    {
            jVec4f ret = { pointToProj[0], pointToProj[1], 1, 1 };
            return projMat * ret;
    }
    inline const jVec4f transform(const jVec3f &pointToProj, const jMat4f &projMat)
    {
            jVec4f ret = { pointToProj[0], pointToProj[1], pointToProj[2], 1 };
            return projMat * ret;
    }
    inline const jVec4f transform(const jVec4f &pointToProj, const jMat4f &projMat) 
    {
            return projMat * pointToProj;
    }

    inline const jMat4f look_at_mat(jVec3f eye_pos, jVec3f look_at, jVec3f up_vec) {
        jVec3f zAxis = (look_at - eye_pos).normalize();
        jVec3f xAxis = cross(up_vec, zAxis).normalize();
        jVec3f yAxis = cross(zAxis, xAxis);

        jMat4f ret = {
            xAxis[0] ,      xAxis[1] ,      xAxis[2],       -(xAxis * eye_pos),
            yAxis[0] ,      yAxis[1] ,      yAxis[2],       -(yAxis * eye_pos),
            zAxis[0] ,      zAxis[1] ,      zAxis[2],       -(zAxis * eye_pos),
            0,              0,              0,              1 
        };
        return ret;
    }

    inline const jMat4f perspective_fov_mat(jfloat fovy, jfloat aspect, jfloat zNear, jfloat zFar) {
        const jfloat h = jfloat(1) / static_cast<jfloat>(std::tan(fovy * PI / 360.0f));
        const jfloat w = h / aspect;
        const jfloat q = zFar / (zFar - zNear);
        const jfloat p = - zFar * zNear / (zFar - zNear);
        jMat4f ret = {
            w ,         0 ,         0,          0,
            0 ,         h ,         0,          0,
            0 ,         0 ,         q,          p,
            0 ,         0 ,         1,          0
        };
        return std::move(ret);
    }

}}

#include "jTestBase.h"
namespace jLib {
    class jMatCvtTest final : public jITestable {
    public:
        virtual void test() override {
            jITestable::test();

            jMat4f fm = {
                1, 1, 1, 1,
                1, 2, 3, 4,
                1, 5, 1, 2,
                1, 3, 9, 5
            };

            jVec4f fv = { 1, 2, 3, 4 };
            std::cout << jGraphic::transform(fv, fm) << std::endl;

            jVec3f eye = { 0, 0, -5.0f };
            jVec3f look_at = { 0, 0, 0 };
            jVec3f up_vec = { 0, 1, 0 };
            jVec3f observe_pos = { 1, 0, 0 };

            auto look_mat = jGraphic::look_at_mat(eye, look_at, up_vec);
            std::cout << look_mat << std::endl;
            auto trans_pos = jGraphic::transform(observe_pos, look_mat);
            std::cout << trans_pos ;
            getchar();
        }
    };
}