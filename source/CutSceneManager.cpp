#include "CutSceneManager.h"

#define TIME_LIMIT 5000

CutSceneManager::CutSceneManager()
{
   IW_CALLSTACK("CutSceneManager::CutSceneManager");

   this->i2Size = CIwSVec2(Screen::getSCREENSIZE().x/2, Screen::getSCREENSIZE().y/2);
   this->i2RegionSize =  CIwSVec2(this->i2Size.x, this->i2Size.y );
   this->i2RegionOffset = CIwSVec2(this->i2RegionSize.x, 0 );
   this->imageSegments = CIwArray<CIwArray<CIw2DImage*> >();
   this->positionArray = CIwArray<CIwSVec2>();

   this->positionArray.push_back(CIwSVec2(0,0));
   this->positionArray.push_back(CIwSVec2(this->i2Size.x,0));
   this->positionArray.push_back(CIwSVec2(0,this->i2Size.y));
   this->positionArray.push_back(CIwSVec2(this->i2Size.x,this->i2Size.y));

   this->time = 0;
   this->iCurrentImage = 0;
   this->bFinished = false;
}


void CutSceneManager::LoadCutScene(string sceneName)
{
   IW_CALLSTACK("CutSceneManager::LoadCutScene");
	
   this->time = 0;
   this->iCurrentImage = 0;
   this->bFinished = false;
   this->imageSegments.clear();

   // if next level does not have a sceneFollowing it
   if (sceneName.compare("") == 0)
   {
      return;
   }
   //file format name has to be "sceneName" + "image number" + "segment number" and then the number of pictures( not including 4 segments each)
   //example introScene10, introScene11, introScene12,  introScene13
   //        introScene20, introScene21, introScene22, etc
   this->sceneName = sceneName;

	SoundManager::setMusic("OhNoesMyCat");
	
   if ( this->sceneName.compare("screen") == 0)
   {
      for ( int i = 0; i < 12; ++i)
      {
         CIwArray<CIw2DImage*> segments;
         string ImageNumber;
         stringstream s1;
		 if ( i < 10)
		 {	
			s1 << 0;
		 }
		 s1 << i;
		 
         ImageNumber = s1.str();

         segments.push_back(ImageManager::getImage( (sceneName + ImageNumber + "0").c_str() ) );
         segments.push_back(ImageManager::getImage( (sceneName + ImageNumber + "1").c_str() ) );
         segments.push_back(ImageManager::getImage( (sceneName + ImageNumber + "2").c_str() ) );
         segments.push_back(ImageManager::getImage( (sceneName + ImageNumber + "3").c_str() ) );

         this->imageSegments.push_back(segments);
      }

      this->frameTime.push_back(12000 * 0.66);   //How I lost my cat
      this->frameTime.push_back(10000 * 0.62);  //cast of characters
      this->frameTime.push_back(1750 * 0.62);   //one day
      this->frameTime.push_back(8250 * 0.62);   //playing with cat
      this->frameTime.push_back(5000 * 0.61);   //zomgz shcrodinger
      this->frameTime.push_back(6000 * 0.62);   //he steals him
      this->frameTime.push_back(13000 * 0.62);  //he falls into le box
      this->frameTime.push_back(4000 * 0.61);   //oh noes stinky box
      this->frameTime.push_back(4000 * 0.51);   //close up on girl
      this->frameTime.push_back(5000 * 0.58);   //look in the box
	  this->frameTime.push_back(8000 * 0.62);    //i haz laser
	  this->frameTime.push_back(14500 * 0.60);   //the end

   }

   this->iCurrentImage = 0;
}
void CutSceneManager::update(uint64 time)
{

   IW_CALLSTACK("CutSceneManager::Update");	

   s3ePointerUpdate();

   if(s3ePointerGetTouchState(0) && S3E_POINTER_TOUCH_EVENT)
   {
      reset();
		SoundManager::setMusic("Tutorial");
      GameState::setState(GameState::PLAY);
      return;
   }

   this->time += time;


   if ( this->time > this->frameTime[this->iCurrentImage] )
   {

      this->time = 0;

      if ( (int)this->imageSegments.size() > this->iCurrentImage + 1)
         ++(this->iCurrentImage);

      else 
      {
         this->reset();
			SoundManager::setMusic("Tutorial");
         GameState::setState(GameState::PLAY);
	  }
   }
}

// returns false when finsished
void CutSceneManager::draw()
{
   IW_CALLSTACK("CutSceneManager::draw");

   for ( int i = 0; i < (int)this->imageSegments[this->iCurrentImage].size(); ++i)
   {
      Iw2DDrawImage(this->imageSegments[this->iCurrentImage][i], this->positionArray[i]);
   }
}

void CutSceneManager::reset()
{
   IW_CALLSTACK("CutSceneManager::reset");

   this->time = 0;
   this->iCurrentImage = 0;
   this->bFinished = false;
   this->imageSegments.clear();

   for ( int i = 0; i < 4; ++i)
   {
      string ImageNumber;
      stringstream s1;

	  if ( i < 10)
	  {	
			s1 << 0;
	  }

      s1 << i;
      ImageNumber = s1.str();

      ImageManager::removeImage((this->sceneName + ImageNumber + "0").c_str());
      ImageManager::removeImage((this->sceneName + ImageNumber + "1").c_str());
      ImageManager::removeImage((this->sceneName + ImageNumber + "2").c_str());
      ImageManager::removeImage((this->sceneName + ImageNumber + "3").c_str());
   }
}
