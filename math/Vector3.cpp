#include "Vector3.h"
#include "Matrix4x4.h"


Vector3 Vector3::operator*(const Matrix4x4& other) const {
	Vector3 result{};
	result.x = x * other.m[0][0] + y * other.m[1][0] + z * other.m[2][0] + other.m[3][0];
	result.y = x * other.m[0][1] + y * other.m[1][1] + z * other.m[2][1] + other.m[3][1];
	result.z = x * other.m[0][2] + y * other.m[1][2] + z * other.m[2][2] + other.m[3][2];
	return result;
}

// 3次元ベクトルの長さを求める
float Length(Vector3 vector) {
	return sqrtf(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}
// 3次元ベクトルの正規化
Vector3 Normalize(Vector3 norm) {
	float length = Length(norm);
	if (length != 0.0f) {
		norm.x /= length;
		norm.y /= length;
		norm.z /= length;
	}
	return norm;
}
// 二つのベクトル間の距離を求める
float Distance(Vector3 v1, Vector3 v2){
	return powf((v2.x - v1.x), 2) + powf((v2.y - v1.y), 2) + powf((v2.z - v1.z), 2);
}
// 線形補完
Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t) { 
	return v1 + ((v2 - v1) * t);
}
// 球面線形補間
Vector3 Slerp(const Vector3& v1, const Vector3& v2, float t) {
	return v1 * (1 - t) + v2 * t;
}