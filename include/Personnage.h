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

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>

using namespace ci;
using namespace ci::app;
using namespace std;

#define DEPLACEMENTWALKX 5
#define DEPLACEMENTWALKY 5
#define DEPLACEMENTJUMPWALKX 20
#define DEPLACEMENTJUMPWALKY 20
#define DEPLACEMENTJUMPRUNX 25
#define DEPLACEMENTJUMPRUNY 25
#define DEPLACEMENTRUNX 15
#define DEPLACEMENTRUNY 15

#define SPEEDANIMATIONSTAND 0.55
#define SPEEDANIMATIONWALK 0.40
#define SPEEDANIMATIONJUMP 0.50
#define SPEEDANIMATIONRUN 0.50
#define SPEEDANIMATIONATTACK 0.55

typedef boost::geometry::model::d2::point_xy<double> point;
typedef boost::geometry::model::polygon< point > polygon;

class Personnage {
public:
	Personnage();
	
	double GetVie();
	double GetVitesse();
	double GetVitesseAttaque();
	double GetDegat();
	double GetArmure();
	double GetTypeDegat();
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
	void SetVitesse(double vitesse);
	void SetVitesseAttaque(double vitesseAttaque);
	void SetDegat(double degat);
	void SetArmure(double armure);
	void SetTypeDegat();
	void SetEtatActuel(string etat);
	void ReceiveDegat(int degat);
	void SetActualAnimation();
	void SetPositionActualAnimation(int pos = -1);
	void SetPosX(double posX);
	void SetPosY(double posY);
	void SetCanChangeAnimationn(bool value);
	double GetPosX();
	double GetPosY();
	short int GetWalkJump();
	void SetWalkJump(short int value);
	float GetOrientation();
	void SetOrientation(float value);

	

	void SetPositionWhenStopPush(std::map<int, bool> touchPressed);
	void JumpFonction(std::map<int, bool> touchPressed);
	bool SetStandIfWalkOpposite(std::map<int, bool> touchPressed);
	void SetWalk(std::map<int, bool> touchPressed);
	bool SetRun(std::map<int, bool> touchPressed);
	bool SetWalkDiagonal(std::map<int, bool> touchPressed);
	bool SetRunDiagonal(std::map<int, bool> touchPressed);
	bool Attack(std::map<int, bool> touchPressed);
	void SetAnimationMainCharacter(std::map<int, bool> touchPressed);
	void SetCollision(bool collision);
	Touches GetallTouches();

	float GetSizeX();
	float GetSizeY();

	void SetSizeX(float sizeX);
	void SetSizeY(float sizeY);

	
	Projectile & GetProjectile() { return this->projectile; }

	polygon GetHitBoxOnCurrentAnimation();
	void SetActuelHitBoxOnCurrentAnimation();
private:
	double vie;
	double vitesse;
	double vitesseAttaque;
	double degat;
	double armure;
	int typeDegat;
	bool canChangeAnimation;
	short int walkJump;
	map<string, vector <pair <ci::gl::TextureRef,polygon>>> animation;
	pair <ci::gl::TextureRef, polygon> actualAnimation;
	string classe;
	int positionActualAnimation =0;
	Timer clockAnimation;
	string etatActuel = "StandR";
	double posX;
	double posY;
	float orientation;
	Touches allTouches;
	bool collision = false;
	double velocityX=0;
	double velocityY=0;
	polygon actualHitBox;
	float sizeX = 150;
	float sizeY=150;

	Projectile projectile;
};


std::string GetFileExtension(const std::string& FileName);
#endif