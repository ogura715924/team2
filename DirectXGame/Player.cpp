#include "Player.h"

void Player::Initialize(Model* model, uint32_t textureHandle) { 
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
}

void Player::Update() { 
	worldTransform_.TransferMatrix();



}

void Player::Draw(ViewProjection& viewProjection) {

	 model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
