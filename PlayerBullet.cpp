#include "PlayerBullet.h"
#include "MatrixMath.h"
#include <assert.h>

void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	// NULLポインタチェック
	assert(model);
	model_ = model;
	// テクスチャ読み込み
	texturehandle_ = TextureManager::Load("white1x1.png");

	worldTransform_.Initialize();

	worldTransform_.translation_ = position;
	
	velocity_ = velocity;
}

void PlayerBullet::Update() {

	worldTransform_.UpdateMatrix();
	
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);

	// 時間経過でデス
	if (--deathtimer_ <= 0) {
		isDead_ = true;
	}
}

// モデルの描画
void PlayerBullet::Draw(const ViewProjection& view) {
	model_->Draw(worldTransform_, view, texturehandle_);
}