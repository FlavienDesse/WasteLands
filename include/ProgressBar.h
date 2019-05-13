#pragma once
#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include "cinder/Utilities.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "Decor.h"
#include "Button.h"
#include "Personnage.h"
#include <map>
#include "ciWMFVideoPlayer.h"
#include "Projectile.h"
#include "Ennemies.h"
#include "Dialogue.h"
#include "cinder\audio\audio.h"
#include "cinder\audio\Node.h"
#include "cinder\audio\Context.h"
using namespace ci;
using namespace app;
using namespace std;
using namespace gl;
using namespace audio;
class ProgressBar
{
public:
	ProgressBar();
	void SetupMenu(std::experimental::filesystem::v1::path & chemin,int pos);
	void SetupMapCharacterEnnemiesDiversAndDialogue(std::experimental::filesystem::v1::path & chemin, string classe, int pos);
	void SetupMap(std::experimental::filesystem::v1::path & chemin,int pos);
	bool GetTerminated() { return this->mTerminated; }

	float getProgress();
	
	void clean();
	void clear();

	vector <Decor> GetAllDecor() { return this->allDecor; }
	vector <Button> GetAllButton() { return this->allButton; }
	TextureRef GetCurrentTextureMap() { return this->currentTextureMap; }
	Personnage GetMainCharacter() { return this->mainCharacter; }

	ciWMFVideoPlayer & GetVideo() { return this->Video; }

	bool GetLoadedMovie() { return this->loadedMovie; }

	int GetPos() { return this->pos; }
	map<string, Ennemiesload> GetEnnemiesLoad() { return this->allEnnemies; }
	vector<Projectile> GetAllProjectileCharacter() { return this->allProjectileCharacter; }
	map <string, SourceFileRef> GetSound() { return this->allAudio; }
	map <string, TextureRef> GetallDialogue() { return this->allDialogue; }
	map<string, TextureRef>  GetDivers() { return this->diversTexture; }
	
private:
	void threadSetupMenu(gl::ContextRef ctx);
	void threadSetupMapCharacterEnnemiesDiversAndDialogue(gl::ContextRef ctx);

	std::unique_ptr<std::thread>  mThread;             
	size_t                        mCount{ 0 };         
	std::vector<fs::path>         mQueue;            
	mutable std::mutex            mQueueMutex;        
	std::vector<gl::TextureRef> mTextures;          
	mutable std::mutex            mTexturesMutex;      
	bool              mTerminated = false ; 

	TextureRef currentTextureMap;
	Personnage mainCharacter;
	map<string,Ennemiesload> allEnnemies;
	vector <Decor> allDecor;
	vector <Button> allButton;
	vector <Projectile> allProjectileCharacter;
	map <string,TextureRef> allDialogue;
	map <string, SourceFileRef> allAudio;
	ciWMFVideoPlayer Video;
	map<string, TextureRef> diversTexture;
	
	bool loadedMovie;
	int pos = 0;
};

#endif