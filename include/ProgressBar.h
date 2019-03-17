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
using namespace ci;
using namespace app;
using namespace std;
using namespace gl;

class ProgressBar
{
public:
	ProgressBar();
	void SetupMenu(std::experimental::filesystem::v1::path & chemin,int pos);
	void SetupMapAndCharacter(std::experimental::filesystem::v1::path & chemin, string classe, int pos);
	
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

	vector<Projectile> GetAllProjectileCharacter() { return this->allProjectileCharacter; }
private:
	void threadSetupMenu(gl::ContextRef ctx);
	void threadSetupMapAndCharacter(gl::ContextRef ctx);

	std::unique_ptr<std::thread>  mThread;             
	size_t                        mCount{ 0 };         
	std::vector<fs::path>         mQueue;            
	mutable std::mutex            mQueueMutex;        
	std::vector<gl::TextureRef> mTextures;          
	mutable std::mutex            mTexturesMutex;      
	bool              mTerminated = false ; 

	TextureRef currentTextureMap;
	Personnage mainCharacter;
	
	vector <Decor> allDecor;
	vector <Button> allButton;
	vector <Projectile> allProjectileCharacter;
	ciWMFVideoPlayer Video;
	bool loadedMovie;
	int pos = 0;
};

#endif