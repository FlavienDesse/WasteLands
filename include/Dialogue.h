#ifndef DIALOGUE_H
#define DIALOGUE_H


#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include <string>
using namespace ci;
using namespace ci::app;
using namespace std;
using namespace ci::gl;

class Dialogue {
public:
	Dialogue(string texte, TextureRef image ): texte(texte), image(image){};
	TextureRef GetImage() { return this->image; }
	void SetImage(TextureRef image) { this->image = image; }

	string GetTexte() { return this -> texte; }
	void SetImage(string texte) { this->texte = texte; }
private:
	TextureRef image;
	string texte;
};


#endif