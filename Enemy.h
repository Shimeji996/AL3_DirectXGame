﻿#pragma once
#include "MatrixMath.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Model.h"
#include <list>
#include "EnemyBullet.h"
#include "TimedCall.h"
#include "Player.h"

enum class Phase {
	Approach, // 接近する
	Leave,    // 離脱する
};

class Player;

class Enemy;

class EnemyState {

protected:
	Enemy* enemy_ = nullptr;

public:
	virtual void SetEnemy(Enemy* enemy) { enemy_ = enemy; }
	virtual void Update(){};
};

class EnemyStateApproah : public EnemyState {

public:
	void Update();
};

class EnemyStateLeave : public EnemyState {

public:
	void Update();
};

class Enemy {

public:
	~Enemy();

	void Initialize(Model* model, const Vector3& position);

	void Update();

	void Draw(const ViewProjection& view);

	void ChangeState(EnemyState* newEnemyState);

	WorldTransform GetWT() { return worldTransform_; }

	void SetPosition(Vector3 speed);

	// 攻撃
	void Attack();

	void Fire();

	void SetPlayer(Player* player) { player_ = player; }

	Vector3 GetWorldPosition();

	// 衝突を検証したら呼び出される関数
	void OnCollision();
	const std::list<EnemyBullet*>& GetBullets() const { return bullets_; }

private:
	WorldTransform worldTransform_;
	Model* model_;
	uint32_t texturehandle_;

	Phase phase_ = Phase::Approach;

	Player* player_ = nullptr;

	EnemyState* state;

	// 弾
	std::list<EnemyBullet*> bullets_;

	std::list<TimedCall*> timedCall_;

	static const int kShotInterval = 60;

	int timer = 0;
};
