#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Collider.h"

class PlayerBullet : public Collider {
public:
	
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	void Update();

	void Draw(const ViewProjection& ViewProjection);

	bool IsDead() const { return isDead_; }

	void OnCollision() override;

	Vector3 GetWorldPosition() override;

private:
	WorldTransform worldTransform_;
	Model* model_;
	uint32_t texturehandle_;
	
	Vector3 velocity_;
	
	static const int32_t kLifeTime = 60;
	// デスタイマー
	int32_t deathtimer_ = kLifeTime;
	// デスフラグ
	bool isDead_ = false;
};