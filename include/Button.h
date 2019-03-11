#ifndef BUTTON_H
#define BUTTON_H

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
typedef boost::geometry::model::d2::point_xy<double> point;
typedef boost::geometry::model::polygon< point > polygon;
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "Personnage.h"

using namespace gl;
using namespace ci;
using namespace ci::app;
using namespace std;

class Button {
public:
	Button() {};
	Button(string polygon, string type);
	Button(string polygon, string type,int  sizeX , int sizeY, int posX , int posY);
	void SetHitbox(polygon hitBox) { this->hitBox = hitBox;}
	string GetTypeButton() { return this->type; }
	bool IsInButton(point point) { return (boost::geometry::within(point, this->hitBox)); }
	vector <point> GetHitBoxVector() { return this->hitBox.outer(); }


	void SetType(string type) { this->type = type; }
	void SetType(polygon polygon) { this->hitBox = polygon; }
	void SetSizeX(int sizeX) { this->sizeX = sizeX; }
	void SetSizeY(int sizeY) { this->sizeY = sizeY; }
	void SetPosX(int posX) { this->posX = posX; }
	void SetPosY(int posY) { this->posY = posY; }
	void SetPosInitialiseX(int posX) { this->posXInitial = posX; }
	void SetPosInitialiseY(int posY) { this->posYInitial = posY; }
	
	void SetSizeInitialiseX(int sizeX) { this->sizeXInitial = sizeX; }
	void SetSizeInitialiseY(int sizeY) { this->sizeYInitial = sizeY; }
	void SetTexture(TextureRef texture) { this->texture = texture; }

	string GetType() { return this->type; }
	int GetSizeX() { return this->sizeX; }
	int GetSizeY() { return this->sizeY; }
	int GetPosX() { return this->posX; }
	int GetPosY() { return this->posY; }
	TextureRef GetTexture() { return this->texture; }

	int GetInitialPosX(){return this->posXInitial; }
	int GetInitialPosY() { return this->posYInitial; }

	int GetInitialSizeX() { return this->sizeXInitial; }
	int GetInitialSizeY() { return this->sizeYInitial; }

	void SetActive(bool active) { this->active = active; }
	bool GetActive() { return this->active; }

	polygon GetInitialHitBox() {return this->hitBoxInitial;}
	void SetInitialHitBox(polygon hitbox) { this->hitBoxInitial = hitBox; }


private:
	TextureRef texture;
	string type;
	polygon hitBox;
	int sizeX;
	int sizeY;
	int posX =0;
	int posY=0;

	int posXInitial;
	int posYInitial;

	int sizeXInitial;
	int sizeYInitial;

	polygon hitBoxInitial;
	bool active = false;
};

#endif