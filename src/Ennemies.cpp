#include "Ennemies.h"

Ennemies Ennemiesload::TransformEnnemiesLoadToEnnemies(string type , Ennemiesload source, int posX ,int posY, vector<Projectile> * pointerToAllProjectile, vec2 velocity, vec2 size , double vie , double degat) {
	Ennemies temp;
	temp.SetProjectile(source.GetProjectile());
	temp.SetPos(vec2(posX, posY));
	temp.SetPointerToAllProjectile(pointerToAllProjectile);
	temp.SetType(type);
	temp.SetallAnimationWithHitBox(source.GetAnimation());
	temp.SetVelocity(velocity);
	temp.SetSize(size);
	temp.SetDegat(degat);
	temp.SetVie(vie);
	
	if (type == "Rose") {

		SetupDeplacementAnimation_  deplacementAnimationTemp;
		deplacementAnimationTemp.DEPLACEMENTWALKX = 5;
		deplacementAnimationTemp.DEPLACEMENTWALKY = 5;
		deplacementAnimationTemp.DEPLACEMENTJUMPWALKX = 20;
		deplacementAnimationTemp.DEPLACEMENTJUMPWALKY = 20;
		deplacementAnimationTemp.DEPLACEMENTJUMPRUNX = 25;
		deplacementAnimationTemp.DEPLACEMENTJUMPRUNY = 25;
		deplacementAnimationTemp.DEPLACEMENTRUNX = 15;
		deplacementAnimationTemp.DEPLACEMENTRUNY = 15;

		deplacementAnimationTemp.SPEEDANIMATIONSTAND = 0.55;
		deplacementAnimationTemp.SPEEDANIMATIONWALK = 0.40;
		deplacementAnimationTemp.SPEEDANIMATIONJUMP = 0.50;
		deplacementAnimationTemp.SPEEDANIMATIONRUN = 0.50;
		deplacementAnimationTemp.SPEEDANIMATIONATTACK = 0.50;
		deplacementAnimationTemp.SPEEDANIMATIONDIE = 0.50;
		temp.SetupDeplacementDelayClock(deplacementAnimationTemp);
		temp.SetAuraKill("Vert");
		
	}
	temp.GetClockAnimation().start();
	return temp;
}



void Ennemies::SetActualHitbox() {
	string tempStringPolygon = "POLYGON((";
	polygon tempPolygon;

	std::vector<point > points = this->currentAnimation.second.outer();

	for (std::vector<point>::size_type i = 0; i < points.size(); ++i)
	{
		double temp1 = this->pos.x+ this->actualVelocity.x+ (points[i].x() - (double)this->currentAnimation.first->getWidth() / 2) * ((double)this->size.x / this->currentAnimation.first->getWidth());
		double temp2 = this->pos.y + this->actualVelocity.y + (points[i].y() - (double)this->currentAnimation.first->getHeight() / 2) * ((double)this->size.y / this->currentAnimation.first->getHeight());

		tempStringPolygon += to_string(temp1) + " " + to_string(temp2) + ",";


	}
	tempStringPolygon.pop_back();
	tempStringPolygon += "))";

	boost::geometry::read_wkt(
		tempStringPolygon, tempPolygon);
	this->actualHitBox = tempPolygon;
}

void Ennemies::Update(const vec2 & posCharacter) {
	if (this->type == "Rose") {
		this->UpdateRose(posCharacter);
	}
}


void Ennemies::SetAnimationWalk(double dx,double dy) {
	if (this->clockAnimation.getSeconds() > (double)this->SetupDeplacementAnimation.SPEEDANIMATIONWALK / this->allAnimationWithHitBox[this->etatActual].size()) {

		this->clockAnimation.stop();
		this->clockAnimation.start();

	if (( (dx <= 1 && dx >= sqrt(3)/2 ) && (dy >= -0.50 && dy<= 0.50))|| ((dx <= 1 && dx >= 0.50) && (dy >= 0 && dy <= sqrt(3)/2))) {
		if (this->etatActual != "WalkR" ||(this->allAnimationWithHitBox[etatActual].size() == this->posAnimation+1 && this->etatActual == "WalkR")) {
			this->etatActual = "WalkR";
			this->posAnimation = 0;
		
		}
		else {
			
			this->posAnimation++;

		}
		
	}
	else if ((dx <= sqrt(3) / 2 && dx >= 0.50) && (dy <=0 && dy >=-sqrt(3)/2 )) {
		if (this->etatActual != "WalkTR" || (this->allAnimationWithHitBox[etatActual].size() == this->posAnimation + 1 && this->etatActual == "WalkTR")) {
			this->etatActual = "WalkTR";
			this->posAnimation = 0;

		}
		else {

			this->posAnimation++;

		}

	}
	else if ((dx <= 0.50 && dx >= -sqrt(3)/2) && (dy <= 0.0 && dy >=-1)) {
		if (this->etatActual != "WalkT" || (this->allAnimationWithHitBox[etatActual].size() == this->posAnimation + 1 && this->etatActual == "WalkT")) {
			this->etatActual = "WalkT";
			this->posAnimation = 0;

		}
		else {

			this->posAnimation++;

		}
		
	}
	else if  ( ((dx >= -1 && dx<= -sqrt(2)/2) && (dy <= 0 && dy >= -0.50)) ||( (dx <= 0.50 && dx >= -1) && (dy >= 0 && dy <= 1 ))) {
		if (this->etatActual != "WalkL" || (this->allAnimationWithHitBox[etatActual].size() == this->posAnimation + 1 && this->etatActual == "WalkL")) {
			this->etatActual = "WalkL";
			this->posAnimation = 0;

		}
		else {

			this->posAnimation++;

		}

	}

	
	this->actualVelocity = vec2(dx * this->velocity.x, dy* this->velocity.y);
	}
}

void Ennemies::SetDie() {
	this->canChangeAnimaion = false;
	this->posAnimation = 0;
	this->etatActual = "DieR";
}

void Ennemies::UpdateRose(const vec2 & posCharacter) {
	if (this->canChangeAnimaion == true) {
		double distanceCharacter = sqrt(pow(this->pos.x - posCharacter.x, 2) + pow(this->pos.y - posCharacter.y, 2));
		double dx = (double)(cos(getAngle(posCharacter, this->pos)));
		double dy = (double)(sin(getAngle(posCharacter, this->pos)));

		if (distanceCharacter > 400) {
			this->SetAnimationWalk(dx, dy);
		}
		else {

			this->SetAnimationShoot(dx, dy);

		}

	}
	else {
		if (this->etatActual == "DieR" || this->etatActual == "DieL") {
			if (this->clockAnimation.getSeconds() > (double)this->SetupDeplacementAnimation.SPEEDANIMATIONDIE / this->allAnimationWithHitBox[this->etatActual].size()) {
				this->posAnimation++;
			}
			if (posAnimation == this->allAnimationWithHitBox[this->etatActual].size()) {
				this->isDying = 2;
			}
		}
	}
	
	
}
void Ennemies::SetAnimationShoot(double dx, double dy) {
	if (this->clockAnimation.getSeconds() > (double)this->SetupDeplacementAnimation.SPEEDANIMATIONATTACK / this->allAnimationWithHitBox[this->etatActual].size()) {
		this->clockAnimation.stop();
		this->clockAnimation.start();
		if (dx <= 1 && dx >= 0) {
			if (this->etatActual != "AttackR" || (this->allAnimationWithHitBox[etatActual].size() == this->posAnimation + 1 && this->etatActual == "AttackR")) {
				if ((this->allAnimationWithHitBox[etatActual].size() == this->posAnimation + 1 && this->etatActual == "AttackR")) {
					Shoot("Ennemies" , this->projectile[0], 2 * atan(dy / (dx + sqrt(pow(dx, 2) + pow(dy, 2)))), vec2(dx, dy));
				}
				this->etatActual = "AttackR";
					this->posAnimation = 0;

			}
			else {

				this->posAnimation++;

			}
		}
		else {
			if (this->etatActual != "AttackL" || (this->allAnimationWithHitBox[etatActual].size() == this->posAnimation + 1 && this->etatActual == "AttackL")) {
				if ((this->allAnimationWithHitBox[etatActual].size() == this->posAnimation + 1 && this->etatActual == "AttackL")) {
					Shoot("Ennemies", this->projectile[0], 2 * atan(dy / (dx + sqrt(pow(dx, 2) + pow(dy, 2)))), vec2(dx, dy));
				}
				this->etatActual = "AttackL";
				this->posAnimation = 0;

			}
			else {

				this->posAnimation++;

			}
		}



	}
}

void Ennemies::Shoot(string source, const Projectile & projectile, double orientation, vec2  & direction) {
	Projectile temp = projectile;
	temp.SetPosX(this->pos.x);
	temp.SetPosY(this->pos.y);
	
	temp.SetSpeedX(temp.GetSpeedX() * direction.x);
	temp.SetSpeedY(temp.GetSpeedY()  * direction.y);
	temp.SetDommage(this->degat);
	
	
	temp.SetOrientation(orientation);
	
	temp.SetSource(source);
	temp.SetStartTime(getElapsedSeconds());
	this->pointerToAllProjectile->push_back(temp);

}

