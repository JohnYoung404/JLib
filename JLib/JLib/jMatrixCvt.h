#pragma once
#include <boost/static_assert.hpp>
#include <cmath>
#include "jMath.h"
#include "jMatrix.h"
#include "jVector.h"

namespace jLib{
namespace jGraphic{

    inline const jContainer::jVecBase<float, 4> transform(const jContainer::jVecBase<float, 2> &pointToProj, const jContainer::jMatBase<float, 4> &projMat) 
    {
            jContainer::jVecBase<float, 4> ret = { pointToProj[0], pointToProj[1], 1, 1 };
            return projMat * ret;
    }
    inline const jContainer::jVecBase<float, 4> transform(const jContainer::jVecBase<float, 3> &pointToProj, const jContainer::jMatBase<float, 4> &projMat)
    {
            jContainer::jVecBase<float, 4> ret = { pointToProj[0], pointToProj[1], pointToProj[2], 1 };
            return projMat * ret;
    }
    inline const jContainer::jVecBase<float, 4> transform(const jContainer::jVecBase<float, 4> &pointToProj, const jContainer::jMatBase<float, 4> &projMat) 
    {
            return projMat * pointToProj;
    }

    inline const jContainer::jMatBase<float, 4> look_at_mat(jContainer::jPoint3D eye_pos, jContainer::jPoint3D look_at, jContainer::jPoint3D up_vec) {
        jContainer::jVec3<float> zAxis = (look_at - eye_pos).normalize();
        jContainer::jVec3<float> xAxis = cross(up_vec, zAxis).normalize();
        jContainer::jVec3<float> yAxis = cross(zAxis, xAxis);

        jContainer::jMatBase<float, 4> ret = {
            xAxis[0] ,      xAxis[1] ,      xAxis[2],       -(xAxis * eye_pos),
            yAxis[0] ,      yAxis[1] ,      yAxis[2],       -(yAxis * eye_pos),
            zAxis[0] ,      zAxis[1] ,      zAxis[2],       -(zAxis * eye_pos),
            0,              0,              0,              1
        };
        return ret;
    }

    inline const jContainer::jMatBase<float, 4> perspective_fov_mat(float fovy, float aspect, float zNear, float zFar) {
        const float h = 1.0f / static_cast<float>(std::tan(fovy * PI / 360.0f));
        const float w = h / aspect;
        const float q = zFar / (zFar - zNear);
        const float p = - zFar * zNear / (zFar - zNear);
        jContainer::jMatBase<float, 4> ret = {
            w ,			0 ,			0,			0,
            0 ,			h ,			0,			0,
            0 ,			0 ,			q,          p,
            0 ,			0 ,		    1,		    0
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
            using namespace jContainer;

            jMatBase<float, 4> fm = {
                1, 1, 1, 1,
                1, 2, 3, 4,
                1, 5, 1, 2,
                1, 3, 9, 5
            };

            jVecBase<float, 4> fv = { 1, 2, 3, 4 };
            std::cout << jGraphic::transform(fv, fm) << std::endl;

            jPoint3D eye = { 0, 0, -5.0f };
            jPoint3D look_at = { 0, 0, 0 };
            jPoint3D up_vec = { 0, 1, 0 };

            jPoint3D observe_pos = { 1, 0, 0 };

            auto look_mat = jGraphic::look_at_mat(eye, look_at, up_vec);
            std::cout << look_mat << std::endl;
            auto trans_pos = jGraphic::transform(observe_pos, look_mat);
            std::cout << trans_pos ;
            getchar();
        }
    };
}