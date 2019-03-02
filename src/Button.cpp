#include "Button.h"

Button::Button(string polygon , string type) {

	this->type = type;
	boost::geometry::read_wkt(polygon,this->hitBox);
}


Button::Button(string polygon, string type, int sizeX , int sizeY,int posX, int posY) {
	this->posX = posX;
	this->posY = posY;
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->type = type;
	boost::geometry::read_wkt(polygon, this->hitBox);
}