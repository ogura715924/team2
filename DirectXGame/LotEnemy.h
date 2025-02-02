﻿#pragma once
#include <Model.h>
#include <cassert>
#include <Input.h>

class LotEnemy {
public:

	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);
	void Update();
	void Draw(const ViewProjection& viewProjection_);

	bool IsDead() const { return isDead_; }

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	Input* input_ = nullptr;

	// 速度
	Vector3 velocity_;
	//寿命
	static const int32_t kLifeTime = 60 * 20;
	//デスタイマー
	int32_t deathTimer_ = kLifeTime;
	//デスフラグ
	bool isDead_ = false;
	
	
};
