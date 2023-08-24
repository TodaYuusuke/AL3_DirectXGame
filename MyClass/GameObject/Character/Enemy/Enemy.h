#pragma once
#include "../BaseCharacter.h"

#define _USE_MATH_DEFINES
#include <math.h>

class Enemy : public BaseCharacter {

public: // メンバ関数

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const std::vector<Model*>& models, Vector3 position) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

private: // メンバ定数
	float kCharacterSpeed = 0.3f;

private: // メンバ変数
	enum Parts {
		Body,
		LeftWheel,
		RightWheel,
	};

private: // プライベートな関数

private: // アニメーション関連
	// 関数
	void InitializeAnimation();
	void Animation();

	// エンジンみたいな振動をするギミック
	const uint16_t kEngineCycle_ = 5;
	const double kEngineStep_ = 2.0f * M_PI / kEngineCycle_;	
	const float kEngineHeight = 0.02f;
	float engineParameter_ = 0.0f;
	void EngineUpdate();

	// 円運動
	const uint16_t kCircleCycle_ = 360;
	const double kCircleStep_ = 2.0f * M_PI / kCircleCycle_;
	const float kCirclePower = 2.0f;
	float circleParameter_ = 0.0f;
	void CircleUpdate();
};
