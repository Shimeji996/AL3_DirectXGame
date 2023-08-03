#pragma once

#include "Audio.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Player.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Enemy.h"
#include "Skydome.h"
#include "RailCamera.h"
#include <sstream>

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 衝突判定と応答
	/// </summary>
	void CheckAllCollisions();

	void AddEnemyBullet(EnemyBullet* enemyBullet);

	void AddEnemy(Enemy* enemy);

	void EnemyIni(Model* model, const Vector3 position);

	void LoadEnemyPopData();

	void UpDateEnemyPopCommands();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	uint32_t textureHandle_ = 0;
	Model* model_ = nullptr;
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	Player* player_ = nullptr;
	bool isDebugCameraActive_ = false;
	DebugCamera* debugCamera_ = nullptr;
	
	std::list<EnemyBullet*> enemyBullets_;
	std::list<Enemy*> enemys_;

	std::stringstream enemyPopCommands;
	bool isWait_ = false;
	int32_t waitTimer_ = 0;

	Skydome* skydome_ = nullptr;
	Model* modelSkydome_ = nullptr;
	RailCamera* railCamera_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};