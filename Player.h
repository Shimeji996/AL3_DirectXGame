#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Model.h"
#include "Input.h"
#include <cassert>
#include "ImGuiManager.h"
#include "PlayerBullet.h"
#include <list>
#include "Collider.h"

class Player : public Collider {

public:
	
	void Initialize(Model* model, uint32_t textureHandle);

	void Update();
	
	void Draw(ViewProjection viewProjection_);

	void Attack();

	~Player();

	Vector3 GetWorldPosition() override;

	void OnCollision() override;
	const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }

private:
	WorldTransform worldTransform_;
	
	Model* model_ = nullptr;
	
	uint32_t textureHandle_ = 0u;
	
	Input* input_ = nullptr;
	
	float inputFloat3[3] = {0, 0, 0};
	// 弾
	// PlayerBullet* bullet_ = nullptr;
	// 弾
	std::list<PlayerBullet*> bullets_;
	int count = 0;
};