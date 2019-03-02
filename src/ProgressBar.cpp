#include "ProgressBar.h"



ProgressBar::ProgressBar(){}

void ProgressBar::SetupMap(std::experimental::filesystem::v1::path & chemin)
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
	
	mThread = std::make_unique<std::thread>(std::bind(&ProgressBar::threadFn, this, backgroundCtx));
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

	
	std::string line;

	ifstream myfile;
	int pos;
	string key, extension;
	polygon polygonEmpty;
	
	for (const auto & allDirectory : std::experimental::filesystem::v1::directory_iterator(getAssetDirectories()[0].u8string()+"\\Character\\"+classe    )) {

		pos = allDirectory.path().u8string().find_last_of('\\') + 1;
		key = allDirectory.path().u8string().substr(pos, allDirectory.path().u8string().size());




		myfile.open(allDirectory.path().u8string() + "\\HitBox.txt");

		if (myfile.is_open() != 0) {

			for (const auto & entry : std::experimental::filesystem::v1::directory_iterator(allDirectory.path())) {

				extension = GetFileExtension(entry.path().u8string());

				if (extension == "png") {

					std::getline(myfile, line);



					boost::geometry::read_wkt(
						line, polygonEmpty);
					std::pair <ci::gl::TextureRef, polygon> temp;
					temp.second = polygonEmpty;
					
					this->animation[key].push_back(temp);

					mQueue.push_back(entry.path());

					
				}

			}




		}


		myfile.close();









	}
	
	// Count the files.
	mCount = mQueue.size();

	// Now create a shared OpenGL context, that we use to load and create textures on a background thread.
	gl::ContextRef backgroundCtx = gl::Context::create(gl::context());

	// Create our background thread, which will load the images in the queue.

	mThread = std::make_unique<std::thread>(std::bind(&ProgressBar::threadFn, this, backgroundCtx));
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

void ProgressBar::threadFn(gl::ContextRef ctx)
{

	

	// Enable the OpenGL context.
	ctx->makeCurrent();
	int numberButton = 0;
	int posAnimation = 0;
	int numberDecor = 0;
	string lastKey = "";
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

		int posDirectoryNameCharacter = file.u8string().find_last_of('\\', posDirectoryName - 2) + 1;
		string keyDirectoryNameCharater = file.u8string().substr(posDirectoryNameCharacter, posDirectoryName - posDirectoryNameCharacter - 1);
		
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
		else if (keyDirectoryNameCharater == "Archer" || keyDirectoryNameCharater == "IceWizard" || keyDirectoryNameCharater == "Knight") {
			
			if (lastKey != keyDirectoryName) {
				posAnimation = 0;
				lastKey = keyDirectoryName;
			}
			else {
				posAnimation++;
			}
				
			this->animation[keyDirectoryName][posAnimation].first = texture;
			
		}
		

		// Note: 'lockTextures' will go out of scope and release the lock for us.
	}

	// Bye bye!
}


