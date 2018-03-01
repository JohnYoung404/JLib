#pragma once
#include "jVector.h"
#include "jMatrix.h"
#include "jMatrixCvt.h"
#include "jMath.h"

NAME_SPACE_BEGIN(jLib)
NAME_SPACE_BEGIN(jGraphic)

class jCamera {
public:
    jCamera() {
        setCameraView(jVec3f{ 0, 0, 1 }, jVec3f{ 0, 0, 0 }, jVec3f{0, 1, 0});
        setCameraProj(45, 1, 1, 1000);
    }
    void setCameraView(jVec3f eye_pos, jVec3f look_at, jVec3f up_vec = jVec3f{ 0.0f, 1.0f, 0.0f }){
        look_at_dist_ = std::sqrt((look_at - eye_pos).square_length());
        
        view_mat_ = look_at_mat(eye_pos, look_at, up_vec);
        inv_view_mat_ = inverse(view_mat_);
    }
    void setCameraProj(jfloat fovy, jfloat aspect, jfloat zNear, jfloat zFar) {
        fovy_ = fovy;
        aspect_ = aspect;
        zNear_ = zNear;
        zFar_ = zFar;
        
        proj_mat_ = perspective_fov_mat(fovy, aspect, zNear, zFar);
        inv_proj_mat_ = inverse(proj_mat_);
    }
    
    jfloat DistToLookAt() {
        return look_at_dist_;
    }
    
    const jVec3f UpVec() {
        jVec3f ret = {
            inv_view_mat_.at(1, 0),
            inv_view_mat_.at(1, 1),
            inv_view_mat_.at(1, 2)
        };
        return ret;
    }
    const jVec3f RightVec() {
        jVec3f ret = {
            inv_view_mat_.at(0, 0),
            inv_view_mat_.at(0, 1),
            inv_view_mat_.at(0, 2)
        };
        return ret;
    }
    const jVec3f FowardVec() {
        jVec3f ret = {
            inv_view_mat_.at(2, 0),
            inv_view_mat_.at(2, 1),
            inv_view_mat_.at(2, 2)
        };
        return ret;
    }
    
    const jVec3f EyePos() {
        jVec3f ret = {
            inv_view_mat_.at(3, 0),
            inv_view_mat_.at(3, 1),
            inv_view_mat_.at(3, 2)
        };
        return ret;
    }
    const jVec3f LookAtPos() {
        return EyePos() + FowardVec() * look_at_dist_;
    }
    
    const jMat4f& ProjMat() {
        return proj_mat_;
    }
    const jMat4f& InvProjMat() {
        return inv_proj_mat_;
    }
    const jMat4f& ViewMat() {
        return view_mat_;
    }
    const jMat4f& InvViewMat() {
        return inv_view_mat_;
    }
private:
    jfloat fovy_;
    jfloat aspect_;
    jfloat zNear_;
    jfloat zFar_;

    jfloat look_at_dist_;

    jMat4f proj_mat_;
    jMat4f inv_proj_mat_;

    jMat4f view_mat_;
    jMat4f inv_view_mat_;
};

NAME_SPACE_END
NAME_SPACE_END


////////////// Unit Test //////////////
#include "jTestBase.h"
JTEST_BEGIN(jCameraTest)
{
    using namespace jGraphic;
    jCamera c;
    std::cout << c.LookAtPos();
    std::cout << c.EyePos();
    std::cout << c.UpVec();
    std::cout << c.RightVec();
    std::cout << c.FowardVec();
}
JTEST_END