#pragma once
#ifndef PERSONNAGE_H
#define PERSONNAGE_H
#include <map>
#include <filesystem>
#include "cinder/gl/Texture.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "Touches.h"
#include "Projectile.h"
#include "Aura.h"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>

using namespace ci;
using namespace ci::app;
using namespace std;



typedef boost::geometry::model::d2::point_xy<double> point;
typedef boost::geometry::model::polygon< point > polygon;

class Personnage {
public:
	Personnage();
	
	double GetVie();

	double GetDegat();
	double GetArmure();

	void SetVelocityX(double velocityX);
	void SetVelocityY(double velocityY);
	double GetVelocityX();
	double GetVelocityY ();

	pair <ci::gl::TextureRef, polygon>  GetActualAnimation();
	map<string, vector <pair <ci::gl::TextureRef,polygon>>>  & GetAnimation();
	
	void SetAnimation(map<string, vector <pair <ci::gl::TextureRef, polygon>>> animation) { this->animation = animation; }
	int GetPositionActualAnimation();
	Timer & GetClockAnimation();
	string GetEtatActuel();
	bool GetCanChangeAnimation();
	void SetVie(double vie);

	void SetDegat(double degat);
	void SetArmure(double armure);

	void SetEtatActuel(string etat);
	void ReceiveDegat(int degat);
	void SetActualAnimation();

	void SetPosX(double posX);
	void SetPosY(double posY);
	void SetCanChangeAnimationn(bool value);
	double GetPosX();
	double GetPosY();
	

	

	


	
	Touches GetallTouches();

	float GetSizeX();
	float GetSizeY();

	void SetSizeX(float sizeX);
	void SetSizeY(float sizeY);

	
	void SetPointerToAllProjectile(vector<Projectile> * allProjectile) { this->pointerToAllProjectile=allProjectile; }

	vector<Projectile> GetProjectile() { return this->projectile; }
	void SetProjectile(vector<Projectile> projectile) { this->projectile = projectile; }
	polygon GetHitBoxOnCurrentAnimation();
	void SetActuelHitBoxOnCurrentAnimation();


	Aura & GetAura() { return this->aura; }
	void  SetAura(Aura aura) {  this->aura=aura; }

	void SetOrientation(vec2 orientation) { this->orientation = orientation; }
	vec2 & GetOrientation() { return this->orientation; }

	void Update(std::map<int, bool> & touchPressed);
	void SetEtatWithOrientation(std::map<int, bool>&  touchPressed);
	void SetCurrentAnimation(std::map<int, bool>&  touchPressed);
	void SetVelocityWalk(std::map<int, bool> & touchPressed);
	void SetVelocityRun(std::map<int, bool>& touchPressed);
	void SetVelocityJump(std::map<int, bool>& touchPressed);
	void Shoot(string source, const Projectile & projectile, double orientation, vec2  & direction);

	void SetMaxVie(double maxVie) { this->maxVie = maxVie; }
	double GetMaxVie() {return this->maxVie ; }

	int GetIsDying() { return this->isDying; }
	void SetIsDying(int isDying) { this->isDying = isDying; }
private:
	double vie = 100;
	double maxVie = 100;
	vec2 orientation{ 0,1 };
	int isDying = 0;
	double degat = 100;
	double armure;
	
	bool canChangeAnimation = true;
	short int walkJump;
	map<string, vector <pair <ci::gl::TextureRef,polygon>>> animation;
	pair <ci::gl::TextureRef, polygon> actualAnimation;
	string classe;
	int positionActualAnimation =0;
	Timer clockAnimation;
	string etatActuel = "StandR";
	string lastEtatActuel;
	double posX;
	double posY;
	

	Touches allTouches;
	bool collision = false;
	double velocityX=0;
	double velocityY=0;
	polygon actualHitBox;
	float sizeX = 150;
	float sizeY=150;
	
	vector<Projectile>* pointerToAllProjectile=NULL;
	vector<Projectile> projectile;

	Aura aura;
	
	float DEPLACEMENTWALKX = 5;
	float DEPLACEMENTWALKY = 5;
	float DEPLACEMENTJUMPWALKX = 20;
	float DEPLACEMENTJUMPWALKY = 20;
	float DEPLACEMENTJUMPRUNX = 25;
	float DEPLACEMENTJUMPRUNY = 25;
	float DEPLACEMENTRUNX = 15;
	float DEPLACEMENTRUNY = 15;

	float SPEEDANIMATIONSTAND = 0.55;
	float SPEEDANIMATIONWALK = 0.40;
	float SPEEDANIMATIONJUMP = 0.50;
	float SPEEDANIMATIONRUN = 0.50;
	float SPEEDANIMATIONATTACK = 0.005;
	float SPEEDANIMATIONDIE = 1;
};


std::string GetFileExtension(const std::string& FileName);
#endif