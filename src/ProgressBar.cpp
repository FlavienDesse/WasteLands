#include "ProgressBar.h"



ProgressBar::ProgressBar(){}

void ProgressBar::SetupMenu(std::experimental::filesystem::v1::path & chemin)
{


	
	mTerminated = false;
	for (const auto &entry : fs::directory_iterator(chemin)) {
		
		
		if (entry.path() == chemin.u8string() + "\\Button") {
			
			fstream myfile(chemin.u8string() + "\\Button\\HitBox.txt");

			



			for (const auto &entry2 : fs::directory_iterator(entry.path())) {

				


				const auto &file = entry2.path();
				
				if (is_regular_file(file) && file.extension() == ".png") {
					Button newButton;
					newButton.SetActive(true);

					std::string line;
					polygon tempPolygon;

					std::getline(myfile, line);
					int pos = line.find(",");

				

					newButton.SetSizeInitialiseX(stof(line.substr(0, pos)));
					newButton.SetSizeInitialiseY(stof(line.substr(pos + 1, line.size())));
					
					


					std::getline(myfile, line);
					pos = line.find(",");
					newButton.SetPosInitialiseX(stof(line.substr(0, pos)));
					newButton.SetPosInitialiseY(stof(line.substr(pos + 1, line.size())));

					



					std::getline(myfile, line);
					boost::geometry::read_wkt(line, tempPolygon);
					newButton.SetHitbox(tempPolygon);
					newButton.SetInitialHitBox(tempPolygon);
					std::getline(myfile, line);
					newButton.SetType(line);

					std::getline(myfile, line);


					this->allButton.push_back(newButton);
					
					tempPolygon.clear();
					mQueue.push_back(file);
					
				}
					
				
			}
			myfile.close();
		}
		
		else if (entry.path().u8string() == chemin.u8string() + "\\fond.png") {
			const auto &file = entry.path();
			if (is_regular_file(file) && file.extension() == ".png")
			{
				
				mQueue.push_back(file);
			}
				
		}

	}

	// Count the files.
	mCount = mQueue.size();

	// Now create a shared OpenGL context, that we use to load and create textures on a background thread.
	gl::ContextRef backgroundCtx = gl::Context::create(gl::context());

	// Create our background thread, which will load the images in the queue.
	
	mThread = std::make_unique<std::thread>(std::bind(&ProgressBar::threadSetupMenu, this, backgroundCtx));
}


void ProgressBar::SetupMapAndCharacter(std::experimental::filesystem::v1::path & chemin, string classe)
{



	mTerminated = false;
	for (const auto &entry : fs::directory_iterator(chemin)) {


		if (entry.path() == chemin.u8string() + "\\Button") {

			fstream myfile(chemin.u8string() + "\\Button\\HitBox.txt");





			for (const auto &entry2 : fs::directory_iterator(entry.path())) {




				const auto &file = entry2.path();



				if (is_regular_file(file) && file.extension() == ".png") {
					Button newButton;


					std::string line;
					polygon tempPolygon;

					std::getline(myfile, line);
					int pos = line.find(",");



					newButton.SetSizeInitialiseX(stof(line.substr(0, pos)));
					newButton.SetSizeInitialiseY(stof(line.substr(pos + 1, line.size())));



					std::getline(myfile, line);
					pos = line.find(",");
					newButton.SetPosInitialiseX(stof(line.substr(0, pos)));
					newButton.SetPosInitialiseY(stof(line.substr(pos + 1, line.size())));





					std::getline(myfile, line);
					boost::geometry::read_wkt(line, tempPolygon);
					newButton.SetHitbox(tempPolygon);

					std::getline(myfile, line);
					newButton.SetType(line);

					std::getline(myfile, line);


					this->allButton.push_back(newButton);

					tempPolygon.clear();
					mQueue.push_back(file);

				}


			}
			myfile.close();
		}
		else if (entry.path() == chemin.u8string() + "\\Decor") {
			fstream myfile(chemin.u8string() + "\\Decor\\HitBox.txt");
			
			for (const auto &entry2 : fs::directory_iterator(entry.path())) {

				const auto &file = entry2.path();



				


				if (is_regular_file(file) && file.extension() == ".png") {
					Decor newDec;

					


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

					std::getline(myfile, line);
					boost::geometry::read_wkt(line, tempPolygon);
					newDec.SetHitboxTexture(tempPolygon);


					this->allDecor.push_back(newDec);
					
					tempPolygon.clear();
					mQueue.push_back(entry2.path());

					std::getline(myfile, line);
				}
			
		}
			myfile.close();
		}
		else if (entry.path().u8string() == chemin.u8string() + "\\fond.png") {
			const auto &file = entry.path();
			if (is_regular_file(file) && file.extension() == ".png")
			{

				mQueue.push_back(file);
			}

		}


	}

	
	
	
	int pos;
	string key, extension;
	
	
	for (const auto & allDirectory : std::experimental::filesystem::v1::directory_iterator(getAssetDirectories()[0].u8string()+"\\Character\\"+classe    )) {

		pos = allDirectory.path().u8string().find_last_of('\\') + 1;
		key = allDirectory.path().u8string().substr(pos, allDirectory.path().u8string().size());


			for (const auto & entry : std::experimental::filesystem::v1::directory_iterator(allDirectory.path())) {

				extension = GetFileExtension(entry.path().u8string());

				if (extension == "png") {



					std::pair <ci::gl::TextureRef, polygon> temp;
					
					this->mainCharacter.GetAnimation()[key].push_back(temp);
					

					mQueue.push_back(entry.path());

					
				}

			}




		








	}
	
	// Count the files.
	mCount = mQueue.size();

	// Now create a shared OpenGL context, that we use to load and create textures on a background thread.
	gl::ContextRef backgroundCtx = gl::Context::create(gl::context());

	// Create our background thread, which will load the images in the queue.

	mThread = std::make_unique<std::thread>(std::bind(&ProgressBar::threadSetupMapAndCharacter, this, backgroundCtx));
}

float ProgressBar::getProgress()
{
	// First, we need to make sure we're the only ones accessing the queue.
	// The background thread might access the queue at the same time and that would be bad.
	std::lock_guard<std::mutex> lock(mQueueMutex);

	// Now calculate and return the progress. It's a value between 0 and 1.
	if (mCount > 0)
		return float(mCount - mQueue.size()) / mCount;

	return 1.0f;
}

void ProgressBar::clear() {
	allDecor.clear();
	allButton.clear();
}

void ProgressBar::clean()
{
	// Terminate our background thread.
	mTerminated = true;

	// Now wait until it is actually terminated.
	if (mThread && mThread->joinable())
		mThread->join();

	// Done.
	mThread.reset();
}

void ProgressBar::threadSetupMapAndCharacter(gl::ContextRef ctx)
{

	
	ctx->makeCurrent();
	int numberButton = 0;
	int posAnimation = 0;
	int numberDecor = 0;
	string lastKey = "";
	fstream fileHitBoxCharacter;
	string hitBoxCharacter;
	polygon polygonEmpty;
	std::pair <ci::gl::TextureRef, polygon> pairEmpty;
	
	while (!mTerminated) {
	
		

		
		std::unique_lock<std::mutex> lockQueue(mQueueMutex);

	
		if (mQueue.empty())
			continue;

	
		const auto file = mQueue.back();
		mQueue.pop_back();

		
		lockQueue.unlock();

	
		const auto texture = gl::Texture::create(loadImage(file));
		

	
		auto fence = gl::Sync::create();
		fence->clientWaitSync();

		
		std::unique_lock<std::mutex> lockTextures(mTexturesMutex);

		

		int pos = file.u8string().find_last_of('\\') + 1;
		string key = file.u8string().substr(pos, file.u8string().size());

		int posDirectoryName = file.u8string().find_last_of('\\', pos - 2) + 1;
		string keyDirectoryName = file.u8string().substr(posDirectoryName, pos - posDirectoryName - 1);

		
		
		if (key == "fond.png") {
			this->currentTextureMap = texture;
		}
		else if (keyDirectoryName == "Button") {
			this->allButton[numberButton].SetTexture(texture);
			numberButton++;
		}
		else if (keyDirectoryName == "Decor") {
			this->allDecor[numberDecor].SetTexture(texture);
			numberDecor++;
		}
		else  {
			
			if (lastKey != keyDirectoryName) {
				fileHitBoxCharacter.close();
				posAnimation = 0;
				lastKey = keyDirectoryName;
				fileHitBoxCharacter.open(file.u8string().substr(0, pos) +"\HitBox.txt");
				
			}
			else {
				posAnimation++;
			}
			std::getline(fileHitBoxCharacter, hitBoxCharacter);
			boost::geometry::read_wkt(
				hitBoxCharacter, polygonEmpty);

			
			if (keyDirectoryName == "WalkL") {
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].second = polygonEmpty;


				this->mainCharacter.GetAnimation()["WalkB"].push_back(pairEmpty);
				this->mainCharacter.GetAnimation()["WalkB"][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()["WalkB"][posAnimation].second = polygonEmpty;

				this->mainCharacter.GetAnimation()["WalkBL"].push_back(pairEmpty);
				this->mainCharacter.GetAnimation()["WalkBL"][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()["WalkBL"][posAnimation].second = polygonEmpty;

				this->mainCharacter.GetAnimation()["WalkTL"].push_back(pairEmpty);
				this->mainCharacter.GetAnimation()["WalkTL"][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()["WalkTL"][posAnimation].second = polygonEmpty;
			}
			else if (keyDirectoryName == "StandR") {
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].second = polygonEmpty;


			}
			else if (keyDirectoryName == "WalkR") {
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].second = polygonEmpty;

				this->mainCharacter.GetAnimation()["WalkBR"].push_back(pairEmpty);
				this->mainCharacter.GetAnimation()["WalkBR"][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()["WalkBR"][posAnimation].second = polygonEmpty;

			}
			else if (keyDirectoryName == "WalkTR") {
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].second = polygonEmpty;

				this->mainCharacter.GetAnimation()["WalkT"].push_back(pairEmpty);
				this->mainCharacter.GetAnimation()["WalkT"][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()["WalkT"][posAnimation].second = polygonEmpty;

			}
			else if (keyDirectoryName == "RunR") {
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].second = polygonEmpty;

				this->mainCharacter.GetAnimation()["RunBR"].push_back(pairEmpty);
				this->mainCharacter.GetAnimation()["RunBR"][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()["RunBR"][posAnimation].second = polygonEmpty;

			}
			else if (keyDirectoryName == "Projectile") {
				this->mainCharacter.GetProjectile().SetTexture(texture);
				this->mainCharacter.GetProjectile().SetHitBox(polygonEmpty);

				this->mainCharacter.GetProjectile().SetSizeX(100);
				this->mainCharacter.GetProjectile().SetSizeY(100);
				
			}
			polygonEmpty.clear();
		}
		

	
	}

	// Bye bye!
}

void ProgressBar::threadSetupMenu(gl::ContextRef ctx)
{



	// Enable the OpenGL context.
	ctx->makeCurrent();
	int numberButton = 0;
	

	// Now load all images one by one.
	while (!mTerminated) {
		// Let's first wait a little, making it easier to see how it works.


		// Make sure we're the only ones accessing the queue.
		// The main thread might access the queue at the same time and that would be bad.
		std::unique_lock<std::mutex> lockQueue(mQueueMutex);

		// If we're done, go back to sleep. 'lockQueue' will go out of scope and release the lock for us.
		if (mQueue.empty())
			continue;

		// Now grab a file from the queue.
		const auto file = mQueue.back();
		mQueue.pop_back();

		// We're done with the queue, so we can release our lock now.
		lockQueue.unlock();

		// Load the image.
		const auto texture = gl::Texture::create(loadImage(file));


		// Make sure OpenGL has finished uploading it to the GPU.
		auto fence = gl::Sync::create();
		fence->clientWaitSync();

		// Make sure we're the only ones accessing the list of textures.
		// The main thread might access the list at the same time and that would be bad.
		std::unique_lock<std::mutex> lockTextures(mTexturesMutex);

		// Finally, add it to the list of loaded textures.

		int pos = file.u8string().find_last_of('\\') + 1;
		string key = file.u8string().substr(pos, file.u8string().size());

		int posDirectoryName = file.u8string().find_last_of('\\', pos - 2) + 1;
		string keyDirectoryName = file.u8string().substr(posDirectoryName, pos - posDirectoryName - 1);

		if (key == "fond.png") {
			this->currentTextureMap = texture;
		}
		else if (keyDirectoryName == "Button") {
			this->allButton[numberButton].SetTexture(texture);
			numberButton++;
		}


		// Note: 'lockTextures' will go out of scope and release the lock for us.
	}

	// Bye bye!
}




