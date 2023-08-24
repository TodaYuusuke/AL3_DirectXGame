#include "BaseCharacter.h"

// 初期化
void BaseCharacter::Initialize(const std::vector<Model*>& models, Vector3 position) {
	models_.clear();

	int i = 0;
	for (Model* model : models) {
		models_.insert({i, {model, WorldTransform()}});
		models_[i].worldTransform_.Initialize();
		i++;
	}

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
}
// 更新
void BaseCharacter::Update() {
	worldTransform_.UpdateMatrix();
	for (int i = 0; i < models_.size(); i++) {
		models_[i].worldTransform_.UpdateMatrix();
	}
}
// 描画
void BaseCharacter::Draw(const ViewProjection& viewProjection) {
	for (int i = 0; i < models_.size(); i++) {
		models_[i].model_->Draw(models_[i].worldTransform_, viewProjection);
	}
}