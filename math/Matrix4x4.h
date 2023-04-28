#pragma once
#include <cassert>
/// <summary>
/// 4x4行列
/// </summary>
struct Matrix4x4 final {
	float m[4][4];

	
#pragma region 演算子オーバーロード

	// +
	inline const Matrix4x4 operator+(const Matrix4x4& other) const {
		Matrix4x4 result{};
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				result.m[y][x] = m[y][x] + other.m[y][x];
			}
		}
		return result;
	}
	// -
	inline const Matrix4x4 operator-(const Matrix4x4& other) const {
		Matrix4x4 result{};
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				result.m[y][x] = m[y][x] - other.m[y][x];
			}
		}
		return result;
	}
	// *
	inline const Matrix4x4 operator*(const float& other) const {
		Matrix4x4 result{};
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				result.m[y][x] = m[y][x] * other;
			}
		}
		return result;
	}
	inline const Matrix4x4 operator*(const Matrix4x4& other) const {
		Matrix4x4 result{};
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				result.m[y][x] = (m[y][0] * other.m[0][x]) + (m[y][1] * other.m[1][x]) +
				                 (m[y][2] * other.m[2][x]) + (m[y][3] * other.m[3][x]);
			}
		}
		return result;
	}

#pragma endregion

#pragma region 行列変換系

	// 行列式を返す関数
	static float Determinant(Matrix4x4 matrix) {
		// 行列式
		return (matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][3]) +
		       (matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][1]) +
		       (matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][2]) -

		       (matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][1]) -
		       (matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][3]) -
		       (matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][2]) -

		       (matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][3]) -
		       (matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][1]) -
		       (matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][2]) +

		       (matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][1]) +
		       (matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][3]) +
		       (matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][2]) +

		       (matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][3]) +
		       (matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][1]) +
		       (matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][2]) -

		       (matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][1]) -
		       (matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][3]) -
		       (matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][2]) -

		       (matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][0]) -
		       (matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][0]) -
		       (matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][0]) +

		       (matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][0]) +
		       (matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][0]) +
		       (matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][0]);
	}
	// 逆行列を返す関数
	static Matrix4x4 Inverse(Matrix4x4 matrix) {
		Matrix4x4 result{};

		result.m[0][0] = (matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][3]) +
		                 (matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][1]) +
		                 (matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][2]) -
		                 (matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][1]) -
		                 (matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][3]) -
		                 (matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][2]);
		result.m[0][1] = -(matrix.m[0][1] * matrix.m[2][2] * matrix.m[3][3]) -
		                 (matrix.m[0][2] * matrix.m[2][3] * matrix.m[3][1]) -
		                 (matrix.m[0][3] * matrix.m[2][1] * matrix.m[3][2]) +
		                 (matrix.m[0][3] * matrix.m[2][2] * matrix.m[3][1]) +
		                 (matrix.m[0][2] * matrix.m[2][1] * matrix.m[3][3]) +
		                 (matrix.m[0][1] * matrix.m[2][3] * matrix.m[3][2]);
		result.m[0][2] = (matrix.m[0][1] * matrix.m[1][2] * matrix.m[3][3]) +
		                 (matrix.m[0][2] * matrix.m[1][3] * matrix.m[3][1]) +
		                 (matrix.m[0][3] * matrix.m[1][1] * matrix.m[3][2]) -
		                 (matrix.m[0][3] * matrix.m[1][2] * matrix.m[3][1]) -
		                 (matrix.m[0][2] * matrix.m[1][1] * matrix.m[3][3]) -
		                 (matrix.m[0][1] * matrix.m[1][3] * matrix.m[3][2]);
		result.m[0][3] = -(matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][3]) -
		                 (matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][1]) -
		                 (matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][2]) +
		                 (matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][1]) +
		                 (matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][3]) +
		                 (matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][2]);

		result.m[1][0] = -(matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][3]) -
		                 (matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][0]) -
		                 (matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][2]) +
		                 (matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][0]) +
		                 (matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][3]) +
		                 (matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][2]);
		result.m[1][1] = (matrix.m[0][0] * matrix.m[2][2] * matrix.m[3][3]) +
		                 (matrix.m[0][2] * matrix.m[2][3] * matrix.m[3][0]) +
		                 (matrix.m[0][3] * matrix.m[2][0] * matrix.m[3][2]) -
		                 (matrix.m[0][3] * matrix.m[2][2] * matrix.m[3][0]) -
		                 (matrix.m[0][2] * matrix.m[2][0] * matrix.m[3][3]) -
		                 (matrix.m[0][0] * matrix.m[2][3] * matrix.m[3][2]);
		result.m[1][2] = -(matrix.m[0][0] * matrix.m[1][2] * matrix.m[3][3]) -
		                 (matrix.m[0][2] * matrix.m[1][3] * matrix.m[3][0]) -
		                 (matrix.m[0][3] * matrix.m[1][0] * matrix.m[3][2]) +
		                 (matrix.m[0][3] * matrix.m[1][2] * matrix.m[3][0]) +
		                 (matrix.m[0][2] * matrix.m[1][0] * matrix.m[3][3]) +
		                 (matrix.m[0][0] * matrix.m[1][3] * matrix.m[3][2]);
		result.m[1][3] = (matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][3]) +
		                 (matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][0]) +
		                 (matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][2]) -
		                 (matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][0]) -
		                 (matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][3]) -
		                 (matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][2]);

		result.m[2][0] = (matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][3]) +
		                 (matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][0]) +
		                 (matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][1]) -
		                 (matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][0]) -
		                 (matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][3]) -
		                 (matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][1]);
		result.m[2][1] = -(matrix.m[0][0] * matrix.m[2][1] * matrix.m[3][3]) -
		                 (matrix.m[0][1] * matrix.m[2][3] * matrix.m[3][0]) -
		                 (matrix.m[0][3] * matrix.m[2][0] * matrix.m[3][1]) +
		                 (matrix.m[0][3] * matrix.m[2][1] * matrix.m[3][0]) +
		                 (matrix.m[0][1] * matrix.m[2][0] * matrix.m[3][3]) +
		                 (matrix.m[0][0] * matrix.m[2][3] * matrix.m[3][1]);
		result.m[2][2] = (matrix.m[0][0] * matrix.m[1][1] * matrix.m[3][3]) +
		                 (matrix.m[0][1] * matrix.m[1][3] * matrix.m[3][0]) +
		                 (matrix.m[0][3] * matrix.m[1][0] * matrix.m[3][1]) -
		                 (matrix.m[0][3] * matrix.m[1][1] * matrix.m[3][0]) -
		                 (matrix.m[0][1] * matrix.m[1][0] * matrix.m[3][3]) -
		                 (matrix.m[0][0] * matrix.m[1][3] * matrix.m[3][1]);
		result.m[2][3] = -(matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][3]) -
		                 (matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][0]) -
		                 (matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][1]) +
		                 (matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][0]) +
		                 (matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][3]) +
		                 (matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][1]);

		result.m[3][0] = -(matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][2]) -
		                 (matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][0]) -
		                 (matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][1]) +
		                 (matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][0]) +
		                 (matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][2]) +
		                 (matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][1]);
		result.m[3][1] = (matrix.m[0][0] * matrix.m[2][1] * matrix.m[3][2]) +
		                 (matrix.m[0][1] * matrix.m[2][2] * matrix.m[3][0]) +
		                 (matrix.m[0][2] * matrix.m[2][0] * matrix.m[3][1]) -
		                 (matrix.m[0][2] * matrix.m[2][1] * matrix.m[3][0]) -
		                 (matrix.m[0][1] * matrix.m[2][0] * matrix.m[3][2]) -
		                 (matrix.m[0][0] * matrix.m[2][2] * matrix.m[3][1]);
		result.m[3][2] = -(matrix.m[0][0] * matrix.m[1][1] * matrix.m[3][2]) -
		                 (matrix.m[0][1] * matrix.m[1][2] * matrix.m[3][0]) -
		                 (matrix.m[0][2] * matrix.m[1][0] * matrix.m[3][1]) +
		                 (matrix.m[0][2] * matrix.m[1][1] * matrix.m[3][0]) +
		                 (matrix.m[0][1] * matrix.m[1][0] * matrix.m[3][2]) +
		                 (matrix.m[0][0] * matrix.m[1][2] * matrix.m[3][1]);
		result.m[3][3] = (matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2]) +
		                 (matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0]) +
		                 (matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1]) -
		                 (matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0]) -
		                 (matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2]) -
		                 (matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1]);

		float constant = 1.0f / Determinant(matrix);
		return result * constant;
	}
	// 転置行列を返す関数
	static Matrix4x4 Transpose(Matrix4x4 matrix) {
		Matrix4x4 result{};
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				result.m[y][x] = matrix.m[x][y];
			}
		}
		return result;
	}

#pragma endregion

#pragma region 行列作成系

	// 平行移動行列
	static Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {
		Matrix4x4 result{};
		result.m[0][0] = 1;
		result.m[1][1] = 1;
		result.m[2][2] = 1;
		result.m[3][3] = 1;
		result.m[3][0] = translate.x;
		result.m[3][1] = translate.y;
		result.m[3][2] = translate.z;
		return result;
	}
	// X軸回転行列
	static Matrix4x4 MakeRotateXMatrix(float radian) {
		Matrix4x4 result{};
		result.m[1][1] = std::cos(radian);
		result.m[1][2] = std::sin(radian);
		result.m[2][1] = -std::sin(radian);
		result.m[2][2] = std::cos(radian);

		result.m[0][0] = 1;
		result.m[3][3] = 1;
		return result;
	}
	// y軸回転行列
	static Matrix4x4 MakeRotateYMatrix(float radian) {
		Matrix4x4 result{};
		result.m[0][0] = std::cos(radian);
		result.m[0][2] = -std::sin(radian);
		result.m[2][0] = std::sin(radian);
		result.m[2][2] = std::cos(radian);

		result.m[1][1] = 1;
		result.m[3][3] = 1;
		return result;
	}
	// z軸回転行列
	static Matrix4x4 MakeRotateZMatrix(float radian) {
		Matrix4x4 result{};
		result.m[0][0] = std::cos(radian);
		result.m[0][1] = std::sin(radian);
		result.m[1][0] = -std::sin(radian);
		result.m[1][1] = std::cos(radian);

		result.m[2][2] = 1;
		result.m[3][3] = 1;
		return result;
	}
	/// <summary>
	/// 合成された回転行列
	/// </summary>
	/// <param name="Pitch">X軸周りの回転</param>
	/// <param name="Yaw">Y軸周りの回転</param>
	/// <param name="Roll">Z軸周りの回転</param>
	/// <returns></returns>
	static Matrix4x4 MakeRotateMatrix(const Vector3& rotate) {
		Matrix4x4 x = MakeRotateXMatrix(rotate.x);
		Matrix4x4 y = MakeRotateYMatrix(rotate.y);
		Matrix4x4 z = MakeRotateZMatrix(rotate.z);
		return x * y * z;
	}
	// 拡大縮小行列
	static Matrix4x4 MakeScaleMatrix(const Vector3& scale) {
		Matrix4x4 result{};
		result.m[0][0] = scale.x;
		result.m[1][1] = scale.y;
		result.m[2][2] = scale.z;
		result.m[3][3] = 1;
		return result;
	}
	
	/// <summary>
	/// アフィン行列を返す関数
	/// </summary>
	/// <returns></returns>
	static Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
		// スケーリング行列の作成
		Matrix4x4 s = Matrix4x4::MakeScaleMatrix(scale);

		// 回転行列の合成
		Matrix4x4 r = Matrix4x4::MakeRotateMatrix(rotate);

		// 平行移動行列の作成
		Matrix4x4 t = Matrix4x4::MakeTranslateMatrix(translate);

		return s * r * t;
	}



	// 座標変換
	static Vector3 TransformCoord(const Vector3& vector, const Matrix4x4 matrix) {
		Vector3 result;
		result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] +
		           vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
		result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] +
		           vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
		result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] +
		           vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
		float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] +
		          vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
		assert(w != 0.0f);
		result.x /= w;
		result.y /= w;
		result.z /= w;
		return result;
	}

	// 単位行列の作成
	static Matrix4x4 MakeIdentity4x4() {
		Matrix4x4 result{};
		for (int i = 0; i < 4; i++) {
			result.m[i][i] = 1;
		}
		return result;
	}

#pragma endregion

	// 描画用定数
	//const int kPrintMatrix4x4RowHeight = 20;
	//const int kPrintMatrix4x4ColumnWidth = 60;

	// 4x4行列の表示
	//void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {

	//	Novice::ScreenPrintf(x, y, "%s", label);
	//	for (int row = 0; row < 4; ++row) {
	//		for (int column = 0; column < 4; ++column) {
	//			Novice::ScreenPrintf(
	//			    x + column * kColumnWidth, y + (row + 1) * kRowHeight, "%6.02f",
	//			    matrix.m[row][column]);
	//		}
	//	}
	//}
};
