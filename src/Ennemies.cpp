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