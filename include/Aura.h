#pragma once
#ifndef AURA_H
#define AURA_H

#include "cinder/gl/Texture.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Aura {

public:
	Aura(){}
	int GetPosAura() { return this->posAura; }
	void SetPosAura(int posAura) { this->posAura = posAura; }

	gl::TextureRef GetTextureAura() { return this->allTextureAura[actualAura][posAura];  }
	
	void SetAllTextureAura(map<string, vector <gl::TextureRef>> allTextureAura) { this->allTextureAura = allTextureAura; }
	map<string, vector <gl::TextureRef>> & GetAllTextureAura() { return this->allTextureAura; }

	Timer & GetClock() { return this->animationClock; }

	void update();
	void ChangeAura();

	string GetActualArea() { return this->actualAura; }
private:
	int posAura=0;
	map<string,vector <gl::TextureRef>> allTextureAura;
	string actualAura = "Gris";
	Timer animationClock;

	double SPEEDANIMATIONAURA =0.5;
};

#endif