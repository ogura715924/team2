﻿#include "Boss.h"

void Boss::Initialize(Model* modelB, Model* modelE) {
	// NULLポインタチェック
	assert(modelB);
	 modelB_= modelB;
	assert(modelE);
	modelE_ = modelE;

	worldTransform_.Initialize();
	 RotateSpeed = 0.07f;
	TimingTimer = 20;
	 worldTransform_.translation_ = {0.0f, 1.0f, 30.0f};

	// ライフ
	Life_ = 3;

	RespawnTime = 600;

	phase_ = Phase::Attack;

}

void Boss::Update() {
	// 行列更新
	worldTransform_.UpdateMatrix();

	//フェーズ
	switch (phase_) { 
	case Phase::Attack:
	default:
		// ボスの回転
		worldTransform_.rotation_.y += RotateSpeed;

		// 小さい敵の発生
		Timing();
		TimingTimer--;

		// 小さい敵の更新
		for (LotEnemy* enemynum : enemyNums_) {
			enemynum->Update();
		}

		break;

		case Phase::noAttack:
		// デスフラグの経った敵の削除
		enemyNums_.remove_if([](LotEnemy* enemynum) {
			if (enemynum->IsDead()) {
				delete enemynum;
				return true;
			}
			return false;
		});
		
		//10秒経ったらまた攻撃し始める
		RespawnTime -= 1;
		if (RespawnTime <= 0) {
			phase_ = Phase::Attack;
			RespawnTime = 600;
		}
			break;
	}

}

void Boss::Draw(const ViewProjection& viewProjection_) {
	// 3Dモデルを描画
	modelB_->Draw(worldTransform_, viewProjection_);

	// 小さい敵の描画複数
	for (LotEnemy* enemynum : enemyNums_) {
		enemynum->Draw(viewProjection_);
	}
}

// 小さい敵複数
void Boss::Timing() {

	//タイマーが0になったら
	if (TimingTimer<=0) {
		//小さい敵の速度
		Vector3 velocity(0.2f, 0, 0.2f);
		//速度ベクトルを自機に向きに合わせて回転させる
		velocity = TransformNormal(velocity, worldTransform_.matWorld_);
		// 敵の生成
		LotEnemy* newEnemynum = new LotEnemy();
		newEnemynum->Initialize(modelE_, worldTransform_.translation_,velocity);
		// 敵の登録
		enemyNums_.push_back(newEnemynum);
		TimingTimer = 20;
	}
}

void Boss::ItemOnColision() {
	//アイテムとプレイヤーが当たったら小さい敵全員が死ぬ
	for (LotEnemy* enemynum : enemyNums_) {
			enemynum->OnCollision();
	}
	phase_ = Phase::noAttack;
}

