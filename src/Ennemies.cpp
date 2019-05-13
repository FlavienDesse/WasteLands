#include "Ennemies.h"

Ennemies Ennemiesload::TransformEnnemiesLoadToEnnemies(string type , Ennemiesload source, int posX ,int posY, vector<Projectile> * pointerToAllProjectile, vec2 velocity, vec2 size , double vie , double degat , double portee) {
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
	temp.SetPortee(portee);
	temp.SetMaxVie(vie);
	
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
		temp.SetAuraKill("Rouge");
		
	}
	else if (type == "BossFactory") {

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
		temp.SetAuraKill("Rouge");


		TimeAttack_ tempA;
		tempA.spawn =5;
		tempA.round = 10;
		temp.SetupTimeAttack(tempA);
		

	}
	else if (type == "Livre") {

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
		deplacementAnimationTemp.SPEEDANIMATIONATTACK = 1;
		deplacementAnimationTemp.SPEEDANIMATIONDIE = 0.50;
		temp.SetupDeplacementDelayClock(deplacementAnimationTemp);
		temp.SetAuraKill("Bleu");


	


	}
	else if (type == "Bouteille") {

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
		deplacementAnimationTemp.SPEEDANIMATIONATTACK = 1;
		deplacementAnimationTemp.SPEEDANIMATIONDIE = 0.50;
		temp.SetupDeplacementDelayClock(deplacementAnimationTemp);
		temp.SetAuraKill("Jaune");


		TimeAttack_ tempA;
		tempA.spawn = 0;
		tempA.round =5;
		temp.SetupTimeAttack(tempA);


	}
	temp.GetClockAnimation().start();
	return temp;
}



void Ennemies::SetActualHitbox() {
	
	
		polygon p = this->currentAnimation.second;

		
		boost::geometry::strategy::transform::translate_transformer<double, 2, 2> translate(-(double)this->currentAnimation.first->getWidth() / 2, -(double)this->currentAnimation.first->getHeight() / 2);
		boost::geometry::transform(p, this->actualHitBox, translate);

		p = this->actualHitBox;
		boost::geometry::strategy::transform::scale_transformer<double, 2, 2> scale((double)this->size.x / this->currentAnimation.first->getWidth());
		boost::geometry::transform(p, this->actualHitBox, scale);

		p = this->actualHitBox;
		boost::geometry::strategy::transform::translate_transformer<double, 2, 2> translateS(this->pos.x + this->actualVelocity.x , this->pos.y + this->actualVelocity.y );
		boost::geometry::transform(p, this->actualHitBox, translateS);
		
	
	
}

void Ennemies::Update(const vec2 & posCharacter, map<string, Ennemiesload> & allEnnemiesLoad, vector <Projectile>&  allProjectile, vector<Ennemies> * allEnnemies) {
	if (this->type == "Rose") {
		this->UpdateRose(posCharacter);
	}
	else if (this->type == "BossFactory") {
	
		this->UpdateBossFactory(posCharacter, allEnnemiesLoad, allProjectile, allEnnemies);
	}
	else if (this->type == "Livre") {

		this->UpdateLivre(posCharacter);
	}
	else if (this->type == "Bouteille") {

		this->UpdateBouteille(posCharacter);
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

void Ennemies::UpdateBouteille(const vec2 & posCharacter) {
	if (this->canChangeAnimaion == true) {
		double distanceCharacter = sqrt(pow(this->pos.x - posCharacter.x, 2) + pow(this->pos.y - posCharacter.y, 2));
		double dx = (double)(cos(getAngle(posCharacter, this->pos)));
		double dy = (double)(sin(getAngle(posCharacter, this->pos)));
	
		if (distanceCharacter > this->portee) {
			this->SetAnimationWalk(dx, dy);
		}
		else {

			this->SetAnimationShootBouteille(posCharacter);

		}

	}
	else {
		if (( this->etatActual == "DieR" || this->etatActual == "DieL" )) {
			if (this->clockAnimation.getSeconds() > (double)this->SetupDeplacementAnimation.SPEEDANIMATIONDIE / this->allAnimationWithHitBox[this->etatActual].size()) {
				this->posAnimation++;
			}
			if (posAnimation == this->allAnimationWithHitBox[this->etatActual].size()) {
				this->isDying = 2;
			}
		}
	}
	
	
}
void Ennemies::UpdateRose(const vec2 & posCharacter) {
	if (this->canChangeAnimaion == true) {
		double distanceCharacter = sqrt(pow(this->pos.x - posCharacter.x, 2) + pow(this->pos.y - posCharacter.y, 2));
		double dx = (double)(cos(getAngle(posCharacter, this->pos)));
		double dy = (double)(sin(getAngle(posCharacter, this->pos)));
		
		if (distanceCharacter > this->portee) {
			this->SetAnimationWalk(dx, dy);
		}
		else {

			this->SetAnimationShoot(dx, dy);

		}

	}
	else {
		if ((this->etatActual == "DieR" || this->etatActual == "DieL")) {
			if (this->clockAnimation.getSeconds() > (double)this->SetupDeplacementAnimation.SPEEDANIMATIONDIE / this->allAnimationWithHitBox[this->etatActual].size()) {
				this->posAnimation++;
			}
			if (posAnimation == this->allAnimationWithHitBox[this->etatActual].size()) {
				this->isDying = 2;
			}
		}
	}


}
void Ennemies::UpdateLivre(const vec2 & posCharacter) {
	if (this->canChangeAnimaion == true) {
		double distanceCharacter = sqrt(pow(this->pos.x - posCharacter.x, 2) + pow(this->pos.y - posCharacter.y, 2));
		double dx = (double)(cos(getAngle(posCharacter, this->pos)));
		double dy = (double)(sin(getAngle(posCharacter, this->pos)));

		if (distanceCharacter > this->portee) {
			this->SetAnimationWalk(dx, dy);
		}
		else {

			this->SetAnimationShoot(dx, dy,"EnnemiesL");

		}

	}
	else {
		if ((this->etatActual == "DieR" || this->etatActual == "DieL")) {
			if (this->clockAnimation.getSeconds() > (double)this->SetupDeplacementAnimation.SPEEDANIMATIONDIE / this->allAnimationWithHitBox[this->etatActual].size()) {
				this->posAnimation++;
			}
			if (posAnimation == this->allAnimationWithHitBox[this->etatActual].size()) {
				this->isDying = 2;
			}
		}
	}


}
void Ennemies::SetAnimationShoot(double dx, double dy,string source) {
	if (this->clockAnimation.getSeconds() > (double)this->SetupDeplacementAnimation.SPEEDANIMATIONATTACK / this->allAnimationWithHitBox[this->etatActual].size()) {
		this->clockAnimation.stop();
		this->clockAnimation.start();
		if (dx <= 1 && dx >= 0) {
			if (this->etatActual != "AttackR" || (this->allAnimationWithHitBox[etatActual].size() == this->posAnimation + 1 && this->etatActual == "AttackR")) {
				if ((this->allAnimationWithHitBox[etatActual].size() == this->posAnimation + 1 && this->etatActual == "AttackR")) {
					Shoot(source , this->projectile[0], vec2(dx, dy));
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
					Shoot(source, this->projectile[0], vec2(dx, dy));
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
void Ennemies::SetAnimationShootBouteille(const vec2 & posCharacter) {
	double dx = (double)(cos(getAngle(posCharacter, this->pos)));
	double dy = (double)(sin(getAngle(posCharacter, this->pos)));
	if (this->clockAnimation.getSeconds() > (double)this->SetupDeplacementAnimation.SPEEDANIMATIONATTACK / this->allAnimationWithHitBox[this->etatActual].size()) {
		this->clockAnimation.stop();
		this->clockAnimation.start();
		if (dx <= 1 && dx >= 0) {
			if (this->etatActual != "AttackR" || (this->allAnimationWithHitBox[etatActual].size() == this->posAnimation + 1 && this->etatActual == "AttackR")) {
				if ((this->allAnimationWithHitBox[etatActual].size() == this->posAnimation + 1 && this->etatActual == "AttackR")) {
					srand(time(NULL));
					for (int i = 0; i < 6; i++) {
						vec2 tempPos = posCharacter + vec2(rand() % 61 - 30, rand() % 61 - 30);
						dx = (double)(cos(getAngle(tempPos, this->pos)));
						dy = (double)(sin(getAngle(tempPos, this->pos)));
						ShootBouteille("Ennemies", this->projectile[0], vec2(dx, dy));
					}
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
					srand(time(NULL));
					for (int i = 0; i < 6; i++) {
						vec2 tempPos = posCharacter + vec2(rand() % 151 - 75, rand() % 151-75);
						dx = (double)(cos(getAngle(tempPos, this->pos)));
						dy = (double)(sin(getAngle(tempPos, this->pos)));
						ShootBouteille("Ennemies", this->projectile[0], vec2(dx, dy));
					}
					
					
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
void Ennemies::UpdateBossFactory(const vec2 & posCharacter, map<string, Ennemiesload> & allEnnemiesLoad, vector <Projectile> &  allProjectile, vector<Ennemies> * allEnnemies) {
	
	if (this->canChangeAnimaion == true) {
		static int lastResult=-1;
		static double temp = getElapsedSeconds();
		static double timeRound = 0;
		if (lastResult == 1 && getElapsedSeconds() - temp < this->timeAttack.round) {
			if (getElapsedSeconds() - timeRound >1.7) {
				for (int i = 0; i <64; i++) {
					double x = this->pos.x + cos(i * M_PI / 32);
					double y = this->pos.y + sin(i * M_PI / 32);
					double dx = (double)(cos(getAngle(vec2(x, y), this->pos)));
					double dy = (double)(sin(getAngle(vec2(x, y), this->pos)));
					
					Shoot("Ennemies", this->projectile[1], vec2(dx, dy));

				}
				
				timeRound= getElapsedSeconds();
			}
		}
		else if (lastResult == 0 && getElapsedSeconds() - temp < this->timeAttack.spawn) {

		}
		else {
			lastResult = -1;
		}
		
		
		if (lastResult == -1 && getElapsedSeconds() - temp > 0.5) {
			int alea;
			if (lastResult == 1) {
				alea = 0;
			}
			else {
				alea=rand() % 2;
			}
		
			lastResult = alea;
			temp = getElapsedSeconds();
			if (alea == 0) {

			
				
				allEnnemies->push_back(allEnnemiesLoad["Rose"].TransformEnnemiesLoadToEnnemies("Rose", allEnnemiesLoad["Rose"], this->pos.x-250, this->pos.y- 250, &allProjectile, vec2(5, 5), vec2(150, 150), 100, 20,800));
				allEnnemies->push_back(allEnnemiesLoad["Rose"].TransformEnnemiesLoadToEnnemies("Rose", allEnnemiesLoad["Rose"], this->pos.x + 250, this->pos.y - 250, &allProjectile, vec2(5, 5), vec2(150, 150), 100, 20, 800));
				allEnnemies->push_back(allEnnemiesLoad["Rose"].TransformEnnemiesLoadToEnnemies("Rose", allEnnemiesLoad["Rose"], this->pos.x + 250, this->pos.y + 250, &allProjectile, vec2(5, 5), vec2(150, 150), 100, 20, 800));
				allEnnemies->push_back(allEnnemiesLoad["Rose"].TransformEnnemiesLoadToEnnemies("Rose", allEnnemiesLoad["Rose"], this->pos.x - 250, this->pos.y + 250, &allProjectile, vec2(5, 5), vec2(150, 150), 100, 20, 800));
			}
			
		}
		
	

	}
	else {
		if ((this->etatActual == "DieR" || this->etatActual == "DieL")) {
			if (this->clockAnimation.getSeconds() > (double)this->SetupDeplacementAnimation.SPEEDANIMATIONDIE / this->allAnimationWithHitBox[this->etatActual].size()) {
				this->posAnimation++;
			}
			if (posAnimation == this->allAnimationWithHitBox[this->etatActual].size()) {

				this->isDying = 2;
			}
		}
	}


}
void Ennemies::Shoot(string source, const Projectile & projectile, vec2  & direction) {
	double orientation;
	
	if (direction.x >0 && direction.y >= 0){
		orientation = atan(direction.y / direction.x);
	}
	else if (direction.x > 0 && direction.y < 0) {
		orientation = atan(direction.y / direction.x) + 2 *M_PI;
	}
	else if (direction.x < 0) {
		orientation = atan(direction.y / direction.x) +  M_PI;
	}
	else if (direction.x == 0 && direction.y > 0) {
		orientation = M_PI / 2;
	}
	else if (direction.x  == 0 && direction.y < 0) {
		orientation = 3*M_PI / 2;
	}
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
void Ennemies::ShootBouteille(string source, const Projectile & projectile, vec2  & direction) {
	double orientation;

	if (direction.x > 0 && direction.y >= 0) {
		orientation = atan(direction.y / direction.x);
	}
	else if (direction.x > 0 && direction.y < 0) {
		orientation = atan(direction.y / direction.x) + 2 * M_PI;
	}
	else if (direction.x < 0) {
		orientation = atan(direction.y / direction.x) + M_PI;
	}
	else if (direction.x == 0 && direction.y > 0) {
		orientation = M_PI / 2;
	}
	else if (direction.x == 0 && direction.y < 0) {
		orientation = 3 * M_PI / 2;
	}
	Projectile temp = projectile;
	temp.SetPosX(this->pos.x);
	temp.SetPosY(this->pos.y);

	temp.SetSpeedX((temp.GetSpeedX() +rand() %6 - 5) * direction.x);
	temp.SetSpeedY( ( temp.GetSpeedY() + rand() % 6 - 5)* direction.y);
	temp.SetDommage(this->degat);



	temp.SetOrientation(orientation);

	temp.SetSource(source);
	temp.SetStartTime(getElapsedSeconds());
	this->pointerToAllProjectile->push_back(temp);

}
