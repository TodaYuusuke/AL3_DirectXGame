#pragma once
#include <cmath>

/// <summary>
/// 3次元ベクトル
/// </summary>
struct Vector3 final {
	float x;
	float y;
	float z;

#pragma region 演算子オーバーロード

	inline Vector3 operator+(const Vector3& other) const {
		return {x + other.x, y + other.y, z + other.z};
	}
	inline Vector3& operator+=(const Vector3& other) { return *this = *this + other; }
	inline Vector3 operator-(const Vector3& other) const {
		return {x - other.x, y - other.y, z - other.z};
	}
	inline Vector3& operator-=(const Vector3& other) { return *this = *this - other; }
	inline Vector3 operator*(const float& other) const {
		return {x * other, y * other, z * other};
	}
	inline Vector3& operator*=(const float& other) { return *this = *this * other; }	

#pragma endregion
};

// 3次元ベクトルの長さを求める
float Length(Vector3 vector);
// 二つのベクトル間の距離を求める
float Distance(Vector3 v1, Vector3 v2);
// 3次元ベクトルの正規化
Vector3 Normalize(Vector3 norm);
// 線形補完
Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t);
// 球面線形補間
Vector3 Slerp(const Vector3& v1, const Vector3& v2, float t);