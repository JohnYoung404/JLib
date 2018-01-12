#include "jPerlinNoise.h"

namespace jLib
{

namespace jAlgorithm
{

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
float basis[12][4] ={
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
unsigned char indices[64] ={
	0,1,2,3,4,5,6,7,8,9,10,11,
	0,9,1,11,
	0,1,2,3,4,5,6,7,8,9,10,11,
	0,1,2,3,4,5,6,7,8,9,10,11,
	0,1,2,3,4,5,6,7,8,9,10,11,
	0,1,2,3,4,5,6,7,8,9,10,11,
};
inline float perlin_lerp(float a, float b, float t)
{
	return a + (b - a) * t;
}
inline int perlin_fastfloor(float a)
{
	int ai = (int)a;
	return (a < ai) ? ai - 1 : ai;
}
float perlin_grad(int hash, float x, float y, float z)
{
	float *grad = basis[indices[hash & 63]];
	return grad[0] * x + grad[1] * y + grad[2] * z;
}
inline float perlin_ease(float a) {
	return ((a * 6 - 15)*a + 10) * a * a * a;
}
}

//reference: https://github.com/nothings/stb/blob/master/stb_perlin.h
namespace jPerlinNoise
{

float perlin_noise3(float x, float y, float z, int x_wrap, int y_wrap, int z_wrap)
	{
		float u, v, w;
		float n000, n001, n010, n011, n100, n101, n110, n111;
		float n00, n01, n10, n11;
		float n0, n1;

		unsigned int x_mask = (x_wrap - 1) & 255;
		unsigned int y_mask = (y_wrap - 1) & 255;
		unsigned int z_mask = (z_wrap - 1) & 255;
		int px = perlin_fastfloor(x);
		int py = perlin_fastfloor(y);
		int pz = perlin_fastfloor(z);
		int x0 = px & x_mask, x1 = (px + 1) & x_mask;
		int y0 = py & y_mask, y1 = (py + 1) & y_mask;
		int z0 = pz & z_mask, z1 = (pz + 1) & z_mask;
		int r0, r1, r00, r01, r10, r11;

		x -= px; u = perlin_ease(x);
		y -= py; v = perlin_ease(y);
		z -= pz; w = perlin_ease(z);

		r0 = randTab[x0];
		r1 = randTab[x1];

		r00 = randTab[r0 + y0];
		r01 = randTab[r0 + y1];
		r10 = randTab[r1 + y0];
		r11 = randTab[r1 + y1];

		n000 = perlin_grad(randTab[r00 + z0], x, y, z);
		n001 = perlin_grad(randTab[r00 + z1], x, y, z - 1);
		n010 = perlin_grad(randTab[r01 + z0], x, y - 1, z);
		n011 = perlin_grad(randTab[r01 + z1], x, y - 1, z - 1);
		n100 = perlin_grad(randTab[r10 + z0], x - 1, y, z);
		n101 = perlin_grad(randTab[r10 + z1], x - 1, y, z - 1);
		n110 = perlin_grad(randTab[r11 + z0], x - 1, y - 1, z);
		n111 = perlin_grad(randTab[r11 + z1], x - 1, y - 1, z - 1);

		n00 = perlin_lerp(n000, n001, w);
		n01 = perlin_lerp(n010, n011, w);
		n10 = perlin_lerp(n100, n101, w);
		n11 = perlin_lerp(n110, n111, w);

		n0 = perlin_lerp(n00, n01, v);
		n1 = perlin_lerp(n10, n11, v);

		return perlin_lerp(n0, n1, u);
	}

float perlin_ridge_noise3(float x, float y, float z, float lacunarity, float gain, float offset, int octaves, int x_wrap, int y_wrap, int z_wrap)
{
	int i;
	float frequency = 1.0f;
	float prev = 1.0f;
	float amplitude = 0.5f;
	float sum = 0.0f;

	for (i = 0; i < octaves; i++) {
		float r = (float)(perlin_noise3(x*frequency, y*frequency, z*frequency, x_wrap, y_wrap, z_wrap));
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

float perlin_fbm_noise3(float x, float y, float z, float lacunarity, float gain, int octaves, int x_wrap, int y_wrap, int z_wrap)
{
	int i;
	float frequency = 1.0f;
	float amplitude = 1.0f;
	float sum = 0.0f;

	for (i = 0; i < octaves; i++) {
		sum += perlin_noise3(x*frequency, y*frequency, z*frequency, x_wrap, y_wrap, z_wrap)*amplitude;
		frequency *= lacunarity;
		amplitude *= gain;
	}
	return sum;
}

float perlin_turbulence_noise3(float x, float y, float z, float lacunarity, float gain, int octaves, int x_wrap, int y_wrap, int z_wrap)
{
	int i;
	float frequency = 1.0f;
	float amplitude = 1.0f;
	float sum = 0.0f;

	for (i = 0; i < octaves; i++) {
		float r = perlin_noise3(x*frequency, y*frequency, z*frequency, x_wrap, y_wrap, z_wrap)*amplitude;
		r = r < 0 ? -r : r; // fabs()
		sum += r;
		frequency *= lacunarity;
		amplitude *= gain;
	}
	return sum;
}

}

}

}