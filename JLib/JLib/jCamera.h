#pragma once
#include "jVector.h"
#include "jMatrix.h"
#include "jMatrixCvt.h"
#include "jMath.h"

namespace jLib{
namespace jGraphic {

	class jCamera {
	public:
        jCamera() {
        	setCameraView(jContainer::jPoint3D{ 0, 0, 1 }, jContainer::jPoint3D{ 0, 0, 0 }, jContainer::jPoint3D{0, 1, 0});
        	setCameraProj(45, 1, 1, 1000);
        }
        void setCameraView(jContainer::jPoint3D eye_pos, jContainer::jPoint3D look_at, jContainer::jPoint3D up_vec = jContainer::jPoint3D{ 0.0f, 1.0f, 0.0f }){
        	look_at_dist_ = std::sqrt((look_at - eye_pos).square_length());
        
        	view_mat_ = look_at_mat(eye_pos, look_at, up_vec);
        	inv_view_mat_ = inverse(view_mat_);
        }
        void setCameraProj(float fovy, float aspect, float zNear, float zFar) {
        	fovy_ = fovy;
        	aspect_ = aspect;
        	zNear_ = zNear;
        	zFar_ = zFar;
        
        	proj_mat_ = perspective_fov_mat(fovy, aspect, zNear, zFar);
        	inv_proj_mat_ = inverse(proj_mat_);
        }
        
        float DistToLookAt() {
        	return look_at_dist_;
        }
        
        const jContainer::jPoint3D UpVec() {
            jContainer::jPoint3D ret = {
                inv_view_mat_.at(1, 0),
                inv_view_mat_.at(1, 1),
                inv_view_mat_.at(1, 2)
            };
            return ret;
        }
        const jContainer::jPoint3D RightVec() {
            jContainer::jPoint3D ret = {
                inv_view_mat_.at(0, 0),
                inv_view_mat_.at(0, 1),
                inv_view_mat_.at(0, 2)
            };
            return ret;
        }
        const jContainer::jPoint3D FowardVec() {
            jContainer::jPoint3D ret = {
                inv_view_mat_.at(2, 0),
                inv_view_mat_.at(2, 1),
                inv_view_mat_.at(2, 2)
        	};
        	return ret;
        }
        
        const jContainer::jPoint3D EyePos() {
            jContainer::jPoint3D ret = {
                inv_view_mat_.at(3, 0),
                inv_view_mat_.at(3, 1),
                inv_view_mat_.at(3, 2)
            };
            return ret;
        }
        const jContainer::jPoint3D LookAtPos() {
            return EyePos() + FowardVec() * look_at_dist_;
        }
        
        const jContainer::jMat4<float>& ProjMat() {
            return proj_mat_;
        }
        const jContainer::jMat4<float>& InvProjMat() {
            return inv_proj_mat_;
        }
        const jContainer::jMat4<float>& ViewMat() {
            return view_mat_;
        }
        const jContainer::jMat4<float>& InvViewMat() {
            return inv_view_mat_;
        }
	private:
        float fovy_;
        float aspect_;
        float zNear_;
        float zFar_;

        float look_at_dist_;

        jContainer::jMat4<float> proj_mat_;
        jContainer::jMat4<float> inv_proj_mat_;

        jContainer::jMat4<float> view_mat_;
        jContainer::jMat4<float> inv_view_mat_;
    };
}}

#include "jTestBase.h"
namespace jLib {
    class jCameraTest final : public jITestable {
    public:
        virtual void test() override {
            jITestable::test();
            using namespace jGraphic;
            jCamera c;
            std::cout << c.LookAtPos();
            std::cout << c.EyePos();
            std::cout << c.UpVec();
            std::cout << c.RightVec();
            std::cout << c.FowardVec();
        }
    };
}