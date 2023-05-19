#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Model.h"
#include "Input.h"
#include <cassert>
#include "ImGuiManager.h"
#include "PlayerBullet.h"
#include <list>

class Player {

public:
	void Initialize(Model* model, uint32_t textureHandle);

	void Update();

	void Draw(ViewProjection viewProjection_);

	void Attack();

	~Player();

private:

	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;

	// キーボード入力
	Input* input_ = nullptr;

	float inputFloat3[3] = {0, 0, 0};

	PlayerBullet* bullet_ = nullptr;

	std::list<PlayerBullet*> bullets_;
};
