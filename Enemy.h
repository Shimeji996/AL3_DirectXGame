#pragma once
#include "Collider.h"
#include "EnemyBullet.h"
#include "Model.h"
#include "WorldTransform.h"

class Player;

class Enemy : public Collider {
public:
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	~Enemy();

	void Update();

	void Draw(const ViewProjection& view);

	void Fire();

	void SetPlayer(Player* player) { player_ = player; }

	Vector3 GetWorldPosition() override;

	static const int kFireInterval = 60;
	int32_t fireTimer;

	void OnCollision() override;
	const std::list<EnemyBullet*>& GetBullets() const { return bullets_; }

private:
	// 行動フェーズ
	enum class Phase {
		Approach, 
		Leave,    
		start,    
	};
	WorldTransform worldTransform_;
	Model* model_;
	uint32_t texturehandle_;
	// フェーズ
	Phase phase_ = Phase::Approach;
	Vector3 velocity_;
	void Approach();
	void Leave();
	static void (Enemy::*EfuncTable[])();
	std::list<EnemyBullet*> bullets_;
	Player* player_ = nullptr;
};