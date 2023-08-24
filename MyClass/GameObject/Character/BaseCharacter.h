#pragma once
#include <map>
#include "Model.h"

class BaseCharacter {
public: // メンバ関数

	// 初期化
	virtual void Initialize(const std::vector<Model*>& models, Vector3 position);
	// 更新
	virtual void Update();
	// 描画
	virtual void Draw(const ViewProjection& viewProjection);

	/// <summary>
	/// ワールド変換データを取得
	/// </summary>
	/// <returns>ワールド変換データ</returns>
	const WorldTransform& GetWorldTransform() { return worldTransform_; }

protected: // メンバ変数
	// モデルデータとモデル別のワールド変換データ
	struct ModelData {
		Model* model_;
		WorldTransform worldTransform_;
	};

	// モデルデータ配列
	std::map<int, ModelData> models_;
	// ワールド変換データ
	WorldTransform worldTransform_;
};