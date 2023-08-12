#pragma once
#include "../Enemy.h"

// 前方宣言
class Enemy;

class IState {
public: // メンバ関数
	// デストラクタ
	virtual ~IState(){};
	
	// 純粋仮想関数
	virtual void Update(Enemy* enemy) = 0;
};