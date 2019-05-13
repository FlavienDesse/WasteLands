#pragma once


#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>

#include "cinder/gl/Texture.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

#include "Projectile.h"
#include <vector>
struct SetupDeplacementAnimation_ {
	float DEPLACEMENTWALKX;
	float DEPLACEMENTWALKY;
	float DEPLACEMENTJUMPWALKX;
	float DEPLACEMENTJUMPWALKY;
	float DEPLACEMENTJUMPRUNX ;
	float DEPLACEMENTJUMPRUNY;
	float DEPLACEMENTRUNX;
	float DEPLACEMENTRUNY;

	float SPEEDANIMATIONSTAND;
	float SPEEDANIMATIONWALK;
	float SPEEDANIMATIONJUMP;
	float SPEEDANIMATIONRUN;
	float SPEEDANIMATIONATTACK;
	float SPEEDANIMATIONDIE;
};

struct TimeAttack_ {
	float spawn;
	float round;
	
};

class Ennemies;
class Ennemiesload {
public:
	Ennemiesload() {};
	map<string, vector <pair <ci::gl::TextureRef, polygon>>> & GetAnimation() { return this->animation; }
	vector<Projectile> & GetProjectile() { return this->projectile; }
	void SetProjectile(vector<Projectile> projectile) { this->projectile = projectile; }
	Ennemies TransformEnnemiesLoadToEnnemies(string type, Ennemiesload source, int posX, int posY, vector<Projectile>* pointerToAllProjectile, vec2 velocity, vec2 size, double vie, double degat, double portee);
private:
	map<string, vector <pair <ci::gl::TextureRef, polygon>>> animation;
	string name;

	vector<Projectile> projectile;
};

class Ennemies
{
public:

	
	void SetPointerToAllProjectile(vector<Projectile> * allProjectile) { this->pointerToAllProjectile = allProjectile; }

	vector<Projectile> GetProjectile() { return this->projectile; }
	void SetProjectile(vector<Projectile> projectile) { this->projectile = projectile; }

	void SetType(string type) { this->type = type; }
	string GetType() { return this->type; }


	void SetPortee(double portee) { this->portee= portee; }

	void SetPos(vec2 pos) { this->pos= pos; }
	vec2 GetPos() { return this->pos; }
	void SetcurrentAnimation() { this->currentAnimation = this->allAnimationWithHitBox[etatActual][posAnimation]; }
	void SetallAnimationWithHitBox(map<string, vector <pair <ci::gl::TextureRef, polygon>>> allAnimationWithHitBox) { this->allAnimationWithHitBox = allAnimationWithHitBox; }
	
	void SetActualHitbox();
	polygon GetActualHitbox() { return this->actualHitBox; }

	void SetVelocity(vec2 velocity) { this->velocity=velocity; }
	vec2 GetVelocity() { return this->velocity; }

	void SetMaxVie(double maxVie) { this->maxVie = vie; }
	double GetMaxVie() {return this->maxVie;}

	void SetActualVelocity(vec2 actualVelocity) { this->actualVelocity= actualVelocity; }
	vec2 GetActualVelocity() { return this->actualVelocity; }


	void SetSize(vec2 size) { this->size=size; }
	vec2 GetSize() { return this->size; }
	
	TextureRef GetCurrentTexture() { return this->currentAnimation.first; }

	void Update(const vec2 & posCharacter, map<string, Ennemiesload> & allEnnemiesLoad, vector <Projectile>&  allProjectile, vector<Ennemies> * allEnnemies);
	void UpdateRose(const vec2 & posCharacter);
	
	void Shoot(string source,const Projectile & projectile ,  vec2  & direction );
	void SetAnimationWalk(double dx, double dy);
	void SetupDeplacementDelayClock(SetupDeplacementAnimation_   temp) { this->SetupDeplacementAnimation = temp; }
	void SetupTimeAttack(TimeAttack_  temp) { this->timeAttack = temp; }
	void UpdateBossFactory(const vec2 & posCharacter, map<string, Ennemiesload> & allEnnemiesLoad, vector <Projectile>&  allProjectile, vector<Ennemies>  *allEnnemies);
	Timer & GetClockAnimation() { return this->clockAnimation; }
	void SetAnimationShoot(double dx , double dy,string source = "Ennemies");

	void SetVie(double vie) { this->vie = vie; }
	double GetVie() { return this->vie; }

	void SetDegat(double degat) { this->degat = degat; }
	double GetDegat() { return this->degat; }
	void UpdateLivre(const vec2 & posCharacter);
	void SetDie();

	int GetisDying() { return this->isDying; }
	void UpdateBouteille(const vec2 & posCharacter);
	void SetAnimationShootBouteille(const vec2 & posCharacter);
	void ShootBouteille(string source, const Projectile & projectile, vec2  & direction);
	void SetAuraKill(string auraKill) { this->auraKill = auraKill; }
	string GetAuraKil() { return this->auraKill; }
private:
	vector<Projectile>* pointerToAllProjectile = NULL;
	vector<Projectile> projectile;
	string type;
	string auraKill;
	vec2 pos;
	map<string, vector <pair <ci::gl::TextureRef, polygon>>> allAnimationWithHitBox;
	int posAnimation = 0;
	pair <ci::gl::TextureRef, polygon> currentAnimation ;
	string etatActual = "StandR";
	polygon actualHitBox;
	vec2 velocity;
	vec2 size;
	vec2 actualVelocity;
	bool canChangeAnimaion = true;
	Timer clockAnimation;
	SetupDeplacementAnimation_  SetupDeplacementAnimation;
	int isDying=0;
	TimeAttack_ timeAttack;
	double degat;
	double vie;
	double portee = 600;
	double maxVie;
};


double getAngle(const vec2 & target1, const vec2 & target2);