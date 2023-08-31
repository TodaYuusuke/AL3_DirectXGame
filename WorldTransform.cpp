#include <3d/WorldTransform.h>

/// <summary>
/// アフィン行列を返す関数
/// </summary>
/// <returns></returns>
Matrix4x4 WorldTransform::MakeAffineMatrix() {
	return Matrix4x4::MakeAffineMatrix(scale_, rotation_, translation_);
}


Vector3 WorldTransform::GetWorldPosition() const {
	Vector3 result;
	result.x = matWorld_.m[3][0];
	result.y = matWorld_.m[3][1];
	result.z = matWorld_.m[3][2];
	return result;
}


/// <summary>
/// 行列を計算、転送する
/// </summary>
void WorldTransform::UpdateMatrix() {
	// アフィン変換行列をワールド行列に代入する
	matWorld_ = MakeAffineMatrix();

	// 親があれば親のワールド行列を掛ける
	if (parent_) {
		matWorld_ = matWorld_ * parent_->matWorld_;
	}

	// 行列を定数バッファに転送
	TransferMatrix();
}