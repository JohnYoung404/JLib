#pragma once
namespace jLib{
namespace jAlgorithm {
namespace jPerlinNoise{
	extern float perlin_noise3(float x, float y, float z, int x_wrap, int y_wrap, int z_wrap);
	extern float perlin_ridge_noise3(float x, float y, float z, float lacunarity, float gain, float offset, int octaves, int x_wrap, int y_wrap, int z_wrap);
	extern float perlin_fbm_noise3(float x, float y, float z, float lacunarity, float gain, int octaves, int x_wrap, int y_wrap, int z_wrap);
	extern float perlin_turbulence_noise3(float x, float y, float z, float lacunarity, float gain, int octaves, int x_wrap, int y_wrap, int z_wrap);
}
}
}

#include "jTestBase.h"
#include "jBitMap.h"
namespace jLib {
	class jPerlinNoiseTest final : public jITestable {
	public:
		virtual void test() override {
			jITestable::test();
			jMedia::jBitMap m;
			m.CreateEmpty(1920, 1080);
			for (int i = 0; i < 1920; ++i)
			{
				for (int j = 0; j < 1080; ++j) {
					float hori_off = (float)i / 1920;
					float vert_off = (float)j / 1080;
					float val = jAlgorithm::jPerlinNoise::perlin_ridge_noise3(hori_off, vert_off, 0.619f, 2.0f, 0.92f, 0.874f, 6, 0, 0, 0);
					m.at(i, j, jMedia::jBitMap::B) = 255;
					m.at(i, j, jMedia::jBitMap::G) = static_cast<uint8_t>(255 * val < 255 ? 255 * val : 255);
					m.at(i, j, jMedia::jBitMap::R) = static_cast<uint8_t>(255 * val < 255 ? 255 * val : 255);
					m.at(i, j, jMedia::jBitMap::A) = 255;
				}
			}
			m.SaveImage("jPerlinNoiseTest/perlin_noise_img.bmp");
            std::cout << "Created a perlinNoise image." << std::endl;
		}
	};
}