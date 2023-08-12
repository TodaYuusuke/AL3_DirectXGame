#pragma once
#include "IState.h"

class Approach : public IState {

	// 更新処理
	void Update(Enemy* enemy);

	//*　　定　数　　*//

	// 接近　速さ
	const Vector3 kApproachSpeed = {0, 0, -0.5f};
};