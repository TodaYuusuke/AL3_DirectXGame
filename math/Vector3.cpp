#include "Vector3.h"
#include "3d/PrimitiveDrawer.h"
#include <algorithm>

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

// Catmull-Romスプライン曲線補間
Vector3 CatmullRom(Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3, float t) {
	return (((p0 * -1) + (p1 * 3) + (p2 * -3) + (p3)) * powf(t, 3.0f) + 
			((p0 *  2) + (p1 * -5) + (p2 * 4) + (p3 * -1)) * powf(t, 2.0f) + 
			((p0 * -1) + (p2)) * t + (p1 * 2)) * (1.0f / 2.0f);
}

// Catmull-Romスプライン曲線補間の座標を求める
Vector3 GetCatmullRomPosition(std::vector<Vector3> controlPoints, float t) {
	// 4頂点未満の場合計算しない
	if (controlPoints.size() < 4) {
		assert(false);
	}

	// サイズに応じて計算する4点とtの値を求める
	float calcT = t * (controlPoints.size() - 1);
	// 整数部を取得
	int roop = static_cast<int>(calcT);
	// 小数部を取得
	calcT -= static_cast<float>(roop);

	roop = std::clamp(roop, 0, static_cast<int>(controlPoints.size() - 1));
	calcT = std::clamp(calcT, 0.0f, 1.0f);

	// 計算する4点を求める
	Vector3 pos0{}, pos1{}, pos2{}, pos3{};
	// 最初のイテレータ
	std::vector<Vector3>::iterator itr = controlPoints.begin();
	for (int i = 0; i <= roop; i++) {

		// pos0は始点の場合 -> pos1と同じ
		if (itr == controlPoints.begin()) {
			pos0 = *itr; // 同じ
			pos1 = *itr;
		} else {
			pos0 = *--itr; // ここでマイナスしてるので
			pos1 = *++itr; // プラスする
		}
		pos2 = *++itr;
		// pos3は終点の場合 -> pos2と同じ
		if (itr == --controlPoints.end()) {
			pos3 = *itr;
		} else {
			pos3 = *++itr;
			--itr; // 戻す
		}
	}

	// 頂点座標を計算
	return CatmullRom(pos0, pos1, pos2, pos3, calcT);
}

// Catmull-Romスプライン曲線の描画
void DrawCatmullRom(
    std::vector<Vector3> controlPoints, size_t segmentCount) {
	// 4頂点未満の場合描画しない
	if (controlPoints.size() < 4) {
		return;
	}

	// 描画用の頂点リスト
	std::vector<Vector3> pointsDrawing;

	// 最初のイテレータ
	std::vector<Vector3>::iterator itr = controlPoints.begin();
	for (; itr != --controlPoints.end();) {
		// 計算する4点を求める
		Vector3 pos0, pos1, pos2, pos3;

		// pos0は始点の場合 -> pos1と同じ
		if (itr == controlPoints.begin()) {
			pos0 = *itr; // 同じ
			pos1 = *itr;
		} else {
			pos0 = *--itr; // ここでマイナスしてるので
			pos1 = *++itr; // プラスする
		}
		pos2 = *++itr;
		// pos3は終点の場合 -> pos2と同じ
		if (itr == --controlPoints.end()) {
			pos3 = *itr;
		} else {
			pos3 = *++itr;
			--itr; // 戻す
		}

		// 線分の数+1個分の頂点座標を計算
		for (size_t i = 0; i < segmentCount + 1; i++) {
			float t = 1.0f / segmentCount * i;
			pointsDrawing.push_back(CatmullRom(pos0, pos1, pos2, pos3, t));
		}
	}

	PrimitiveDrawer* primitiveDrawer = PrimitiveDrawer::GetInstance();

	// 描画
	itr = pointsDrawing.begin();
	for (; itr != --pointsDrawing.end();) {
		Vector3 pos0 = *itr;
		Vector3 pos1 = *++itr;
		Vector4 color = {1.0f, 0.0f, 0.0f, 1.0f};
		primitiveDrawer->DrawLine3d(pos0, pos1, color);
	}
}