#include "BackgroundManager.h"

// use time and screen multiplyer

BackgroundManager::BackgroundManager()
{
	 IW_CALLSTACK("BackgroundManager::BackgroundManager");
	this->i2Size = CIwSVec2(Screen::getSCREENSIZE().x/2, Screen::getSCREENSIZE().y/2); 
	this->positionArray = CIwArray<CIwSVec2>();
	this->units = CIwArray<BackgroundUnit*>();

	this->backgroundSegments = CIwArray<CIw2DImage*>();
	this->positionArray.push_back(CIwSVec2(0,0));
	this->positionArray.push_back(CIwSVec2(this->i2Size.x,0));
	this->positionArray.push_back(CIwSVec2(0,this->i2Size.y));
	this->positionArray.push_back(CIwSVec2(this->i2Size.x,this->i2Size.y));
	
}

void BackgroundManager::loadBackground(string backgroundName, CIwArray<string> extras)
{
	IW_CALLSTACK("BackgroundManager::loadBackground");
	
	this->units.clear();

	if ( extras.size() != 0)
	{
		for ( int x = 0;  x < (int)extras.size();  ++x)
		{
			if (extras[x].compare("cloud") == 0)
			{
				IwRandSeed  ( time(NULL)   );
				int num = IwRandMinMax(1, 6); // how many clouds should be made

				for ( int i = 0; i < num ; ++i)
				{
					CIwSVec2 pos = CIwSVec2( IwRandMinMax(-Screen::getBOXSIZE().x, Screen::getSCREENSIZE().x), IwRandMinMax(0, (int)(Screen::getSCREENSIZE().y * 0.33f)));
					float velocity =  (float) IwRandMinMax(500 ,2000) / 1000.0f;
					int type = IwRandMinMax(1, 10); // the number of cloud pictures we have
					Cloud * cloud = new Cloud(pos, velocity, type);
					this->units.push_back(cloud);
				}
			}
			else if (extras[x].compare("bird") == 0 )
			{
				
				CIwSVec2 pos = CIwSVec2(IwRandMinMax(0, Screen::getSCREENSIZE().x), IwRandMinMax(0, (int)(Screen::getSCREENSIZE().y * 0.4f)));
				float velocity = IwRandMinMax(1000, 4000)/100.0f;
				Bird  * bird = new Bird(pos, velocity);
				this->units.push_back(bird);
				

			}
			else if (extras[x].compare("gear") == 0 )
			{

				CIwSVec2 pos = CIwSVec2((int)(Screen::getSCREENSIZE().x * 0.3f), (int)(Screen::getSCREENSIZE().y * 0.4f)); 
				float velocity = (float)IwRandMinMax(1, 1000) / 10.0f;

				Gear  * gear = new Gear(0);
				Gear  * gear1 = new Gear(1);
				Gear  * gear2 = new Gear(2);

				this->units.push_back(gear);
				this->units.push_back(gear1);
				this->units.push_back(gear2);
			}
			else if (extras[x].compare("spiral") == 0)
			{
				this->units.push_back(new Spiral(CIwSVec2(Screen::getSCREENSIZE().x * 0.5 - 268/2, Screen::getSCREENSIZE().y * 0.5 - 268/2)));
				//this->units.push_back(new Spiral(CIwSVec2(Screen::getSCREENSIZE().x * 0.75 - 268/4, Screen::getSCREENSIZE().y * 0.5 - 272/4)));
			}
		}
	}
	this->backgroundSegments.clear();
	
	//if background is undefined no background is shown
	if ( backgroundName.compare("") == 0)
	{
		return;
	}
	
	// format has to follow backgroundName + "piece number"
	
	this->backgroundSegments.push_back(ImageManager::getImage( (backgroundName+"0").c_str() ));
	this->backgroundSegments.push_back(ImageManager::getImage( (backgroundName+"1").c_str() ));
	this->backgroundSegments.push_back(ImageManager::getImage( (backgroundName+"2").c_str() ));
	this->backgroundSegments.push_back(ImageManager::getImage( (backgroundName+"3").c_str() ));
}

// maps pages number to its background for the levelnavigation
// these values will eventually need to be changed
void BackgroundManager::loadBackground(int pageNum)
{
	 IW_CALLSTACK("BackgroundManager::LoadBackground");

	string backgroundName ="";
	CIwArray<string> extras = CIwArray<string>();

	switch (pageNum)
	{
	
		case 0:
			backgroundName = "mountains";
			extras.push_back("cloud");
			extras.push_back("bird");
			extras.push_back("bird");
			extras.push_back("bird");
			extras.push_back("bird");
			break;
		case 1:
			backgroundName = "industrial";
			extras.push_back("gear");
			break;
		case 2:
			backgroundName = "demoneyes";
			extras.push_back("spiral");
			break;
	}

	this->loadBackground(backgroundName, extras);
}

void BackgroundManager::update(uint64 time)
{
	IW_CALLSTACK("BackgroundManager::Update")
	for ( int i = 0; i < (int)this->units.size(); ++i)
		this->units[i]->update(time);

}

void BackgroundManager::draw()
{

	IW_CALLSTACK("BackgroundManager::Draw")

	for ( int i = 0; i < (int)this->backgroundSegments.size(); ++i)
		Iw2DDrawImageRegion(this->backgroundSegments[i], this->positionArray[i] , this->i2Size, CIwSVec2(0,0) , this->i2Size);

	for ( int i = 0; i < (int)this->units.size(); ++i)
		this->units[i]->draw();

	

}

BackgroundManager::~BackgroundManager()
{
	 IW_CALLSTACK("BackgroundManager::~BackgroundManager");

   for ( int i = 0; i < (int)this->units.size(); ++i)
   {
      delete this->units[i];
   }
}
