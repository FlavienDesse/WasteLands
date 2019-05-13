

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/algorithms/distance.hpp>



typedef boost::geometry::model::d2::point_xy<double> point;
typedef boost::geometry::model::polygon< point > polygon;
#include <iostream>
#include "utf8cpp/checked.h"
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
#include "ciWMFVideoPlayer.h"
#include "Ennemies.h"
#include <functional>
#include "cinder\audio\audio.h"
#include "cinder/Text.h"
#include "cinder/Utilities.h"
#include "cinder/ImageIo.h"
#include "cinder/Font.h"
#include <vector>
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
5 = on est mouru
6 = dialogue 
7 = Factory
8 = Factory dialogue
9 = fin du jeu
*/

//WalkL = BottomLeft LEft
//WalkR = Bottome BottomRight et Right
//WalktTR = Tr Top
//WalkTL = TL

// Aura vert = végétaux
// Jaune = recyclable ( verre , carton , plastique , conserve )
// Noir = non recycable
// Gris = ?



using namespace ci;
using namespace ci::app;
using namespace std;
using namespace gl;
using namespace audio;







class WasteLands : public App {
public:
	void setup() override;
	WasteLands();
	void mouseDown(MouseEvent event) override;
	void keyDown(KeyEvent event) override;
	void keyUp(KeyEvent event) override;
	void mouseMove(MouseEvent event) override;
	void mouseUp(MouseEvent event) override;
	void update() override;
	void draw() override;
	void resize() override;
	void drawTex(const ci::gl::Texture2dRef &tex, const ci::vec2 &pos, const Rectf & size);
	void drawMainCharacter(const ci::gl::Texture2dRef& tex, const ci::vec2& pos, const Rectf& size);
	
	void SetPositionDecor();
	void SetCameraOutOfBound();
	void DrawPrincipalMenu();
	void DrawMainMap();

	void ClickOnPlay();
	void ClickOnCredits();
	void ClickOnReplay();
	void AttribAllImage(int pos);

	void ResizeButton(vec2 &sizeFond);
	void DrawButton();

	polygon TransformHitBoxInOneray(polygon Polygon);
	void  DrawMenuDie();
	void drawProjectile(const ci::gl::Texture2dRef &tex, const ci::vec2 &pos, const Rectf & size, double orientation);
	void DrawHp();
	void Case2Update();
	void DrawDialogue(Dialogue & dialogueToDraw);
	void changeMapFactory();
	void Clean();
	void DrawInteractive();
	void UpdateSound();
	void DrawDivers();
	void SpawnEnnemiFactory();
	void DrawIndicatorAura();
	void DrawHpBoss(Ennemies & a);
private:
	std::map<int, bool> touchPressed;
	Personnage mainCharacter;
	vector<pair<vec2, function<void(WasteLands&)>>> allInteractive;
	vector <Projectile> allProjectile;
	map <string, TextureRef> allDialogueLoad;
	int lastMap = -1;
	int actualMap =-1;
	int zoom = 1;
	Map currentMap;
	ProgressBar progressBarVar;
	vector <TextureToDraw> allThingToDraw;
	map<string, Ennemiesload> allEnnemiesLoad;
	vector <Dialogue> allDialogue;
	vector<Ennemies> allEnnemies;
	ciWMFVideoPlayer * Video = NULL;
	TextureRef mTextureForInteract;
	
	Font mFont = Font("Times New Roman", 32);
	
	Font fontDialogue = Font("Arial", 25);

	map <string, SourceFileRef> allAudioLoad;
	VoiceRef actualSoundRef;
	string soundName ;

	map<string, TextureRef> diversTexture;

	void ChangeSound(string name) {
		this->soundName = name;
		this->actualSoundRef = Voice::create(this->allAudioLoad[name]);
		this->actualSoundRef->start();
	}

	
};

void DebugDrawPolygon(polygon polygon) {
	std::vector<point > points = polygon.outer();

	for (std::vector<point>::size_type i = 0; i < points.size(); ++i)
	{
		if (i + 1 != points.size()) {
			drawLine(vec2(points[i].x(), points[i].y()), vec2(points[i + 1].x(), points[i + 1].y()));
		}
		else {
			drawLine(vec2(points[i].x(), points[i].y()), vec2(points[0].x(), points[0].y()));
		}


	}
}

void WasteLands::ResizeButton(vec2 &sizeFond) {
	for (auto & i : this->currentMap.GetAllButton()) {
		
		
		i.SetPosX((i.GetInitialPosX() * getWindowWidth()) / sizeFond.x);
		i.SetPosY((i.GetInitialPosY()* getWindowHeight()) / sizeFond.y);
		i.SetSizeX((i.GetInitialSizeX() * getWindowWidth()) / sizeFond.x);
		i.SetSizeY((i.GetInitialSizeY()* getWindowHeight()) / sizeFond.y);


		string tempStringPolygon = "POLYGON((";
		polygon tempPolygon;
		std::vector<point > points = i.GetInitialHitBox().outer();
		
		for (std::vector<point>::size_type j = 0; j < points.size(); ++j)
		{
			double temp1 = (points[j].x() * getWindowWidth()) / sizeFond.x;
			double temp2 = (points[j].y()* getWindowHeight()) / sizeFond.y;

			tempStringPolygon += to_string(temp1) + " " + to_string(temp2) + ",";

		}
		tempStringPolygon.pop_back();
		tempStringPolygon += "))";
	
		boost::geometry::read_wkt(
			tempStringPolygon, tempPolygon);
		i.SetHitbox( tempPolygon);
		
		
		
		
	}
	
}



double getAngle(const vec2 & target1, const vec2 & target2) {
	double angle = atan2(target1.y - target2.y, target1.x - target2.x);
	if (angle < 0) {
		angle += 2 * M_PI;
	}


	return angle;
}

WasteLands::WasteLands() {
	
}

void WasteLands::changeMapFactory() {
	std::experimental::filesystem::v1::path  path = getAssetDirectories()[0].generic_u8string() + "\\Map\\Factory";



	this->progressBarVar.SetupMap(path, 8);
}


void WasteLands::AttribAllImage(int pos) {
	this->currentMap.SetcurrentTextureMap(this->progressBarVar.GetCurrentTextureMap());
	this->lastMap = this->actualMap;
	this->actualMap = pos;
	switch (pos)
	{
	case 0:
	{
		this->Clean();
		this->currentMap.SetAllButton(this->progressBarVar.GetAllButton());
		if (this->progressBarVar.GetLoadedMovie() == true) {
			this->Video = &this->progressBarVar.GetVideo();

			Video->play();
		}
		this->allAudioLoad = this->progressBarVar.GetSound();
		this->ResizeButton(vec2(this->currentMap.GetTextureCurrentMap()->getWidth(), this->currentMap.GetTextureCurrentMap()->getHeight()));


		this->ChangeSound("intro");
		
		
	}
		break;
	
	case 2: {
		this->Clean();
	}
		break;
	
	case 5:
	{
		
		this->ResizeButton(vec2(1920,1080));
	}
	break;
	case 6:
	{
		

		this->Clean();
		
		this->diversTexture = this->progressBarVar.GetDivers();
		this->allDialogueLoad = this->progressBarVar.GetallDialogue();
		this->currentMap.SetAllButton(this->progressBarVar.GetAllButton());
		if (this->progressBarVar.GetMainCharacter().GetAnimation().size() != 0) {
			this->mainCharacter = this->progressBarVar.GetMainCharacter();
			this->mainCharacter.SetActualAnimation();
			this->mainCharacter.SetPointerToAllProjectile(&this->allProjectile);
			this->mainCharacter.SetProjectile(this->progressBarVar.GetAllProjectileCharacter());
			this->mainCharacter.GetClockAnimation().start();
			this->mainCharacter.SetPosX(1880);
			this->mainCharacter.SetPosY(1110);
		}
		if (this->progressBarVar.GetAllDecor().size() != 0) {

			this->currentMap.SetDecor(this->progressBarVar.GetAllDecor());
			for (auto i : this->currentMap.GetDecor()) {
				TextureToDraw temp;
				temp.SetSource("Decor");
				temp.SetDistance(boost::geometry::distance(this->TransformHitBoxInOneray(i.GetHitBoxTexture()), point(this->currentMap.GetTextureCurrentMap()->getActualWidth(), this->currentMap.GetTextureCurrentMap()->getActualHeight()*getWindowWidth())));
				temp.SetPos(vec2(i.GetPositionX(), i.GetPositionY()));
			
				temp.SetSize(Rectf(0, 0, i.GetSizeX(), i.GetSizeY()));
				temp.SetTexture(i.GetTexture());
				this->allThingToDraw.push_back(temp);
			}
		}
		this->allEnnemiesLoad = this->progressBarVar.GetEnnemiesLoad();


		
		this->mainCharacter.GetAura().GetClock().start();
	
		
		this->allDialogue.push_back(Dialogue(string("Bonjour, humain ! Je suis Whaea, deesse de la nature. Je t'ai choisi pour combattre les wastes."), this->allDialogueLoad["Dialogue-Nature"]));
		this->allDialogue.push_back(Dialogue(string("Ce sont des etres resultants de l'antique pollution humaine."), this->allDialogueLoad["Dialogue-Nature"]));
		this->allDialogue.push_back(Dialogue(string("Pour que tu puisses les vaincre, je t'ai fait don des pouvoirs elementaires du sorting.La seule magie capable de les purifier."), this->allDialogueLoad["Dialogue-Nature"]));
		this->allDialogue.push_back(Dialogue(string("Dirige-toi vers l'est pour affronter Fir, le premier general des wastes que tu devras vaincre."), this->allDialogueLoad["Dialogue-Nature"]));
		this->allDialogue.push_back(Dialogue(string("Va heros, va accomplir ton destin !"), this->allDialogueLoad["Dialogue-Nature"]));
		
		allInteractive.push_back(std::make_pair(vec2(3821,1247), &WasteLands::changeMapFactory));
		

		
		break;
	}
	case 8:
		this->Clean();
	
	
		if (this->progressBarVar.GetAllDecor().size() != 0) {

			this->currentMap.SetDecor(this->progressBarVar.GetAllDecor());
			for (auto i : this->currentMap.GetDecor()) {
				TextureToDraw temp;

				temp.SetDistance(boost::geometry::distance(this->TransformHitBoxInOneray(i.GetHitBoxTexture()), point(this->currentMap.GetTextureCurrentMap()->getActualWidth(), this->currentMap.GetTextureCurrentMap()->getActualHeight()*getWindowWidth())));
				temp.SetPos(vec2(i.GetPositionX(), i.GetPositionY()));
				temp.SetSize(Rectf(0, 0, i.GetSizeX(), i.GetSizeY()));
				temp.SetTexture(i.GetTexture());
				this->allThingToDraw.push_back(temp);
			}
		}
		
		this->mainCharacter.SetPosX(500);
		this->mainCharacter.SetPosY(500);
		
		this->allDialogue.push_back(Dialogue(string("Whaea se reveille enfin.Je suppose que tu es son champion."), this->allDialogueLoad["Dialogue-Sapin_Arch"]));
		this->allDialogue.push_back(Dialogue(string("Je ne te laisserai pas detruire mon peuple sans rien faire. "), this->allDialogueLoad["Dialogue-Sapin_Arch"]));
	
		
	
		
		
		
		
		break;
	break;
	default:
		break;
	}
	
	
	
	

	
	
		
	
	

	

}

void WasteLands::resize() {
	switch (this->actualMap)
	{
	case 0:

		this->ResizeButton(vec2(this->currentMap.GetTextureCurrentMap()->getWidth(), this->currentMap.GetTextureCurrentMap()->getHeight()));

		break;
	case 5:
		this->ResizeButton(vec2(1920,1080));
		break;


	}
}



double distance(vec2 a , vec2 b) {
	return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
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
	switch (this->actualMap)
	{
	case 0:
		for (auto i : this->currentMap.GetAllButton()) {
			if (i.IsInButton(point(event.getX(), event.getY())) && i.GetActive()) {

			}
		}
		break;
	case 2:
	{
		
		event.setPos(getMousePos() - getWindowPos());
		double x;
		double y;
		if (this->getWindowWidth() / 2 >= this->mainCharacter.GetPosX()) {

			x = event.getX();


		}
		else if (this->currentMap.GetTextureCurrentMap()->getWidth() <= this->mainCharacter.GetPosX() + this->getWindowWidth() / 2) {
			x = this->currentMap.GetTextureCurrentMap()->getWidth() - this->getWindowWidth() + event.getX();

		}
		else {
			x = this->mainCharacter.GetPosX() - this->getWindowWidth() / 2 + event.getX();
			
		}

		if (this->getWindowHeight() / 2 >= this->mainCharacter.GetPosY()) {

			y = event.getY();


		}
		else if (this->currentMap.GetTextureCurrentMap()->getHeight() <= this->mainCharacter.GetPosY() + this->getWindowHeight() / 2) {
			
			y = this->currentMap.GetTextureCurrentMap()->getHeight() - this->getWindowHeight() + event.getY();
		}
		else {

			
			y = this->mainCharacter.GetPosY() - this->getWindowHeight() / 2 + event.getY();
		}
		double dx = (double)(cos(getAngle(vec2(this->mainCharacter.GetPosX(), this->mainCharacter.GetPosY()), vec2(x, y))));
		double dy = (double)(sin(getAngle(vec2(this->mainCharacter.GetPosX(), this->mainCharacter.GetPosY()),vec2(x,y))));
		this->mainCharacter.SetOrientation(vec2(-dx,- dy));
	}
		break;
	case 7:
	{

		event.setPos(getMousePos() - getWindowPos());
		double x;
		double y;
		if (this->getWindowWidth() / 2 >= this->mainCharacter.GetPosX()) {

			x = event.getX();


		}
		else if (this->currentMap.GetTextureCurrentMap()->getWidth() <= this->mainCharacter.GetPosX() + this->getWindowWidth() / 2) {
			x = this->currentMap.GetTextureCurrentMap()->getWidth() - this->getWindowWidth() + event.getX();

		}
		else {
			x = this->mainCharacter.GetPosX() - this->getWindowWidth() / 2 + event.getX();

		}

		if (this->getWindowHeight() / 2 >= this->mainCharacter.GetPosY()) {

			y = event.getY();


		}
		else if (this->currentMap.GetTextureCurrentMap()->getHeight() <= this->mainCharacter.GetPosY() + this->getWindowHeight() / 2) {

			y = this->currentMap.GetTextureCurrentMap()->getHeight() - this->getWindowHeight() + event.getY();
		}
		else {


			y = this->mainCharacter.GetPosY() - this->getWindowHeight() / 2 + event.getY();
		}
		double dx = (double)(cos(getAngle(vec2(this->mainCharacter.GetPosX(), this->mainCharacter.GetPosY()), vec2(x, y))));
		double dy = (double)(sin(getAngle(vec2(this->mainCharacter.GetPosX(), this->mainCharacter.GetPosY()), vec2(x, y))));
		this->mainCharacter.SetOrientation(vec2(-dx, -dy));
	}
	break;
	default:
		break;
	}


	
}
void WasteLands::Clean() {
	this->allInteractive.clear();
	this->allProjectile.clear();
	progressBarVar.clean();
	allThingToDraw.clear();
	allDialogue.clear();
	allEnnemies.clear();
	this->currentMap.clean();

	

}



void WasteLands::ClickOnReplay() {
	this->touchPressed.clear();
	this->allProjectile.clear();
	this->mainCharacter.SetEtatActuel("StandR");
	this->mainCharacter.SetActualAnimation();
	this->allEnnemies.clear();
	this->mainCharacter.SetCanChangeAnimationn(true);
	this->allDialogue.clear();
	this->mainCharacter.SetVie(this->mainCharacter.GetMaxVie());
	this->mainCharacter.SetIsDying(0);
	
	switch (this->lastMap)
	{
	case 2:
		this->actualMap = 6;
		this->mainCharacter.SetPosX(1880);
		this->mainCharacter.SetPosY(1110);
		break;
	case 6:
		this->actualMap = 6;
		this->mainCharacter.SetPosX(1880);
		this->mainCharacter.SetPosY(1110);;
		break;
	case 7:
		
		this->actualMap = 8;
		this->mainCharacter.SetPosX(500);
		this->mainCharacter.SetPosY(500);
	
	
		
	
		
		
		break;
	case 8:
	
		this->actualMap = 8;
		this->mainCharacter.SetPosX(500);
		this->mainCharacter.SetPosY(500);
	

		
	
		
		
		break;
	default:
		break;
	}
	
}

void WasteLands::ClickOnPlay() {
	

	




	std::experimental::filesystem::v1::path  path = getAssetDirectories()[0].generic_u8string() + "\\Map\\Spawn";



	this->progressBarVar.SetupMapCharacterEnnemiesDiversAndDialogue(path, "Archer",6);
	

	this->Video->close();
}
void  WasteLands::ClickOnCredits() {
	
}

void WasteLands::SpawnEnnemiFactory() {
	static int wave = 0;
	
	if (wave == 3) {
		bool find = false; 
		for (auto a : this->allEnnemies) {
			if (a.GetType() == "BossFactory") {
				find = true;
			}
		}
		if (find = false) {
			this->allEnnemies.clear();
			
		}
	}
	if (this->allEnnemies.size() == 0 ) {
		switch (wave)
		{

		case 0:
		{
			for (int i = 0; i < 5; i++) {
				this->allEnnemies.push_back(this->allEnnemiesLoad["Rose"].TransformEnnemiesLoadToEnnemies("Rose", this->allEnnemiesLoad["Rose"], 2540, 450 + i * 150, &this->allProjectile, vec2(5, 5), vec2(150, 150), 100, 20,800));

			}
			this->allDialogue.push_back(Dialogue(string("Pour t'attaquer a moi tu devras vaincre ma garde epineuse. "), this->allDialogueLoad["Dialogue-Sapin_Arch"]));
			wave++;
			break;
		}
		
		case 1: 
		{
			this->allDialogue.push_back(Dialogue(string("Tu resistes a ma garde, tu sais te battre. En avant, renvoyer le a l'etat de poussiere."), this->allDialogueLoad["Dialogue-Sapin_Arch"]));
			for (int i = 0; i < 5; i++) {
				this->allEnnemies.push_back(this->allEnnemiesLoad["Livre"].TransformEnnemiesLoadToEnnemies("Livre", this->allEnnemiesLoad["Livre"], 2350, 500 + i * 150, &this->allProjectile, vec2(5, 5), vec2(150, 150), 150, 20,700));

			}

			for (int i = 0; i < 3; i++) {
				this->allEnnemies.push_back(this->allEnnemiesLoad["Rose"].TransformEnnemiesLoadToEnnemies("Rose", this->allEnnemiesLoad["Rose"], 2540, 500 + i * 250, &this->allProjectile, vec2(5, 5), vec2(150, 150), 100, 20,800));

			}
			wave++;
			break;
		}
		case 2:
		{
			this->allDialogue.push_back(Dialogue(string("Comment oses-tu les abattre tous ! Ta vie n'est que destruction."), this->allDialogueLoad["Dialogue-Sapin_Arch"]));
			for (int i = 0; i < 4; i++) {
				this->allEnnemies.push_back(this->allEnnemiesLoad["Bouteille"].TransformEnnemiesLoadToEnnemies("Bouteille", this->allEnnemiesLoad["Bouteille"], 2540, 500 + i * 150, &this->allProjectile, vec2(5, 5), vec2(200, 200), 200, 30,1000));

			}
		
			wave++;
			break;
		}
		case 3:
		{
			this->allDialogue.push_back(Dialogue(string("Ma colere me permettra de te vaincre !"), this->allDialogueLoad["Dialogue-Sapin_Arch"]));
			this->allEnnemies.push_back(this->allEnnemiesLoad["BossFactory"].TransformEnnemiesLoadToEnnemies("BossFactory", this->allEnnemiesLoad["BossFactory"], 2400, 700, &this->allProjectile, vec2(5, 5), vec2(300, 300), 1000, 30, 1000));
			
			wave++;
			 
			break;
		}
		case 4:
			
			this->allDialogue.push_back(Dialogue(string("Je suis vaincu ! Un jour tu comprendras son vrai objectif....  "), this->allDialogueLoad["Dialogue-Sapin_Arch"]));
			wave++; 
			break;
			

		case 5:
			this->actualMap = 9;
			break;
		default:
			
			break;
		}
	}

	if (this->mainCharacter.GetIsDying() == 1 || this->mainCharacter.GetIsDying() == 2) {
		wave = 0;
	}
}

void WasteLands::setup()
{
	setFrameRate(60);
	//setFullScreen(true);
	std::experimental::filesystem::v1::path chemin = getAssetDirectories()[0].u8string() + "\\Map\\PrincipalMenu";
	
	this->progressBarVar.SetupMenu(chemin,0);
	
	TextLayout layout;
	layout.setFont(Font("Arial", 24));
	layout.setColor(Color(1, 1, 1));
	layout.addLine("Appuyer sur            pour interagir");
	Surface8u rendered = layout.render(true, false);
	this->mTextureForInteract = gl::Texture2d::create(rendered);

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
					break;
				}
			}
		}
		break;

	case 2:
		if (event.isRight()) {
			this->mainCharacter.GetAura().ChangeAura();

		}
		else if (event.isLeft()) {

			this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("Shot")] = true;
		}
		break;
	case 5:
		for (auto i : this->currentMap.GetAllButton()) {
			if (i.IsInButton(point(event.getX(), event.getY())) && i.GetActive()) {
				if (i.GetTypeButton() == "ClickOnReplay()") {
					this->ClickOnReplay();
					break;
				}
			}
		}
	
		break;
	case 7:
		if (this->allDialogue.size() == 0) {
			if (event.isRight()) {
				this->mainCharacter.GetAura().ChangeAura();

			}
			else if (event.isLeft()) {

				this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("Shot")] = true;
			}
		}
		else {
			
			this->allDialogue.erase(this->allDialogue.begin());
			
		}
		break;
	case 6:

		this->allDialogue.erase(this->allDialogue.begin());

		if (allDialogue.size() == 0) {
			this->actualMap = 2;
		}

		break;

	case 8:

		this->allDialogue.erase(this->allDialogue.begin());

		if (allDialogue.size() == 0) {
			this->actualMap = 7;
		}

		break;
	}

}


void WasteLands::mouseUp(MouseEvent event) {
	switch (this->actualMap){

	case 2:
		
		if (event.isLeft()) {
			
			this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("Shot")] = false;
		}
		
		break;
	

	case 7:

		if (event.isLeft()) {

			this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("Shot")] = false;
		}

		break;
	}
}

void WasteLands::keyDown(KeyEvent event)
{
	
	switch (this->actualMap)
	{
	case 2:
	{
		if (event.isShiftDown()) {
			this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("Shift")] = true;

		}

		int touch = event.getCode();


		if (this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("Interaction")] == false && touch == this->mainCharacter.GetallTouches().GetValueTouche("Interaction")) {

			for (auto & a : this->allInteractive) {
				if (distance(vec2(this->mainCharacter.GetPosX(), this->mainCharacter.GetPosY()), a.first) < 100) {
					a.second(*this);
					break;
				}
			}
		}
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
	}
		break;
	case 7:
	{
		if (event.isShiftDown()) {
			this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("Shift")] = true;

		}

		int touch = event.getCode();


		if (this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("Interaction")] == false && touch == this->mainCharacter.GetallTouches().GetValueTouche("Interaction")) {

			for (auto & a : this->allInteractive) {
				if (distance(vec2(this->mainCharacter.GetPosX(), this->mainCharacter.GetPosY()), a.first) < 100) {
					a.second(*this);
					break;
				}
			}
		}
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
	}
	break;

	}
	

}
void WasteLands::keyUp(KeyEvent event)
{

	switch (this->actualMap)
	{
	case 2 :
	{
		if (event.isShiftDown() == false) {

			this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("Shift")] = false;
		}

		int touch = event.getCode();
		if (this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("ChangeAura")] == true && touch == this->mainCharacter.GetallTouches().GetValueTouche("ChangeAura")) {
			this->mainCharacter.GetAura().ChangeAura();
		}
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
	}
		break;
	
	
	case 7:
	{
		if (event.isShiftDown() == false) {

			this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("Shift")] = false;
		}
		int touch = event.getCode();

		if (this->touchPressed[this->mainCharacter.GetallTouches().GetValueTouche("ChangeAura")] == true && touch == this->mainCharacter.GetallTouches().GetValueTouche("ChangeAura")) {
			this->mainCharacter.GetAura().ChangeAura();
		}
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
	}
		break;
	
	}
}





bool Collision(polygon first,polygon second) {
	

		 return boost::geometry::intersects(first, second);
	


	
	

}




bool ValueCmp(TextureToDraw a, TextureToDraw b)
{
	return a.GetDistance() > b.GetDistance();
}

polygon WasteLands::TransformHitBoxInOneray(polygon Polygon) {
	polygon temp;
	string tempPoly = "POLYGON((";
	for (auto i : Polygon.outer()) {
		tempPoly += to_string(i.x());
		tempPoly += " ";
		tempPoly += to_string(i.y()*getWindowWidth());

		tempPoly += ",";
	}
	tempPoly.pop_back();
	tempPoly += "))";

	boost::geometry::read_wkt(
		tempPoly, temp);
	return temp;
}


void WasteLands::SetPositionDecor() {
	
	
	for (int posErase = 0; posErase < this->allThingToDraw.size(); posErase++) {
		if (this->allThingToDraw[posErase].GetDontMove() == false) {
			this->allThingToDraw.erase(this->allThingToDraw.begin() + posErase);
			posErase--;
		}
		
		
	}
	
	
	TextureToDraw temp;
	temp.SetDontMove(false);
	temp.SetDistance(boost::geometry::distance(this->TransformHitBoxInOneray(this->mainCharacter.GetHitBoxOnCurrentAnimation()), point(this->currentMap.GetTextureCurrentMap()->getActualWidth(), this->currentMap.GetTextureCurrentMap()->getActualHeight()*getWindowWidth())));
	temp.SetPos(vec2(this->mainCharacter.GetPosX(), this->mainCharacter.GetPosY()));
	temp.SetSize(Rectf(0, 0,this->mainCharacter.GetSizeX(), this->mainCharacter.GetSizeY()));
	temp.SetTexture(this->mainCharacter.GetActualAnimation().first);
	temp.SetSource("Main character");
	this->allThingToDraw.push_back(temp);

	for (int posErase = 0; posErase < this->allProjectile.size(); posErase++) {
		auto & a = this->allProjectile[posErase];
	
		if (-a.GetStartTime() + getElapsedSeconds() > 5.0) {
			
			this->allProjectile.erase(this->allProjectile.begin() + posErase);
			posErase--;
		}
		else {
			TextureToDraw temp;
			temp.SetDontMove(false);
			temp.SetDistance(boost::geometry::distance(this->TransformHitBoxInOneray(a.GetActualHitBox()), point(this->currentMap.GetTextureCurrentMap()->getActualWidth(), this->currentMap.GetTextureCurrentMap()->getActualHeight()*getWindowWidth())));
			temp.SetPos(vec2(a.GetPosX(), a.GetPosY()));
			temp.SetSize(Rectf(0, 0, a.GetSizeX(), a.GetSizeY()));
			temp.SetTexture(a.GetTexture());
			temp.SetSource("Projectile");
			temp.SetOrientation(a.GetOrientation());
			this->allThingToDraw.push_back(temp);
		}
		
	}
	double p= getElapsedSeconds();
	for (int posErase = 0; posErase < this->allEnnemies.size(); posErase++) {
		auto & a = this->allEnnemies[posErase];
		TextureToDraw temp;
		temp.SetDontMove(false);
		
		temp.SetDistance(boost::geometry::distance(this->TransformHitBoxInOneray(a.GetActualHitbox()), point(this->currentMap.GetTextureCurrentMap()->getActualWidth(), this->currentMap.GetTextureCurrentMap()->getActualHeight()*getWindowWidth())));
		
		temp.SetPos(vec2(a.GetPos().x, a.GetPos().y));
		temp.SetSize(Rectf(0, 0, a.GetSize().x, a.GetSize().y));
		temp.SetTexture(a.GetCurrentTexture());
		temp.SetSource("Ennemies");
		this->allThingToDraw.push_back(temp);
		

	}

	//touchPressed[this->allTouches.GetValueTouche("RunTR")]
	std::sort(this->allThingToDraw.begin(), this->allThingToDraw.begin()+ this->allThingToDraw.size(), ValueCmp);

	

}

void WasteLands::Case2Update() {
	this->mouseMove(MouseEvent());
	
	static bool dialogueMort = false;
	bool temp = false;
	
	if (this->mainCharacter.GetIsDying() == 2) {
		
		if (dialogueMort == false) {
			this->allDialogue.push_back(Dialogue(string("Ma volonte est ineluctable, mon pouvoir coule dans tes veines.Releve toi heros !"), this->allDialogueLoad["Dialogue-Nature"]));
			dialogueMort = true;
		}
		else {
			
			dialogueMort = false;
			AttribAllImage(5);
		}
		
	}
	else {

		



		this->mainCharacter.Update(this->touchPressed);
		this->mainCharacter.SetActuelHitBoxOnCurrentAnimation();
		this->mainCharacter.GetAura().update();

		//0.002 12%
		for (int j = 0; j < this->allEnnemies.size(); j++) {
			
			auto & a = this->allEnnemies[j];
			if (a.GetisDying() == 2) {
				this->allEnnemies.erase(this->allEnnemies.begin() + j);
				--j;
			}
			else {
				a.SetcurrentAnimation();
				
				a.Update(vec2(this->mainCharacter.GetPosX(), this->mainCharacter.GetPosY()), this->allEnnemiesLoad, this->allProjectile, &this->allEnnemies);
				auto & a = this->allEnnemies[j];
				a.SetActualHitbox();
				
			}


		}

		//0.00920746  55.24 %
		
	
		for (int j = 0; j < this->allEnnemies.size(); j++) {
			
			auto & a = this->allEnnemies[j];
			if (a.GetActualVelocity() != vec2(0, 0)) {

				//0.0015 9 % 
				for (auto & i : this->currentMap.GetDecor()) {
					if (distance(vec2(i.GetPositionX(), i.GetPositionY()), a.GetPos()) < sqrt(pow(a.GetSize().x,2)+pow(a.GetSize().y,2))) {
						if (temp = Collision(a.GetActualHitbox(), i.GetHitBox())) {

							break;
						}
					}

				}

				if (temp == false)
					for (auto & i : this->allEnnemies) {

						if (a.GetPos() != i.GetPos() && distance(i.GetPos(), a.GetPos()) < sqrt(pow(a.GetSize().x, 2) + pow(a.GetSize().y, 2))) {

							if (temp = Collision(a.GetActualHitbox(), i.GetActualHitbox())) {

								break;
							}
						}
					}
				if (temp == false) {
					
					a.SetPos(vec2(a.GetPos()) + a.GetActualVelocity());

				}
				
				a.SetActualVelocity(vec2(0, 0));
			}
	

		}
	
		


		temp = false;


		//0.00046848 2.81 %
		if (this->mainCharacter.GetVelocityX() != 0 || this->mainCharacter.GetVelocityY() != 0) {
			for (auto & i : this->currentMap.GetDecor()) {

				if (temp = Collision(this->mainCharacter.GetHitBoxOnCurrentAnimation(), i.GetHitBox())) {
					break;
				}
			}
			if (temp == false) {
				this->mainCharacter.SetPosX(this->mainCharacter.GetVelocityX() + this->mainCharacter.GetPosX());
				this->mainCharacter.SetPosY(this->mainCharacter.GetVelocityY() + this->mainCharacter.GetPosY());

			}
			this->mainCharacter.SetVelocityX(0);
			this->mainCharacter.SetVelocityY(0);
		}


		//0.0219039  4.87 % 
		this->mainCharacter.SetActuelHitBoxOnCurrentAnimation();

		
		
		for (int j = 0; j < this->allProjectile.size(); j++) {
			bool temp = false;
			auto & a = this->allProjectile[j];
			

			a.SetAtualHitBox();
			for (auto & i : this->currentMap.GetDecor()) {
				if (distance(vec2(i.GetPositionX(), i.GetPositionY()), vec2(a.GetPosX(), a.GetPosY())) < sqrt(pow(i.GetSizeX(),2) + pow(i.GetSizeY(),2)) && i.GetCollisionWithDecor()==1) {
					if (temp = Collision(a.GetActualHitBox(), i.GetHitBox())) {
						this->allProjectile.erase(this->allProjectile.begin() + j);
						--j;

						break;
					}
				}
			}
			if (temp == false) {
				string sourceProjectile = a.GetSource();
				string type = sourceProjectile.substr(0, sourceProjectile.find(" "));
				
				if (type == "Ennemies" || type == "EnnemiesL") {

					if (temp = Collision(a.GetActualHitBox(), this->mainCharacter.GetHitBoxOnCurrentAnimation()) && distance(vec2(this->mainCharacter.GetPosX(), this->mainCharacter.GetPosY()), vec2(a.GetPosX(), a.GetPosY())) < 500.00) {
						if (this->mainCharacter.GetInvicibility() == false) {
							if (this->mainCharacter.GetVie() > 0) {
								
								this->mainCharacter.checkInviciblity(true);
								this->mainCharacter.SetVie(this->mainCharacter.GetVie() - a.GetDommage());
								if (this->mainCharacter.GetVie() <= 0) {
									this->mainCharacter.SetVie(0);
									this->mainCharacter.SetEtatActuel("DieR");
									this->mainCharacter.SetCanChangeAnimationn(false);
									this->mainCharacter.SetIsDying(1);
								}
								else {
									double dx = this->mainCharacter.GetOrientation().x;
									double dy = this->mainCharacter.GetOrientation().y;
									if (dx > 0) {
										this->mainCharacter.SetEtatActuel("HitR");
									}
									else {
										this->mainCharacter.SetEtatActuel("HitL");
									}
									this->mainCharacter.SetCanChangeAnimationn(false);
								}
							}
						}

						this->allProjectile.erase(this->allProjectile.begin() + j);
						--j;
					}
				}
				else if (type == "MainCharacter") {
					string aura = sourceProjectile.substr(sourceProjectile.find(" ") + 1);
					for (auto & i : this->allEnnemies) {
						if (temp = Collision(a.GetActualHitBox(), i.GetActualHitbox()) && distance(i.GetPos(), vec2(a.GetPosX(), a.GetPosY())) < sqrt(pow(i.GetSize().x, 2) + pow(i.GetSize().y, 2))) {
							if (aura == i.GetAuraKil()) {
								i.SetVie(i.GetVie() - a.GetDommage());
								if (i.GetVie() <= 0 && i.GetisDying() == 0) {
									i.SetDie();

								}
								else {

								}
							}
							this->allProjectile.erase(this->allProjectile.begin() + j);
							--j;
							break;
						}
					}

				}
				

			}

			if (temp == false) {
				if (a.GetSource() == "EnnemiesL") {
					
					a.SetPosX(a.GetPosX() +15*cos(a.GetIteration()/4)+ a.GetSpeedX());
					a.SetPosY(a.GetPosY() + 15 * sin(a.GetIteration() / 4) +a.GetSpeedY());
					a.SetIteration();
					
				}
				else {
					a.SetPosX(a.GetPosX() + a.GetSpeedX());
					a.SetPosY(a.GetPosY() + a.GetSpeedY());
				}
				

			}
		}

		double mama = getElapsedSeconds();
		
		//0.00305067 18.3 % 
		this->SetPositionDecor();
		
	}


}


void WasteLands::UpdateSound() {
	switch (this->actualMap)
	{
	case 0:
		if (!this->actualSoundRef->isPlaying() && this->soundName == "stanza") {
			this->ChangeSound("stanza");
		}
		else if (!this->actualSoundRef->isPlaying() && this->soundName == "preStanza") {
			this->ChangeSound("stanza");
		}
		else if (!this->actualSoundRef->isPlaying() && this->soundName == "intro") {
			this->ChangeSound("preStanza");
		}
		break;
	case 2:
		if (!this->progressBarVar.GetTerminated() && this->soundName == "stanza" && !this->actualSoundRef->isPlaying()) {
			this->ChangeSound("preDrop");
		}
		else if (!this->actualSoundRef->isPlaying() && this->soundName == "stanza") {
			this->ChangeSound("stanza");
		}
		else if (!this->actualSoundRef->isPlaying() && this->soundName == "preStanza") {
			this->ChangeSound("stanza");
		}
		else if (!this->actualSoundRef->isPlaying() && this->soundName == "intro") {
			this->ChangeSound("preStanza");
		}
		break;
	case 6:
		if (!this->actualSoundRef->isPlaying() && this->soundName == "stanza" ) {
			this->ChangeSound("stanza");
		}
		else if (!this->actualSoundRef->isPlaying() && this->soundName == "preStanza") {
			this->ChangeSound("stanza");
		}
		else if (!this->actualSoundRef->isPlaying() && this->soundName == "intro") {
			this->ChangeSound("preStanza");
		}
		break;
	
	case 8:
		if (!this->actualSoundRef->isPlaying() && this->soundName == "preStanza") {
			this->ChangeSound("stanza");
		}
		else if (!this->actualSoundRef->isPlaying() && this->soundName == "intro") {
			this->ChangeSound("preStanza");
		}
		if (this->soundName == "drop" && !this->actualSoundRef->isPlaying()) {
			this->ChangeSound("drop");
		}
		else if (this->soundName == "preDrop" && !this->actualSoundRef->isPlaying()) {
			this->ChangeSound("drop");
		}
		else if (this->soundName == "stanza" && !this->actualSoundRef->isPlaying()) {
			this->ChangeSound("preDrop");
		}
		break;
	
	case 7:
	
		if (!this->actualSoundRef->isPlaying() && this->soundName == "preStanza") {
			this->ChangeSound("stanza");
		}
		else if (!this->actualSoundRef->isPlaying() && this->soundName == "intro") {
			this->ChangeSound("preStanza");
		}
		if (this->soundName == "drop" && !this->actualSoundRef->isPlaying()) {
			this->ChangeSound("drop");
		}
		else if (this->soundName == "preDrop" && !this->actualSoundRef->isPlaying()) {
			this->ChangeSound("drop");
		}
		else if (this->soundName == "stanza"  && !this->actualSoundRef->isPlaying()) {
			this->ChangeSound("preDrop");
		}
		break;
	}
	
	
}

void WasteLands::update()
{
	this->UpdateSound();
	static bool alreadyPass = false;
	if (this->progressBarVar.GetTerminated()) {
		switch (this->actualMap)
		{
		case 0:
			Video->update();
			
		



			break;
		case 2:
		{
			this->Case2Update();
			alreadyPass = false;
			break;
		}
	

		case 6	:
		{
			
			if (alreadyPass == false) {
				this->Case2Update();
				alreadyPass = true;
			}

			if (allDialogue.size() == 0) {
				this->actualMap = 2;
			}
		}
		break;
		case 7:
		{
			
			if (this->allDialogue.size() == 0) {
				this->SpawnEnnemiFactory();
				this->Case2Update();
				alreadyPass = false;
			}
			
			
		}
		break;
		case 8:
		{
			
			if (alreadyPass == false) {
				this->Case2Update();
				
				alreadyPass = true;
			}

			if (allDialogue.size() == 0) {
			
				this->actualMap = 7;
			}
		}
		break;
			
		default:
			break;
		}
	}
	

	
	



}


void WasteLands::DrawHp() {
	gl::ScopedModelMatrix scpModel;

	double x ;
	double y;
	if (this->getWindowWidth() / 2 >= this->mainCharacter.GetPosX()) {

		x = 30;


	}
	else if (this->currentMap.GetTextureCurrentMap()->getWidth() <= this->mainCharacter.GetPosX() + this->getWindowWidth() / 2) {
		x = this->currentMap.GetTextureCurrentMap()->getWidth() - getWindowWidth()+30;

	}
	else {
		x = this->mainCharacter.GetPosX() - getWindowWidth() / 2 + 30;

	}

	if (this->getWindowHeight() / 2 >= this->mainCharacter.GetPosY()) {

		y = 10;


	}
	else if (this->currentMap.GetTextureCurrentMap()->getHeight() <= this->mainCharacter.GetPosY() + this->getWindowHeight() / 2) {

		y = this->currentMap.GetTextureCurrentMap()->getHeight() - this->getWindowHeight() + 10;
	}
	else {


		y = this->mainCharacter.GetPosY() - getWindowHeight() / 2 + 10;
	}
	gl::translate(x, y);
	
	Area srcArea{ 0,0,(int)( this->diversTexture["InterieurBarreVie"]->getWidth()*(this->mainCharacter.GetVie() / this->mainCharacter.GetMaxVie())), this->diversTexture["InterieurBarreVie"]->getHeight() }; // portion of the image in pixels
	 

	gl::draw(this->diversTexture["InterieurBarreVie"], srcArea,Rectf(0,0, this->diversTexture["InterieurBarreVie"]->getWidth()*((float)this->getWindowWidth() / 1280.0F)*0.2*(this->mainCharacter.GetVie() / this->mainCharacter.GetMaxVie()), this->diversTexture["InterieurBarreVie"]->getHeight()*((float)this->getWindowHeight() / 720.0F)*0.2));
	gl::draw(this->diversTexture["ContourBarreVie"], Rectf(0, 0, this->diversTexture["ContourBarreVie"]->getWidth()*((float)this->getWindowWidth() / 1280.0F)*0.2, this->diversTexture["ContourBarreVie"]->getHeight()*((float)this->getWindowHeight() / 720.0F)*0.2));
	
}


void WasteLands::DrawHpBoss(Ennemies & a) {
	
	gl::ScopedModelMatrix scpModel;

	double x;
	double y;
	if (this->getWindowWidth() / 2 >= this->mainCharacter.GetPosX()) {

		x = this->getWindowWidth() / 2 - (this->diversTexture["ContourBarreVie"]->getWidth()*((float)this->getWindowWidth() / 1280.0F)*0.3) / 2;


	}
	else if (this->currentMap.GetTextureCurrentMap()->getWidth() <= this->mainCharacter.GetPosX() + this->getWindowWidth() / 2) {
		x = this->currentMap.GetTextureCurrentMap()->getWidth() - getWindowWidth() + this->getWindowWidth() / 2 - (this->diversTexture["ContourBarreVie"]->getWidth()*((float)this->getWindowWidth() / 1280.0F)*0.3) / 2;

	}
	else {
		x = this->mainCharacter.GetPosX() - getWindowWidth() / 2 + this->getWindowWidth() / 2 - (this->diversTexture["ContourBarreVie"]->getWidth()*((float)this->getWindowWidth() / 1280.0F)*0.3) / 2;

	}

	if (this->getWindowHeight() / 2 >= this->mainCharacter.GetPosY()) {

		y = 10;


	}
	else if (this->currentMap.GetTextureCurrentMap()->getHeight() <= this->mainCharacter.GetPosY() + this->getWindowHeight() / 2) {

		y = this->currentMap.GetTextureCurrentMap()->getHeight() - this->getWindowHeight() + 10;
	}
	else {


		y = this->mainCharacter.GetPosY() - getWindowHeight() / 2 + 10;
	}
	gl::translate(x, y);



	Area srcArea{ 0,0,(int)(this->diversTexture["InterieurBarreVie"]->getWidth()*(a.GetVie() / a.GetMaxVie())), this->diversTexture["InterieurBarreVie"]->getHeight() }; // portion of the image in pixels

	
	gl::draw(this->diversTexture["InterieurBarreVie"], srcArea, Rectf(0, 0, this->diversTexture["InterieurBarreVie"]->getWidth()*((float)this->getWindowWidth() / 1280.0F)*0.3*(a.GetVie() /a.GetMaxVie()), this->diversTexture["InterieurBarreVie"]->getHeight()*((float)this->getWindowHeight() / 720.0F)*0.2));
	gl::draw(this->diversTexture["ContourBarreVie"], Rectf(0, 0, this->diversTexture["ContourBarreVie"]->getWidth()*((float)this->getWindowWidth() / 1280.0F)*0.3, this->diversTexture["ContourBarreVie"]->getHeight()*((float)this->getWindowHeight() / 720.0F)*0.2));
}

void WasteLands::DrawMainMap() {

	

	gl::ScopedModelMatrix scpModel;
	gl::translate(getWindowCenter());
	gl::scale(vec2(this->zoom));
	
	this->SetCameraOutOfBound();
	gl::draw(this->currentMap.GetTextureCurrentMap());
	


	

	

	Rectf size(0, 0, this->mainCharacter.GetSizeX(), this->mainCharacter.GetSizeY());

	
	int test = 0;
	for (auto i : this->allThingToDraw) {
		if (i.GetSource() == "Projectile") {
			
			this->drawProjectile(i.GetTexture(), i.GetPos(), i.GetSize(), i.GetOrientation());
			
		}
		else if (i.GetSource() == "Main character") {
			this->drawMainCharacter(i.GetTexture(), i.GetPos(), i.GetSize());
			this->drawMainCharacter(this->mainCharacter.GetAura().GetTextureAura(), i.GetPos(), i.GetSize());
		
			
		}
		else if (i.GetSource() == "Decor") {
			this->drawTex(i.GetTexture(), i.GetPos(), i.GetSize());
		}
		else {
			this->drawMainCharacter(i.GetTexture(), i.GetPos(), i.GetSize());
		}
	
		
	}
	/*for (auto & i : this->allProjectile) {
		this->drawProjectile(i.GetTexture(), vec2(i.GetPosX(), i.GetPosY()), Rectf(0, 0, i.GetSizeX(), i.GetSizeY()), i.GetOrientation());
	}

	for (auto & i : this->allEnnemies) {
		this->drawTex(i.GetCurrentTexture(), vec2(i.GetPos().x, i.GetPos().y), Rectf(0, 0, i.GetSize().x, i.GetSize().y));
	}

	this->drawTex(this->mainCharacter.GetActualAnimation().first, vec2(this->mainCharacter.GetPosX(), this->mainCharacter.GetPosY()), Rectf(0, 0, this->mainCharacter.GetSizeX(), this->mainCharacter.GetSizeY()));
	this->drawTex(this->mainCharacter.GetAura().GetTextureAura(), vec2(this->mainCharacter.GetPosX(), this->mainCharacter.GetPosY()), Rectf(0, 0, this->mainCharacter.GetSizeX(), this->mainCharacter.GetSizeY()));

	for (auto & i : this->currentMap.GetDecor()) {
		this->drawTex(i.GetTexture(), vec2(i.GetPositionX(), i.GetPositionY()),Rectf(0,0,i.GetSizeX(),i.GetSizeY()));
	}*/
	
	

	bool find = false;
	for (auto a : this->allEnnemies) {
		if (a.GetType() == "BossFactory") {
			this->DrawHpBoss(a);
		}
	
	}

	
	this->DrawIndicatorAura();
	this->DrawDivers();
	for (auto & a : this->allInteractive) {
		if (distance(vec2(this->mainCharacter.GetPosX(), this->mainCharacter.GetPosY()), a.first) < 100) {
			this->DrawInteractive();
		}
	}
	



	//////////////////////////////DEBUG///////////////////

	/*for (auto a : this->allEnnemies) {
		DebugDrawPolygon(a.GetActualHitbox());
	}

	for (auto a : this->currentMap.GetDecor()) {
		DebugDrawPolygon(a.GetHitBox());
	}

	for (auto a : this->allProjectile) {
		DebugDrawPolygon(a.GetActualHitBox());
	}

	DebugDrawPolygon(this->mainCharacter.GetHitBoxOnCurrentAnimation());*/

}



void WasteLands::DrawDivers() {
	this->DrawHp();
	gl::ScopedModelMatrix scpModel;
	{
		double posAideX;
		double posAideY;
		if (this->getWindowWidth() / 2 >= this->mainCharacter.GetPosX()) {

			posAideX = this->getWindowWidth() - this->diversTexture["AidePouvoirs"]->getWidth()*((float)this->getWindowWidth() / 1280.0F)*0.35;

		}
		else if (this->currentMap.GetTextureCurrentMap()->getWidth() <= this->mainCharacter.GetPosX() + this->getWindowWidth() / 2) {

			posAideX = this->currentMap.GetTextureCurrentMap()->getWidth() - this->diversTexture["AidePouvoirs"]->getWidth()*((float)this->getWindowWidth() / 1280.0F)* 0.35;
		}
		else {

			posAideX = this->mainCharacter.GetPosX() + this->getWindowWidth() / 2 - this->diversTexture["AidePouvoirs"]->getWidth()*((float)this->getWindowWidth() / 1280.0F)* 0.35;
		}

		if (this->getWindowHeight() / 2 >= this->mainCharacter.GetPosY()) {

			posAideY = 0;

		}
		else if (this->currentMap.GetTextureCurrentMap()->getHeight() <= this->mainCharacter.GetPosY() + this->getWindowHeight() / 2) {
			posAideY = this->currentMap.GetTextureCurrentMap()->getHeight() - this->getWindowHeight();

		}
		else {

			posAideY = this->mainCharacter.GetPosY() - this->getWindowHeight() / 2;

		}

		gl::translate(posAideX, posAideY);
		gl::draw(this->diversTexture["AidePouvoirs"], Rectf(0, 0, this->diversTexture["AidePouvoirs"]->getWidth()* 0.35 *((float)this->getWindowWidth() / 1280.0F), this->diversTexture["AidePouvoirs"]->getHeight()* 0.35 *((float)this->getWindowHeight() / 720.0F)));

	}
	
	
}

void WasteLands::DrawInteractive() {
	gl::ScopedModelMatrix scpModel;
	
	
	double posX;
	double posY;
	
	
	{
		if (this->getWindowWidth() / 2 >= this->mainCharacter.GetPosX()) {

			posX = getWindowCenter().x;
			

		}
		else if (this->currentMap.GetTextureCurrentMap()->getWidth() <= this->mainCharacter.GetPosX() + this->getWindowWidth() / 2) {
			posX = this->currentMap.GetTextureCurrentMap()->getWidth() - getWindowCenter().x;
			
		}
		else {
			posX = this->mainCharacter.GetPosX();
		
		}

		if (this->getWindowHeight() / 2 >= this->mainCharacter.GetPosY()) {

			posY = getWindowCenter().y + getWindowHeight() / 2 * 0.80;


		}
		else if (this->currentMap.GetTextureCurrentMap()->getHeight() <= this->mainCharacter.GetPosY() + this->getWindowHeight() / 2) {
			posY = this->currentMap.GetTextureCurrentMap()->getHeight() - getWindowCenter().y + getWindowHeight() / 2 * 0.80;

		}
		else {

			posY = this->mainCharacter.GetPosY() + getWindowHeight() / 2 * 0.80;

		}


		gl::translate(vec2(posX, posY));
		
		gl::draw(this->diversTexture["E"]);

		gl::draw(mTextureForInteract, vec2(-110, 10));
	}



	
	

	


}
void WasteLands::DrawIndicatorAura() {
	double posAideX,posAideY;
	if (this->getWindowWidth() / 2 >= this->mainCharacter.GetPosX()) {

		posAideX = this->getWindowWidth() - this->diversTexture["AidePouvoirs"]->getWidth()*((float)this->getWindowWidth() / 1280.0F)*0.35;

	}
	else if (this->currentMap.GetTextureCurrentMap()->getWidth() <= this->mainCharacter.GetPosX() + this->getWindowWidth() / 2) {

		posAideX = this->currentMap.GetTextureCurrentMap()->getWidth() - this->diversTexture["AidePouvoirs"]->getWidth()*((float)this->getWindowWidth() / 1280.0F)* 0.35;
	}
	else {

		posAideX = this->mainCharacter.GetPosX() + this->getWindowWidth() / 2 - this->diversTexture["AidePouvoirs"]->getWidth()*((float)this->getWindowWidth() / 1280.0F)* 0.35;
	}

	if (this->getWindowHeight() / 2 >= this->mainCharacter.GetPosY()) {

		posAideY = 0;

	}
	else if (this->currentMap.GetTextureCurrentMap()->getHeight() <= this->mainCharacter.GetPosY() + this->getWindowHeight() / 2) {
		posAideY = this->currentMap.GetTextureCurrentMap()->getHeight() - this->getWindowHeight();

	}
	else {

		posAideY = this->mainCharacter.GetPosY() - this->getWindowHeight() / 2;

	}
	float radius = 7 * ((float)this->getWindowWidth() / 1280.0F);
	if (this->mainCharacter.GetAura().GetActualAura() == "Rouge") {
	
		drawSolidCircle(vec2(posAideX + 1230 * ((float)this->getWindowWidth() / 1280.0F)*0.35, posAideY+130* 0.35 *((float)this->getWindowHeight() / 720.0F)), radius);
		
	}
	else if (this->mainCharacter.GetAura().GetActualAura() == "Vert") {

		drawSolidCircle(vec2(posAideX + 1230 * ((float)this->getWindowWidth() / 1280.0F)*0.35, posAideY + 320 * 0.35 *((float)this->getWindowHeight() / 720.0F)), radius);

	}
	else if (this->mainCharacter.GetAura().GetActualAura() == "Bleu") {

		drawSolidCircle(vec2(posAideX + 1230 * ((float)this->getWindowWidth() / 1280.0F)*0.35, posAideY + 510 * 0.35 *((float)this->getWindowHeight() / 720.0F)), radius);

	}
	else if (this->mainCharacter.GetAura().GetActualAura() == "Jaune") {

		drawSolidCircle(vec2(posAideX + 1230 * ((float)this->getWindowWidth() / 1280.0F)*0.35, posAideY + 720 * 0.35 *((float)this->getWindowHeight() / 720.0F)), radius);

	}
	else if (this->mainCharacter.GetAura().GetActualAura() == "Noir") {

		drawSolidCircle(vec2(posAideX + 1230 * ((float)this->getWindowWidth() / 1280.0F)*0.35, posAideY + 930 * 0.35 *((float)this->getWindowHeight() / 720.0F)), radius);

	}
}
void WasteLands::DrawDialogue(Dialogue & dialogueToDraw) {
	gl::ScopedModelMatrix scpModel;
	TextureRef & temp = dialogueToDraw.GetImage();
	Rectf size(0, 0, getWindowWidth(), getWindowHeight());

	double posY = getWindowHeight() - temp->getHeight();
	
	if (posY < 0) {
		
		posY = 0;
		
	}
	string txt = dialogueToDraw.GetTexte();
	

	
	

	TextBox tbox = TextBox().alignment(TextBox::LEFT).font(fontDialogue).size(ivec2(getWindowWidth() - 20, TextBox::GROW)).text(txt);
	
	


	gl::draw(temp, size);
	gl::translate(10, getWindowHeight()*0.70);
	gl::draw(gl::Texture2d::create(tbox.render()));
}
void WasteLands::DrawButton() {
	gl::ScopedModelMatrix scpModel;
	for (auto i : this->currentMap.GetAllButton()) {
		Rectf sizeButton(0, 0, i.GetSizeX(), i.GetSizeY());
		vec2 pos = vec2(i.GetPosX(), i.GetPosY());
		
		gl::translate(pos);
		gl::draw(i.GetTexture(), sizeButton);
		gl::translate(-pos);
		
	

	}
	
}
void WasteLands::DrawMenuDie() {
	gl::ScopedModelMatrix scpModel;
	this->DrawMainMap();
	for (auto i : this->currentMap.GetAllButton()) {
		if (i.GetTexture()->getLabel() == "MenuMort") {
			
			Rectf sizeButton(0, 0, i.GetSizeX(), i.GetSizeY());
			vec2 pos = vec2(i.GetPosX(), i.GetPosY());
			gl::translate(pos);
			gl::draw(i.GetTexture(), sizeButton);
			gl::translate(-pos);
		}
		



	}
	

	
}
void WasteLands::DrawPrincipalMenu() {
	
	
	this->Video->draw(0, 0, getWindowWidth(), getWindowHeight());
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
		{
			this->DrawPrincipalMenu();
		
			break;
		}
		case 2:
			this->DrawMainMap();
			break;
		case 5:
			this->DrawMainMap();
			this->DrawMenuDie();
			break;
		case 6:
			this->DrawMainMap();
			try
			{
				this->DrawDialogue(this->allDialogue[0]);
			}
			catch (int e) 
			{
				this->actualMap = 2;
			}
			
			break;
		case 7:
		{
			this->DrawMainMap();

			if (this->allDialogue.size() != 0) {
				this->DrawDialogue(this->allDialogue[0]);
			}

			
		}
			break;
		case 8:
		{


			this->DrawMainMap();
			try
			{
				this->DrawDialogue(this->allDialogue[0]);
			}
			catch (int e)
			{
				this->actualMap = 7;
			}
		}
			break;

		case 9:
		{
			gl::ScopedModelMatrix scpModel;
			static double time = getElapsedSeconds();
			Surface mySurface;
			TextLayout layout;
		
			layout.setFont(this->mFont);
			
			
		
			if (getElapsedSeconds() - time < 3) {
				
				this->DrawMainMap();
				mySurface = Surface(getWindowWidth(), getWindowHeight(), true); 
				float alpha = (getElapsedSeconds() - time)/3*255;
				for (int i = 0; i < getWindowWidth(); i++) {
					for (int j = 0; j < getWindowHeight(); j++) {
						layout.setColor(ColorA(255, 255, 255, alpha));
						
						mySurface.setPixel(vec2(i, j), ColorA8u(0, 0, 0, alpha));
					}
				}
			}
			else {
				
				mySurface = Surface(getWindowWidth(), getWindowHeight(), true);
				(getWindowWidth(), getWindowHeight(), true);
				for (int i = 0; i < getWindowWidth(); i++) {
					for (int j = 0; j < getWindowHeight(); j++) {
						layout.setColor(ColorA(255, 255, 255, 255));
						mySurface.setPixel(vec2(i, j), ColorA8u(0, 0, 0, 255));
					}
				}
			}
			TextureRef d = gl::Texture::create(mySurface);
			
			layout.addLine("Merci d'avoir joue a notre jeu !");
			Texture2dRef font = gl::Texture2d::create(layout.render(true, true));
			gl::draw(d);
			
			gl::draw(font, vec2(getWindowWidth() / 2 - font->getWidth() / 2, getWindowHeight() / 2 - font->getHeight() / 2));
			break;
		}
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
			this->AttribAllImage(this->progressBarVar.GetPos());
		}
		
	}
	

	gl::drawString("Framerate: " + to_string(getAverageFps()), vec2(0, 0), Color::white(), Font("Arial", 12));


}




void WasteLands::drawTex(const ci::gl::Texture2dRef &tex, const ci::vec2 &pos, const Rectf & size)
{
	gl::ScopedModelMatrix scpModel;
	gl::translate(pos);
	if (size.getHeight() == 0 && size.getWidth() == 0) {
		gl::draw(tex);
	}
	else {
		
		gl::draw(tex, size);
	}
	
}

void WasteLands::drawMainCharacter(const ci::gl::Texture2dRef& tex, const ci::vec2& pos, const Rectf& size)
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

void WasteLands::drawProjectile(const ci::gl::Texture2dRef &tex, const ci::vec2 &pos, const Rectf & size , double orientation)
{
	gl::ScopedModelMatrix scpModel;
	
	gl::translate(pos );
	

	gl::rotate(orientation );
	gl::translate(-vec2(size.getWidth() / 2, size.getHeight() / 2));
	
	
	
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