#pragma once
#include "IState.h"

class Leave : public IState {

	// 更新処理
	void Update(Enemy* enemy);

	//*　　定　数　　*//

	// 撤退　速さ
	const Vector3 kLeaveSpeed = {-0.2f, 0.2f, 0};
};