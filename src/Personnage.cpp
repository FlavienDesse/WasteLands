#include "Personnage.h"
#include <cstdlib>
#include "cinder/app/App.h"
typedef boost::geometry::model::d2::point_xy<double> point;
typedef boost::geometry::model::polygon< point > polygon;
Personnage::Personnage() :allTouches(102, -12, -11, 10, -9, -5, -6, -7, -8, 275, 273, 276, 274, 32, -1, -2, -3, -4, 304,103) {}

Touches Personnage::GetallTouches() {
	return this->allTouches;
}



std::string GetFileExtension(const std::string& FileName)
{
	if (FileName.find_last_of(".") != std::string::npos) {
		return FileName.substr(FileName.find_last_of(".") + 1);
	}
		
	
	return "";
}


void Personnage::SetWalkJump(short int value) {
	this->walkJump = value;
}
short int Personnage::GetWalkJump() {
	return this->walkJump;
}

void Personnage::SetCollision(bool collision) {
	this->collision = collision;
}


void Personnage::SetPositionActualAnimation(int pos ) {
	if (pos != -1) {
		this->positionActualAnimation = pos;
	}
	if (this->etatActuel == "WalkR") {
		this->SetCanChangeAnimationn(true);
		if (this->animation[this->etatActuel].size() -1 > this->positionActualAnimation) {
			
			this->velocityX = DEPLACEMENTWALKX;
			
				
			

			this->positionActualAnimation++;
		}
		else {
			this->positionActualAnimation = 0;
			this->SetEtatActuel("StandR");
		}
	}
	else if (this->etatActuel == "WalkL") {
		
		this->SetCanChangeAnimationn(true);
		if (this->animation[this->etatActuel].size() - 1 > this->positionActualAnimation) {
			this->velocityX = -DEPLACEMENTWALKX;
			this->positionActualAnimation++;
		}
		else {
			this->positionActualAnimation = 0;
			this->SetEtatActuel("StandL");
		}
	}
	else if (this->etatActuel == "WalkB") {

		this->SetCanChangeAnimationn(true);
		if (this->animation[this->etatActuel].size() - 1 > this->positionActualAnimation) {
		
			this->velocityY = DEPLACEMENTWALKY;
			this->positionActualAnimation++;
		}
		else {
			this->positionActualAnimation = 0;
			this->SetEtatActuel("StandB");
		}
	}
	else if (this->etatActuel == "WalkT") {

		this->SetCanChangeAnimationn(true);
		if (this->animation[this->etatActuel].size() - 1 > this->positionActualAnimation) {
			this->velocityY = -DEPLACEMENTWALKY;
			this->positionActualAnimation++;
		}
		else {
			this->positionActualAnimation = 0;
			this->SetEtatActuel("StandT");
		}
	}
	else if (this->etatActuel == "RunR") {
		this->SetCanChangeAnimationn(true);
		if (this->animation[this->etatActuel].size() - 1 > this->positionActualAnimation) {
			
			this->velocityX = DEPLACEMENTRUNX;
			this->positionActualAnimation++;
		}
		else {
			this->positionActualAnimation = 0;
			this->SetEtatActuel("StandR");
		}
	}
	else if (this->etatActuel == "RunL") {
		this->SetCanChangeAnimationn(true);
		if (this->animation[this->etatActuel].size() - 1 > this->positionActualAnimation) {
			this->velocityX = -DEPLACEMENTRUNX;
			this->positionActualAnimation++;
		}
		else {
			this->positionActualAnimation = 0;
			this->SetEtatActuel("StandL");
		}
	}
	else if (this->etatActuel == "RunT") {
		this->SetCanChangeAnimationn(true);
		if (this->animation[this->etatActuel].size() - 1 > this->positionActualAnimation) {
			this->velocityY = -DEPLACEMENTRUNY;
			this->positionActualAnimation++;
		}
		else {
			this->positionActualAnimation = 0;
			this->SetEtatActuel("StandT");
		}
	}
	else if (this->etatActuel == "RunB") {
		this->SetCanChangeAnimationn(true);
		if (this->animation[this->etatActuel].size() - 1 > this->positionActualAnimation) {
			this->velocityY = DEPLACEMENTRUNY;
			this->positionActualAnimation++;
		}
		else {
			this->positionActualAnimation = 0;
			this->SetEtatActuel("StandB");
		}
	}
	else if (this->etatActuel == "JumpR") {
		if (this->GetWalkJump() == 1) {
		
			this->velocityX = DEPLACEMENTJUMPWALKX;
		}
		else if (this->GetWalkJump() == 2) {
			this->velocityX = DEPLACEMENTJUMPRUNX;
			
		}
		if (this->animation[this->etatActuel].size() - 1 > this->positionActualAnimation) {
			this->SetCanChangeAnimationn(false);
			this->positionActualAnimation++;
		}
		else {
			this->SetCanChangeAnimationn(true);
			this->positionActualAnimation = 0;
			this->SetWalkJump(false);
			this->SetEtatActuel("StandR");
		}
	}
	else if (this->etatActuel == "JumpL") {
		if (this->GetWalkJump() == 1) {
			this->velocityX =- DEPLACEMENTJUMPWALKX;
		}
		else if (this->GetWalkJump() == 2) {
			this->velocityX =- DEPLACEMENTJUMPRUNX;
		}
		if (this->animation[this->etatActuel].size() - 1 > this->positionActualAnimation) {
			this->SetCanChangeAnimationn(false);
			this->positionActualAnimation++;
		}
		else {
			this->SetCanChangeAnimationn(true);
			this->positionActualAnimation = 0;
			this->SetWalkJump(false);
			this->SetEtatActuel("StandL");
		}
	}
	else if (this->etatActuel == "JumpT") {
	if (this->GetWalkJump() == 1) {
		this->velocityY = -DEPLACEMENTJUMPWALKY;
	}
	else if (this->GetWalkJump() == 2) {
		this->velocityY= -DEPLACEMENTJUMPRUNY;
	}
	if (this->animation[this->etatActuel].size() - 1 > this->positionActualAnimation) {
		this->SetCanChangeAnimationn(false);
		this->positionActualAnimation++;
	}
	else {
		this->SetCanChangeAnimationn(true);
		this->positionActualAnimation = 0;
		this->SetWalkJump(false);
		this->SetEtatActuel("StandT");
	}
	}
	else if (this->etatActuel == "JumpB") {
	if (this->GetWalkJump() == 1) {
		this->velocityY = DEPLACEMENTJUMPWALKY;
	}
	else if (this->GetWalkJump() == 2) {
		this->velocityY = DEPLACEMENTJUMPRUNY;
	}
	if (this->animation[this->etatActuel].size() - 1 > this->positionActualAnimation) {
		this->SetCanChangeAnimationn(false);
		this->positionActualAnimation++;
	}
	else {
		this->SetCanChangeAnimationn(true);
		this->positionActualAnimation = 0;
		this->SetWalkJump(false);
		this->SetEtatActuel("StandB");
	}
	}
	else if (this->etatActuel == "JumpTR") {
	if (this->GetWalkJump() == 1) {
		this->velocityX = DEPLACEMENTJUMPWALKX / 2;
		this->velocityY =- DEPLACEMENTJUMPWALKY / 2;
		
	}
	else if (this->GetWalkJump() == 2) {
		this->velocityX = DEPLACEMENTJUMPRUNX / 2;
		this->velocityY = -DEPLACEMENTJUMPRUNY / 2;
	}
	if (this->animation[this->etatActuel].size() - 1 > this->positionActualAnimation) {
		this->SetCanChangeAnimationn(false);
		this->positionActualAnimation++;
	}
	else {
		this->SetCanChangeAnimationn(true);
		this->positionActualAnimation = 0;
		this->SetWalkJump(false);
		this->SetEtatActuel("StandR");
	}
	}
	else if (this->etatActuel == "JumpTL") {
	if (this->GetWalkJump() == 1) {
		this->velocityX = -DEPLACEMENTJUMPWALKX / 2;
		this->velocityY = -DEPLACEMENTJUMPWALKY / 2;
	}
	else if (this->GetWalkJump() == 2) {
		this->velocityX = -DEPLACEMENTJUMPRUNX / 2;
		this->velocityY = -DEPLACEMENTJUMPRUNY / 2;
	}
	if (this->animation[this->etatActuel].size() - 1 > this->positionActualAnimation) {
		this->SetCanChangeAnimationn(false);
		this->positionActualAnimation++;
	}
	else {
		this->SetCanChangeAnimationn(true);
		this->positionActualAnimation = 0;
		this->SetWalkJump(false);
		this->SetEtatActuel("StandL");
	}
	}
	else if (this->etatActuel == "JumpBL") {
	if (this->GetWalkJump() == 1) {
		this->velocityX = -DEPLACEMENTJUMPWALKX / 2;
		this->velocityY = +DEPLACEMENTJUMPWALKY / 2;
	}
	else if (this->GetWalkJump() == 2) {
		this->velocityX = -DEPLACEMENTJUMPRUNX / 2;
		this->velocityY = +DEPLACEMENTJUMPRUNY / 2;
	}
	if (this->animation[this->etatActuel].size() - 1 > this->positionActualAnimation) {
		this->SetCanChangeAnimationn(false);
		this->positionActualAnimation++;
	}
	else {
		this->SetCanChangeAnimationn(true);
		this->positionActualAnimation = 0;
		this->SetWalkJump(false);
		this->SetEtatActuel("StandL");
	}
	}
	else if (this->etatActuel == "JumpBR") {
	if (this->GetWalkJump() == 1) {
		this->velocityX = +DEPLACEMENTJUMPWALKX / 2;
		this->velocityY = +DEPLACEMENTJUMPWALKY / 2;
	}
	else if (this->GetWalkJump() == 2) {
		this->velocityX = +DEPLACEMENTJUMPRUNX / 2;
		this->velocityY = +DEPLACEMENTJUMPRUNY / 2;
	}
	if (this->animation[this->etatActuel].size() - 1 > this->positionActualAnimation) {
		this->SetCanChangeAnimationn(false);
		this->positionActualAnimation++;
	}
	else {
		this->SetCanChangeAnimationn(true);
		this->positionActualAnimation = 0;
		this->SetWalkJump(false);
		this->SetEtatActuel("StandR");
	}
	}
	else if (this->etatActuel == "WalkTR") {
		this->SetCanChangeAnimationn(true);
		if (this->animation[this->etatActuel].size() - 1 > this->positionActualAnimation) {
			this->velocityX = +DEPLACEMENTWALKX / 2;
			this->velocityY = -DEPLACEMENTWALKY / 2;
			this->positionActualAnimation++;
		
		}
		else {
			this->positionActualAnimation = 0;
			this->SetEtatActuel("StandR");
		}
	}
	else if (this->etatActuel == "WalkTL") {
	this->SetCanChangeAnimationn(true);
	if (this->animation[this->etatActuel].size() - 1 > this->positionActualAnimation) {
		this->velocityX = -DEPLACEMENTWALKX / 2;
		this->velocityY = -DEPLACEMENTWALKY / 2;
		this->positionActualAnimation++;

	}
	else {
		this->positionActualAnimation = 0;
		this->SetEtatActuel("StandL");
	}
	}
	else if (this->etatActuel == "WalkBL") {
	this->SetCanChangeAnimationn(true);
	if (this->animation[this->etatActuel].size() - 1 > this->positionActualAnimation) {
		this->velocityX = -DEPLACEMENTWALKX / 2;
		this->velocityY = +DEPLACEMENTWALKY / 2;
		this->positionActualAnimation++;

	}
	else {
		this->positionActualAnimation = 0;
		this->SetEtatActuel("StandL");
	}
	}
	else if (this->etatActuel == "WalkBR") {
	this->SetCanChangeAnimationn(true);
	if (this->animation[this->etatActuel].size() - 1 > this->positionActualAnimation) {
		this->velocityX = +DEPLACEMENTWALKX / 2;
		this->velocityY = +DEPLACEMENTWALKY / 2;
		this->positionActualAnimation++;

	}
	else {
		this->positionActualAnimation = 0;
		this->SetEtatActuel("StandR");
	}
	}
	else if (this->etatActuel == "RunTL") {
	this->SetCanChangeAnimationn(true);
	if (this->animation[this->etatActuel].size() - 1 > this->positionActualAnimation) {
		this->velocityX = -DEPLACEMENTRUNX / 2;
		this->velocityY = -DEPLACEMENTRUNY / 2;
		this->positionActualAnimation++;
	}
	else {
		this->positionActualAnimation = 0;
		this->SetEtatActuel("StandR");
	}
	}
	else if (this->etatActuel == "RunTR") {
	this->SetCanChangeAnimationn(true);
	if (this->animation[this->etatActuel].size() - 1 > this->positionActualAnimation) {
		this->velocityX = +DEPLACEMENTRUNX / 2;
		this->velocityY = -DEPLACEMENTRUNY / 2;
		this->positionActualAnimation++;
	}
	else {
		this->positionActualAnimation = 0;
		this->SetEtatActuel("StandL");
	}
	}
	else if (this->etatActuel == "RunBL") {
	this->SetCanChangeAnimationn(true);
	if (this->animation[this->etatActuel].size() - 1 > this->positionActualAnimation) {
		this->velocityX = -DEPLACEMENTRUNX / 2;
		this->velocityY = +DEPLACEMENTRUNY / 2;
		this->positionActualAnimation++;
	}
	else {
		
		this->positionActualAnimation = 0;
		this->SetEtatActuel("StandL");
	}
	}
	else if (this->etatActuel == "RunBR") {
	this->SetCanChangeAnimationn(true);
	if (this->animation[this->etatActuel].size() - 1 > this->positionActualAnimation) {
		this->velocityX = +DEPLACEMENTRUNX / 2;
		this->velocityY = +DEPLACEMENTRUNY / 2;
		this->positionActualAnimation++;
	}
	else {
		this->positionActualAnimation = 0;
		this->SetEtatActuel("StandR");
	}
	}

	else if (this->etatActuel == "ShotR") {
	this->SetCanChangeAnimationn(false);
		if (this->animation[this->etatActuel].size() - 1 > this->positionActualAnimation) {
			this->positionActualAnimation++;
		}
		else {
			this->positionActualAnimation = 0;
			this->projectile[0].SetPosX(this->GetPosX());
			this->projectile[0].SetPosY(this->GetPosY());
			this->projectile[0].SetDommage(this->degat);
			this->projectile[0].SetSpeedX(10);
			this->projectile[0].SetSpeedY(0);
			this->projectile[0].SetOrientation(0 * -M_PI / 2);
			this->projectile[0].SetSource("MainCharacter " + this->GetAura().GetActualArea() );
			this->projectile[0].SetStartTime(getElapsedSeconds());
			this->pointerToAllProjectile->push_back(this->projectile[0]);
			this->SetEtatActuel("StandR");
		}
	}
	else if (this->etatActuel == "ShotT") {
	this->SetCanChangeAnimationn(false);
	if (this->animation[this->etatActuel].size() - 1 > this->positionActualAnimation) {
		this->positionActualAnimation++;
	}
	else {
		this->positionActualAnimation = 0;
		this->projectile[0].SetPosX(this->GetPosX());
		this->projectile[0].SetPosY(this->GetPosY());
		this->projectile[0].SetSpeedX(0);
		this->projectile[0].SetDommage(this->degat);
		this->projectile[0].SetSpeedY(-10);
		this->projectile[0].SetOrientation(1*-M_PI/2);
		this->projectile[0].SetSource("MainCharacter " + this->GetAura().GetActualArea());
		this->projectile[0].SetStartTime(getElapsedSeconds());
		this->pointerToAllProjectile->push_back(this->projectile[0]);
		this->SetEtatActuel("StandT");
	}
	}
	else if (this->etatActuel == "ShotL") {
	this->SetCanChangeAnimationn(false);
	if (this->animation[this->etatActuel].size() - 1 > this->positionActualAnimation) {
		this->positionActualAnimation++;
	}
	else {
		this->positionActualAnimation = 0;
		this->projectile[0].SetPosX(this->GetPosX());
		this->projectile[0].SetPosY(this->GetPosY());
		this->projectile[0].SetSpeedX(-10);
		this->projectile[0].SetSpeedY(0);
		this->projectile[0].SetDommage(this->degat);
		this->projectile[0].SetOrientation(2 * -M_PI / 2);
		this->projectile[0].SetSource("MainCharacter " + this->GetAura().GetActualArea());
		this->projectile[0].SetStartTime(getElapsedSeconds());
		this->pointerToAllProjectile->push_back(this->projectile[0]);
		this->SetEtatActuel("StandL");
	}
	}
	else if (this->etatActuel == "ShotB") {
	this->SetCanChangeAnimationn(false);
	if (this->animation[this->etatActuel].size() - 1 > this->positionActualAnimation) {
		this->positionActualAnimation++;
	}
	else {
		this->positionActualAnimation = 0;
		this->projectile[0].SetPosX(this->GetPosX());
		this->projectile[0].SetPosY(this->GetPosY());
		this->projectile[0].SetSpeedX(0);
		this->projectile[0].SetSpeedY(10);
		this->projectile[0].SetDommage(this->degat);
		this->projectile[0].SetOrientation(3 * -M_PI / 2);
		this->projectile[0].SetSource("MainCharacter "+this->GetAura().GetActualArea() );
		this->projectile[0].SetStartTime(getElapsedSeconds());
		this->pointerToAllProjectile->push_back(this->projectile[0]);
		this->SetEtatActuel("StandB");
	}
	}
	else if (this->etatActuel == "ShotTR") {
	this->SetCanChangeAnimationn(false);
	if (this->animation[this->etatActuel].size() - 1 > this->positionActualAnimation) {
		this->positionActualAnimation++;
	}
	else {
		this->positionActualAnimation = 0;
		this->projectile[0].SetPosX(this->GetPosX());
		this->projectile[0].SetPosY(this->GetPosY());
		this->projectile[0].SetSpeedX(10);
		this->projectile[0].SetOrientation(0.5*-M_PI / 2);
		this->projectile[0].SetSpeedY(-10);
		this->projectile[0].SetDommage(this->degat);
		this->projectile[0].SetSource("MainCharacter " + this->GetAura().GetActualArea() );
		this->projectile[0].SetStartTime(getElapsedSeconds());
		this->pointerToAllProjectile->push_back(this->projectile[0]);
		this->SetEtatActuel("StandTR");
	}
	}
	else if (this->etatActuel == "ShotTL") {
	this->SetCanChangeAnimationn(false);
	if (this->animation[this->etatActuel].size() - 1 > this->positionActualAnimation) {
		this->positionActualAnimation++;
	}
	else {
		this->positionActualAnimation = 0;
		this->projectile[0].SetPosX(this->GetPosX());
		this->projectile[0].SetPosY(this->GetPosY());
		this->projectile[0].SetSpeedX(-10);
		this->projectile[0].SetSpeedY(-10);
		this->projectile[0].SetDommage(this->degat);
		this->projectile[0].SetOrientation(1.5*-M_PI / 2);
		this->projectile[0].SetSource("MainCharacter " + this->GetAura().GetActualArea());
		this->projectile[0].SetStartTime(getElapsedSeconds());
		this->pointerToAllProjectile->push_back(this->projectile[0]);
		this->SetEtatActuel("StandTL");
	}
	}
	else if (this->etatActuel == "ShotBL") {
	this->SetCanChangeAnimationn(false);
	if (this->animation[this->etatActuel].size() - 1 > this->positionActualAnimation) {
		this->positionActualAnimation++;
	}
	else {
		this->positionActualAnimation = 0;
		this->projectile[0].SetPosX(this->GetPosX());
		this->projectile[0].SetPosY(this->GetPosY());
		this->projectile[0].SetSpeedX(-10);
		this->projectile[0].SetOrientation(2.5*-M_PI / 2);
		this->projectile[0].SetSpeedY(10);
		this->projectile[0].SetDommage(this->degat);
		this->projectile[0].SetSource("MainCharacter " + this->GetAura().GetActualArea());
		this->projectile[0].SetStartTime(getElapsedSeconds());
		this->pointerToAllProjectile->push_back(this->projectile[0]);
		this->SetEtatActuel("StandBL");
	}
	}
	else if (this->etatActuel == "ShotBR") {
	this->SetCanChangeAnimationn(false);
	if (this->animation[this->etatActuel].size() - 1 > this->positionActualAnimation) {
		this->positionActualAnimation++;
	}
	else {
		this->positionActualAnimation = 0;
		this->projectile[0].SetPosX(this->GetPosX());
		this->projectile[0].SetPosY(this->GetPosY());
		this->projectile[0].SetSpeedX(10);
		this->projectile[0].SetOrientation(3.5*-M_PI / 2);
		this->projectile[0].SetSpeedY(10);
		this->projectile[0].SetDommage(this->degat);
		this->projectile[0].SetSource("MainCharacter " + this->GetAura().GetActualArea());
		this->projectile[0].SetStartTime(getElapsedSeconds());
		this->pointerToAllProjectile->push_back(this->projectile[0]);
		this->SetEtatActuel("StandBR");
	}
	}
	else {
		SetCanChangeAnimationn(true);
		if (this->animation[this->etatActuel].size() - 1 > this->positionActualAnimation) {
			this->positionActualAnimation++;
		}
		else {
			this->positionActualAnimation = 0;
		}
	}


}

void Personnage::SetVelocityX(double velocityX) {
	this->velocityX = velocityX;
}

void Personnage::SetVelocityY(double velocityY) {
	this->velocityY= velocityY;
}


double Personnage::GetVelocityX() {
	return this->velocityX;
}


double Personnage::GetVelocityY() {
	return this->velocityY;
}

map<string, vector <pair <ci::gl::TextureRef,polygon>>> &  Personnage::GetAnimation() {
	return this->animation;
}

bool Personnage::GetCanChangeAnimation() {
	return this->canChangeAnimation;
}
void Personnage::SetCanChangeAnimationn(bool value) {
	this->canChangeAnimation = value;
}

void Personnage::SetActualAnimation() {
	this->actualAnimation = this->animation[this->GetEtatActuel()][this->positionActualAnimation];
}
string Personnage::GetEtatActuel() {
	return this->etatActuel;
}
void Personnage::SetEtatActuel(string etat) {
	this->etatActuel = etat;
}

pair <ci::gl::TextureRef, polygon> Personnage::GetActualAnimation() {
	return this->actualAnimation;
}
int Personnage::GetPositionActualAnimation() {
	return this->positionActualAnimation;
}
double Personnage::GetVie() {
	return this->vie;
}

double Personnage::GetDegat() {
	return this->degat;
}
double Personnage::GetArmure() {
	return this->armure;
}

void Personnage::SetPosX(double posX) {
	this->posX = posX;
}
void  Personnage::SetPosY(double posY) {
	this->posY = posY;
}
double Personnage::GetPosX() {
	return this->posX;
}
double Personnage::GetPosY() {
	return this->posY;
}

void Personnage::SetVie(double vie) {
	this->vie = vie;
}

void Personnage::SetDegat(double degat) {
	this->degat = degat;
}
void Personnage::SetArmure(double armure) {
	this->armure = armure;
}
float Personnage::GetOrientation() {
	return this->orientation;
}

void Personnage::SetOrientation(float value) {
	this->orientation= value;
}

void Personnage::ReceiveDegat(int degat) {
	double vieTemp = this->vie - degat;
	if (vieTemp <= 0) {
		/* TODO

		on est mort - checkpoint 
		
		
		*/
	}
	else {
		this->vie = vieTemp;
	}
	
}


Timer & Personnage::GetClockAnimation() {
	return this->clockAnimation;
}
void Personnage::SetPositionWhenStopPush(std::map<int, bool> touchPressed) {
	string etatActuel = this->GetEtatActuel();
	if (touchPressed.find(this->allTouches.GetValueTouche("RunR")) != touchPressed.end() && etatActuel == "RunR" && touchPressed[this->allTouches.GetValueTouche("RunR")] != true) {
		this->SetOrientation(0);
		this->SetEtatActuel("StandR");
		this->SetPositionActualAnimation(0);
	}
	else if (touchPressed.find(this->allTouches.GetValueTouche("WalkR")) != touchPressed.end() && etatActuel == "WalkR" && touchPressed[this->allTouches.GetValueTouche("WalkR")] != true) {
		this->SetOrientation(0);
		this->SetEtatActuel("StandR");
		this->SetPositionActualAnimation(0);
	}

	else if (touchPressed.find(this->allTouches.GetValueTouche("RunL")) != touchPressed.end() && etatActuel == "RunL" && touchPressed[this->allTouches.GetValueTouche("RunL")] != true) {
		this->SetOrientation(2);
		this->SetEtatActuel("StandL");
		this->SetPositionActualAnimation(0);
	}
	else if (touchPressed.find(this->allTouches.GetValueTouche("WalkL")) != touchPressed.end() && etatActuel == "WalkL" && touchPressed[this->allTouches.GetValueTouche("WalkL")] != true) {
		this->SetOrientation(2);
		this->SetEtatActuel("StandL");
		this->SetPositionActualAnimation(0);
	}

	if (touchPressed.find(this->allTouches.GetValueTouche("RunT")) != touchPressed.end() && etatActuel == "RunT" && touchPressed[this->allTouches.GetValueTouche("RunT")] != true) {
		this->SetOrientation(1);
		this->SetEtatActuel("StandT");
		this->SetPositionActualAnimation(0);
	}
	else if (touchPressed.find(this->allTouches.GetValueTouche("WalkT")) != touchPressed.end() && etatActuel == "WalkT" && touchPressed[this->allTouches.GetValueTouche("WalkT")] != true) {
		this->SetOrientation(1);
		this->SetEtatActuel("StandT");
		this->SetPositionActualAnimation(0);
	}

	if (touchPressed.find(this->allTouches.GetValueTouche("RunB")) != touchPressed.end() && etatActuel == "RunB" && touchPressed[this->allTouches.GetValueTouche("RunB")] != true) {
		this->SetOrientation(3);
		this->SetEtatActuel("StandB");
		this->SetPositionActualAnimation(0);
	}
	else if (touchPressed.find(this->allTouches.GetValueTouche("WalkB")) != touchPressed.end() && etatActuel == "WalkB" && touchPressed[this->allTouches.GetValueTouche("WalkB")] != true) {
		this->SetOrientation(3);
		this->SetEtatActuel("StandB");
		this->SetPositionActualAnimation(0);
	}

	if (touchPressed.find(this->allTouches.GetValueTouche("RunTL")) != touchPressed.end() && etatActuel == "RunTL" && touchPressed[this->allTouches.GetValueTouche("RunTL")] != true) {
		this->SetOrientation(2);
		this->SetEtatActuel("StandL");
		this->SetPositionActualAnimation(0);
	}
	else if (touchPressed.find(this->allTouches.GetValueTouche("WalkTL")) != touchPressed.end() && etatActuel == "WalkTL" && touchPressed[this->allTouches.GetValueTouche("WalkTL")] != true) {
		this->SetOrientation(2);
		this->SetEtatActuel("StandL");
		this->SetPositionActualAnimation(0);
	}

	if (touchPressed.find(this->allTouches.GetValueTouche("RunTR")) != touchPressed.end() && etatActuel == "RunTR" && touchPressed[this->allTouches.GetValueTouche("RunTR")] != true) {
		this->SetOrientation(0);
		this->SetEtatActuel("StandR");
		this->SetPositionActualAnimation(0);
	}
	else if (touchPressed.find(this->allTouches.GetValueTouche("WalkTR")) != touchPressed.end() && etatActuel == "WalkTR" && touchPressed[this->allTouches.GetValueTouche("WalkTR")] != true) {
		this->SetOrientation(0);
		this->SetEtatActuel("StandR");
		this->SetPositionActualAnimation(0);
	}

	if (touchPressed.find(this->allTouches.GetValueTouche("RunBR")) != touchPressed.end() && etatActuel == "RunBR" && touchPressed[this->allTouches.GetValueTouche("RunBR")] != true) {
		this->SetOrientation(0);
		this->SetEtatActuel("StandR");
		this->SetPositionActualAnimation(0);
	}
	else if (touchPressed.find(this->allTouches.GetValueTouche("WalkBR")) != touchPressed.end() && etatActuel == "WalkBR" && touchPressed[this->allTouches.GetValueTouche("WalkBR")] != true) {
		this->SetOrientation(0);
		this->SetEtatActuel("StandR");
		this->SetPositionActualAnimation(0);
	}

	if (touchPressed.find(this->allTouches.GetValueTouche("RunBL")) != touchPressed.end() && etatActuel == "RunBL" && touchPressed[this->allTouches.GetValueTouche("RunBL")] != true) {
		this->SetOrientation(2);
		this->SetEtatActuel("StandL");
		this->SetPositionActualAnimation(0);
	}
	else if (touchPressed.find(this->allTouches.GetValueTouche("WalkBL")) != touchPressed.end() && etatActuel == "WalkBL" && touchPressed[this->allTouches.GetValueTouche("WalkBL")] != true) {
		this->SetOrientation(2);
		this->SetEtatActuel("StandL");
		this->SetPositionActualAnimation(0);
	}

}
void Personnage::JumpFonction(std::map<int, bool> touchPressed) {
	string etatActuel = this->GetEtatActuel();
	if (touchPressed[this->allTouches.GetValueTouche("Jump")] == true) {

		if (this->GetOrientation() == 0 && ((etatActuel != "JumpR") || (etatActuel == "JumpR" && (this->GetAnimation()["JumpR"].size() - 1 == this->GetPositionActualAnimation()))))
		{
			if (touchPressed[this->allTouches.GetValueTouche("WalkR")] != true || touchPressed[this->allTouches.GetValueTouche("WalkL")] != true) {
				if (touchPressed[this->allTouches.GetValueTouche("RunR")] == true) {
					this->SetWalkJump(2);
				}
				else if (touchPressed[this->allTouches.GetValueTouche("WalkR")] == true) {

					this->SetWalkJump(1);
				}
			}
			else {
				this->SetWalkJump(false);
			}
			this->SetEtatActuel("JumpR");
			this->SetPositionActualAnimation(0);
		}
		else if (this->GetOrientation() == 0.5 && ((etatActuel != "JumpTR") || (etatActuel == "JumpTR" && (this->GetAnimation()["JumpTR"].size() - 1 == this->GetPositionActualAnimation()))))
		{
			if (touchPressed[this->allTouches.GetValueTouche("RunTR")] == true) {
				this->SetWalkJump(2);
			}
			else if (touchPressed[this->allTouches.GetValueTouche("WalkTR")] == true) {

				this->SetWalkJump(1);
			}
			else {
				this->SetWalkJump(false);
			}
			this->SetEtatActuel("JumpTR");
			this->SetPositionActualAnimation(0);
		}
		else if (this->GetOrientation() == 1 && ((etatActuel != "JumpT") || (etatActuel == "JumpT" && (this->GetAnimation()["JumpT"].size() - 1 == this->GetPositionActualAnimation()))))
		{
			if (touchPressed[this->allTouches.GetValueTouche("WalkT")] != true || touchPressed[this->allTouches.GetValueTouche("WalkB")] != true) {
				if (touchPressed[this->allTouches.GetValueTouche("RunT")] == true) {
					this->SetWalkJump(2);
				}
				else if (touchPressed[this->allTouches.GetValueTouche("WalkT")] == true) {
					this->SetWalkJump(1);
				}
			}
			else {
				this->SetWalkJump(false);
			}
			this->SetEtatActuel("JumpT");
			this->SetPositionActualAnimation(0);
		}
		else if (this->GetOrientation() == 1.5 && ((etatActuel != "JumpTL") || (etatActuel == "JumpTL" && (this->GetAnimation()["JumpTL"].size() - 1 == this->GetPositionActualAnimation()))))
		{
			if (touchPressed[this->allTouches.GetValueTouche("RunTL")] == true) {
				this->SetWalkJump(2);
			}
			else if (touchPressed[this->allTouches.GetValueTouche("WalkTL")] == true) {

				this->SetWalkJump(1);
			}

			else {
				this->SetWalkJump(false);
			}
			this->SetEtatActuel("JumpTL");
			this->SetPositionActualAnimation(0);
		}
		else if (this->GetOrientation() == 2 && ((etatActuel != "JumpL") || (etatActuel == "JumpL" && (this->GetAnimation()["JumpL"].size() - 1 == this->GetPositionActualAnimation()))))
		{
			if (touchPressed[this->allTouches.GetValueTouche("WalkL")] != true || touchPressed[this->allTouches.GetValueTouche("WalkR")] != true) {
				if (touchPressed[this->allTouches.GetValueTouche("RunL")] == true) {
					this->SetWalkJump(2);
				}
				else if (touchPressed[this->allTouches.GetValueTouche("WalkL")] == true) {
					this->SetWalkJump(1);
				}
			}
			else {
				this->SetWalkJump(false);
			}
			this->SetEtatActuel("JumpL");
			this->SetPositionActualAnimation(0);
		}
		else if (this->GetOrientation() == 2.5 && ((etatActuel != "JumpBL") || (etatActuel == "JumpBL" && (this->GetAnimation()["JumpBL"].size() - 1 == this->GetPositionActualAnimation()))))
		{

			if (touchPressed[this->allTouches.GetValueTouche("RunBL")] == true) {
				this->SetWalkJump(2);
			}
			else if (touchPressed[this->allTouches.GetValueTouche("WalkBL")] == true) {

				this->SetWalkJump(1);
			}

			else {
				this->SetWalkJump(false);
			}
			this->SetEtatActuel("JumpBL");
			this->SetPositionActualAnimation(0);
		}
		else if (this->GetOrientation() == 3 && ((etatActuel != "JumpB") || (etatActuel == "JumpB" && (this->GetAnimation()["JumpB"].size() - 1 == this->GetPositionActualAnimation()))))
		{
			if (touchPressed[this->allTouches.GetValueTouche("WalkB")] != true || touchPressed[this->allTouches.GetValueTouche("WalkT")] != true) {
				if (touchPressed[this->allTouches.GetValueTouche("WalkB")] == true) {
					this->SetWalkJump(1);
				}
				else if (touchPressed[this->allTouches.GetValueTouche("RunB")] == true) {
					this->SetWalkJump(2);
				}
			}
			else {
				this->SetWalkJump(false);
			}
			this->SetEtatActuel("JumpB");
			this->SetPositionActualAnimation(0);
		}
		else if (this->GetOrientation() == 3.5 && ((etatActuel != "JumpBR") || (etatActuel == "JumpBR" && (this->GetAnimation()["JumpBR"].size() - 1 == this->GetPositionActualAnimation()))))
		{
			if (touchPressed[this->allTouches.GetValueTouche("RunBR")] == true) {
				this->SetWalkJump(2);
			}
			else if (touchPressed[this->allTouches.GetValueTouche("WalkBR")] == true) {

				this->SetWalkJump(1);
			}

			else {
				this->SetWalkJump(false);
			}
			this->SetEtatActuel("JumpBR");
			this->SetPositionActualAnimation(0);
		}
	}
}
bool Personnage::SetStandIfWalkOpposite(std::map<int, bool> touchPressed) {
	string etatActuel = this->GetEtatActuel();
	if (touchPressed[this->allTouches.GetValueTouche("WalkL")] == true && touchPressed[this->allTouches.GetValueTouche("WalkR")] == true) {
		if (this->GetOrientation() == 0 && (etatActuel != "StandR" || (etatActuel == "StandR" && (this->GetAnimation()["StandR"].size() - 1 == this->GetPositionActualAnimation())))) {
			this->SetEtatActuel("StandR");
			this->SetOrientation(0);
			this->SetPositionActualAnimation(0);

		}
		else if (this->GetOrientation() == 2 && (etatActuel != "StandL" || (etatActuel == "StandL" && (this->GetAnimation()["StandL"].size() - 1 == this->GetPositionActualAnimation())))) {
			this->SetEtatActuel("StandL");
			this->SetOrientation(2);
			this->SetPositionActualAnimation(0);

		}
		return true;
	}

	else if (touchPressed[this->allTouches.GetValueTouche("WalkT")] == true && touchPressed[this->allTouches.GetValueTouche("WalkB")] == true) {
		if (this->GetOrientation() == 3 && (etatActuel != "StandB" || (etatActuel == "StandB" && (this->GetAnimation()["StandB"].size() - 1 == this->GetPositionActualAnimation())))) {
			this->SetEtatActuel("StandB");
			this->SetOrientation(3);
			this->SetPositionActualAnimation(0);
			return true;
		}
		else if (this->GetOrientation() == 1 && (etatActuel != "StandT" || (etatActuel == "StandT" && (this->GetAnimation()["StandT"].size() - 1 == this->GetPositionActualAnimation())))) {
			this->SetEtatActuel("StandT");
			this->SetOrientation(1);
			this->SetPositionActualAnimation(0);
		}
		return true;
	}
	return false;
}
void Personnage::SetWalk(std::map<int, bool> touchPressed) {
	string etatActuel = this->GetEtatActuel();
	if (touchPressed[this->allTouches.GetValueTouche("WalkR")] == true && ((touchPressed.find(this->allTouches.GetValueTouche("WalkR")) != touchPressed.end() && etatActuel != "WalkR" &&etatActuel != "RunR") || (etatActuel == "WalkR" && (this->GetAnimation()["WalkR"].size() - 1 == this->GetPositionActualAnimation())))) {
		this->SetOrientation(0);
		this->SetEtatActuel("WalkR");
		this->SetPositionActualAnimation(0);
	}
	else if (touchPressed[this->allTouches.GetValueTouche("WalkL")] == true && ((touchPressed.find(this->allTouches.GetValueTouche("WalkL")) != touchPressed.end() && etatActuel != "WalkL" &&etatActuel != "RunL") || (etatActuel == "WalkL" && (this->GetAnimation()["WalkL"].size() - 1 == this->GetPositionActualAnimation())))) {
		this->SetOrientation(2);
		this->SetEtatActuel("WalkL");
		this->SetPositionActualAnimation(0);

	}

	if (touchPressed[this->allTouches.GetValueTouche("WalkT")] == true && ((touchPressed.find(this->allTouches.GetValueTouche("WalkT")) != touchPressed.end() && etatActuel != "WalkT" &&etatActuel != "RunT") || (etatActuel == "WalkT" && (this->GetAnimation()["WalkT"].size() - 1 == this->GetPositionActualAnimation())))) {
		this->SetOrientation(1);
		this->SetEtatActuel("WalkT");
		this->SetPositionActualAnimation(0);
	}
	else if (touchPressed[this->allTouches.GetValueTouche("WalkB")] == true && ((touchPressed.find(this->allTouches.GetValueTouche("WalkB")) != touchPressed.end() && etatActuel != "WalkB" &&etatActuel != "RunB") || (etatActuel == "WalkB" && (this->GetAnimation()["WalkB"].size() - 1 == this->GetPositionActualAnimation())))) {
		this->SetOrientation(3);
		this->SetEtatActuel("WalkB");
		this->SetPositionActualAnimation(0);
	}

}
bool Personnage::SetRun(std::map<int, bool> touchPressed) {
	string etatActuel = this->GetEtatActuel();
	if (touchPressed[this->allTouches.GetValueTouche("RunR")] == true || touchPressed[this->allTouches.GetValueTouche("RunT")] == true || touchPressed[this->allTouches.GetValueTouche("RunL")] == true || touchPressed[this->allTouches.GetValueTouche("RunB")] == true) {
		if (touchPressed[this->allTouches.GetValueTouche("RunR")] == true && ((touchPressed.find(this->allTouches.GetValueTouche("RunR")) != touchPressed.end() && etatActuel != "RunR") || (etatActuel == "RunR" && (this->GetAnimation()["RunR"].size() - 1 == this->GetPositionActualAnimation())))) {
			this->SetOrientation(0);
			this->SetEtatActuel("RunR");
			this->SetPositionActualAnimation(0);
		}
		else if (touchPressed[this->allTouches.GetValueTouche("RunL")] == true && ((touchPressed.find(this->allTouches.GetValueTouche("RunL")) != touchPressed.end() && etatActuel != "RunL") || (etatActuel == "RunL" && (this->GetAnimation()["RunL"].size() - 1 == this->GetPositionActualAnimation())))) {
			this->SetOrientation(2);
			this->SetEtatActuel("RunL");
			this->SetPositionActualAnimation(0);
		}
		else if (touchPressed[this->allTouches.GetValueTouche("RunT")] == true && ((touchPressed.find(this->allTouches.GetValueTouche("RunT")) != touchPressed.end() && etatActuel != "RunT") || (etatActuel == "RunT" && (this->GetAnimation()["RunT"].size() - 1 == this->GetPositionActualAnimation())))) {
			this->SetOrientation(1);
			this->SetEtatActuel("RunT");
			this->SetPositionActualAnimation(0);
		}
		else if (touchPressed[this->allTouches.GetValueTouche("RunB")] == true && ((touchPressed.find(this->allTouches.GetValueTouche("RunB")) != touchPressed.end() && etatActuel != "RunB") || (etatActuel == "RunB" && (this->GetAnimation()["RunB"].size() - 1 == this->GetPositionActualAnimation())))) {
			this->SetOrientation(3);
			this->SetEtatActuel("RunB");
			this->SetPositionActualAnimation(0);
		}
		return true;
	}
	return false;
}
bool Personnage::SetWalkDiagonal(std::map<int, bool> touchPressed) {
	string etatActuel = this->GetEtatActuel();
	if (touchPressed[this->allTouches.GetValueTouche("WalkBR")] == true || touchPressed[this->allTouches.GetValueTouche("WalkBL")] == true || touchPressed[this->allTouches.GetValueTouche("WalkTR")] == true || touchPressed[this->allTouches.GetValueTouche("WalkTL")] == true) {
		if (touchPressed[this->allTouches.GetValueTouche("WalkTR")] == true && ((touchPressed.find(this->allTouches.GetValueTouche("WalkTR")) != touchPressed.end() && etatActuel != "WalkTR" &&etatActuel != "RunTR") || (etatActuel == "WalkTR" && (this->GetAnimation()["WalkTR"].size() - 1 == this->GetPositionActualAnimation())))) {
			this->SetOrientation(0.5);
			this->SetEtatActuel("WalkTR");
			this->SetPositionActualAnimation(0);
		}
		else if (touchPressed[this->allTouches.GetValueTouche("WalkTL")] == true && ((touchPressed.find(this->allTouches.GetValueTouche("WalkTL")) != touchPressed.end() && etatActuel != "WalkTL" &&etatActuel != "RunTL") || (etatActuel == "WalkTL" && (this->GetAnimation()["WalkTL"].size() - 1 == this->GetPositionActualAnimation())))) {
			this->SetOrientation(1.5);
			this->SetEtatActuel("WalkTL");
			this->SetPositionActualAnimation(0);
		}
		else if (touchPressed[this->allTouches.GetValueTouche("WalkBL")] == true && ((touchPressed.find(this->allTouches.GetValueTouche("WalkBL")) != touchPressed.end() && etatActuel != "WalkBL" &&etatActuel != "RunBL") || (etatActuel == "WalkBL" && (this->GetAnimation()["WalkBL"].size() - 1 == this->GetPositionActualAnimation())))) {
			this->SetOrientation(2.5);
			this->SetEtatActuel("WalkBL");
			this->SetPositionActualAnimation(0);
		}
		else if (touchPressed[this->allTouches.GetValueTouche("WalkBR")] == true && ((touchPressed.find(this->allTouches.GetValueTouche("WalkBR")) != touchPressed.end() && etatActuel != "WalkBR" &&etatActuel != "RunBR") || (etatActuel == "WalkBR" && (this->GetAnimation()["WalkBR"].size() - 1 == this->GetPositionActualAnimation())))) {
			this->SetOrientation(3.5);
			this->SetEtatActuel("WalkBR");
			this->SetPositionActualAnimation(0);
		}
		return true;
	}
	return false;
}
bool Personnage::SetRunDiagonal(std::map<int, bool> touchPressed) {
	string etatActuel = this->GetEtatActuel();

	if (touchPressed[this->allTouches.GetValueTouche("RunTR")] == true || touchPressed[this->allTouches.GetValueTouche("RunTL")] == true || touchPressed[this->allTouches.GetValueTouche("RunBL")] == true || touchPressed[this->allTouches.GetValueTouche("RunBR")] == true) {
		if (touchPressed[this->allTouches.GetValueTouche("RunTR")] == true && ((touchPressed.find(this->allTouches.GetValueTouche("RunTR")) != touchPressed.end() && etatActuel != "RunTR") || (etatActuel == "RunTR" && (this->GetAnimation()["RunTR"].size() - 1 == this->GetPositionActualAnimation())))) {
			this->SetOrientation(0.5);
			this->SetEtatActuel("RunTR");
			this->SetPositionActualAnimation(0);
		}
		else if (touchPressed[this->allTouches.GetValueTouche("RunTL")] == true && ((touchPressed.find(this->allTouches.GetValueTouche("RunTL")) != touchPressed.end() && etatActuel != "RunTL") || (etatActuel == "RunTL" && (this->GetAnimation()["RunTL"].size() - 1 == this->GetPositionActualAnimation())))) {
			this->SetOrientation(1.5);
			this->SetEtatActuel("RunTL");
			this->SetPositionActualAnimation(0);
		}
		else if (touchPressed[this->allTouches.GetValueTouche("RunBL")] == true && ((touchPressed.find(this->allTouches.GetValueTouche("RunBL")) != touchPressed.end() && etatActuel != "RunBL") || (etatActuel == "RunBL" && (this->GetAnimation()["RunBL"].size() - 1 == this->GetPositionActualAnimation())))) {
			this->SetOrientation(2.5);
			this->SetEtatActuel("RunBL");
			this->SetPositionActualAnimation(0);
		}
		else if (touchPressed[this->allTouches.GetValueTouche("RunBR")] == true && ((touchPressed.find(this->allTouches.GetValueTouche("RunBR")) != touchPressed.end() && etatActuel != "RunBR") || (etatActuel == "RunBR" && (this->GetAnimation()["RunBR"].size() - 1 == this->GetPositionActualAnimation())))) {
			this->SetOrientation(3.5);
			this->SetEtatActuel("RunBR");
			this->SetPositionActualAnimation(0);
		}
		return true;
	}
	return false;
}
bool Personnage::Attack(std::map<int, bool> touchPressed) {
	string etatActuel = this->GetEtatActuel();
	if (touchPressed[this->allTouches.GetValueTouche("Shot")] == true) {
		if (this->GetOrientation() == 0 && ((etatActuel != "ShotR") || (etatActuel == "ShotR" && (this->GetAnimation()["ShotR"].size() - 1 == this->GetPositionActualAnimation())))) {
			this->SetOrientation(0);
			this->SetEtatActuel("ShotR");
			this->SetPositionActualAnimation(0);
		}
		else if (this->GetOrientation() == 1 && ((etatActuel != "ShotT") || (etatActuel == "ShotT" && (this->GetAnimation()["ShotT"].size() - 1 == this->GetPositionActualAnimation())))) {
			this->SetOrientation(1);
			this->SetEtatActuel("ShotT");
			this->SetPositionActualAnimation(0);
		}
		else if (this->GetOrientation() == 2 && ((etatActuel != "ShotL") || (etatActuel == "ShotL" && (this->GetAnimation()["ShotL"].size() - 1 == this->GetPositionActualAnimation())))) {
			this->SetOrientation(2);
			this->SetEtatActuel("ShotL");
			this->SetPositionActualAnimation(0);
		}
		else if (this->GetOrientation() == 3 && ((etatActuel != "ShotB") || (etatActuel == "ShotB" && (this->GetAnimation()["ShotB"].size() - 1 == this->GetPositionActualAnimation())))) {
			this->SetOrientation(3);
			this->SetEtatActuel("ShotB");
			this->SetPositionActualAnimation(0);
		}
		else if (this->GetOrientation() == 0.5 && ((etatActuel != "ShotTR") || (etatActuel == "ShotTR" && (this->GetAnimation()["ShotTR"].size() - 1 == this->GetPositionActualAnimation())))) {
			this->SetOrientation(0.5);
			this->SetEtatActuel("ShotTR");
			this->SetPositionActualAnimation(0);
		}
		else if (this->GetOrientation() == 1.5 && ((etatActuel != "ShotTL") || (etatActuel == "ShotTL" && (this->GetAnimation()["ShotTL"].size() - 1 == this->GetPositionActualAnimation())))) {
			this->SetOrientation(1.5);
			this->SetEtatActuel("ShotTL");
			this->SetPositionActualAnimation(0);
		}
		else if (this->GetOrientation() == 2.5 && ((etatActuel != "ShotBL") || (etatActuel == "ShotBL" && (this->GetAnimation()["ShotBL"].size() - 1 == this->GetPositionActualAnimation())))) {
			this->SetOrientation(2.5);
			this->SetEtatActuel("ShotBL");
			this->SetPositionActualAnimation(0);
		}
		else if (this->GetOrientation() == 3.5 && ((etatActuel != "ShotBR") || (etatActuel == "ShotBR" && (this->GetAnimation()["ShotBR"].size() - 1 == this->GetPositionActualAnimation())))) {
			this->SetOrientation(3.5);
			this->SetEtatActuel("ShotBR");
			this->SetPositionActualAnimation(0);
		}
		return true;
	}
	return false;
}
void Personnage::SetAnimationMainCharacter(std::map<int, bool> touchPressed) {
	



	string etatActuel = this->GetEtatActuel();

	this->SetPositionWhenStopPush(touchPressed);
	if (this->GetCanChangeAnimation()) {
		bool isStandWalkOpposite = SetStandIfWalkOpposite(touchPressed);
		if (isStandWalkOpposite == false) {
			bool isRunningDiagonal = this->SetRunDiagonal(touchPressed);
			if (isRunningDiagonal == false) {
				bool isRunning = this->SetRun(touchPressed);
				if (isRunning == false) {
					bool isWalkingDiagonale = this->SetWalkDiagonal(touchPressed);
					if (isWalkingDiagonale == false) {
						this->SetWalk(touchPressed);
					}
				}
			}
		}



		bool isAttack = this->Attack(touchPressed);
		if (isAttack == false) {
			JumpFonction(touchPressed);
		}

	}

	if (etatActuel == "WalkR" || etatActuel == "WalkL" || etatActuel == "WalkT" || etatActuel == "WalkB" || etatActuel == "WalkTR" || etatActuel == "WalkTL" || etatActuel == "WalkBL" || etatActuel == "WalkBR") {
		if (this->GetClockAnimation().getSeconds() > (double)SPEEDANIMATIONWALK / this->GetAnimation()[this->GetEtatActuel()].size()) {
			this->SetPositionActualAnimation();
			this->SetActualAnimation();
			this->GetClockAnimation().stop();
			this->GetClockAnimation().start();
		}
	}
	else if (etatActuel == "JumpR" || etatActuel == "JumpL" || etatActuel == "JumpT" || etatActuel == "JumpB" || etatActuel == "JumpTL" || etatActuel == "JumpTR" || etatActuel == "JumpBL" || etatActuel == "JumpBR") {
		if (this->GetClockAnimation().getSeconds() > (double)SPEEDANIMATIONJUMP / this->GetAnimation()[this->GetEtatActuel()].size()) {
			this->SetPositionActualAnimation();
			this->SetActualAnimation();
			this->GetClockAnimation().stop();
			this->GetClockAnimation().start();
		}
	}
	else if (etatActuel == "ShotR" || etatActuel == "ShotL" || etatActuel == "ShotB" || etatActuel == "ShotT" || etatActuel == "ShotTL" || etatActuel == "ShotTR" || etatActuel == "ShotBL" || etatActuel == "ShotBR") {
		if (this->GetClockAnimation().getSeconds() > (double)SPEEDANIMATIONATTACK / this->GetAnimation()[this->GetEtatActuel()].size()) {
			this->SetPositionActualAnimation();
			this->SetActualAnimation();
			this->GetClockAnimation().stop();
			this->GetClockAnimation().start();
		}
	}
	else if (etatActuel == "RunR" || etatActuel == "RunL" || etatActuel == "RunT" || etatActuel == "RunB" || etatActuel == "RunTR" || etatActuel == "RunTL" || etatActuel == "RunBL" || etatActuel == "RunBR") {
		if (this->GetClockAnimation().getSeconds() > (double)SPEEDANIMATIONRUN / this->GetAnimation()[this->GetEtatActuel()].size()) {
			this->SetPositionActualAnimation();
			this->SetActualAnimation();
			this->GetClockAnimation().stop();
			this->GetClockAnimation().start();
		}
	}
	else if (etatActuel == "StandR" || etatActuel == "StandL" || etatActuel == "StandB" || etatActuel == "StandT" || etatActuel == "StandTL" || etatActuel == "StandTR" || etatActuel == "StandBL" || etatActuel == "StandBR") {
		if (this->GetClockAnimation().getSeconds() > (double)SPEEDANIMATIONSTAND / this->GetAnimation()[this->GetEtatActuel()].size()) {
			this->SetPositionActualAnimation();
			this->SetActualAnimation();
			this->GetClockAnimation().stop();
			this->GetClockAnimation().start();
		}
	}
}

float Personnage::GetSizeX() {
	return this->sizeX;
}
float Personnage::GetSizeY() {
	return this->sizeY;
}

void  Personnage::SetSizeY(float sizeY) {
	this->sizeY = sizeY;
}


void  Personnage::SetSizeX(float sizeX) {
	this->sizeX = sizeX;
}




polygon Personnage::GetHitBoxOnCurrentAnimation() {

	return this->actualHitBox;
}


void  Personnage::SetActuelHitBoxOnCurrentAnimation() {

	string tempStringPolygon = "POLYGON((";
	polygon tempPolygon;

	std::vector<point > points = this->actualAnimation.second.outer();

	for (std::vector<point>::size_type i = 0; i < points.size(); ++i)
	{
		double temp1 = this->GetPosX() + this->velocityX + (points[i].x()  -(double) this->actualAnimation.first->getWidth()/2) * ((double)this->sizeX/this->actualAnimation.first->getWidth());
		double temp2 = this->GetPosY() + this->velocityY+(points[i].y()  - (double)this->actualAnimation.first->getHeight() / 2) * ((double)this->sizeY / this->actualAnimation.first->getHeight());
		
		tempStringPolygon += to_string(temp1) + " " + to_string(temp2) + ",";


	}
	tempStringPolygon.pop_back();
	tempStringPolygon += "))";
	
	boost::geometry::read_wkt(
		tempStringPolygon, tempPolygon);
	this->actualHitBox = tempPolygon;
}

