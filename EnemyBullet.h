﻿#pragma once
#include "Model.h"
#include "Collider.h"
#include "CollisionConfig.h"

class EnemyBullet : public Collider {
public:
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	void Update();

	void Draw(const ViewProjection& view);

	bool isDead() const { return isDead_; }

	void OnCollision() override;

	Vector3 GetWorldPosition() override;

private:
	WorldTransform worldTransform_;
	Model* model_;
	uint32_t texturehandle_;
	Vector3 velocity_;
	static const int32_t kLifeTime = 110;
	int32_t deathTimer_ = kLifeTime;
	bool isDead_ = false;
};