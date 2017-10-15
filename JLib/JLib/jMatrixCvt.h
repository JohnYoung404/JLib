#pragma once
#include "jMath.h"
#include "jMatrix.h"
#include "jVector.h"
#include "boost/static_assert.hpp"

namespace jGraphic {
	using jMatProj = jMat_4<float>;
	
	template<size_t Degree>
	const jVector_base<4, float> transform(const jVector_base<Degree, float> &pointToProj, const jMatProj &projMat) {
		BOOST_STATIC_ASSERT((Degree >= 2) && (Degree <= 4), "Point degree should be 2, 3 or 4.");
		if (Degree == 2) {
			jVector_base<4, float> ret = { pointToProj[0], pointToProj[1], 1, 1 };
			return std::move(projMat * ret);
		}
		else if(Degree == 3)
		{
			jVector_base<4, float> ret = { pointToProj[0], pointToProj[1], pointToProj[2], 1 };
			return std::move(projMat * ret);
		}
		else if (Degree == 4){
			return std::move(projMat * pointToProj);
		}
	}

	const jMatProj look_at_mat(jPoint3D eye_pos, jPoint3D look_at, jPoint3D up_vec) {
		jVec_3<float> zAxis = (look_at - eye_pos).Normalize();
		jVec_3<float> xAxis = (doCross(up_vec, zAxis).Normalize());
		jVec_3<float> yAxis = doCross(zAxis, xAxis);

		jMatProj ret = {
			xAxis[0] ,			xAxis[1] ,			xAxis[2],			-(xAxis * eye_pos),
			yAxis[0] ,			yAxis[1] ,			yAxis[2],			-(yAxis * eye_pos),
			zAxis[0] ,			zAxis[1] ,			zAxis[2],			-(zAxis * eye_pos),
			        0,                  0,                 0,                           1
		};
		return std::move(ret);
	}

	const jMatProj perspective_fov_mat(float fovy, float aspect, float zNear, float zFar) {
		const float h = 1.0f / tan(fovy / 2);
		const float w = h / aspect;
		const float q = - (zFar + zNear ) / (zFar - zNear);
        const float p = -2 * zFar * zNear / (zFar - zNear);
		jMatProj ret = {
            w ,			0 ,			0,			0,
            0 ,			h ,			0,			0,
            0 ,			0 ,			q,          p,
            0 ,			0 ,		    -1,		    0
		};
		return std::move(ret);
	}

}