#include "Vector3.h"

/// 3次元ベクトルの長さを求める
float Length(Vector3 vector) {
	return sqrtf(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}
/// 3次元ベクトルの正規化
Vector3 Normalize(Vector3 norm) {
	float length = Length(norm);
	if (length != 0.0f) {
		norm.x /= length;
		norm.y /= length;
		norm.z /= length;
	}
	return norm;
}
// 線形補完
Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t) { 
	return v1 + ((v2 - v1) * t);
}
// 球面線形補間
Vector3 Slerp(const Vector3& v1, const Vector3& v2, float t) {
	return v1 * (1 - t) + v2 * t;
}