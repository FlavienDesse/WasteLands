#include "Ennemies.h"

Ennemies Ennemiesload::TransformEnnemiesLoadToEnnemies(string type , Ennemiesload source, int posX ,int posY, vector<Projectile> * pointerToAllProjectile, vec2 velocity, vec2 size) {
	Ennemies temp;
	temp.SetProjectile(source.GetProjectile());
	temp.SetPos(vec2(posX, posY));
	temp.SetPointerToAllProjectile(pointerToAllProjectile);
	temp.SetType(type);
	temp.SetallAnimationWithHitBox(source.GetAnimation());
	temp.SetVelocity(velocity);
	temp.SetSize(size);
	return temp;
}

void Ennemies::SetActualHitbox() {
	string tempStringPolygon = "POLYGON((";
	polygon tempPolygon;

	std::vector<point > points = this->currentAnimation.second.outer();

	for (std::vector<point>::size_type i = 0; i < points.size(); ++i)
	{
		double temp1 = this->pos.x+ this->velocity.x+ (points[i].x() - (double)this->currentAnimation.first->getWidth() / 2) * ((double)this->size.x / this->currentAnimation.first->getWidth());
		double temp2 = this->pos.y + this->velocity.y + (points[i].y() - (double)this->currentAnimation.first->getHeight() / 2) * ((double)this->size.y / this->currentAnimation.first->getHeight());

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

float getAngle(const vec2 & target1 , const vec2 & target2) {
	double angle = atan2(target1.y - target2.y, target1.x - target2.x);
	if (angle < 0) {
		angle += 2 * M_PI;
	}
	

	return angle;
}

void Ennemies::SetAnimationWalk(double dx,double dy) {
	if ((dx <= 1 && dx >= 0.9) && (dy >= -0.30 && dy<= 0.30)) {
		if (this->etatActual != "WalkR" ||(this->allAnimationWithHitBox[etatActual].size() == this->posAnimation+1 && this->etatActual == "WalkR")) {
			this->etatActual = "WalkR";
			this->posAnimation = 0;
			console() << this->etatActual << endl;
		}
		else {
			
			this->posAnimation++;

		}
		
	}
	else if ((dx <= 0.1 && dx >= -0.1) && (dy >= -0.90 && dy <= -1)) {
		if (this->etatActual != "WalkT" || (this->allAnimationWithHitBox[etatActual].size() == this->posAnimation + 1 && this->etatActual == "WalkT")) {
			this->etatActual = "WalkT";
			this->posAnimation = 0;

		}
		else {

			this->posAnimation++;

		}
		
	}
	else if ((dx <= -1 && dx >= -0.9) && (dy >= -0.30 && dy <= 0.30)) {
		if (this->etatActual != "WalkL" || (this->allAnimationWithHitBox[etatActual].size() == this->posAnimation + 1 && this->etatActual == "WalkL")) {
			this->etatActual = "WalkL";
			this->posAnimation = 0;

		}
		else {

			this->posAnimation++;

		}

	}
	else if ((dx <= 0.1 && dx >= -0.1) && (dy >= 0.90 && dy <=1)) {
		if (this->etatActual != "WalkR" || (this->allAnimationWithHitBox[etatActual].size() == this->posAnimation + 1 && this->etatActual == "WalkR")) {
			this->etatActual = "WalkR";
			this->posAnimation = 0;
			
		}
		else {

			this->posAnimation++;

		}

	}
	
	this->actualVelocity = vec2(dx * this->velocity.x, dy* this->velocity.y);
}

void Ennemies::UpdateRose(const vec2 & posCharacter) {
	double distanceCharacter = sqrt(pow(this->pos.x - posCharacter.x, 2) + pow(this->pos.y - posCharacter.y, 2)); 
	double dx = (double)(cos(getAngle(posCharacter, this->pos)));
	double dy = (double)(sin(getAngle(posCharacter, this->pos)) );
	
	if (distanceCharacter > 400) {
		this->SetAnimationWalk(dx,dy);
	}
	else {
		
		Shoot("Rose " + 0 ,this->projectile[0], 2 * atan(dy / (dx + sqrt(pow(dx, 2) + pow(dy, 2)))), vec2(dx,dy));
	}

	
	
}

void Ennemies::Shoot(string source, const Projectile & projectile, double orientation, vec2  & direction) {
	Projectile temp = projectile;
	temp.SetPosX(this->pos.x);
	temp.SetPosY(this->pos.y);
	
	temp.SetSpeedX(temp.GetSpeedX() * direction.x);
	temp.SetSpeedY(temp.GetSpeedY()  * direction.y);

	
	
	temp.SetOrientation(orientation);
	
	temp.SetSource(source);
	temp.SetStartTime(getElapsedSeconds());
	this->pointerToAllProjectile->push_back(temp);

}

