#pragma once

#include "jColor.h"
#include "jVector.h"

namespace jGraphic {

	class jLight {
	public:
		virtual ~jLight() {};
		virtual bool SetColor(jColor color) {
			color_ = color;
			return true;
		};
		virtual bool SetIndensity(float indensity) {
			indensity_ = indensity;
			return true;
		}
	protected:
		jLight() {};
	private:
		float indensity_;
		jColor color_;
	};

	class jDirecLight : public jLight {
	public:
		jDirecLight() {};
	private:
		jVec_3<float> direction_;
	};

	class jAmbientLight : public jLight {
	public:
		jAmbientLight() {};
	private:

	};

	class jPointLight : public jLight {
	public:
		jPointLight() {};
	private:
		jVec_3<float> position_;
	};

}
