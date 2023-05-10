#include <3d/WorldTransform.h>

/// <summary>
/// アフィン行列を返す関数
/// </summary>
/// <returns></returns>
Matrix4x4 WorldTransform::MakeAffineMatrix() {
	return Matrix4x4::MakeAffineMatrix(scale_, rotation_, translation_);
}


/// <summary>
/// 行列を計算、転送する
/// </summary>
void WorldTransform::UpdateMatrix() {
	// アフィン変換行列をワールド行列に代入する
	matWorld_ = MakeAffineMatrix();
	// 行列を定数バッファに転送
	TransferMatrix();
}