#ifndef	MAP_H
#define MAP_H

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include <fstream>
#include "Decor.h"
#include <vector>
#include "Button.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace gl;

class Map {
public:
	Map();
	
	

	TextureRef GetTextureCurrentMap();
	vector <Decor> GetDecor();
	void SetDecor(vector <Decor>);

	




	

	void PushAllButton(Button button);

	
	
	void SetcurrentTextureMap(TextureRef currentTextureMap) { this->currentTextureMap = currentTextureMap;}
	vector <Button> & GetAllButton() { return  this->allButton; }
	void SetAllButton(vector <Button> allButton) {this->allButton = allButton;}
	void clean();
private:
	TextureRef currentTextureMap;
	vector <Decor> allDecor;
	vector <Button> allButton;

	

	
};




std::string GetFileExtension(const std::string& FileName);
#endif