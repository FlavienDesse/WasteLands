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
using namespace ci;
using namespace app;
using namespace std;
using namespace gl;

class ProgressBar
{
public:
	ProgressBar();
	void SetupMenu(std::experimental::filesystem::v1::path & chemin);
	void SetupMapAndCharacter(std::experimental::filesystem::v1::path & chemin, string classe);
	
	bool GetTerminated() { return this->mTerminated; }

	float getProgress();
	
	void clean();
	void clear();

	vector <Decor> GetAllDecor() { return this->allDecor; }
	vector <Button> GetAllButton() { return this->allButton; }
	TextureRef GetCurrentTextureMap() { return this->currentTextureMap; }
	Personnage GetMainCharacter() { return this->mainCharacter; }
private:
	void threadSetupMenu(gl::ContextRef ctx);
	void threadSetupMapAndCharacter(gl::ContextRef ctx);

	std::unique_ptr<std::thread>  mThread;             
	size_t                        mCount{ 0 };         
	std::vector<fs::path>         mQueue;            
	mutable std::mutex            mQueueMutex;        
	std::vector<gl::TextureRef> mTextures;          
	mutable std::mutex            mTexturesMutex;      
	bool              mTerminated = true ; 

	TextureRef currentTextureMap;
	Personnage mainCharacter;
	
	vector <Decor> allDecor;
	vector <Button> allButton;

};

#endif