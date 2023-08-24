#pragma once
#include <cmath>

struct Matrix4x4;

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
	inline Vector3 operator*(const float& other) const { return {x * other, y * other, z * other}; }
	inline Vector3& operator*=(const float& other) { return *this = *this * other; }
	// Vector3 Multiply(*) Matrix4x4
	Vector3 operator*(const Matrix4x4& other) const;
	// friend Vector3 operator*(Matrix4x4 scalar, const Vector3& vec) { return vec * scalar; }

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
// 最短角度補間
float LeapShortAngle(float a, float b, float t);
// 球面線形補間
Vector3 Slerp(const Vector3& v1, const Vector3& v2, float t);

// radianからdegreeに変換する関数
// 返り値：degree
// 引数：
// radian ... radianの角度
// radianの角度をdegreeの角度に変換する関数。引数で要求されるのは基本Degreeなのであまり使わない。
float RadiantoDegree(float radian);

// degreeからradianに変換する関数
// 返り値：radian
// 引数：
// degree ... degreeの角度
// degreeの角度をradianの角度に変換する関数。引数で要求されるのは基本Degreeなので関数内では使われる。
float DegreetoRadian(float degree);