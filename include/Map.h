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
	void LoadAllFileMapPlayable(std::experimental::filesystem::v1::path & chemin);
	

	TextureRef GetTextureCurrentMap();
	vector <Decor> GetDecor();
	void SetDecor(vector <Decor>);

	vector <int> GetAllTexturePositionFront();
	void SetAllTexurePositionFront(vector <int> allTexturePositionFront);
	vector  <int>  GetAllTexturePositionBack();
	void  SetAllTexturePositionBack(vector <int> allTexturePositionBack);


	void PushBackAllTexturePositionFront(int i);
	void PushBackAllTexturePositionBack(int i);

	

	void PushAllButton(Button button);

	void ClearAllTexturePositionFront();
	void ClearAllTexturePositionBack();

	
	void SetcurrentTextureMap(TextureRef currentTextureMap) { this->currentTextureMap = currentTextureMap;}
	vector <Button> & GetAllButton() { return  this->allButton; }
	void SetAllButton(vector <Button> allButton) {this->allButton = allButton;}
private:
	TextureRef currentTextureMap;
	vector <Decor> allDecor;
	vector <int> allTexturePositionFront;
	vector <int> allTexturePositionBack;
	vector <Button> allButton;

	

	
};




std::string GetFileExtension(const std::string& FileName);
#endif