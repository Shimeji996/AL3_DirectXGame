#pragma once
#include "ImGuiManager.h"
#include "Input.h"
#include "Model.h"
#include "PlayerBullet.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <cassert>
#include <list>

class Player {

public:
	///< summary>
	/// 初期化
	///</summary>
	void Initialize(Model* model, uint32_t textureHandle);

	void Update();

	void Draw(ViewProjection viewProjection_);

	void Attack();

	~Player();

	Vector3 GetWorldPosition();

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	// キーボード入力
	Input* input_ = nullptr;
	// ImGUiで値を入力する変数
	float inputFloat3[3] = {0, 0, 0};
	// 弾
	// PlayerBullet* bullet_ = nullptr;
	// 弾
	std::list<PlayerBullet*> bullets_;
	int count = 0;
};