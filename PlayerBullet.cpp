#include "PlayerBullet.h"
#include <assert.h>
#include "MatrixMath.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	
	assert(model);
	model_ = model;
	// テクスチャ読み込み
	texturehandle_ = TextureManager::Load("./Resources/white1x1.png");

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;

	velocity_ = velocity;
}

void PlayerBullet::Update() {
	worldTransform_.UpdateMatrix(); 
	
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);

	if (--deathtimer_ <= 0) {
		isDead_ = true;
	}
}

// モデルの描画
void PlayerBullet::Draw(const ViewProjection& view) {
	model_->Draw(worldTransform_, view, texturehandle_);
}