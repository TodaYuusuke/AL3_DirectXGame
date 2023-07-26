#pragma once
#include <cmath>
#include <vector>

struct ViewProjection;
class PrimitiveDrawer;

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

// Catmull-Romスプライン曲線補間
Vector3 CatmullRom(Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3, float t);
/// <summary>
/// Catmull-Romスプライン曲線補間の座標を求める
/// </summary>
/// <param name="controlPoints">頂点の可変長配列</param>
/// <param name="t">全体の0.0～1.0</param>
Vector3 GetCatmullRomPosition(std::vector<Vector3> controlPoints, float t);
// 曲線描画
void DrawCatmullRom(std::vector<Vector3> pointsDrawing, size_t segmentCount);