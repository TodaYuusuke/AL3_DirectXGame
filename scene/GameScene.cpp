#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <AxisIndicator.h>
#include "./MyClass/Scene/Title.h"
#include "./MyClass/Scene/GamePlay.h"

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {
	// 乱数シードを設定
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	
	currentScene_ = new Title();
	currentScene_->Initialize();
}

void GameScene::Update() {
	if (currentScene_->nextScene_ != nullptr) {
		currentScene_ = currentScene_->nextScene_;
		currentScene_->Initialize();
	}

	currentScene_->Update();
}

void GameScene::Draw() {
	currentScene_->Draw();
}