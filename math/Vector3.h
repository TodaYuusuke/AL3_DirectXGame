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

/// 3次元ベクトルの長さを求める
float Length(Vector3 vector);
/// 3次元ベクトルの正規化
Vector3 Normalize(Vector3 norm);