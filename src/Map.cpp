#include "Map.h"








Map::Map() {};

void Map::PushAllButton(Button button) {
	this->allButton.push_back(button);
}








TextureRef Map::GetTextureCurrentMap() {
	return this->currentTextureMap;
}

vector <Decor> Map::GetDecor() {
	return this->allDecor;
}
void Map::SetDecor(vector <Decor> allDecor) {
	this->allDecor = allDecor;
}


