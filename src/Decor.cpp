#include "Decor.h"

Decor::Decor() {

}



void Decor::SetPositionX(float positionX) {
	this->positionX = positionX;
}
void  Decor::SetPositionY(float positionY) {
	this->positionY = positionY;
}
float  Decor::GetPositionX() {
	return this->positionX;
}
float  Decor::GetPositionY() {
	return this->positionY;
}

void  Decor::SetSizeX(float sizeX) {
	this->sizeX = sizeX;
}
void  Decor::SeSizeY(float sizeY) {
	this->sizeY = sizeY;
}
float  Decor::GetSizeX() {
	return this->sizeX;
}
float  Decor::GetSizeY() {
	return this->sizeY;
}

void  Decor::SetTexture(TextureRef texture) {
	this->texture = texture;
}
TextureRef  Decor::GetTexture() {
	return this->texture;
}

void  Decor::SetHitbox(polygon hitbox) {
	this->hitbox = hitbox;
}
polygon  Decor::GetHitBox() {
	return this->hitbox;
}