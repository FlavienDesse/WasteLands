#include "Projectile.h"

void  Projectile::SetAtualHitBox(){

	string tempStringPolygon = "POLYGON((";
	polygon tempPolygon;

	std::vector<point > points = this->hitBox.outer();

	for (std::vector<point>::size_type i = 0; i < points.size(); ++i)
	{
		double temp1 = this->GetPosX() + this->speedX + (points[i].x() - (double)this->texture->getWidth() / 2) * ((double)this->sizeX / this->texture->getWidth());
		double temp2 = this->GetPosY() + this->speedY + (points[i].y() - (double)this->texture->getHeight() / 2) * ((double)this->sizeY / this->texture->getHeight());

		tempStringPolygon += to_string(temp1) + " " + to_string(temp2) + ",";


	}
	tempStringPolygon.pop_back();
	tempStringPolygon += "))";

	boost::geometry::read_wkt(
		tempStringPolygon, tempPolygon);
	this->actualHitBox = tempPolygon;
}