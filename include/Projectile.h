#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "cinder/Utilities.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>

typedef boost::geometry::model::d2::point_xy<double> point;
typedef boost::geometry::model::polygon< point > polygon;

using namespace ci;
using namespace app;
using namespace std;
using namespace gl;
class Projectile {
public:
	Projectile() {};

	TextureRef GetTexture() { return this->texture; }
	void SetTexture(TextureRef texture) { this->texture = texture; }

	polygon GetHitBox() { return this->hitBox; }
	void SetHitBox(polygon hitBox) { this->hitBox = hitBox; }

	string GetSource() { return this->source; }
	void SetSource(string source) { this->source= source; }


	double GetDommage() { return this->dommage; }
	void SetDommage(double dommage) { this->dommage = dommage; }

	int GetSpeedX() { return this->speedX; }
	void SetSpeedX(double speedX) { this->speedX= speedX; }

	int GetSpeedY() { return this->speedY; }
	void SetSpeedY(double speedY) { this->speedY = speedY; }

	int GetPosX() { return this->posX; }
	void SetPosX(int posX) { this->posX = posX; }

	int GetPosY() { return this->posY; }
	void SetPosY(int posY) { this->posY = posY; }

	int GetSizeX() { return this->sizeX; }
	void SetSizeX(int sizeX) { this->sizeX = sizeX; }

	int GetSizeY() { return this->sizeY; }
	void SetSizeY(int sizeY) { this->sizeY = sizeY; }

	void SetAtualHitBox();
	polygon GetActualHitBox(){ return this->actualHitBox; }

	float GetOrientation() { return this->orientation; }
	void SetOrientation(float orientation) { this->orientation = orientation; }
private:
	TextureRef texture;
	polygon hitBox;
	polygon actualHitBox;
	string source;
	double dommage;

	int speedX;
	int speedY;

	int posX;
	int posY;

	int sizeX;
	int sizeY;

	float orientation;
};

#endif
