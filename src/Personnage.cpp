#include "Personnage.h"
#include <cstdlib>
#include "cinder/app/App.h"
typedef boost::geometry::model::d2::point_xy<double> point;
typedef boost::geometry::model::polygon< point > polygon;
Personnage::Personnage() :allTouches(102, -12, -11, 10, -9, -5, -6, -7, -8,100, 122,113, 115, 32, -1, -2, -3, -4, 304,103) {}

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






void Personnage::SetVelocityWalk(std::map<int, bool>& touchPressed) {
	double dx = this->orientation.x;
	double dy = this->orientation.y;
	
	
	if (touchPressed[this->allTouches.GetValueTouche("WalkTR")]) {
		this->velocityX = DEPLACEMENTWALKX;
		this->velocityY = -DEPLACEMENTWALKY;
	}
	else if (touchPressed[this->allTouches.GetValueTouche("WalkBL")]) {
		this->velocityX = -DEPLACEMENTWALKX;
		this->velocityY = DEPLACEMENTWALKY;
	}
	else if (touchPressed[this->allTouches.GetValueTouche("WalkTL")]) {
		this->velocityX = -DEPLACEMENTWALKX;
		this->velocityY = -DEPLACEMENTWALKY;
	}
	else if (touchPressed[this->allTouches.GetValueTouche("WalkBR")]) {
		this->velocityX = DEPLACEMENTWALKX;
		this->velocityY = DEPLACEMENTWALKY;
	}
	else if (touchPressed[this->allTouches.GetValueTouche("WalkR")]) {
		this->velocityX = DEPLACEMENTWALKX;
	}
	else if (touchPressed[this->allTouches.GetValueTouche("WalkB")]) {
		this->velocityY = DEPLACEMENTWALKY;
	}
	
	else if (touchPressed[this->allTouches.GetValueTouche("WalkT")]) {
		this->velocityY = -DEPLACEMENTWALKY;
	}
	else if (touchPressed[this->allTouches.GetValueTouche("WalkL")]) {
		this->velocityX =- DEPLACEMENTWALKX;
	}

}
void Personnage::SetVelocityRun(std::map<int, bool>& touchPressed) {
	double dx = this->orientation.x;
	double dy = this->orientation.y;


	if (touchPressed[this->allTouches.GetValueTouche("RunTR")]) {
		this->velocityX = DEPLACEMENTRUNX;
		this->velocityY = -DEPLACEMENTRUNY;
	}
	else if (touchPressed[this->allTouches.GetValueTouche("RunBL")]) {
		this->velocityX = -DEPLACEMENTRUNX;
		this->velocityY = DEPLACEMENTRUNY;
	}
	else if (touchPressed[this->allTouches.GetValueTouche("RunTL")]) {
		this->velocityX = -DEPLACEMENTRUNX;
		this->velocityY = -DEPLACEMENTRUNY;
	}
	else if (touchPressed[this->allTouches.GetValueTouche("RunBR")]) {
		this->velocityX = DEPLACEMENTRUNX;
		this->velocityY = DEPLACEMENTRUNY;
	}
	else if (touchPressed[this->allTouches.GetValueTouche("RunR")]) {
		this->velocityX = DEPLACEMENTRUNX;
	}
	else if (touchPressed[this->allTouches.GetValueTouche("RunB")]) {
		this->velocityY = DEPLACEMENTRUNY;
	}

	else if (touchPressed[this->allTouches.GetValueTouche("RunT")]) {
		this->velocityY = -DEPLACEMENTRUNY;
	}
	else if (touchPressed[this->allTouches.GetValueTouche("RunL")]) {
		this->velocityX = -DEPLACEMENTRUNX;
	}

}
void Personnage::SetVelocityJump(std::map<int, bool>& touchPressed) {
	double dx = this->orientation.x;
	double dy = this->orientation.y;

	if (this->walkJump == 1) {
		
	}
	else if (this->walkJump == 2) {

	}
	
}

void Personnage::SetCurrentAnimation(std::map<int, bool>&  touchPressed) {

	if (etatActuel == "WalkR" || etatActuel == "WalkTR" || etatActuel == "WalkT" || etatActuel == "WalkTL" || etatActuel == "WalkL"|| etatActuel == "WalkBL" || etatActuel == "WalkB" || etatActuel == "WalkBR") {
		if (this->clockAnimation.getSeconds() > (double)this->SPEEDANIMATIONWALK / this->animation[this->etatActuel].size()) {
			this->clockAnimation.stop();
			this->clockAnimation.start();
			
			positionActualAnimation++;
			this->SetVelocityWalk(touchPressed);
			if (positionActualAnimation == this->animation[this->etatActuel].size()) {
				positionActualAnimation = 0;
				
				
			}
		}
	}
	else if (etatActuel == "RunR" || etatActuel == "RunTR" || etatActuel == "RunT" || etatActuel == "RunTL" || etatActuel == "RunL" || etatActuel == "RunBL" || etatActuel == "RunB" || etatActuel == "RunBR") {
		if (this->clockAnimation.getSeconds() > (double)this->SPEEDANIMATIONRUN / this->animation[this->etatActuel].size()) {
			this->clockAnimation.stop();
			this->clockAnimation.start();
			positionActualAnimation++;
			SetVelocityRun(touchPressed);
			if (positionActualAnimation == this->animation[this->etatActuel].size()) {
				positionActualAnimation = 0;
				
				
			}
		}
	}
	else if (etatActuel == "JumpR" || etatActuel == "JumpTR" || etatActuel == "JumpT" || etatActuel == "JumpTL" || etatActuel == "JumpL" || etatActuel == "JumpBL" || etatActuel == "JumpB" || etatActuel == "JumpBR") {
		if (this->clockAnimation.getSeconds() > (double)this->SPEEDANIMATIONJUMP/ this->animation[this->etatActuel].size()) {
			this->clockAnimation.stop();
			this->clockAnimation.start();
			positionActualAnimation++;
			this->SetVelocityJump(touchPressed);
			if (positionActualAnimation == this->animation[this->etatActuel].size()) {
				positionActualAnimation = 0;
				
				this->walkJump = 0;
				this->canChangeAnimation = true;
			}
		}
	}
	else if (etatActuel == "StandR" || etatActuel == "StandTR" || etatActuel == "StandT" || etatActuel == "StandTL" || etatActuel == "StandL" || etatActuel == "StandBL" || etatActuel == "StandB" || etatActuel == "StandBR") {
		if (this->clockAnimation.getSeconds() > (double)this->SPEEDANIMATIONSTAND / this->animation[this->etatActuel].size()) {
			this->clockAnimation.stop();
			this->clockAnimation.start();
			positionActualAnimation++;
			if (positionActualAnimation == this->animation[this->etatActuel].size()) {
				positionActualAnimation = 0;
			}
		}
	}
	else if (etatActuel == "ShotR" || etatActuel == "ShotTR" || etatActuel == "ShotT" || etatActuel == "ShotTL" || etatActuel == "ShotL" || etatActuel == "ShotBL" || etatActuel == "ShotB" || etatActuel == "ShotBR") {
		if (this->clockAnimation.getSeconds() > (double)this->SPEEDANIMATIONATTACK / this->animation[this->etatActuel].size()) {
			this->clockAnimation.stop();
			this->clockAnimation.start();
			positionActualAnimation++;
			if (positionActualAnimation == this->animation[this->etatActuel].size()) {
				positionActualAnimation = 0;
				this->canChangeAnimation = true;
				this->Shoot("MainCharacter " + this->aura.GetActualAura(), this->projectile[0], 2 * atan(this->orientation.y / (this->orientation.x + sqrt(pow(this->orientation.x, 2) + pow(this->orientation.y, 2)))), vec2(this->orientation.x, this->orientation.y));
			}
		}
	}



	



}

void Personnage::Shoot(string source, const Projectile & projectile, double orientation, vec2  & direction) {
	Projectile temp = projectile;
	temp.SetPosX(this->posX);
	temp.SetPosY(this->posY);
	
	temp.SetSpeedX(temp.GetSpeedX() * direction.x); 
	temp.SetSpeedY(temp.GetSpeedY()  * direction.y);
	temp.SetDommage(this->degat);


	temp.SetOrientation(orientation);

	temp.SetSource(source);
	temp.SetStartTime(getElapsedSeconds());
	this->pointerToAllProjectile->push_back(temp);

}


void Personnage::Update(std::map<int, bool> & touchPressed) {

	if (this->canChangeAnimation == true) {
		this->SetEtatWithOrientation(touchPressed);
		if (this->lastEtatActuel != this->etatActuel) {
			this->positionActualAnimation = 0;
			this->lastEtatActuel = this->etatActuel;
			this->clockAnimation.stop();
			this->clockAnimation.start();
		}
	}

	
	
	this->SetCurrentAnimation(touchPressed);
	

	this->actualAnimation = this->animation[this->etatActuel][positionActualAnimation];


}


void Personnage::SetEtatWithOrientation(std::map<int, bool>& touchPressed) {
	double dx = this->orientation.x;
	double dy = this->orientation.y;
	bool walk = false;
	bool run = false;

	if (touchPressed[this->allTouches.GetValueTouche("WalkR")]==true || touchPressed[this->allTouches.GetValueTouche("WalkTR")] == true || touchPressed[this->allTouches.GetValueTouche("WalkT")] == true || touchPressed[this->allTouches.GetValueTouche("WalkTL")] == true || touchPressed[this->allTouches.GetValueTouche("WalkL")] == true || touchPressed[this->allTouches.GetValueTouche("WalkBL")] == true || touchPressed[this->allTouches.GetValueTouche("WalkB")] == true || touchPressed[this->allTouches.GetValueTouche("WalkBR")] == true)
		walk = true;

	if (touchPressed[this->allTouches.GetValueTouche("RunR")] == true || touchPressed[this->allTouches.GetValueTouche("RunTR")] == true || touchPressed[this->allTouches.GetValueTouche("RunT")] == true || touchPressed[this->allTouches.GetValueTouche("RunTL")] == true || touchPressed[this->allTouches.GetValueTouche("RunL")] == true || touchPressed[this->allTouches.GetValueTouche("RunBL")] == true || touchPressed[this->allTouches.GetValueTouche("RunB")] == true || touchPressed[this->allTouches.GetValueTouche("RunBR")] == true)
		run = true;


	if ((dx <= 1.0 && dx >= sqrt(3) / 2) && (dy <= 1.0 / 2.0 && dy >= -1.0 / 2.0)) {
	
		if (touchPressed[this->allTouches.GetValueTouche("Jump")]) {
			this->etatActuel = "JumpR";
			
			this->canChangeAnimation = false;
		}
		else if (touchPressed[this->allTouches.GetValueTouche("Shot")]) {
			this->etatActuel = "ShotR";
			this->canChangeAnimation = false;
		}
		else if (run) {
			this->etatActuel = "RunR";
		}
		else if (walk) {
			this->etatActuel = "WalkR";
		}
		else {
			this->etatActuel = "StandR";
		}
	}
	else if ((dx <= sqrt(3)/2 && dx >=1.0/2.0) && (dy >=-sqrt(3)/2 && dy <= -1.0 / 2.0)) {
		
		if (touchPressed[this->allTouches.GetValueTouche("Jump")]) {
			this->etatActuel = "JumpTR";
		
			this->canChangeAnimation = false;
		}
		else if (touchPressed[this->allTouches.GetValueTouche("Shot")]) {
			this->etatActuel = "ShotTR";
			this->canChangeAnimation = false;
		}
		else if (run) {
			this->etatActuel = "RunTR";
		}
		else if (walk) {
			this->etatActuel = "WalkTR";
		}
		else {
			this->etatActuel = "StandTR";
		}
	}
	else if ((dx <= 1.0 / 2.0 && dx >= -1.0 / 2.0) && (dy <= -sqrt(3) / 2 && dy >= -1.0)) {
		if (touchPressed[this->allTouches.GetValueTouche("Jump")]) {
			this->etatActuel = "JumpT";
			
			
			this->canChangeAnimation = false;
		}
		else if (touchPressed[this->allTouches.GetValueTouche("Shot")]) {
			this->etatActuel = "ShotT";
			this->canChangeAnimation = false;
		}
		else if (run) {
			this->etatActuel = "RunT";
		}
		else if (walk) {
			this->etatActuel = "WalkT";
		}
		else {
			this->etatActuel = "StandT";
		}
	}
	else if ((dx <= -1.0 / 2.0 && dx >= -sqrt(3) / 2.0) && (dy >= -sqrt(3) / 2 && dy <= -1.0 / 2.0)) {
		if (touchPressed[this->allTouches.GetValueTouche("Jump")]) {
			this->etatActuel = "JumpTL";


			this->canChangeAnimation = false;
		}
		else if (touchPressed[this->allTouches.GetValueTouche("Shot")]) {
			this->etatActuel = "ShotTL";
			this->canChangeAnimation = false;
		}
		else if (run) {
			this->etatActuel = "RunTL";
		}
		else if (walk) {
			this->etatActuel = "WalkTL";
		}
		else {
			this->etatActuel = "StandTL";
		}
	}
	else if ((dx >= -1.0 && dx <= -sqrt(3) / 2) && (dy <= 1.0 / 2.0 && dy >= -1.0 / 2.0)) {
		if (touchPressed[this->allTouches.GetValueTouche("Jump")]) {
			this->etatActuel = "JumpL";

			this->canChangeAnimation = false;
		}
		else if (touchPressed[this->allTouches.GetValueTouche("Shot")]) {
			this->etatActuel = "ShotL";
			this->canChangeAnimation = false;
		}
		else if (run) {
			this->etatActuel = "RunL";
		}
		else if (walk) {
			this->etatActuel = "WalkL";
		}
		else {
			this->etatActuel = "StandL";
		}
	}
	else if ((dx >= -sqrt(3) / 2 && dx <= -1.0 / 2.0) && (dy <= sqrt(3) / 2 && dy >= 1.0 / 2.0)) {
		if (touchPressed[this->allTouches.GetValueTouche("Jump")]) {
			this->etatActuel = "JumpBL";

			this->canChangeAnimation = false;
		}
		else if (touchPressed[this->allTouches.GetValueTouche("Shot")]) {
			this->etatActuel = "ShotBL";
			this->canChangeAnimation = false;
		}
		else if (run) {
			this->etatActuel = "RunBL";
		}
		else if (walk) {
			this->etatActuel = "WalkBL";
		}
		else {
			this->etatActuel = "StandBL";
		}
	}
	else if ((dx <= 1.0 / 2.0 && dx >= -1.0 / 2.0) && (dy >= sqrt(3) / 2 && dy <= 1.0)) {
		if (touchPressed[this->allTouches.GetValueTouche("Jump")]) {
			this->etatActuel = "JumpB";

			this->canChangeAnimation = false;
		}
		else if (touchPressed[this->allTouches.GetValueTouche("Shot")]) {
			this->etatActuel = "ShotB";
			this->canChangeAnimation = false;
		}
		else if (run) {
			this->etatActuel = "RunB";
		}
		else if (walk) {
			this->etatActuel = "WalkB";
		}
		else {
			this->etatActuel = "StandB";
		}
	}
	else if ((dx >= 1.0 / 2.0 && dx <= sqrt(3) / 2.0) && (dy <= sqrt(3) / 2 && dy >= 1.0 / 2.0)) {
		if (touchPressed[this->allTouches.GetValueTouche("Jump")]) {
			this->etatActuel = "JumpBR";

			this->canChangeAnimation = false;
		}
		else if (touchPressed[this->allTouches.GetValueTouche("Shot")]) {
			this->etatActuel = "ShotBR";
			this->canChangeAnimation = false;
		}
		else if (run) {
			this->etatActuel = "RunBR";
		}
		else if (walk) {
			this->etatActuel = "WalkBR";
		}
		else {
			this->etatActuel = "StandBR";
		}
	}
	else {
		console() << "ERREUR" << endl;
		this->etatActuel = "StandR";
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

