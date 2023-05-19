#include "Player.h"
#include "MatrixMath.h"

void Player::Attack() {
	if (input_->PushKey(DIK_RETURN)) {
		PlayerBullet* newBulllet = new PlayerBullet();
		newBulllet->Initialize(model_, worldTransform_.translation_);
		
		bullet_ = newBulllet;
	}
}

void Player::Initialize(Model* model, uint32_t textureHandle) {

	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;
	worldTransform_.Initialize();
	input_ = Input::GetInstance();
}

void Player::Update() {
	worldTransform_.TransferMatrix();

	// キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};

	// キャラクターの移動速さ
	const float kCharacterSpeed = 0.2f;

	// 押した方向で移動ベクトルを変更（左右）
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
		inputFloat3[0] = worldTransform_.translation_.x;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
		inputFloat3[0] = worldTransform_.translation_.x;
	}

	// 押した方向で移動ベクトルを変更（上下）
	if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
		inputFloat3[1] = worldTransform_.translation_.y;
	} else if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
		inputFloat3[1] = worldTransform_.translation_.y;
	}

	const float kRotSpeed = 0.02f;

	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	} else if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y += kRotSpeed;
	}

	worldTransform_.translation_.x = inputFloat3[0];
	worldTransform_.translation_.y = inputFloat3[1];

	worldTransform_.translation_ = Add(worldTransform_.translation_, move);
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	ImGui::Begin("PlayerDebug");
	ImGui::Text("DebugCamera Toggle : SPACE");
	ImGui::SliderFloat3("Positions", inputFloat3, -20.0f, 20.0f);

	ImGui::End();

	const float kMoveLimitX = 34;
	const float kMoveLimitY = 18;
	
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	Attack();
	if (bullet_) {
		bullet_->Update();
	}

}

void Player::Draw(ViewProjection viewProjection){

	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	if (bullet_) {
		bullet_->Draw(viewProjection);
	}
}

