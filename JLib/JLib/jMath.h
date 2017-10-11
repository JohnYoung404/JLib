#pragma once
#include <cmath>
#include <cfloat>

#define PI 3.14159265359

inline bool AlmostEqual(float lhs, float rhs) {
	if (lhs == 0)
	{
		return abs(rhs) < FLT_EPSILON;
	}
	else {
		return abs(lhs - rhs) / abs(lhs) < FLT_EPSILON;
	}
}


//reference: https://github.com/nothings/stb/blob/master/stb_perlin.h
namespace {
	const unsigned char randTab[] = {
		23, 125, 161, 52, 103, 117, 70, 37, 247, 101, 203, 169, 124, 126, 44, 123,
		152, 238, 145, 45, 171, 114, 253, 10, 192, 136, 4, 157, 249, 30, 35, 72,
		175, 63, 77, 90, 181, 16, 96, 111, 133, 104, 75, 162, 93, 56, 66, 240,
		8, 50, 84, 229, 49, 210, 173, 239, 141, 1, 87, 18, 2, 198, 143, 57,
		225, 160, 58, 217, 168, 206, 245, 204, 199, 6, 73, 60, 20, 230, 211, 233,
		94, 200, 88, 9, 74, 155, 33, 15, 219, 130, 226, 202, 83, 236, 42, 172,
		165, 218, 55, 222, 46, 107, 98, 154, 109, 67, 196, 178, 127, 158, 13, 243,
		65, 79, 166, 248, 25, 224, 115, 80, 68, 51, 184, 128, 232, 208, 151, 122,
		26, 212, 105, 43, 179, 213, 235, 148, 146, 89, 14, 195, 28, 78, 112, 76,
		250, 47, 24, 251, 140, 108, 186, 190, 228, 170, 183, 139, 39, 188, 244, 246,
		132, 48, 119, 144, 180, 138, 134, 193, 82, 182, 120, 121, 86, 220, 209, 3,
		91, 241, 149, 85, 205, 150, 113, 216, 31, 100, 41, 164, 177, 214, 153, 231,
		38, 71, 185, 174, 97, 201, 29, 95, 7, 92, 54, 254, 191, 118, 34, 221,
		131, 11, 163, 99, 234, 81, 227, 147, 156, 176, 17, 142, 69, 12, 110, 62,
		27, 255, 0, 194, 59, 116, 242, 252, 19, 21, 187, 53, 207, 129, 64, 135,
		61, 40, 167, 237, 102, 223, 106, 159, 197, 189, 215, 137, 36, 32, 22, 5,

		23, 125, 161, 52, 103, 117, 70, 37, 247, 101, 203, 169, 124, 126, 44, 123,
		152, 238, 145, 45, 171, 114, 253, 10, 192, 136, 4, 157, 249, 30, 35, 72,
		175, 63, 77, 90, 181, 16, 96, 111, 133, 104, 75, 162, 93, 56, 66, 240,
		8, 50, 84, 229, 49, 210, 173, 239, 141, 1, 87, 18, 2, 198, 143, 57,
		225, 160, 58, 217, 168, 206, 245, 204, 199, 6, 73, 60, 20, 230, 211, 233,
		94, 200, 88, 9, 74, 155, 33, 15, 219, 130, 226, 202, 83, 236, 42, 172,
		165, 218, 55, 222, 46, 107, 98, 154, 109, 67, 196, 178, 127, 158, 13, 243,
		65, 79, 166, 248, 25, 224, 115, 80, 68, 51, 184, 128, 232, 208, 151, 122,
		26, 212, 105, 43, 179, 213, 235, 148, 146, 89, 14, 195, 28, 78, 112, 76,
		250, 47, 24, 251, 140, 108, 186, 190, 228, 170, 183, 139, 39, 188, 244, 246,
		132, 48, 119, 144, 180, 138, 134, 193, 82, 182, 120, 121, 86, 220, 209, 3,
		91, 241, 149, 85, 205, 150, 113, 216, 31, 100, 41, 164, 177, 214, 153, 231,
		38, 71, 185, 174, 97, 201, 29, 95, 7, 92, 54, 254, 191, 118, 34, 221,
		131, 11, 163, 99, 234, 81, 227, 147, 156, 176, 17, 142, 69, 12, 110, 62,
		27, 255, 0, 194, 59, 116, 242, 252, 19, 21, 187, 53, 207, 129, 64, 135,
		61, 40, 167, 237, 102, 223, 106, 159, 197, 189, 215, 137, 36, 32, 22, 5,
	};
}
class jPerlinNoise
{
public:
	static float stb_perlin_noise3(float x, float y, float z, int x_wrap, int y_wrap, int z_wrap)
	{
		float u, v, w;
		float n000, n001, n010, n011, n100, n101, n110, n111;
		float n00, n01, n10, n11;
		float n0, n1;

		unsigned int x_mask = (x_wrap - 1) & 255;
		unsigned int y_mask = (y_wrap - 1) & 255;
		unsigned int z_mask = (z_wrap - 1) & 255;
		int px = stb__perlin_fastfloor(x);
		int py = stb__perlin_fastfloor(y);
		int pz = stb__perlin_fastfloor(z);
		int x0 = px & x_mask, x1 = (px + 1) & x_mask;
		int y0 = py & y_mask, y1 = (py + 1) & y_mask;
		int z0 = pz & z_mask, z1 = (pz + 1) & z_mask;
		int r0, r1, r00, r01, r10, r11;

		x -= px; u = stb__perlin_ease(x);
		y -= py; v = stb__perlin_ease(y);
		z -= pz; w = stb__perlin_ease(z);

		r0 = randTab[x0];
		r1 = randTab[x1];

		r00 = randTab[r0 + y0];
		r01 = randTab[r0 + y1];
		r10 = randTab[r1 + y0];
		r11 = randTab[r1 + y1];

		n000 = stb__perlin_grad(randTab[r00 + z0], x, y, z);
		n001 = stb__perlin_grad(randTab[r00 + z1], x, y, z - 1);
		n010 = stb__perlin_grad(randTab[r01 + z0], x, y - 1, z);
		n011 = stb__perlin_grad(randTab[r01 + z1], x, y - 1, z - 1);
		n100 = stb__perlin_grad(randTab[r10 + z0], x - 1, y, z);
		n101 = stb__perlin_grad(randTab[r10 + z1], x - 1, y, z - 1);
		n110 = stb__perlin_grad(randTab[r11 + z0], x - 1, y - 1, z);
		n111 = stb__perlin_grad(randTab[r11 + z1], x - 1, y - 1, z - 1);

		n00 = stb__perlin_lerp(n000, n001, w);
		n01 = stb__perlin_lerp(n010, n011, w);
		n10 = stb__perlin_lerp(n100, n101, w);
		n11 = stb__perlin_lerp(n110, n111, w);

		n0 = stb__perlin_lerp(n00, n01, v);
		n1 = stb__perlin_lerp(n10, n11, v);

		return stb__perlin_lerp(n0, n1, u);
	}
	static float stb_perlin_ridge_noise3(float x, float y, float z, float lacunarity, float gain, float offset, int octaves, int x_wrap, int y_wrap, int z_wrap)
	{
		int i;
		float frequency = 1.0f;
		float prev = 1.0f;
		float amplitude = 0.5f;
		float sum = 0.0f;

		for (i = 0; i < octaves; i++) {
			float r = (float)(stb_perlin_noise3(x*frequency, y*frequency, z*frequency, x_wrap, y_wrap, z_wrap));
			r = r < 0 ? -r : r; // fabs()
			r = offset - r;
			r = r*r;
			sum += r*amplitude*prev;
			prev = r;
			frequency *= lacunarity;
			amplitude *= gain;
		}
		return sum;
	}
	static float stb_perlin_fbm_noise3(float x, float y, float z, float lacunarity, float gain, int octaves, int x_wrap, int y_wrap, int z_wrap)
	{
		int i;
		float frequency = 1.0f;
		float amplitude = 1.0f;
		float sum = 0.0f;

		for (i = 0; i < octaves; i++) {
			sum += stb_perlin_noise3(x*frequency, y*frequency, z*frequency, x_wrap, y_wrap, z_wrap)*amplitude;
			frequency *= lacunarity;
			amplitude *= gain;
		}
		return sum;
	}
	static float stb_perlin_turbulence_noise3(float x, float y, float z, float lacunarity, float gain, int octaves, int x_wrap, int y_wrap, int z_wrap)
	{
		int i;
		float frequency = 1.0f;
		float amplitude = 1.0f;
		float sum = 0.0f;

		for (i = 0; i < octaves; i++) {
			float r = stb_perlin_noise3(x*frequency, y*frequency, z*frequency, x_wrap, y_wrap, z_wrap)*amplitude;
			r = r < 0 ? -r : r; // fabs()
			sum += r;
			frequency *= lacunarity;
			amplitude *= gain;
		}
		return sum;
	}
private:
	static float stb__perlin_lerp(float a, float b, float t)
	{
		return a + (b - a) * t;
	}
	static int stb__perlin_fastfloor(float a)
	{
		int ai = (int)a;
		return (a < ai) ? ai - 1 : ai;
	}
	static float stb__perlin_grad(int hash, float x, float y, float z)
	{
		static float basis[12][4] =
		{
			{ 1, 1, 0 },
			{ -1, 1, 0 },
			{ 1,-1, 0 },
			{ -1,-1, 0 },
			{ 1, 0, 1 },
			{ -1, 0, 1 },
			{ 1, 0,-1 },
			{ -1, 0,-1 },
			{ 0, 1, 1 },
			{ 0,-1, 1 },
			{ 0, 1,-1 },
			{ 0,-1,-1 },
		};

		// perlin's gradient has 12 cases so some get used 1/16th of the time
		// and some 2/16ths. We reduce bias by changing those fractions
		// to 5/64ths and 6/64ths, and the same 4 cases get the extra weight.
		static unsigned char indices[64] =
		{
			0,1,2,3,4,5,6,7,8,9,10,11,
			0,9,1,11,
			0,1,2,3,4,5,6,7,8,9,10,11,
			0,1,2,3,4,5,6,7,8,9,10,11,
			0,1,2,3,4,5,6,7,8,9,10,11,
			0,1,2,3,4,5,6,7,8,9,10,11,
		};

		// if you use reference permutation table, change 63 below to 15 to match reference
		// (this is why the ordering of the table above is funky)
		float *grad = basis[indices[hash & 63]];
		return grad[0] * x + grad[1] * y + grad[2] * z;
	}
	static inline float stb__perlin_ease(float a) {
		return ((a * 6 - 15)*a + 10) * a * a * a;
	}
};