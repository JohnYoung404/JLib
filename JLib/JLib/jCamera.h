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
			setCameraProj(static_cast<float>(PI / 4), 1, 1, 1000);
		}
		void setCameraView(jPoint3D eye_pos, jPoint3D look_at, jPoint3D up_vec = jPoint3D{ 0.0f, 1.0f, 0.0f }){
			look_at_dist_ = (look_at - eye_pos).Length();

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

		const jVec_3<float> UpVec() {
			jPoint3D ret = {
                inv_view_mat_.RefOfPos(0, 1),
                inv_view_mat_.RefOfPos(1, 1),
                inv_view_mat_.RefOfPos(2, 1)
			};
			return std::move(ret);
		}
		const jVec_3<float> RightVec() {
			jPoint3D ret = {
                inv_view_mat_.RefOfPos(0, 0),
                inv_view_mat_.RefOfPos(1, 0),
                inv_view_mat_.RefOfPos(2, 0)
			};
			return std::move(ret);
		}
		const jVec_3<float> FowardVec() {
			jPoint3D ret = {
                inv_view_mat_.RefOfPos(0, 2),
                inv_view_mat_.RefOfPos(1, 2),
                inv_view_mat_.RefOfPos(2, 2)
			};
			return std::move(ret);
		}

		const jPoint3D EyePos() {
			jPoint3D ret = {
                inv_view_mat_.RefOfPos(0, 3),
                inv_view_mat_.RefOfPos(1, 3),
                inv_view_mat_.RefOfPos(2, 3)
			};
			return std::move(ret);
		}
		const jPoint3D LookAtPos() {
			return EyePos() + FowardVec() * look_at_dist_;
		}

        const jMat_4<float>& ProjMat() {
            return proj_mat_;
        }
        const jMat_4<float>& InvProjMat() {
            return inv_proj_mat_;
        }
        const jMat_4<float>& ViewMat() {
            return view_mat_;
        }
        const jMat_4<float>& InvViewMat() {
            return inv_view_mat_;
        }
	private:
		float fovy_;
		float aspect_;
		float zNear_;
		float zFar_;

		float look_at_dist_;

		jMat_4<float> proj_mat_;
		jMat_4<float> inv_proj_mat_;

		jMat_4<float> view_mat_;
		jMat_4<float> inv_view_mat_;
	};

}}
