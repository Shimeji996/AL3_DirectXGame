﻿#include "Player.h"
#include "MatrixMath.h"

Player::~Player() {
	for (PlayerBullet* bullet : bullets_) {
		delete bullet;
	}
}

Vector3 Player::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標）
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

void Player::OnCollision() {}

void Player::Attack() {
	if (input_->PushKey(DIK_SPACE)) {
		if (count == 0) {
			// 弾の速度
			const float kBulletSpeed = 1.0f;
			Vector3 velocity(0, 0, kBulletSpeed);
			// 速度ベクトルの自機の向きに合わせて回転させる
			velocity = TransformNormal(velocity, worldTransform_.matWorld_);
			PlayerBullet* newBulllet = new PlayerBullet();
			newBulllet->Initialize(model_, worldTransform_.translation_, velocity);
			// 弾を登録する
			bullets_.push_back(newBulllet);
			count++;
		}
	} else {

		count = 0;
	}
}

void Player::Initialize(Model* model, uint32_t textureHandle) {
	// NULLポインタチェック
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;
	worldTransform_.Initialize();
	input_ = Input::GetInstance();
}

void Player::Update() {
	// デスフラグのたった弾を削除
	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});
	// 行列更新
	worldTransform_.TransferMatrix();
	// キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};

	// キャラクターの移動速さ
	const float kCharacterSpeed = 0.2f;

	// 押した方向で移動ベクトルを変更(左右)
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
		inputFloat3[0] = worldTransform_.translation_.x;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
		inputFloat3[0] = worldTransform_.translation_.x;
	}

	// 押した方向で移動ベクトルを変更(上下)
	if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
		inputFloat3[1] = worldTransform_.translation_.y;
	} else if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
		inputFloat3[1] = worldTransform_.translation_.y;
	}

	// 回転速さ[ラジアン/frame]
	const float kRotSpeed = 0.02f;

	// 押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	} else if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y += kRotSpeed;
	}

	// ImGui加算用
	worldTransform_.translation_.x = inputFloat3[0];
	worldTransform_.translation_.y = inputFloat3[1];

	// ベクターの加算
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);
	// アフィン変換行列の作成
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	// ImGuiスライダー
	ImGui::Begin("PlayerDebug");
	ImGui::Text("DebugCamera Toggle : ENTER");
	ImGui::SliderFloat3("Positions", inputFloat3, -20.0f, 20.0f);
	// ImGui終わり
	ImGui::End();

	// 移動限界座標
	const float kMoveLimitX = 34;
	const float kMoveLimitY = 18;

	// 範囲を超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	Attack();

	// 弾更新
	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
	}
}

void Player::Draw(ViewProjection viewProjection_) {
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);

	// 弾の描画
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(viewProjection_);
	}
}