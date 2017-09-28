#pragma once

template <typename T>
Matrix4_T<T> inverse(Matrix4_T<T> const & rhs) noexcept
{
	T const _2132_2231(rhs(1, 0) * rhs(2, 1) - rhs(1, 1) * rhs(2, 0));
	T const _2133_2331(rhs(1, 0) * rhs(2, 2) - rhs(1, 2) * rhs(2, 0));
	T const _2134_2431(rhs(1, 0) * rhs(2, 3) - rhs(1, 3) * rhs(2, 0));
	T const _2142_2241(rhs(1, 0) * rhs(3, 1) - rhs(1, 1) * rhs(3, 0));
	T const _2143_2341(rhs(1, 0) * rhs(3, 2) - rhs(1, 2) * rhs(3, 0));
	T const _2144_2441(rhs(1, 0) * rhs(3, 3) - rhs(1, 3) * rhs(3, 0));
	T const _2233_2332(rhs(1, 1) * rhs(2, 2) - rhs(1, 2) * rhs(2, 1));
	T const _2234_2432(rhs(1, 1) * rhs(2, 3) - rhs(1, 3) * rhs(2, 1));
	T const _2243_2342(rhs(1, 1) * rhs(3, 2) - rhs(1, 2) * rhs(3, 1));
	T const _2244_2442(rhs(1, 1) * rhs(3, 3) - rhs(1, 3) * rhs(3, 1));
	T const _2334_2433(rhs(1, 2) * rhs(2, 3) - rhs(1, 3) * rhs(2, 2));
	T const _2344_2443(rhs(1, 2) * rhs(3, 3) - rhs(1, 3) * rhs(3, 2));
	T const _3142_3241(rhs(2, 0) * rhs(3, 1) - rhs(2, 1) * rhs(3, 0));
	T const _3143_3341(rhs(2, 0) * rhs(3, 2) - rhs(2, 2) * rhs(3, 0));
	T const _3144_3441(rhs(2, 0) * rhs(3, 3) - rhs(2, 3) * rhs(3, 0));
	T const _3243_3342(rhs(2, 1) * rhs(3, 2) - rhs(2, 2) * rhs(3, 1));
	T const _3244_3442(rhs(2, 1) * rhs(3, 3) - rhs(2, 3) * rhs(3, 1));
	T const _3344_3443(rhs(2, 2) * rhs(3, 3) - rhs(2, 3) * rhs(3, 2));

	// 行列式的值
	T const det(determinant(rhs));
	if (equal<T>(det, 0))
	{
		return rhs;
	}
	else
	{
		T invDet(T(1) / det);

		return Matrix4_T<T>(
			+invDet * (rhs(1, 1) * _3344_3443 - rhs(1, 2) * _3244_3442 + rhs(1, 3) * _3243_3342),
			-invDet * (rhs(0, 1) * _3344_3443 - rhs(0, 2) * _3244_3442 + rhs(0, 3) * _3243_3342),
			+invDet * (rhs(0, 1) * _2344_2443 - rhs(0, 2) * _2244_2442 + rhs(0, 3) * _2243_2342),
			-invDet * (rhs(0, 1) * _2334_2433 - rhs(0, 2) * _2234_2432 + rhs(0, 3) * _2233_2332),

			-invDet * (rhs(1, 0) * _3344_3443 - rhs(1, 2) * _3144_3441 + rhs(1, 3) * _3143_3341),
			+invDet * (rhs(0, 0) * _3344_3443 - rhs(0, 2) * _3144_3441 + rhs(0, 3) * _3143_3341),
			-invDet * (rhs(0, 0) * _2344_2443 - rhs(0, 2) * _2144_2441 + rhs(0, 3) * _2143_2341),
			+invDet * (rhs(0, 0) * _2334_2433 - rhs(0, 2) * _2134_2431 + rhs(0, 3) * _2133_2331),

			+invDet * (rhs(1, 0) * _3244_3442 - rhs(1, 1) * _3144_3441 + rhs(1, 3) * _3142_3241),
			-invDet * (rhs(0, 0) * _3244_3442 - rhs(0, 1) * _3144_3441 + rhs(0, 3) * _3142_3241),
			+invDet * (rhs(0, 0) * _2244_2442 - rhs(0, 1) * _2144_2441 + rhs(0, 3) * _2142_2241),
			-invDet * (rhs(0, 0) * _2234_2432 - rhs(0, 1) * _2134_2431 + rhs(0, 3) * _2132_2231),

			-invDet * (rhs(1, 0) * _3243_3342 - rhs(1, 1) * _3143_3341 + rhs(1, 2) * _3142_3241),
			+invDet * (rhs(0, 0) * _3243_3342 - rhs(0, 1) * _3143_3341 + rhs(0, 2) * _3142_3241),
			-invDet * (rhs(0, 0) * _2243_2342 - rhs(0, 1) * _2143_2341 + rhs(0, 2) * _2142_2241),
			+invDet * (rhs(0, 0) * _2233_2332 - rhs(0, 1) * _2133_2331 + rhs(0, 2) * _2132_2231));
	}
}

template <typename T>
T determinant(Matrix4_T<T> const & rhs) noexcept
{
	T const _3142_3241(rhs(2, 0) * rhs(3, 1) - rhs(2, 1) * rhs(3, 0));
	T const _3143_3341(rhs(2, 0) * rhs(3, 2) - rhs(2, 2) * rhs(3, 0));
	T const _3144_3441(rhs(2, 0) * rhs(3, 3) - rhs(2, 3) * rhs(3, 0));
	T const _3243_3342(rhs(2, 1) * rhs(3, 2) - rhs(2, 2) * rhs(3, 1));
	T const _3244_3442(rhs(2, 1) * rhs(3, 3) - rhs(2, 3) * rhs(3, 1));
	T const _3344_3443(rhs(2, 2) * rhs(3, 3) - rhs(2, 3) * rhs(3, 2));

	return rhs(0, 0) * (rhs(1, 1) * _3344_3443 - rhs(1, 2) * _3244_3442 + rhs(1, 3) * _3243_3342)
		- rhs(0, 1) * (rhs(1, 0) * _3344_3443 - rhs(1, 2) * _3144_3441 + rhs(1, 3) * _3143_3341)
		+ rhs(0, 2) * (rhs(1, 0) * _3244_3442 - rhs(1, 1) * _3144_3441 + rhs(1, 3) * _3142_3241)
		- rhs(0, 3) * (rhs(1, 0) * _3243_3342 - rhs(1, 1) * _3143_3341 + rhs(1, 2) * _3142_3241);
}

class InvMat
{
	public static double[][] InverseMatrix(double[][] matrix)
	{
		double dDeterminant = Determinant(matrix);

		double[][] result = AdjointMatrix(matrix);

		for (int i = 0; i < matrix.Length; i++)
		{
			for (int j = 0; j < matrix.Length; j++)
			{
				result[i][j] = result[i][j] / dDeterminant;
			}
		}

		return result;
	}
	public static double Determinant(double[][] matrix)
	{
		//二阶及以下行列式直接计算
		if (matrix.Length == 0) return 0;
		else if (matrix.Length == 1) return matrix[0][0];
		else if (matrix.Length == 2)
		{
			return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
		}

		//对第一行使用“加边法”递归计算行列式的值
		double dSum = 0, dSign = 1;
		for (int i = 0; i < matrix.Length; i++)
		{
			double[][] matrixTemp = new double[matrix.Length - 1][];
			for (int count = 0; count < matrix.Length - 1; count++)
			{
				matrixTemp[count] = new double[matrix.Length - 1];
			}

			for (int j = 0; j < matrixTemp.Length; j++)
			{
				for (int k = 0; k < matrixTemp.Length; k++)
				{
					matrixTemp[j][k] = matrix[j + 1][k >= i ? k + 1 : k];
				}
			}

			dSum += (matrix[0][i] * dSign * Determinant(matrixTemp));
			dSign = dSign * -1;
		}

		return dSum;
	}
	public static double[][] AdjointMatrix(double[][] matrix)
	{
		//制作一个伴随矩阵大小的矩阵
		double[][] result = new double[matrix.Length][];
		for (int i = 0; i < result.Length; i++)
		{
			result[i] = new double[matrix[i].Length];
		}

		//生成伴随矩阵
		for (int i = 0; i < result.Length; i++)
		{
			for (int j = 0; j < result.Length; j++)
			{
				//存储代数余子式的矩阵（行、列数都比原矩阵少1）
				double[][] temp = new double[result.Length - 1][];
				for (int k = 0; k < result.Length - 1; k++)
				{
					temp[k] = new double[result[k].Length - 1];
				}

				//生成代数余子式
				for (int x = 0; x < temp.Length; x++)
				{
					for (int y = 0; y < temp.Length; y++)
					{
						temp[x][y] = matrix[x < i ? x : x + 1][y < j ? y : y + 1];
					}
				}

				result[j][i] = ((i + j) % 2 == 0 ? 1 : -1) * Determinant(temp);
			}
		}
		return result;
	}
}