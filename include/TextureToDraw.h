#pragma once

#ifndef TEXTURETODRAW_H
#define TEXTURETODRAW_H

#include "cinder/gl/Texture.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace gl;
using namespace std;
class TextureToDraw
{
public:
	TextureToDraw();
	~TextureToDraw();

	TextureRef GetTexture() { return this->texture; }
	void SetTexture(TextureRef texture) { this->texture = texture; }

	vec2 GetPos() { return this->pos; }
	void SetPos(vec2 pos) { this->pos= pos; }

	Rectf GetSize() { return this->size; }
	void SetSize(Rectf size) { this->size = size; }

	

	double GetDistance() { return this->distance; }
	void SetDistance(double distance) { this->distance = distance; }

	bool GetDontMove() { return this->dontMove; }
	void SetDontMove(bool dontMove) { this->dontMove = dontMove; }

	string GetSource() { return this->source; }
	void SetSource(string source) { this->source = source; }
	
	float GetOrientation() { return this->orientation; }
	void SetOrientation(float orientation) { this->orientation = orientation; }
private:
	ci::gl::TextureRef texture;
	vec2 pos;
	Rectf size;
	double distance;
	bool dontMove = true;
	string source;
	float orientation;
};

#endif

