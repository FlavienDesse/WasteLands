#pragma once
#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include "cinder/Utilities.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "Decor.h"
#include "Button.h"
#include <map>
using namespace ci;
using namespace app;
using namespace std;
using namespace gl;

class ProgressBar
{
public:
	ProgressBar();
	void SetupMap(std::experimental::filesystem::v1::path & chemin);
	void SetupMapAndCharacter(std::experimental::filesystem::v1::path & chemin, string classe);
	
	bool GetTerminated() { return this->mTerminated; }

	float getProgress();
	
	void clean();
	void clear();

	vector <Decor> GetAllDecor() { return this->allDecor; }
	vector <Button> GetAllButton() { return this->allButton; }
	TextureRef GetCurrentTextureMap() { return this->currentTextureMap; }
	map<string, vector <pair <ci::gl::TextureRef, polygon>>> GetAnimation() { return this->animation; }
private:
	void threadFn(gl::ContextRef ctx);

	std::unique_ptr<std::thread>  mThread;             // Our background loading thread.
	size_t                        mCount{ 0 };         // The number of files to load.
	std::vector<fs::path>         mQueue;              // The list of files to load.
	mutable std::mutex            mQueueMutex;         // Controls access to the queue.
	std::vector<gl::TextureRef> mTextures;           // The list of loaded textures.
	mutable std::mutex            mTexturesMutex;      // Controls access to the loaded textures.
	bool              mTerminated = true ; // Will make sure our background thread is properly terminated.

	TextureRef currentTextureMap;
	map<string, vector <pair <ci::gl::TextureRef, polygon>>> animation;
	vector <Decor> allDecor;
	vector <Button> allButton;

};

#endif