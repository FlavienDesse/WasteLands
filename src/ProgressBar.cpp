#include "ProgressBar.h"



ProgressBar::ProgressBar(){}

void ProgressBar::SetupMenu(std::experimental::filesystem::v1::path & chemin,int pos)
{
	this->pos = pos;
	std::string line;
	
	mTerminated = false;
	for (const auto &entry : fs::directory_iterator(chemin)) {
		
		
		if (entry.path() == chemin.u8string() + "\\Button") {
			
			ifstream myfile(chemin.u8string() + "\\Button\\HitBox.txt",ios::in);

			
			
		

			

			for (const auto &entry2 : fs::directory_iterator(entry.path())) {

				


				const auto &file = entry2.path();
				
				if (is_regular_file(file) && file.extension() == ".png") {
					Button newButton;
					newButton.SetActive(true);

					
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

					


					this->allButton.push_back(newButton);
					
					tempPolygon.clear();
					mQueue.push_back(file);
					std::getline(myfile, line);
					
				}
	
					
				
			}
			myfile.close();
		}
		
		else if (entry.path().u8string() == chemin.u8string() + "\\fond.png") {
			const auto &file = entry.path();
			mQueue.push_back(file);
				
		}
		else if (entry.path().u8string() == chemin.u8string() + "\\Video.mp4") {
			mQueue.push_back(entry.path());
			
			
		}

	}

	// Count the files.
	mCount = mQueue.size();

	// Now create a shared OpenGL context, that we use to load and create textures on a background thread.
	gl::ContextRef backgroundCtx = gl::Context::create(gl::context());

	// Create our background thread, which will load the images in the queue.
	
	mThread = std::make_unique<std::thread>(std::bind(&ProgressBar::threadSetupMenu, this, backgroundCtx));
}


void ProgressBar::SetupMapCharacterAndEnnemies(std::experimental::filesystem::v1::path & chemin, string classe, int pos)
{

	this->pos = pos;

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




	int posDirectory;
	string key, extension;


	for (const auto & allDirectory : std::experimental::filesystem::v1::directory_iterator(getAssetDirectories()[0].u8string() + "\\Character\\" + classe)) {

		posDirectory = allDirectory.path().u8string().find_last_of('\\') + 1;
		key = allDirectory.path().u8string().substr(posDirectory, allDirectory.path().u8string().size());


		for (const auto & entry : std::experimental::filesystem::v1::directory_iterator(allDirectory.path())) {

			extension = GetFileExtension(entry.path().u8string());

			if (extension == "png") {



				std::pair <ci::gl::TextureRef, polygon> temp;

				this->mainCharacter.GetAnimation()[key].push_back(temp);


				mQueue.push_back(entry.path());


			}

		}













	}


	for (const auto &entry : fs::directory_iterator(getAssetDirectories()[0].u8string() + "\\Ennemies")) {
		int a = 0;
		
		int pos = entry.path().u8string().find_last_of('\\') + 1;
		string keyName = entry.path().u8string().substr(pos, entry.path().u8string().size());
		this->allEnnemies[keyName] = Ennemiesload();
		for (const auto &entry2 : fs::directory_iterator(entry)) {
			posDirectory = entry2.path().u8string().find_last_of('\\') + 1;
			key = entry2.path().u8string().substr(posDirectory, entry2.path().u8string().size());
	
			for (const auto &entry3 : fs::directory_iterator(entry2)) {
				extension = GetFileExtension(entry3.path().u8string());
			
				if (extension == "png") {
					std::pair <ci::gl::TextureRef, polygon> temp;
				
					this->allEnnemies[keyName].GetAnimation()[key].push_back(temp);
					mQueue.push_back(entry3.path());


				}

			}
		}
		a++;
	}


			

	// Count the files.
	mCount = mQueue.size();

	// Now create a shared OpenGL context, that we use to load and create textures on a background thread.
	gl::ContextRef backgroundCtx = gl::Context::create(gl::context());

	// Create our background thread, which will load the images in the queue.

	mThread = std::make_unique<std::thread>(std::bind(&ProgressBar::threadSetupMapCharacterAndEnnemies, this, backgroundCtx));
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
	
	currentTextureMap = NULL;
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

void ProgressBar::threadSetupMapCharacterAndEnnemies(gl::ContextRef ctx)
{

	
	ctx->makeCurrent();
	int numberButton = 0;
	int posAnimation = 0;
	int numberDecor = 0;
	int numberEnnemies = -1;
	string lastKey = "";
	fstream fileHitBoxCharacter;
	string hitBoxCharacter;
	polygon polygonEmpty;
	std::pair <ci::gl::TextureRef, polygon> pairEmpty;
	
	while (!mTerminated) {
	
		

		
		std::unique_lock<std::mutex> lockQueue(mQueueMutex);

	
		if (mQueue.empty())
			continue;

	
		const auto file = mQueue.front();
		mQueue.erase(mQueue.begin());

		
		lockQueue.unlock();

	
		const auto texture = gl::Texture::create(loadImage(file));
		
		
	
		auto fence = gl::Sync::create();
		fence->clientWaitSync();

		
		std::unique_lock<std::mutex> lockTextures(mTexturesMutex);

		

		int pos = file.u8string().find_last_of('\\') + 1;
		string key = file.u8string().substr(pos, file.u8string().size());

		int posDirectoryName = file.u8string().find_last_of('\\', pos - 2) + 1;
		string keyDirectoryName = file.u8string().substr(posDirectoryName, pos - posDirectoryName - 1);

		int pos3 = file.u8string().find_last_of('\\', posDirectoryName - 2) + 1;
		string key3 = file.u8string().substr(pos3, posDirectoryName - pos3 - 1);

		
		
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
		
		else if(key3=="Archer" || key3 == "Knight" || key3 == "Wizard") {
			
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
			

		
			
			
			if (keyDirectoryName == "Projectile") {
				int pos;
				Projectile newProjectile;
				pos = hitBoxCharacter.find(",");
				newProjectile.SetSizeX(stof(hitBoxCharacter.substr(0, pos)));
				newProjectile.SetSizeY(stof(hitBoxCharacter.substr(pos + 1, hitBoxCharacter.size())));
				
				std::getline(fileHitBoxCharacter, hitBoxCharacter);
				boost::geometry::read_wkt(
					hitBoxCharacter, polygonEmpty);
				newProjectile.SetHitBox(polygonEmpty);
				newProjectile.SetTexture(texture);
				this->allProjectileCharacter.push_back(newProjectile);
			}
			else {
				
			if (fileHitBoxCharacter.is_open()) {
				boost::geometry::read_wkt(
					hitBoxCharacter, polygonEmpty);
			}
			 if (keyDirectoryName == "WalkL") {
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].second = polygonEmpty;


				this->mainCharacter.GetAnimation()["WalkBL"].push_back(pairEmpty);
				this->mainCharacter.GetAnimation()["WalkBL"][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()["WalkBL"][posAnimation].second = polygonEmpty;

			}
			else if (keyDirectoryName == "RunL") {
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].second = polygonEmpty;

				this->mainCharacter.GetAnimation()["RunBL"].push_back(pairEmpty);
				this->mainCharacter.GetAnimation()["RunBL"][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()["RunBL"][posAnimation].second = polygonEmpty;
			}
			else if (keyDirectoryName == "StandL") {
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].second = polygonEmpty;

				this->mainCharacter.GetAnimation()["StandBL"].push_back(pairEmpty);
				this->mainCharacter.GetAnimation()["StandBL"][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()["StandBL"][posAnimation].second = polygonEmpty;
			}
			else if (keyDirectoryName == "JumpL") {
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].second = polygonEmpty;

				this->mainCharacter.GetAnimation()["JumpBL"].push_back(pairEmpty);
				this->mainCharacter.GetAnimation()["JumpBL"][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()["JumpBL"][posAnimation].second = polygonEmpty;
			}
			else if (keyDirectoryName == "DieL") {
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].first = texture;



			}
			else if (keyDirectoryName == "ShotL") {
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].second = polygonEmpty;

				this->mainCharacter.GetAnimation()["ShotBL"].push_back(pairEmpty);
				this->mainCharacter.GetAnimation()["ShotBL"][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()["ShotBL"][posAnimation].second = polygonEmpty;
			}

			else if (keyDirectoryName == "StandR") {
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].second = polygonEmpty;

				this->mainCharacter.GetAnimation()["StandB"].push_back(pairEmpty);
				this->mainCharacter.GetAnimation()["StandB"][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()["StandB"][posAnimation].second = polygonEmpty;

				this->mainCharacter.GetAnimation()["StandBR"].push_back(pairEmpty);
				this->mainCharacter.GetAnimation()["StandBR"][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()["StandBR"][posAnimation].second = polygonEmpty;
			}
			else if (keyDirectoryName == "WalkR") {
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].second = polygonEmpty;

				this->mainCharacter.GetAnimation()["WalkBR"].push_back(pairEmpty);
				this->mainCharacter.GetAnimation()["WalkBR"][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()["WalkBR"][posAnimation].second = polygonEmpty;

				this->mainCharacter.GetAnimation()["WalkB"].push_back(pairEmpty);
				this->mainCharacter.GetAnimation()["WalkB"][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()["WalkB"][posAnimation].second = polygonEmpty;

			}
			else if (keyDirectoryName == "JumpR") {
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].second = polygonEmpty;

				this->mainCharacter.GetAnimation()["JumpBR"].push_back(pairEmpty);
				this->mainCharacter.GetAnimation()["JumpBR"][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()["JumpBR"][posAnimation].second = polygonEmpty;

				this->mainCharacter.GetAnimation()["JumpB"].push_back(pairEmpty);
				this->mainCharacter.GetAnimation()["JumpB"][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()["JumpB"][posAnimation].second = polygonEmpty;

			}
			else if (keyDirectoryName == "RunR") {
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].second = polygonEmpty;

				this->mainCharacter.GetAnimation()["RunBR"].push_back(pairEmpty);
				this->mainCharacter.GetAnimation()["RunBR"][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()["RunBR"][posAnimation].second = polygonEmpty;

				this->mainCharacter.GetAnimation()["RunB"].push_back(pairEmpty);
				this->mainCharacter.GetAnimation()["RunB"][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()["RunB"][posAnimation].second = polygonEmpty;

			}
			else if (keyDirectoryName == "DieR") {
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].first = texture;

			}
			else if (keyDirectoryName == "ShotR") {
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].second = polygonEmpty;

				this->mainCharacter.GetAnimation()["ShotBR"].push_back(pairEmpty);
				this->mainCharacter.GetAnimation()["ShotBR"][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()["ShotBR"][posAnimation].second = polygonEmpty;

				this->mainCharacter.GetAnimation()["ShotB"].push_back(pairEmpty);
				this->mainCharacter.GetAnimation()["ShotB"][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()["ShotB"][posAnimation].second = polygonEmpty;
			}

			else if (keyDirectoryName == "WalkTR") {
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].second = polygonEmpty;

				this->mainCharacter.GetAnimation()["WalkT"].push_back(pairEmpty);
				this->mainCharacter.GetAnimation()["WalkT"][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()["WalkT"][posAnimation].second = polygonEmpty;

			}
			else if (keyDirectoryName == "RunTR") {
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].second = polygonEmpty;

				this->mainCharacter.GetAnimation()["RunT"].push_back(pairEmpty);
				this->mainCharacter.GetAnimation()["RunT"][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()["RunT"][posAnimation].second = polygonEmpty;

			}
			else if (keyDirectoryName == "JumpTR") {
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].second = polygonEmpty;

				this->mainCharacter.GetAnimation()["JumpT"].push_back(pairEmpty);
				this->mainCharacter.GetAnimation()["JumpT"][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()["JumpT"][posAnimation].second = polygonEmpty;

			}
			else if (keyDirectoryName == "StandTR") {
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].second = polygonEmpty;

				this->mainCharacter.GetAnimation()["StandT"].push_back(pairEmpty);
				this->mainCharacter.GetAnimation()["StandT"][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()["StandT"][posAnimation].second = polygonEmpty;

			}
			else if (keyDirectoryName == "ShotTR") {
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].second = polygonEmpty;

				this->mainCharacter.GetAnimation()["ShotT"].push_back(pairEmpty);
				this->mainCharacter.GetAnimation()["ShotT"][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()["ShotT"][posAnimation].second = polygonEmpty;

			}

			else if (keyDirectoryName == "WalkTL") {
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].second = polygonEmpty;
			}
			else if (keyDirectoryName == "RunTL") {
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].second = polygonEmpty;



			}
			else if (keyDirectoryName == "JumpTL") {
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].second = polygonEmpty;


			}
			else if (keyDirectoryName == "StandTL") {
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].second = polygonEmpty;


			}
			else if (keyDirectoryName == "ShotTL") {
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].first = texture;
				this->mainCharacter.GetAnimation()[keyDirectoryName][posAnimation].second = polygonEmpty;


			}


			polygonEmpty.clear();
			}
			}
		else if (key3 == "Rose") {
		
			if (lastKey != keyDirectoryName) {
				fileHitBoxCharacter.close();
				posAnimation = 0;
				lastKey = keyDirectoryName;
				fileHitBoxCharacter.open(file.u8string().substr(0, pos) + "\HitBox.txt");
				
			}
			else {
				posAnimation++;
			}
			std::getline(fileHitBoxCharacter, hitBoxCharacter);
			if (keyDirectoryName == "Projectile") {
				int pos;
				Projectile newProjectile;
				pos = hitBoxCharacter.find(",");
				newProjectile.SetSizeX(stof(hitBoxCharacter.substr(0, pos)));
				newProjectile.SetSizeY(stof(hitBoxCharacter.substr(pos + 1, hitBoxCharacter.size())));
				std::getline(fileHitBoxCharacter, hitBoxCharacter);
				pos = hitBoxCharacter.find(",");
				newProjectile.SetSpeedX(stof(hitBoxCharacter.substr(0, pos)));
				newProjectile.SetSpeedY(stof(hitBoxCharacter.substr(pos + 1, hitBoxCharacter.size())));
				std::getline(fileHitBoxCharacter, hitBoxCharacter);
				boost::geometry::read_wkt(
					hitBoxCharacter, polygonEmpty);
				newProjectile.SetHitBox(polygonEmpty);
				newProjectile.SetTexture(texture);
				this->allEnnemies[key3].GetProjectile().push_back(newProjectile);
			}
			else {
				if (fileHitBoxCharacter.is_open()) {
					
					boost::geometry::read_wkt(
						hitBoxCharacter, polygonEmpty);
					this->allEnnemies[key3].GetAnimation()[keyDirectoryName][posAnimation].first = texture;
					this->allEnnemies[key3].GetAnimation()[keyDirectoryName][posAnimation].second = polygonEmpty;
				}
				
				
				
			}
		}
			
		

	
	}

	// Bye bye!
}

void ProgressBar::threadSetupMenu(gl::ContextRef ctx)
{



	// Enable the OpenGL context.
	ctx->makeCurrent();
	int numberButton = 0;
	
	TextureRef texture;
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
		const auto file = mQueue.front();
		mQueue.erase(mQueue.begin());

		int pos = file.u8string().find_last_of('\\') + 1;
		string key = file.u8string().substr(pos, file.u8string().size());

		int posDirectoryName = file.u8string().find_last_of('\\', pos - 2) + 1;
		string keyDirectoryName = file.u8string().substr(posDirectoryName, pos - posDirectoryName - 1);

		// We're done with the queue, so we can release our lock now.
		lockQueue.unlock();

		if (key != "Video.mp4") {
			texture = gl::Texture::create(loadImage(file));
		}
		
		
		


		// Make sure OpenGL has finished uploading it to the GPU.
		auto fence = gl::Sync::create();
		fence->clientWaitSync();

		// Make sure we're the only ones accessing the list of textures.
		// The main thread might access the list at the same time and that would be bad.
		std::unique_lock<std::mutex> lockTextures(mTexturesMutex);

		// Finally, add it to the list of loaded textures.

		

		if (key == "fond.png") {
			this->currentTextureMap = texture;
		}
		else if (keyDirectoryName == "Button") {
			this->allButton[numberButton].SetTexture(texture);
			numberButton++;
		}
		else if (key == "Video.mp4") {
			
			this->loadedMovie=this->Video.loadMovie(file);
			this->Video.setVolume(0.5);
			this->Video.setLoop(true);
			
			
			
		}

		// Note: 'lockTextures' will go out of scope and release the lock for us.
	}

	// Bye bye!
}




