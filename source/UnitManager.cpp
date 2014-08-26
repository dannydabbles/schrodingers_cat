//
//
//
//   Project : Schrˆdinger's cat
//   File Name : UnitManager.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//

#include "UnitManager.h"

UnitManager::UnitManager(Grid* gGrid, LaserPointer* laser, Blood* blood)
{
   IW_CALLSTACK("UnitManager::UnitManager");

   this->uUnitList = CIwArray<Unit*>();
   this->uCollisionList = CIwArray<Unit*>();
   this->gGrid = gGrid;
   this->blood = blood;
   this->laser = laser;
}

void UnitManager::setCollisionList(CIwArray<Unit*> uCollisionList)
{
   IW_CALLSTACK("UnitManager::setCollisionList");

   this->uCollisionList = uCollisionList;
}

void UnitManager::update(uint64 time)
{
   IW_CALLSTACK("UnitManager::update");

   CIwArray<Unit*> uMovingList = CIwArray<Unit*>();
   for(int i = 0; i < (int)this->uUnitList.size(); ++i)
   {
      uUnitList[i]->update(time);
      if(uUnitList[i]->bIsMoving == true)
      {
         uMovingList.push_back(uUnitList[i]);
      }
   }
   for(int i = 0; i < (int)uMovingList.size(); ++i)
   {
      this->gGrid->changeUnitBox(uMovingList[i]);
      if(uMovingList[i]->sName.find("wall") != string::npos)
      {
         uMovingList[i]->bBox->bIsFilled = true;
      }
      /*if(uMovingList[i]->sName.compare("laser") == 0)
      {
      cout << "LZ0R Box: " << uMovingList[i]->bBox->i2Index.x << ", " << uMovingList[i]->bBox->i2Index.y << endl; 
      }*/
   }

   if(CatState::getState() == CatState::DEAD)
   {
      this->blood->bUpdate = true;
      this->blood->setPosition(this->gGrid->cCat->i2Position);
   }
}

void UnitManager::draw()
{
   IW_CALLSTACK("UnitManager::draw");

   for(int i = 0; i < (int)this->uUnitList.size(); ++i)
   {
      // kill the messages if paused or levelbeaten menus are being drawn
      if (GameState::getState() == GameState::PLAY || ((GameState::getState() == GameState::PAUSE || GameState::getState() == GameState::LEVELBEATEN) && this->uUnitList[i]->sName.compare("message") != 0))
         uUnitList[i]->draw();
   }

   if(GameState::getDebugging() == true)
   {
      this->drawBoxes();
   }
}

void UnitManager::drawBoxes()
{
   IW_CALLSTACK("UnitManager::drawBoxes");

   for (int i = 0; i < (int)this->uUnitList.size(); ++i)
   {
      this->uUnitList[i]->getBR().draw();
   }
}

// sets the order of the unit lists so
//cat,start and endbox, and laser pointer are drawn last
// and platforms first
// super ineffecient but its at the mpa load time so who gives a poop
void UnitManager::setUnitListOrder()
{
   Unit* cat = NULL;
   Unit* mouse = NULL;
   Unit* catevent = NULL;
   Unit* startbox = NULL;
   Unit* endbox = NULL;
   Unit* laser= NULL;
   CIwArray<Unit * > messages = CIwArray<Unit *>();
   CIwArray<Unit * > kittyLitters = CIwArray<Unit * >();
   CIwArray<Unit * > scythes = CIwArray<Unit * >();


    //first pass find refrence to various objects
   for ( int i = 0; i < (int)this->uUnitList.size(); ++i)
   {
      if ( this->uUnitList[i]->sName.compare("cat") == 0 )
      {
         cat = this->uUnitList[i];
      }
      else if (this->uUnitList[i]->sName.compare("startbox") == 0 )
      {
         startbox = this->uUnitList[i];
      }
      else if ( this->uUnitList[i]->sName.compare("endbox") == 0 )
      {
         endbox = this->uUnitList[i];
      }
      else if ( this->uUnitList[i]->sName.compare("catevent") == 0 )
      {
         catevent = this->uUnitList[i];
      }
      else if ( this->uUnitList[i]->sName.compare("mouse") == 0 )
      {
         mouse = this->uUnitList[i];
      }
      else if ( this->uUnitList[i]->sName.compare("message") == 0 )
      {
         messages.push_back( this->uUnitList[i] );
      }
      /*else if  (this->uUnitList[i]->sName.compare("litterbox") == 0 )
      {
         kittyLitters.push_back( this->uUnitList[i] );
      }*/
	  else if ( this->uUnitList[i]->sName.compare("scythe") == 0 )
	  {
		scythes.push_back(this->uUnitList[i]);
	  }
   }

   //remove the found objects from above from list
   this->uUnitList.find_and_remove_fast(cat);
   this->uUnitList.find_and_remove_fast(startbox);
   this->uUnitList.find_and_remove_fast(endbox);
   this->uUnitList.find_and_remove_fast(catevent); 
   this->uUnitList.find_and_remove(mouse);

   for ( int i = 0; i < (int) messages.size(); ++i)
   {
      this->uUnitList.find_and_remove( messages[i] );
   }
   /*for ( int i = 0; i < (int) kittyLitters.size(); ++i)
   {
        this->uUnitList.find_and_remove( kittyLitters[i] );
   }*/
   for ( int i = 0; i < (int) scythes.size(); ++i)
   {
        this->uUnitList.find_and_remove( scythes[i] );
   }

   // second pass, move all platforms to back ( so drawn in front)
   for ( int i = 0; i < (int)this->uUnitList.size(); ++i)
   {
      if ( this->uUnitList[i]->sName.compare("platform") == 0 )
      {
         Unit* platform = this->uUnitList[i];
         this->uUnitList.find_and_remove(this->uUnitList[i]);
         this->uUnitList.push_back(platform);  // insert_slow(platform, this->uUnitList.size());
      }
   }

   // third pass add buzzsaws and anvials to back ( so drawn in front)
   for ( int i = 0; i < (int)this->uUnitList.size(); ++i)
   {
      if ( this->uUnitList[i]->sName.compare("buzzsaw") == 0 || this->uUnitList[i]->sName.compare("anvil") == 0 || this->uUnitList[i]->sName.compare("block") == 0)
      {
         Unit* obj = this->uUnitList[i];
         this->uUnitList.find_and_remove(this->uUnitList[i]);
         this->uUnitList.push_back(obj);  
      }
   }

   // put in various objects to back ( so drawn in front)
   // 
   for ( int i = 0; i < (int)scythes.size(); ++i)
   {
      this->uUnitList.push_back( scythes[i] );
   }

   for ( int i = 0; i < (int)messages.size(); ++i)
   {
      this->uUnitList.push_back( messages[i] );
   }

   if ( mouse != NULL)
   {
      this->uUnitList.push_back(mouse);
   }

   this->uUnitList.push_back(cat);

   /*for ( int i = 0; i < (int)kittyLitters.size(); ++i)
   {
      this->uUnitList.push_back( kittyLitters[i] );
   }*/

   this->uUnitList.push_back(catevent);
   this->uUnitList.push_back(startbox);
   this->uUnitList.push_back(endbox);
   this->uUnitList.push_back(this->blood);
   this->uUnitList.push_back(this->laser);

}

UnitManager::~UnitManager()
{
   for(int i = 0; i < (int)this->uUnitList.size() - 2; ++i) // don't delete blood or the laserpointer
   {
      if(this->uUnitList[i]->sName.compare("anvil") == 0) {
         Anvil* tmp = dynamic_cast<Anvil*>(this->uUnitList[i]);
         delete tmp;
      }
      else if(this->uUnitList[i]->sName.compare("beartrap") == 0)
      {
         BearTrap* tmp =  dynamic_cast<BearTrap*>(this->uUnitList[i]);
         delete tmp;
      }
      else if(this->uUnitList[i]->sName.compare("block") == 0)
      {
         Block* tmp =  dynamic_cast<Block*>(this->uUnitList[i]);
         delete tmp;
      }
      else if(this->uUnitList[i]->sName.compare("bucket") == 0)
      {
         Bucket* tmp =  dynamic_cast<Bucket*>(this->uUnitList[i]);
         delete tmp;
      }
      else  if (this->uUnitList[i]->sName.compare("buzzsaw") == 0) 
      {
         Buzzsaw* tmp = dynamic_cast<Buzzsaw*>(this->uUnitList[i]);
         delete tmp;

      }
      else if (this->uUnitList[i]->sName.compare("cat") == 0)
      {
         Cat* tmp =  dynamic_cast<Cat*>(this->uUnitList[i]);
         delete tmp;

      }
      else  if(this->uUnitList[i]->sName.compare("catevent") == 0) 
      {
         CatEvent* tmp = dynamic_cast<CatEvent*>(this->uUnitList[i]);
         delete tmp;
      }
      else  if(this->uUnitList[i]->sName.compare("endbox") == 0) 
      {
         EndBox* tmp = dynamic_cast<EndBox*>(this->uUnitList[i]);
         delete tmp;
      }
      else  if (this->uUnitList[i]->sName.compare("food") == 0) 
      {
         Food* tmp = dynamic_cast<Food*>(this->uUnitList[i]);
         delete tmp;
      }
      else  if (this->uUnitList[i]->sName.compare("lever") == 0) 
      {
         Lever* tmp = dynamic_cast<Lever*>(this->uUnitList[i]);
         delete tmp;
      }
      else  if (this->uUnitList[i]->sName.compare("litterbox") == 0) 
      {
         LitterBox* tmp = dynamic_cast<LitterBox*>(this->uUnitList[i]);
         delete tmp;
      }
      else if (this->uUnitList[i]->sName.find("wall") != string::npos)
      {
         MechanicalWall* tmp = dynamic_cast<MechanicalWall*> (this->uUnitList[i]);
         delete tmp;
      }
      else if(this->uUnitList[i]->sName.compare("message") == 0)
      {
         Message* tmp =  dynamic_cast<Message*>(this->uUnitList[i]);
         delete tmp;
      }
      else if(this->uUnitList[i]->sName.compare("mouse") == 0)
      {
         Mouse* tmp =  dynamic_cast<Mouse*>(this->uUnitList[i]);
         delete tmp;
      }
      else if(this->uUnitList[i]->sName.compare("mousehole") == 0)
      {
         MouseHole* tmp =  dynamic_cast<MouseHole*>(this->uUnitList[i]);
         delete tmp;
      }
      else if (this->uUnitList[i]->sName.compare("platform") == 0)
      {
         Platform* tmp = dynamic_cast<Platform*>(this->uUnitList[i]);
         delete tmp;
      }
      else if (this->uUnitList[i]->sName.compare("pressureplate") == 0)
      {
         PressurePlate* tmp = dynamic_cast<PressurePlate*>(this->uUnitList[i]);
         delete tmp;
      }
      else if (this->uUnitList[i]->sName.compare("rope") == 0)
      {
         Rope* tmp = dynamic_cast<Rope*>(this->uUnitList[i]);
         delete tmp;
      }	
      else if (this->uUnitList[i]->sName.compare("scratchingpost") == 0)
      {
         ScratchingPost* tmp = dynamic_cast<ScratchingPost*>(this->uUnitList[i]);
         delete tmp;
      }		
      else if (this->uUnitList[i]->sName.compare("scythe") == 0)
      {
         Scythe* tmp = dynamic_cast<Scythe*>(this->uUnitList[i]);
         delete tmp;
      }
      else if (this->uUnitList[i]->sName.compare("scytheright") == 0)
      {
         ScytheRight* tmp = dynamic_cast<ScytheRight*>(this->uUnitList[i]);
         delete tmp;
      }
      else if (this->uUnitList[i]->sName.compare("scytheleft") == 0)
      {
         ScytheLeft* tmp = dynamic_cast<ScytheLeft*>(this->uUnitList[i]);
         delete tmp;
      }
      else if (this->uUnitList[i]->sName.compare("spike") == 0)
      {
         Spike* tmp = dynamic_cast<Spike*>(this->uUnitList[i]);
         delete tmp;
      }		
      else  if (this->uUnitList[i]->sName.compare("startbox") == 0) {
         StartBox* tmp = dynamic_cast<StartBox*>(this->uUnitList[i]);
         delete tmp;
      }
   }
   this->uUnitList.clear_optimised();
   this->uCollisionList.clear_optimised();
}
