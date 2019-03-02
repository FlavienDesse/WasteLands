#include "Map.h"








Map::Map() {};

void Map::PushAllButton(Button button) {
	this->allButton.push_back(button);
}

void Map::ClearAllTexturePositionFront() {
	this->allTexturePositionFront.clear();
}
void Map::ClearAllTexturePositionBack() {
	this->allTexturePositionBack.clear();
}

void Map::LoadAllFileMapPlayable(std::experimental::filesystem::v1::path & chemin) {


	for (const auto & allDirectory : std::experimental::filesystem::v1::directory_iterator(chemin)) {

		int const pos = allDirectory.path().u8string().find_last_of('\\') + 1;
		string key = allDirectory.path().u8string().substr(pos, allDirectory.path().u8string().size());
		string extension = GetFileExtension(key);

		if (key == "fond.png") {

			this->currentTextureMap = gl::Texture2d::create(loadImage(allDirectory.path()));
		}
		else if (extension == "png") {
			Decor newDec;

			newDec.SetTexture(gl::Texture2d::create(loadImage(allDirectory.path())));

			ifstream myfile;
			string path = allDirectory.path().u8string();
			path.replace(path.end() - 3, path.end(), "txt");
			myfile.open(path);

			std::string line;
			polygon tempPolygon;

			std::getline(myfile, line);
			int pos = line.find(",");



			newDec.SetSizeX(stof(line.substr(0, pos)));
			newDec.SeSizeY(stof(line.substr(pos + 1, line.size())));


			std::getline(myfile, line);
			pos = line.find(",");
			newDec.SetPositionX(stof(line.substr(0, pos)));
			newDec.SetPositionY(stof(line.substr(pos + 1, line.size())));





			std::getline(myfile, line);
			boost::geometry::read_wkt(line, tempPolygon);
			newDec.SetHitbox(tempPolygon);



			this->allDecor.push_back(newDec);
			myfile.close();
			tempPolygon.clear();

		}
	}
}



void Map::PushBackAllTexturePositionFront(int i) {
	this->allTexturePositionFront.push_back(i);
}


void Map::PushBackAllTexturePositionBack(int i) {
	this->allTexturePositionBack.push_back(i);
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

vector <int>  Map::GetAllTexturePositionFront() {
	return this->allTexturePositionFront;
}
void Map::SetAllTexurePositionFront(vector <int> allTexturePositionFront) {
	this->allTexturePositionFront = allTexturePositionFront;
}
vector <int> Map::GetAllTexturePositionBack() {
	return this->allTexturePositionBack;
}
void Map::SetAllTexturePositionBack(vector <int> allTexturePositionBack) {
	this->allTexturePositionBack = allTexturePositionBack;
}
