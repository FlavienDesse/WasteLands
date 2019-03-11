

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/algorithms/distance.hpp>
typedef boost::geometry::model::d2::point_xy<double> point;
typedef boost::geometry::model::polygon< point > polygon;


#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "Personnage.h"
#include "cinder/qtime/QuickTimeGlImplAvf.h"
#include "Decor.h"
#include "Map.h"
#include "ProgressBar.h"
#include <Windows.h>
#include "Resources.h"
#include "Projectile.h"
#include "TextureToDraw.h"

//0 Droite
//1 Haut
//2 gauche
//3 Bas



/* MAP 


0 = menu 
1=choix perso
2 = map ou on peux bouger / jouer
3 = credits 
4 = echap




*/

//WalkL BottomLeft LEft
//WalkR = Bottome BottomRight et Right
//WalktTR = Tr Top
//WalkTL = TL






using namespace ci;
using namespace ci::app;
using namespace std;
using namespace gl;




class WasteLands : public App {
public:
	void setup() override;
	WasteLands();
	void mouseDown(MouseEvent event) override;
	void keyDown(KeyEvent event) override;
	void keyUp(KeyEvent event) override;
	void mouseMove(MouseEvent event) override;
	void update() override;
	void draw() override;
	void resize() override;
	void drawTex(const ci::gl::Texture2dRef &tex, const ci::vec2 &pos, const Rectf & size);
	bool Collision();
	void SetPositionDecor();
	void SetCameraOutOfBound();
	void DrawPrincipalMenu();
	void DrawMainMap();

	void ClickOnPlay();
	void ClickOnCredits();

	void AttribAllImage();

	void ResizeButton();
	void DrawButton();
private:
	std::map<int, bool> touchPressed;
	Personnage mainCharacter;

	vector <Projectile> allProjectile;

	int actualMap =0;
	int zoom = 1;
	Map currentMap;
	ProgressBar progressBarVar;
	vector <TextureToDraw> allThingToDraw;
};



void WasteLands::ResizeButton() {
	for (auto & i : this->currentMap.GetAllButton()) {
		

		i.SetPosX((i.GetInitialPosX() * getWindowWidth()) / this->currentMap.GetTextureCurrentMap()->getWidth());
		i.SetPosY((i.GetInitialPosY()* getWindowHeight()) / this->currentMap.GetTextureCurrentMap()->getHeight());
		i.SetSizeX((i.GetInitialSizeX() * getWindowWidth()) / this->currentMap.GetTextureCurrentMap()->getWidth());
		i.SetSizeY((i.GetInitialSizeY()* getWindowHeight()) / this->currentMap.GetTextureCurrentMap()->getHeight());


		string tempStringPolygon = "POLYGON((";
		polygon tempPolygon;
		std::vector<point > points = i.GetInitialHitBox().outer();
		
		for (std::vector<point>::size_type j = 0; j < points.size(); ++j)
		{
			double temp1 = (points[j].x() * getWindowWidth()) / this->currentMap.GetTextureCurrentMap()->getWidth();
			double temp2 = (points[j].y()* getWindowHeight()) / this->currentMap.GetTextureCurrentMap()->getHeight();

			tempStringPolygon += to_string(temp1) + " " + to_string(temp2) + ",";

		}
		tempStringPolygon.pop_back();
		tempStringPolygon += "))";
		console() << tempStringPolygon << endl;
		boost::geometry::read_wkt(
			tempStringPolygon, tempPolygon);
		i.SetHitbox( tempPolygon);
		
		
		
		
	}

}

WasteLands::WasteLands() {
	
}

void WasteLands::AttribAllImage() {
	
	this->currentMap.SetAllButton(this->progressBarVar.GetAllButton());
	this->currentMap.SetcurrentTextureMap(this->progressBarVar.GetCurrentTextureMap());
	
	if (this->progressBarVar.GetMainCharacter().GetAnimation().size() != 0) {
		this->mainCharacter = this->progressBarVar.GetMainCharacter();
		this->mainCharacter.SetActualAnimation();
		this->mainCharacter.GetClockAnimation().start();
		this->mainCharacter.SetPosX(1);
		this->mainCharacter.SetPosY(1);
	}
	if (this->progressBarVar.GetAllDecor().size() != 0){
		
		this->currentMap.SetDecor(this->progressBarVar.GetAllDecor());
	}
	this->ResizeButton();
}

void WasteLands::resize() {
	switch (this->actualMap)
	{
	case 0:
		
		this->ResizeButton();
		
		break;
	case 1:

		break;

	}

}

void WasteLands::SetCameraOutOfBound()
{

	mat4 view = getModelMatrix();
	if (this->getWindowWidth() / 2 >= this->mainCharacter.GetPosX()) {

		view[3][0] = 0;


	}
	else if (this->currentMap.GetTextureCurrentMap()->getWidth() <= this->mainCharacter.GetPosX() + this->getWindowWidth() / 2) {
		view[3][0] = -this->currentMap.GetTextureCurrentMap()->getWidth() + this->getWindowWidth();

	}
	else {

		view[3][0] = -this->mainCharacter.GetPosX() + this->getWindowWidth() / 2;
	}

	if (this->getWindowHeight() / 2 >= this->mainCharacter.GetPosY()) {

		view[3][1] = 0;


	}
	else if (this->currentMap.GetTextureCurrentMap()->getHeight() <= this->mainCharacter.GetPosY() + this->getWindowHeight() / 2) {
		view[3][1] = -this->currentMap.GetTextureCurrentMap()->getHeight() + this->getWindowHeight();

	}
	else {

		view[3][1] = -this->mainCharacter.GetPosY() + this->getWindowHeight() / 2;
	}


	gl::setModelMatrix(view);

}



void WasteLands::mouseMove(MouseEvent event) {
	for (auto i : this->currentMap.GetAllButton()) {
		if (i.IsInButton(point(event.getX(), event.getY())) && i.GetActive()) {

		}
	}
}

void WasteLands::ClickOnPlay() {
	

	this->progressBarVar.clear();




	std::experimental::filesystem::v1::path  path = getAssetDirectories()[0].generic_u8string() + "\\Map\\Spawn";



	this->progressBarVar.SetupMapAndCharacter(path, "Archer");
	
	this->actualMap = 2;
}
void  WasteLands::ClickOnCredits() {
	
}


void WasteLands::setup()
{
	setFrameRate(60);
	//setFullScreen(true);
	//setWindowPos(vec2(0, 0));
	//setWindowSize(vec2(getDisplay()->getWidth(), getDisplay()->getHeight()));
	std::experimental::filesystem::v1::path chemin = getAssetDirectories()[0].u8string() + "\\Map\\PrincipalMenu";
	
	this->progressBarVar.SetupMenu(chemin);
	
	

}

void WasteLands::mouseDown(MouseEvent event)
{
	switch (this->actualMap)
	{
	case 0:
		for (auto i : this->currentMap.GetAllButton()) {
			if (i.IsInButton(point(event.getX(), event.getY())) && i.GetActive()) {
				if (i.GetTypeButton() == "ClickOnPlay()") {
					this->ClickOnPlay();
				}
			}
		}
		break;
	}
}

void WasteLands::keyDown(KeyEvent event)
{
	switch (this->actualMap)
	{
	case 2:
		if (event.isShiftDown()) {
			this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("Shift")] = true;

		}

		int touch = event.getCode();
		this->touchPressed[touch] = true;

		if (this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("Shift")] && this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkR")]) {
			this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("RunR")] = true;
		}
		if (this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("Shift")] && this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkL")]) {
			this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("RunL")] = true;
		}
		if (this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("Shift")] && this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkT")]) {
			this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("RunT")] = true;
		}
		if (this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("Shift")] && this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkB")]) {
			this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("RunB")] = true;

		}

		if (this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkR")] && this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkT")]) {
			this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkTR")] = true;
		}
		if (this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkT")] && this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkL")]) {
			this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkTL")] = true;
		}
		if (this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkL")] && this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkB")]) {
			this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkBL")] = true;
		}
		if (this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkB")] && this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkR")]) {
			this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkBR")] = true;
		}

		if (this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("Shift")] && this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkTR")]) {
			this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("RunTR")] = true;
		}
		if (this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("Shift")] && this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkTL")]) {
			this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("RunTL")] = true;
		}
		if (this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("Shift")] && this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkBL")]) {
			this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("RunBL")] = true;
		}
		if (this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("Shift")] && this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkBR")]) {
			this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("RunBR")] = true;

		}
		break;
	
	}
	

}
void WasteLands::keyUp(KeyEvent event)
{
	switch (this->actualMap)
	{
	case 2:
		
		if (event.isShiftDown() == false) {

			this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("Shift")] = false;
		}
		int touch = event.getCode();
		this->touchPressed[touch] = false;
		if ((this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("Shift")] == false || this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkR")] == false) && this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("RunR")] == true) {
			this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("RunR")] = false;
		}
		if ((this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("Shift")] == false || this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkL")] == false) && this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("RunL")] == true) {
			this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("RunL")] = false;
		}
		if ((this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("Shift")] == false || this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkT")] == false) && this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("RunT")] == true) {
			this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("RunT")] = false;
		}
		if ((this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("Shift")] == false || this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkB")] == false) && this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("RunB")] == true) {
			this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("RunB")] = false;
		}


		if ((this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkR")] == false || this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkT")] == false) && this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkTR")] == true) {
			this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkTR")] = false;
		}
		if ((this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkT")] == false || this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkL")] == false) && this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkTL")] == true) {
			this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkTL")] = false;
		}
		if ((this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkL")] == false || this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkB")] == false) && this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkBL")] == true) {
			this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkBL")] = false;
		}
		if ((this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkB")] == false || this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkR")] == false) && this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkBR")] == true) {
			this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkBR")] = false;
		}

		if ((this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("Shift")] == false || this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkTR")] == false) && this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("RunTR")] == true) {
			this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("RunTR")] = false;
		}
		if ((this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("Shift")] == false || this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkTL")] == false) && this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("RunTL")] == true) {
			this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("RunTL")] = false;
		}
		if ((this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("Shift")] == false || this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkBL")] == false) && this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("RunBL")] == true) {
			this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("RunBL")] = false;
		}
		if ((this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("Shift")] == false || this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("WalkBR")] == false) && this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("RunBR")] == true) {
			this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("RunBR")] = false;
		}

		break;
	
	}
	


}





bool WasteLands::Collision() {
	bool temp;


	for (int i = 0; i < this->currentMap.GetDecor().size(); i++) {

		temp = boost::geometry::intersects(this->mainCharacter.GetHitBoxOnCurrentAnimation(), this->currentMap.GetDecor()[i].GetHitBox());
		if (temp == true) {
			return true;
		}


	}
	return false;

}


double GetTheMaximumDistance(polygon Polygon, point Point) {
	double maxDistance = 0;
	double temp1;
	point temp1;
	for (auto i : Polygon.outer()) {
		temp1 = boost::geometry::distance(point(i.x(), i.y() * getWindowWidth()), Point);

		if (maxDistance < temp1) {

			maxDistance = temp1;
		}
	}
	return maxDistance;
}


void WasteLands::SetPositionDecor() {
	bool temp;
	double temp1;
	double temp2;
	for (auto i : this->currentMap.GetDecor()) {
		bool temp = false;
		temp1=GetTheMaximumDistance(i.GetHitBoxTexture(), point(0,0));
		temp2=GetTheMaximumDistance(this->mainCharacter.GetHitBoxOnCurrentAnimation(), point(0, 0));
		if (temp1 > temp2) {

		}
	}
}



void WasteLands::update()
{
	/*HINSTANCE hInst;
	hInst = GetModuleHandle(NULL);
	HCURSOR mainCursor=LoadCursor(hInst, C);*/
	
	if (this->progressBarVar.GetTerminated()) {
		switch (this->actualMap)
		{
		case 0:

			break;
		case 2:
			

			this->mainCharacter.SetAnimationMainCharacter(this->touchPressed);

			this->mainCharacter.SetActuelHitBoxOnCurrentAnimation();

			if (this->Collision() == false) {

				this->mainCharacter.SetPosX(this->mainCharacter.GetVelocityX() + this->mainCharacter.GetPosX());

				this->mainCharacter.SetPosY(this->mainCharacter.GetVelocityY() + this->mainCharacter.GetPosY());
			}
			else {

			}

			this->mainCharacter.SetVelocityX(0);
			this->mainCharacter.SetVelocityY(0);


			this->SetPositionDecor();


			break;
		default:
			break;
		}
	}
	

	
	



}


void WasteLands::DrawMainMap() {

	

	gl::ScopedModelMatrix scpModel;
	gl::translate(getWindowCenter());
	gl::scale(vec2(this->zoom));

	this->SetCameraOutOfBound();
	gl::draw(this->currentMap.GetTextureCurrentMap());


	Rectf size(0, 0, this->mainCharacter.GetSizeX(), this->mainCharacter.GetSizeY());

	this->drawTex(this->currentMap.GetTextureCurrentMap(),vec2(0,0),Rectf(0,0,0,0));

	for (auto i : this->allThingToDraw) {
		this->drawTex(i.GetTexture(), i.GetPos(), i.GetSize());
	}


	std::vector<point > points = this->mainCharacter.GetHitBoxOnCurrentAnimation().outer();

	for (int a = 0; a < points.size(); a++) {
		if (a + 1 == points.size()) {
			gl::drawLine(vec2(points[a].x(), points[a].y()), vec2(points[0].x(), points[0].y()));
		}
		else {
			gl::drawLine(vec2(points[a].x(), points[a].y()), vec2(points[a + 1].x(), points[a + 1].y()));
		}
	}

	this->DrawButton();

}

void WasteLands::DrawButton() {
	gl::ScopedModelMatrix scpModel;
	for (auto i : this->currentMap.GetAllButton()) {
		Rectf sizeButton(0, 0, i.GetSizeX(), i.GetSizeY());
		vec2 pos = vec2(i.GetPosX(), i.GetPosY());
		gl::translate(pos);
		gl::draw(i.GetTexture(), sizeButton);


		

	}
}

void WasteLands::DrawPrincipalMenu() {
	
	
	Rectf size(0, 0,getWindowWidth(), getWindowHeight());
	gl::draw(this->currentMap.GetTextureCurrentMap(), size);
	
	

	this->DrawButton();
	
}
void WasteLands::draw()
{
	
	if (this->progressBarVar.GetTerminated()) {
		
		gl::clear(Color(0, 0, 0));

		switch (this->actualMap)
		{
		case 0:
			this->DrawPrincipalMenu();
			break;
		case 2:
			this->DrawMainMap();
			break;
		default:
			break;
		}
	}
	else {
		gl::clear(Color(0, 0, 0));
		if (this->progressBarVar.getProgress() < 1.0f) {
			// Draw the progress bar.
			gl::ScopedModelMatrix scpModel;

			const auto size = vec2(256, 16);
			gl::translate(getWindowCenter());
			gl::translate(-0.5f * size);
			gl::drawSolidRect({ 0, 0, this->progressBarVar.getProgress() * size.x, size.y });
			gl::drawStrokedRect({ 0, 0, size.x, size.y });
			// Draw an animated spinner.
			

			const float angle = float(getElapsedSeconds());
			const float step = glm::radians(30.0f);
			const float radius = 25.0f;
			
			gl::translate(vec2(0, 100));
			gl::translate(0.5f * size);
			for (int i = 0; i < 12; ++i) {
				gl::drawSolidCircle(radius * vec2(glm::sin(i * step - angle), glm::cos(i * step - angle)), 3.0f);
			}
		}
		else {
			this->progressBarVar.clean();
			this->AttribAllImage();
		}
		
	}
	if (this->currentMap.GetAllButton().size() != 0) {
		auto i = this->currentMap.GetAllButton()[0];
		for (int a = 0; a < i.GetHitBoxVector().size(); a++) {

			if (a + 1 == i.GetHitBoxVector().size()) {
				gl::drawLine(vec2(i.GetHitBoxVector()[a].x(), i.GetHitBoxVector()[a].y()), vec2(i.GetHitBoxVector()[0].x(), i.GetHitBoxVector()[0].y()));
			}
			else {
				
				gl::drawLine(vec2(i.GetHitBoxVector()[a].x(), i.GetHitBoxVector()[a].y()), vec2(i.GetHitBoxVector()[a + 1].x(), i.GetHitBoxVector()[a + 1].y()));
			}
		}

	}
	

	gl::drawString("Framerate: " + to_string(getAverageFps()), vec2(0, 0), Color::white(), Font("Arial", 12));


}




void WasteLands::drawTex(const ci::gl::Texture2dRef &tex, const ci::vec2 &pos, const Rectf & size)
{
	gl::ScopedModelMatrix scpModel;
	gl::translate(pos - vec2(size.getWidth() / 2, size.getHeight() / 2));
	if (size.getHeight() == 0 && size.getWidth() == 0) {
		gl::draw(tex);
	}
	else {
		gl::draw(tex, size);
	}
	
}




CINDER_APP(WasteLands, RendererGl(),
	[&](App::Settings *settings) {


})