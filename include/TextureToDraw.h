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
	void SetTexture(Rectf size) { this->size = size; }

private:
	ci::gl::TextureRef texture;
	vec2 pos;
	Rectf size;

};

#endif

