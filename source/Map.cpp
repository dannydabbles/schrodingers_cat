//
//
//
//   Project : Schrödinger's cat
//   File Name : Map.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "Map.h"
#include "stdlib.h" // remove if you see this 


Map::Map(string sLevelName, Blood* blood, Grid* grid, FILE* fAllOut)
{
   IW_CALLSTACK("Map::Map");

   IwAssertMsg(MYAPP, fAllOut != NULL, ("allOut is NULL in map"));
   this->fAllOutFile = fAllOut;
   PlayerProfile::setDeath(0);
   PlayerProfile::setTime(0);
   this->sBackground = "";
   this->sBackgroundExtras = CIwArray<string>();
   this->sCutSceneName = "";
   this->sLevelName = sLevelName;
   fprintf(this->fAllOutFile, "%s:\n",this->sLevelName.c_str());
   this->gGrid = grid;
   this->gGrid->reset();
   this->bBegin= NULL;
   this->bEnd = NULL;
   this->uCurrent = NULL;
   this->stBacklog = CIwArray<string>();
   this->pLabelList = CIwArray<pair<string, CIwArray<string> > >();
   this->pMultiBoxEffectList = CIwArray<pair<pair<pair<char,char>,string>,pair<pair<int,int>,Box*> > >();
   this->pStructuresList = CIwArray<pair<pair<char,char>,Unit*> >();
   this->ulMouseList = CIwArray<Mouse*>();
   this->vvsInstruct = CIwArray<CIwArray<string> >();
   this->sBackgroundMusic = "";
   this->laser = new LaserPointer();
   this->umManager = new UnitManager(this->gGrid, laser, blood);
   this->bDone = false;
   //this->pButton = new PauseButton();
   this->tLevelTime = 0; //time(NULL);
   this->suShinyList = CIwArray<ShinyUnit*>();
   ShinyUnit::setShiniestUnit(NULL);
   ShinyUnit::setShinyDropDownBox(NULL);
   // keep last
   this->iColorCode = 0;
   this->readFiles();
   this->mAI = new MouseAI(this->ulMouseList);
   this->suShinyList.push_back(laser);
   this->csmStateManager = new CatStateManager();
   this->cAI = new CatAI(this->bBegin, this->bEnd, this->cKitty, this->gGrid, this->suShinyList, this->csmStateManager, laser);
   this->gGrid->setPathFinder(this->cAI->getPathFinder());
   GameState::setReInitializePathing(true);
   GameState::setState(GameState::PLAY);

   if(this->sBackgroundMusic.empty() == false)
   {
      SoundManager::setMusic(this->sBackgroundMusic);
   }
   else
   {
      SoundManager::setMusic("kittydub");
   }

}

pair<string, CIwArray<string> > Map::getBackgroundNames()
{
   IW_CALLSTACK("Map::getBackgroundNames");

   return pair<string, CIwArray<string> >(this->sBackground, this->sBackgroundExtras);
}

string Map::getCutSceneName()
{
   IW_CALLSTACK("Map::getCutSceneName");

   return this->sCutSceneName;
}

void Map::update(uint64 time)
{
   IW_CALLSTACK("Map::update");

   this->tLevelTime += time;
   PlayerProfile::setTime(tLevelTime);

   if(CatState::getState() == CatState::DEAD)
   {
      this->catIsDead();
   }

   if(GameState::getState() == GameState::PLAY)
   {
      this->gGrid->update(time);
      this->umManager->update(time);
      this->cAI->update(time);
      this->csmStateManager->update();
      this->mAI->update(this->cKitty);
   }

   if(GameState::getState() == GameState::LEVELBEATEN)
   {
      this->writeFile();
      this->bDone = true;
      return;
   }
   IwAssertMsg(MYAPP, CatState::getState() != CatState::TRANSITIONING, ("Map update exited with interrupt state")); 
}

void Map::readLabels()
{
   IW_CALLSTACK("Map::readLabels");

   ifstream fFile("all.labels");

   if(fFile.is_open())
   {
      char buffer[1024];
      pLabelList = CIwArray<pair<string, CIwArray<string> > >();

      int j=0;
      while(fFile.good())
      {
         fFile.getline(buffer, 1024);
         string label = "";
         label.append(&buffer[0], 1);
         label.append(&buffer[1], 1);
         //cout << label << " ";
         CIwArray<string> words = CIwArray<string>();
         string sTemp = "";

         for(int i = 3; ; ++i)
         {
            if(buffer[i] == ' ')
            {
               words.push_back(sTemp);
               //cout << sTemp << " ";
               sTemp.clear();					
            }
            else if(buffer[i] == '\r' || buffer[i] == '\n')
            {
               words.push_back(sTemp);
               //cout << sTemp << endl;
               sTemp.clear();
               break;
            }
            else
            {
               sTemp += buffer[i];
            }
         }
         pLabelList.push_back(pair<string, CIwArray<string> >(label, words));
         //cout << vpLabelList[j].first << "\n";
         j++;
      }
   }
   else
   {
      IwAssertMsg(MYAPP, false, ("Could not read label file"));
   }
}


//Reads a .map and parses it into two different variables.  It also initializes each object found within the map.
void Map::readMap() 
{
   IW_CALLSTACK("Map::readMap");

   CIwArray<pair<pair<char,char>,pair<int,int> > > stopRope = CIwArray<pair<pair<char,char>,pair<int,int> > >();
   string path = sLevelName + ".map";
   string grids[15][12];
   ifstream fFile(path.c_str());
   //ifstream fFile("map2.map");

   this->umManager->uUnitList.size();

   if(fFile.is_open())
   {
      char buffer[1024];
      fFile.getline(buffer,1024);
      for(int j = 0; j < 12 ; j++){
         fFile.getline(buffer,1024);
         for(int i=2;i<32;i+=2){
            grids[(i-2)/2][j] += buffer[i];
            grids[(i-2)/2][j] += buffer[i+1];

            CIwArray<string> tempVec;
            CIwArray<Unit*> tempUnitVec = CIwArray<Unit*>();
            if(grids[(i-2)/2][j] != "  " && grids[(i-2)/2][j] != "--")
            { 
               if(buffer[i+1]>=48 && buffer[i+1]<=57)
               {
                  tempVec=findVector(grids[(i-2)/2][j].substr(0,1) + "#");
               }
               else
                  tempVec = findVector(grids[(i-2)/2][j]);
               pair<char,char> tempChar = pair<char,char>(buffer[i],buffer[i+1]);
               pair<int,int> tempint = pair<int,int>((i-2)/2,j);
               pair<pair<int,int>,Box*> temp2 = pair<pair<int,int>,Box*>();
               pair<pair<char,char>,string> temp3 = pair<pair<char,char>,string>(tempChar,tempVec[0]);
               temp2.first = tempint;
               temp2.second = gGrid->getBox((i-2)/2,j, true);
               if(temp3.second.find("wall") != string::npos) temp2.second->bIsFilled = true;
               pMultiBoxEffectList.push_back(pair<pair<pair<char,char>,string>,pair<pair<int,int>,Box*> >(temp3,temp2));
               if(tempVec[0] == "rope" && j != 2)
               {
                  stopRope.push_back(pair<pair<char,char>,pair<int,int> >(tempChar,tempint));
               }
               //}
               //else
               //tempVec=findVector(grids[(i-2)/2][j]);
               for(int n=0;n<(int)tempVec.size();++n)
               {
                  Box* currentBox = pMultiBoxEffectList[pMultiBoxEffectList.size()-1].second.second;
                  Unit * unit = getUnit(tempVec[n], CIwSVec2(((i-2)/2)*Screen::getBOXSIZE().y, (j-2)*Screen::getBOXSIZE().x));
                  unit->bBox = currentBox;
                  if(unit->sName.compare("endbox") == 0)
                  {
                     unit->bBox->bConnectList[1]->bIsWalkable = true;
                     unit->bBox->bIsFilled = true;
                     unit->bBox->bIsWalkable = false;
                  }
                  this->umManager->uUnitList.push_back(unit);
                  if(unit->bIsShiny == true)
                  {
                     this->suShinyList.push_back(dynamic_cast<ShinyUnit*>(unit));
                  }
                  if(unit->sName.find("wall") != string::npos) 
                     gGrid->getBox(((i-2)/2), j, true)->bIsFilled = true;
                  tempUnitVec.push_back(unit);

                  if ( unit->sName.compare("cat")== 0)
                     this->gGrid->setCat((Cat*)unit);
               }
               //if(tempVec[0] == "scratchingpost")
               //{
                //  if(stBacklog.empty() == false)
                //  {
                //     tempUnitVec[0]->bDrawn = true;
                //     stBacklog.pop_back();
                //  }
                //  else
                 //    stBacklog.push_back(tempVec[0]);
              // }
               gGrid->loadBox(tempUnitVec,(i-2) / 2, j);

               if(tempVec[0] == "startbox") //Huh?
               {
                  Unit * unit = getUnit("platform", CIwSVec2(((i-2)/2)*Screen::getBOXSIZE().y, (j-3)*Screen::getBOXSIZE().x));
                  tempUnitVec.clear();
                  tempUnitVec.push_back(unit);
                  gGrid->loadBox(tempUnitVec, (i-2)/2, j-1);
                  unit->bDrawn = true;
               }

               if(tempVec[0].find("wall") != string::npos)
               {
                  this->gGrid->getBox((i-2)/2,j,true)->bIsFilled = true;
                  //this->gGrid->getBox((i-2)/2,j,true)->bIsWalkable = false;
               }

               //cout<<(i-2)/2<<" "<<j<<gGrid->getBox((i-2)/2,j,true)->uUnitList.size()<<"\n\n\n";
               //cout<<endl;
               tempVec.clear();
            }
            /*
            for(int a=0;a<(int)pMultiBoxEffectList.size();++a)
            {
            if(pMultiBoxEffectList[a].first.second == "rope")
            {
            if(pMultiBoxEffectList[a].second.first.first == (i-2)/2 && j != 2)
            {
            bool tempmatch=false;
            for(int o = 0 ; o < (int)stopRope.size(); ++o)
            {
            if(stopRope[o].second.first == (i-2)/2 && (stopRope[o].second.second <= j))
            {
            tempmatch = true;
            if(stopRope[o].second.second == j)
            {
            if(buffer[i] == 'R')
            gGrid->getBox((i-2)/2,j, true)->getUnit("rope")->changeTexture(1);
            else
            gGrid->getBox((i-2)/2,j, true)->getUnit("rope")->changeTexture(2);
            }
            }
            }
            if(!tempmatch){
            tempUnitVec.clear();
            tempUnitVec.push_back(getUnit("rope", CIwSVec2(((i-2)/2)*32, (j-2)*32)));
            //tempUnitVec should be size one containing one rope
            gGrid->loadBox(tempUnitVec, (i-2)/2, j);
            pair<int,int> tempint = pair<int,int>((i-2)/2, j);
            pair<pair<int,int>,Box*> temp2 = pair<pair<int,int>,Box*>();
            temp2.first = tempint;
            temp2.second = gGrid->getBox((i-2)/2, j, true);
            //temp2.second is the current box
            tempUnitVec[0]->bBox = temp2.second;
            this->umManager->uUnitList.push_back(tempUnitVec[0]);
            pMultiBoxEffectList.push_back(pair<pair<pair<char,char>,string>,pair<pair<int,int>,Box*> >(pMultiBoxEffectList[a].first,temp2));
            //cout<<"\n\n\n\n\n"<<tempint.first<<", "<<tempint.second;
            break;
            }
            }
            }
            }
            */	
         }
      }

      //Puts the top left Unit* into vpStructures and both puts all other similar units into that units attatchedto,
      //as well as putting that unit into all others attatched to

      for(int i = 0; i < (int)pMultiBoxEffectList.size(); ++i)
      {
         if(pStructuresList.empty())
         {
            pStructuresList.push_back(pair<pair<char,char>,Unit*>(pMultiBoxEffectList[i].first.first,pMultiBoxEffectList[i].second.second->getUnit(pMultiBoxEffectList[i].first.second)));
            pStructuresList[0].second->bTop = true;
         }
         else
         {
            bool match=false;
            for(int j=0 ; j < (int)pStructuresList.size(); ++j)
            {
               if((pStructuresList[j].first.first == toupper(pMultiBoxEffectList[i].first.first.first) || pStructuresList[j].first.first == tolower(pMultiBoxEffectList[i].first.first.first) ) && pStructuresList[j].first.second == pMultiBoxEffectList[i].first.first.second)
               {
                  match=true;
                  pStructuresList[j].second->addUnit(gGrid->getBox(pMultiBoxEffectList[i].second.first.first,pMultiBoxEffectList[i].second.first.second, true)->getUnit(pMultiBoxEffectList[i].first.second));
                  pMultiBoxEffectList[i].second.second->getUnit(pMultiBoxEffectList[i].first.second)->addUnit(pStructuresList[j].second);
                  //cout<<"\n\n\n\n\na\n\n\n\n";
               }
            }
            if(!match)
            {
               string stemp = pMultiBoxEffectList[i].first.second;
               Box* bTemp = pMultiBoxEffectList[i].second.second;
               Unit* utunit = pMultiBoxEffectList[i].second.second->getUnit(pMultiBoxEffectList[i].first.second);
               pStructuresList.push_back(pair<pair<char,char>,Unit*>(pMultiBoxEffectList[i].first.first,pMultiBoxEffectList[i].second.second->getUnit(pMultiBoxEffectList[i].first.second)));
               pStructuresList[(int)pStructuresList.size() - 1].second->bTop = true;
            }
         }
      }
      CIwArray<Unit*> tempFoodArray = CIwArray<Unit*>();
      CIwArray<Unit*> tempLitterArray = CIwArray<Unit*>();
      for(int i = 0; i < (int)pStructuresList.size(); ++i)
      {
         if(this->pStructuresList[i].first.first == 'C' && this->pStructuresList[i].first.second == 'F')
         {
            tempFoodArray.push_back(this->pStructuresList[i].second);
            for(int j = 0; j < (int)pStructuresList[i].second->uAttatchedToList.size(); ++j)
            {
               tempFoodArray.push_back(this->pStructuresList[i].second->uAttatchedToList[j]);
            }
         }
         if(this->pStructuresList[i].first.first == 'L' && this->pStructuresList[i].first.second == 'B')
         {
            tempLitterArray.push_back(this->pStructuresList[i].second);
            for(int j = 0; j < (int)pStructuresList[i].second->uAttatchedToList.size(); ++j)
            {
               tempLitterArray.push_back(this->pStructuresList[i].second->uAttatchedToList[j]);
            }
         }
      }
      for( int i = 0; i < (int) pStructuresList.size(); ++i)
      {
         if(this->pStructuresList[i].first.first == 'M')
            this->pStructuresList[i].second->uAffectList = tempFoodArray;
      }
      for(int i = 0; i <(int)tempFoodArray.size(); ++i)
      {
         tempFoodArray[i]->uAffectList = tempLitterArray;
         tempFoodArray[i]->uAttatchedToList = tempFoodArray;
      }
      for(int i = 0; i <(int)tempLitterArray.size(); ++i)
      {
         tempLitterArray[i]->uAffectList = tempFoodArray;
         tempLitterArray[i]->uAttatchedToList = tempLitterArray;
      }
      /*
      cout<<"\n\n\n\n\n\n";
      for(int w = 0; w < (int)vpStructures.size(); ++w)
      {
      int a=vpStructures[w].second->i2Position.x/32;
      int b=vpStructures[w].second->i2Position.y/32+2;
      cout<<gGrid.getBox(a,b, true)->uUnitList[0]->uAttatchedToList.size()<<"\n";
      }
      cout<<"\n";
      */
   }
   fFile.close();

   this->umManager->setUnitListOrder();


}

//reads the .label file for each map.  Separates the lines into a vector of strings by word, seperates file into a vector of those lines.
void Map::readInteractions()
{
   IW_CALLSTACK("Map::readInteractions");

   string path = sLevelName + ".label";
   ifstream fFile(path.c_str());
   if(fFile.is_open())
   {
      char buffer[1024];
      CIwArray<string> vtempString = CIwArray<string>();
      string temp = "";
      while(fFile.good())
      {
         cout<<"\n";
         fFile.getline(buffer,1024);
         for(int i = 0; ; ++i)
         {
            if(buffer[i] == '\r' || buffer[i] == '\n' || buffer[i] == 0)
            {
               vtempString.push_back(temp);
               cout<<"\n"<<temp<<"\n";
               temp.clear();
               break;
            }
            if(buffer[i] != '_')
               temp+=buffer[i];
            else if(buffer[i] == '_'){
               vtempString.push_back(temp);
               cout<<"\n"<<temp<<"\n";
               temp.clear();
            }

         }
         vvsInstruct.push_back(vtempString);
         vtempString.clear();
      }
      for ( int i = 0; i < (int)vvsInstruct.size(); ++i)
      {
         if ( vvsInstruct[i][0].compare("background") == 0)
         {
            this->sBackground = vvsInstruct[i][1];
         }
         else if ( vvsInstruct[i][0].compare("backgroundextras") == 0)
         {
            this->sBackgroundExtras.clear();

            for ( int x = 1; x < (int)vvsInstruct[i].size(); ++x)
            {
               this->sBackgroundExtras.push_back(vvsInstruct[i][x]);
            }
         }
         else if ( vvsInstruct[i][0].compare("cutscene") == 0)
         {
            this->sCutSceneName = vvsInstruct[i][1];
         }
         else if( vvsInstruct[i][0].compare("backgroundmusic") == 0)
         {
            this->sBackgroundMusic = vvsInstruct[i][1];
         }
         else if(vvsInstruct[i][0].compare("platform") == 0)
         {
            for(int a = 0; a < (int)pMultiBoxEffectList.size(); ++a)
            {
               //if(pMultiBoxEffectList[a].first.second == "platform" || pMultiBoxEffectList[a].first.first.first == '^' || (pMultiBoxEffectList[a].first.first.first >= 'A' && pMultiBoxEffectList[a].first.first.first <= 'Z') || (pMultiBoxEffectList[a].first.first.first == '_' || pMultiBoxEffectList[a].first.first.second == '_'))
               //{
               //   pMultiBoxEffectList[a].second.second->getUnit("platform")->changeTexture(ConvertStringToInt( vvsInstruct[i][1])-1);
               //}
				Unit* pTemp = pMultiBoxEffectList[a].second.second->getUnit("platform");
				if(pTemp != NULL)
				{
					pTemp->changeTexture(ConvertStringToInt(vvsInstruct[i][1])-1);
				}
            }
         }
      }

      for(int i = 0; i < (int)vvsInstruct.size(); ++i)
      {
         for(int j = 0; j < (int)pStructuresList.size(); ++j)
         {
            if(vvsInstruct[i][0].at(0) == pStructuresList[j].first.first && vvsInstruct[i][0].at(1) == pStructuresList[j].first.second)
            {
               string tempString = vvsInstruct[i][0].substr(0,1) + "#";
               string sName = findVector(vvsInstruct[i][0].substr(0,1)+"#")[0];
               Unit* uAffectedUnit = NULL;
               int iLast = vvsInstruct[i].size() - 1;
               for(int a = 1; a < (int)vvsInstruct[i].size(); ++a)
               {
                  if(sName == "buzzsaw")
                  {
                     Buzzsaw* tempSaw = dynamic_cast<Buzzsaw*>(pStructuresList[j].second);
                     if(vvsInstruct[i][a] == "capis")
                     {
                        tempSaw->setCap(ConvertStringToInt(vvsInstruct[i][a+1]));
                     }
                     else if(vvsInstruct[i][a] == "isoff")
                     {
                        tempSaw->toggleOn();
                     }
                     else if(vvsInstruct[i][a] == "islarge")
                     {
                        //pStructuresList[j].second->changeTexture(0);
                        for(int m = 0; m < (int)pStructuresList[j].second->uAttatchedToList.size(); m++)
                        {
                           pStructuresList[j].second->uAttatchedToList[m]->bDrawn = false;
                        }
                     }
                     else if(vvsInstruct[i][a] == "drainsto")
                     {
                        pStructuresList[j].second->uAffectList.push_back(getFirstInStruct(vvsInstruct[i][a + 1].at(0), vvsInstruct[i][a + 1].at(1)));
                     }
                  }
                  else if(sName == "mechwallleft" || sName == "mechwallright" || sName == "mechwall")
                  {
                     MechanicalWall *tempWall = dynamic_cast<MechanicalWall*>(pStructuresList[j].second);
                     if(vvsInstruct[i][a] == "movesby")
                     {
                        tempWall->setMoveDist(ConvertStringToInt(vvsInstruct[i][a+1]));
                        tempWall->setAll();
                     }
                     else if(vvsInstruct[i][a] == "isdown")
                     {
                        tempWall->setDown(true);
                     }
                  }
                  else if(sName == "block")
                  {
                     Block *tempBlock = dynamic_cast<Block*>(pStructuresList[j].second);
                     if(vvsInstruct[i][a] == "movesby")
                     {
                        int moves = ConvertStringToInt(vvsInstruct[i][a+1]);
                        tempBlock->setMoveDist(ConvertStringToInt(vvsInstruct[i][a+1]));
                        //Box* tempBox = tempBlock->bBox;
                        //for( int w = 0; w < moves - 1; ++w)
                        {
                           //	tempBox = tempBox->bConnectList[5];
                        }
                        //this->umManager->uUnitList.push_back(this->getUnit("platform", tempBox->i2Position));
                        //tempBox->addUnit(this->umManager->uUnitList[(int)this->umManager->uUnitList.size()-1]);
                        //tempBox->bIsWalkable = false;
                     }
                  }
                  else if(sName == "scythe")
                  {
                     Scythe* tempScythe = dynamic_cast<Scythe*>(pStructuresList[j].second);
                     if(vvsInstruct[i][a] == "runsfrom")
                     {
                        tempScythe->uAttatchedToList.push_back(getFirstInStruct(vvsInstruct[i][a + 1].at(0), vvsInstruct[i][a + 1].at(1)));
                     }
                     else if(vvsInstruct[i][a] == "runsto")
                     {

                        tempScythe->uAttatchedToList.push_back(getFirstInStruct(vvsInstruct[i][a + 1].at(0), vvsInstruct[i][a + 1].at(1)));

                        // can remove this if, meant to check if .label was made correctly
                        if ( tempScythe->uAttatchedToList.size() != 2)
                           IwAssertMsg(MYAPP, false, ("scythe left must be before scythe right"));

                        // gets scythe's box and then insert it into , this may not be the best way to insert scythe into box
                        tempScythe->calculateMaxRotation(); // do some calcs to find how far sythe rotates, needs its attached list to be set before doing so done here insteads of constructor
                        Box * b = this->gGrid->getBox(tempScythe->i2Position.x, tempScythe->i2Position.y);
                        b->addUnit(tempScythe);
                     }
                  }
                  else if(sName == "rope")
                  {
                     Rope* tempRope = (Rope*)pStructuresList[j].second;
                     if(vvsInstruct[i][a] == "connectedto")
                     {
                        uAffectedUnit = getFirstInStruct(vvsInstruct[i][a + 1].at(0), vvsInstruct[i][a + 1].at(1));
                        if(uAffectedUnit->sName != "bucket")
                        {
                           tempRope->uAffectList.push_back(uAffectedUnit);
                        }
                        else
                        {
                           Bucket* tempBucket = (Bucket*)uAffectedUnit;
                           tempBucket->uAffectList.push_back(tempRope);
                        }
                        if(uAffectedUnit->sName != "rope")
                        {
                           tempRope->setCuttable(false);
                        }
                     }
                     if(vvsInstruct[i][a] == "rises")
                     {
                        tempRope->setRiseable(true);
                     }
                     if(vvsInstruct[i][a] == "falls")
                     {
                        tempRope->setFallable(true);
                     }
                     if(vvsInstruct[i][a] == "movesby")
                     {
                        tempRope->setMoveDist(ConvertStringToInt(vvsInstruct[i][a+1]));
                        tempRope->setAll();
                     }
                  }
                  else if(sName == "lever")
                  {
                     if(vvsInstruct[i][a] == "switches" || vvsInstruct[i][a] == "powers")
                     {
                        Lever* tempLever = (Lever*)pStructuresList[j].second;
                        Unit* uTarget = getFirstInStruct(vvsInstruct[i][a + 1].at(0),vvsInstruct[i][a + 1].at(1));
                        if(uTarget->sName.find("wall") != string::npos)
                        {
                           dynamic_cast<MechanicalWall*>(uTarget)->setColor(tempLever->getColor());
                        }
                        else if (uTarget->sName.compare("buzzsaw") == 0)
                        {
                           dynamic_cast<Buzzsaw*>(uTarget)->setColor(tempLever->getColor());
                        }
                        else if (uTarget->sName.compare("anvil") == 0)
                        {
                           dynamic_cast<Anvil*>(uTarget)->setColor(tempLever->getColor());
                        }
                        else if (uTarget->sName.compare("block") == 0)
                        {
                           dynamic_cast<Block*>(uTarget)->setColor(tempLever->getColor());
                        }
                        tempLever->uAffectList.push_back(uTarget);
                     }

                  }
                  else if(sName == "pressureplate" || sName == "trigger")
                  {
                     PressurePlate* tempPlate = (PressurePlate*)pStructuresList[j].second;
                     //if(vvsInstruct[i][a] == "drops")
                     //{
                     //   tempPlate->uAffectList.push_back(uAffectedUnit);
                     //}
                     if(vvsInstruct[i][a] == "switches" || vvsInstruct[i][a] == "powers" || vvsInstruct[i][a] == "drops" || vvsInstruct[i][a] == "triggers")
                     {
                        Unit* uTarget = getFirstInStruct(vvsInstruct[i][a + 1].at(0),vvsInstruct[i][a + 1].at(1));
                        if(uTarget->sName.find("wall") != string::npos)
                        {
                           dynamic_cast<MechanicalWall*>(uTarget)->setColor(tempPlate->getColor());
                        }
                        else if (uTarget->sName.compare("buzzsaw") == 0)
                        {
                           dynamic_cast<Buzzsaw*>(uTarget)->setColor(tempPlate->getColor());
                        }
                        else if (uTarget->sName.compare("anvil") == 0)
                        {
                           dynamic_cast<Anvil*>(uTarget)->setColor(tempPlate->getColor());
                        }
                        else if (uTarget->sName.compare("block") == 0)
                        {
                           dynamic_cast<Block*>(uTarget)->setColor(tempPlate->getColor());
                        }
                        tempPlate->uAffectList.push_back(uTarget);
                     }
                  }
                  else if(sName == "bucket")
                  {
                     Bucket* tempBucket = (Bucket*)pStructuresList[j].second;
                     if(vvsInstruct[i][a] == "capis")
                     {
                        tempBucket->setCap(ConvertStringToInt(vvsInstruct[i][a+1]));
                     }
                     if(vvsInstruct[i][a] == "movesby")
                     {
                        tempBucket->setMoveDist(ConvertStringToInt(vvsInstruct[i][a + 1]));
                     }
                  }
                  if(sName == "mouse")
                  {
                     Mouse* tempMouse = dynamic_cast<Mouse*>(pStructuresList[j].second);
                     if(vvsInstruct[i][a] == "runsto")
                     {
                        tempMouse->setTarget(getFirstInStruct(vvsInstruct[i][a + 1].at(0), vvsInstruct[i][a + 1].at(1)));
                        //tempMouse->uTarget = getFirstInStruct(vvsInstruct[i][a + 1].at(0), vvsInstruct[i][a + 1].at(1));
                     }
                  }
                  if(sName == "message")
                  {
                     Message* tempMessage = ((Message*)pStructuresList[j].second);
                     if(vvsInstruct[i][a] == "isoff")
                     {
                        tempMessage->bDrawn = true;
                     }

                     if(vvsInstruct[i][a] == "uses")
                     {
                        tempMessage->changeTexture(ConvertStringToInt(vvsInstruct[i][a + 1]));
                        tempMessage->setUseTexture(true);
                     }
                     if(vvsInstruct[i][a] == "usespng")
                     {
                        tempMessage->setTexture(vvsInstruct[i][a+1]);
                     }
                     if(vvsInstruct[i][a] == "usesfont")
                     {
                        tempMessage->setFont(vvsInstruct[i][a+1]);
                        tempMessage->setUseTexture(false);
                     }
                     if(vvsInstruct[i][a] == "says")
                     {
                        tempMessage->setString(vvsInstruct[i][a+1]);
                        tempMessage->setUseTexture(false);
                     }
                     if(vvsInstruct[i][a] == "moveto")
                     {
                        if(vvsInstruct[i].size() == 3)
                           tempMessage->setPosition(getFirstInStruct(vvsInstruct[i][a+1][0], vvsInstruct[i][a+1][1])->getPosition());
                        else if(vvsInstruct[i].size() == 4)
                           tempMessage->setPosition(CIwSVec2( ConvertStringToInt(vvsInstruct[i][a+1]),ConvertStringToInt(vvsInstruct[i][a+2])));
                     }
                  }
                  if(sName == "anvil")
                  {
                     Anvil* tempAnvil = dynamic_cast<Anvil*>(pStructuresList[j].second);
                     if(vvsInstruct[i][a] == "movesby")
                     {
                        tempAnvil->setMoveDist(ConvertStringToInt(vvsInstruct[i][a+1]));
                     }
                  }
               }
            }
         }
      }
   }
   fFile.close();
}

void Map::readFiles()
{
   IW_CALLSTACK("Map::readFiles");

   readLabels();
   readMap();
   readInteractions();
}

void Map::draw()
{
   IW_CALLSTACK("Map::draw");

   if(GameState::getDebugging())
   {
      this->gGrid->drawGrid();
   }
   this->umManager->draw();
}

Unit* Map::getFirstInStruct(char a, char b)
{
   IW_CALLSTACK("Map::getFirstInStruct");

   for(int i = 0; i < (int)pStructuresList.size(); ++i)
   {
      if(pStructuresList[i].first.first == a && pStructuresList[i].first.second == b)
      {
         return pStructuresList[i].second;
      }
   }
   IwAssertMsg(MYAPP, false, ("%c%c was not found", a, b));
   return NULL;
}

CIwArray<string> Map::findVector(string label)
{
   IW_CALLSTACK("Map::findVector");

   for(int i = 0; i < (int)pLabelList.size(); ++i)
   {
      if(pLabelList[i].first == label)
         return pLabelList[i].second;
   }
   IwAssertMsg(MYAPP, false, ("Sorry you failed, check label list and make your map fit the labels"));
   return CIwArray<string>();
}

Unit* Map::getUnit(string ObjectName, CIwSVec2 i2Position)
{
   IW_CALLSTACK("Map::getUnit");

   if(ObjectName.compare("platform") == 0)
   {
      this->gGrid->getBox(i2Position.x / Screen::getBOXSIZE().x, i2Position.y / Screen::getBOXSIZE().y + 2, true)->bIsWalkable = true;
      return new Platform(i2Position);
   }

   if(ObjectName.compare("message") == 0)
   {
      return new Message(i2Position);
   }

   if(ObjectName.compare("wall") == 0)
   {
      return new MechanicalWall(i2Position, "wall", true, 0);
   }

   if(ObjectName.compare("rightwall") == 0)
   {
      return new MechanicalWall(i2Position, "rightwall", true, 2);
   }

   if(ObjectName.compare("leftwall") == 0)
   {
      return new MechanicalWall(i2Position, "leftwall", true, 1);
   }

   if(ObjectName.compare("bothwall") == 0)
   {
      return new MechanicalWall(i2Position, "bothwall", true, 3);
   }

   if(ObjectName.compare("startbox") == 0)
   {
      this->bBegin = this->gGrid->getBox(i2Position.x, i2Position.y);
      // not sure if we want to do this here
      // make start box unwalkable
      Box* temp = this->gGrid->getBox(i2Position.x, i2Position.y);
      temp->bIsWalkable = false;
      temp->bConnectList[1]->bIsWalkable = true;
      this->gGrid->bStart = temp;
      this->gGrid->bStart->bIsFilled = true;
      return new StartBox(i2Position);
   }

   if(ObjectName.compare("catevent") == 0)
   {
      CatEvent* ce = new CatEvent(i2Position);
      if ( this->cKitty == NULL )
         IwAssertMsg(MYAPP, true, ("Kitty is null when making a cat event"));
      this->cKitty->ceEvent = ce;
      return ce; 
   }

   if(ObjectName.compare("cat") == 0 )
   {
      // this may not be where we want to do this but the cats position should be above the startbox so subtract boxsize
      CIwSVec2 newPos = CIwSVec2(i2Position.x, i2Position.y - Screen::getBOXSIZE().y);
      // this->cKitty = new Cat(newPos);
      this->cKitty = new Cat(i2Position); // start in start box
      this->cKitty->setFinish(CIwSVec2(i2Position.x + Screen::getBOXSIZE().x, i2Position.y));
      gGrid->cCat = this->cKitty;
      //gGrid->cCat->bBox = gGrid->getBox(this->pcKitty->i2Position.x, this->pcKitty->i2Position.y); shouldn't be needed
      return this->cKitty;
   }

   if(ObjectName.compare("supershiny") == 0 )
   {
      return new SuperShinyJumpOutofBoxShinyUnit(CIwSVec2(i2Position.x + Screen::getBOXSIZE().x, i2Position.y - Screen::getBOXSIZE().y));
   }

   if(ObjectName.compare("endbox") == 0)
   {
      this->bEnd = this->gGrid->getBox(i2Position.x, i2Position.y);
      this->gGrid->bFinish = this->bEnd;
      return new EndBox(i2Position);
   }

   if ( ObjectName.compare("mouse") == 0 )
   {
      Mouse* tempMouse = new Mouse(i2Position);
      ulMouseList.push_back(tempMouse);
      return tempMouse;
   }

   if ( ObjectName.compare("mousehole") == 0 )
      return new MouseHole(i2Position);

   if ( ObjectName.compare("scratchingpost") == 0 )
      return new ScratchingPost(i2Position);

   if ( ObjectName.compare("block") == 0 )
      return new Block(i2Position);

   if ( ObjectName.compare("food") == 0 )
      return new Food(i2Position);

   /* if ( ObjectName.compare("catnip") == 0 )
   return new CatNip(i2Position);*/

   if ( ObjectName.compare("litterbox") == 0 )
      return new LitterBox(i2Position);

   if ( ObjectName.compare("buzzsaw") == 0 )
      return new Buzzsaw(i2Position);

   if (ObjectName.compare("mechwall") == 0 )
   {
      //this->gGrid.getBox(i2Position.x/32, i2Position.y/32-2);
      return new MechanicalWall(i2Position, "mechwall", false, 0);
   }

   if ( ObjectName.compare("mechwallleft") == 0 )
      return new MechanicalWall(i2Position,"mechwallleft", false, 1);

   if ( ObjectName.compare("mechwallright") == 0 )
      return new MechanicalWall(i2Position, "mechwallright", false, 2);

   if ( ObjectName.compare("beartrap") == 0 )
      return new BearTrap(i2Position);

   if(ObjectName.compare("spike") == 0)
   {
      this->gGrid->getBox(i2Position.x / Screen::getBOXSIZE().x, i2Position.y / Screen::getBOXSIZE().y + 2, true)->bIsWalkable = true;
      return new Spike(i2Position);
   }

   if(ObjectName.compare("scythe") == 0)
   {
      return new Scythe(i2Position);
   }

   if(ObjectName.compare("scytheleft") == 0)
   {
      return new ScytheLeft(i2Position);
   }

   if(ObjectName.compare("scytheright") == 0)
   {
      return new ScytheRight(i2Position);
   }

   if(ObjectName.compare("rope") == 0)
   {
      return new Rope(i2Position);
   }

   if(ObjectName.compare("lever") == 0)
   {
      Lever* tempLever = new Lever(i2Position);
      tempLever->setColor(iColorCode);
      ++this->iColorCode;
      return tempLever;
   }

   if(ObjectName.compare("pressureplate") == 0)
   {
      PressurePlate* tempPressure = new PressurePlate(i2Position, "pressureplate");
      tempPressure->setColor(this->iColorCode);
      ++this->iColorCode;
      return tempPressure;
   }

   if(ObjectName.compare("trigger") == 0)
   {
      PressurePlate* tempTrigger = new PressurePlate(i2Position, "trigger");
      tempTrigger->bDrawn = true;
      return tempTrigger;
   }

   if(ObjectName.compare("bucket") == 0)
   {
      return new Bucket(i2Position);
   }

   if(ObjectName.compare("anvil") == 0)
   {
      return new Anvil(i2Position);
   }
   IwAssertMsg(MYAPP, false, ("There was a problem loading a Unit named %s", ObjectName.c_str()));

   return NULL;
}

int Map::ConvertStringToInt(string s)
{
   IW_CALLSTACK("Map::ConvertStringToInt");
   int temp = 0;
   int tempsize = s.size();
   for(int w = 0; w < tempsize; ++w)
   {
      temp += (int)((s.at(w) - 48) * pow(10.0, tempsize - 1 - w));
   }
   cout<<endl<<temp<<endl;
   cout<<endl;
   return temp;
}

void Map::writeFile()
{
   IW_CALLSTACK("Map::writeFile");
   int size = vvsInstruct.size();
   if(size == 0)
      IwAssertMsg(MYAPP, false, ("There is no .label file"));


   PlayerProfile::setWin(this->getExpected());
   PlayerProfile::writeProfile();
   /*
   int iTotalDeathCount = 0;
   bool bKiller = false;
   fprintf(this->fAllOutFile,"\n");
   for(int i = 0; i < (int)pStructuresList.size(); ++i)
   {
   if(pStructuresList[i].first.second != 'S' && (pStructuresList[i].first.first == 's' || pStructuresList[i].first.first == 'S'))
   {
   bKiller = true;
   fprintf(this->fAllOutFile,"Buzzsaw %c%c killed the cat %d times\n",pStructuresList[i].first.first,pStructuresList[i].first.second, dynamic_cast<Buzzsaw*>(pStructuresList[i].second)->getDeathCount());
   }
   }
   for(int i = 0; i < (int)pMultiBoxEffectList.size(); ++i)
   {
   if(pMultiBoxEffectList[i].first.second == "beartrap")
   {
   string sDead = "";
   bKiller = true;
   if(dynamic_cast<BearTrap*>(pMultiBoxEffectList[i].second.second->getUnit("beartrap"))->getDeathCount() < 1)
   sDead = "not ";
   fprintf(this->fAllOutFile, "The Cat was %skilled by the Bear Trap at grid coordinates %i, %i\n",sDead.c_str(),pMultiBoxEffectList[i].second.first.first,pMultiBoxEffectList[i].second.first.second);
   }
   if(pMultiBoxEffectList[i].first.second == "spike")
   {
   string sDead = "";
   bKiller = true;
   if(dynamic_cast<Spike*>(pMultiBoxEffectList[i].second.second->getUnit("spike"))->getDeathCount() < 1)
   sDead = "not ";
   fprintf(this->fAllOutFile, "The Cat was %skilled by the Spikes at grid coordinates %i, %i\n",sDead.c_str(),pMultiBoxEffectList[i].second.first.first,pMultiBoxEffectList[i].second.first.second);
   }

   if(pMultiBoxEffectList[i].first.second == "block")
   {
   string sDead = "";
   bKiller = true;
   if(dynamic_cast<LethalUnit*>(this->getFirstInStruct(this->pMultiBoxEffectList[i].first.first.first, this->pMultiBoxEffectList[i].first.first.second))->getDeathCount() < 1)
   sDead = "not ";
   fprintf(this->fAllOutFile, "The Cat was %skilled by the Blocks at grid coordinates %i, %i\n",sDead.c_str(),pMultiBoxEffectList[i].second.first.first,pMultiBoxEffectList[i].second.first.second);
   }
   if(pMultiBoxEffectList[i].first.second == "anvil")
   {
   string sDead = "";
   bKiller = true;
   if(dynamic_cast<LethalUnit*>(this->getFirstInStruct(this->pMultiBoxEffectList[i].first.first.first, this->pMultiBoxEffectList[i].first.first.second))->getDeathCount() < 1)
   sDead = "not ";
   fprintf(this->fAllOutFile, "The Cat was %skilled by the Blocks at grid coordinates %i, %i\n",sDead.c_str(),pMultiBoxEffectList[i].second.first.first,pMultiBoxEffectList[i].second.first.second);
   }
   }
   if(bKiller == false)
   fprintf(this->fAllOutFile,"There was nothing to kill it\n");
   fprintf(this->fAllOutFile,"The expected number of deaths was %s\nThe player died a total of %i times in this level\nThe player took %i seconds to complete the level",vvsInstruct[(int)vvsInstruct.size()-1][1].c_str(),this->cKitty->iDeathCount,(int)tLevelTime);
   fprintf(this->fAllOutFile,"\n\n");
   string stemppath = sLevelName + ".label";

   FILE * fReWrite = fopen(stemppath.c_str(),"w");
   for(int i = 0; i < (int)vvsInstruct.size()-3; ++i)
   {
   for(int j = 0; j < (int)vvsInstruct[i].size();++j)
   {
   if(j != 0)
   fprintf(fReWrite,"_");
   fprintf(fReWrite,"%s",vvsInstruct[i][j].c_str());
   if(j == (int)vvsInstruct[i].size() - 1 && i != (int)vvsInstruct.size() - 1)
   fprintf(fReWrite,"\n");
   }
   }
   int i = (int)vvsInstruct.size() - 3;
   //fprintf(fReWrite,"%s_%s_%s\n",vvsInstruct[i][0].c_str(),vvsInstruct[i][1].c_str(),"5";
   fprintf(fReWrite,"%s_%s_%s\n",vvsInstruct[i][0].c_str(),vvsInstruct[i][1].c_str(),vvsInstruct[i][2].c_str());
   ++i;
   int itempdeath = ConvertStringToInt(vvsInstruct[i][2]);
   if(itempdeath > this->cKitty->iDeathCount)
   itempdeath = this->cKitty->iDeathCount;
   fprintf(fReWrite,"%s_%s_%i\n",vvsInstruct[i][0].c_str(),vvsInstruct[i][1].c_str(),itempdeath);
   ++i;
   uint64 iTempTime = ConvertStringToInt(vvsInstruct[i][2]);
   if(tLevelTime <= iTempTime)
   iTempTime = tLevelTime;
   fprintf(fReWrite,"%s_%s_%i",vvsInstruct[i][0].c_str(),vvsInstruct[i][1].c_str(),iTempTime);
   fclose(fReWrite);
   */
}

void Map::catIsDead()
{
   IW_CALLSTACK("Map::catIsDead");

   this->cAI->reset();
   this->csmStateManager->reset();
   this->cKitty->reset();
   this->laser->reset();
   this->gGrid->changeUnitBox(this->cKitty);
   this->gGrid->changeUnitBox(this->laser);
   CatState::setState(CatState::IDLING);
   PlayerProfile::addDeath(1);
}

int Map::getDeaths()
{
   IW_CALLSTACK("Map::getDeaths");

   return this->cKitty->iDeathCount;
}

int Map::getExpected()
{
   IW_CALLSTACK("Map::getExpected");

   return ConvertStringToInt(vvsInstruct[(int)vvsInstruct.size()-1][1]);
}

uint64 Map::getTime()
{
   IW_CALLSTACK("Map::getTime");

   return this->tLevelTime;
}

Map::~Map()
{

   IW_CALLSTACK("Map::~Map");

   delete cAI;
   delete csmStateManager;
   delete mAI;
   delete umManager;
}
