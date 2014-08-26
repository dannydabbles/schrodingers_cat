#include "ClassTracker.h"

int ClassTracker::units = 0;
int ClassTracker::message = 0;
int ClassTracker::maps = 0;
int ClassTracker::catAI = 0;
int ClassTracker::grid = 0;
int ClassTracker::mouseAI = 0;
int ClassTracker::blood = 0;
CIwArray<string> ClassTracker::unitsArray = CIwArray<string>();

void ClassTracker::print()
{
   cout << "unit constructor Called: " << units << "versus: " <<  (int) unitsArray.size() << endl;
   for ( int i = 0; i < (int) unitsArray.size(); ++i)
   {
      cout << unitsArray[i] << endl; 
   }
   /*cout << "Messages: " << message << endl;
   cout << "maps: " << maps << endl;
   cout << "catAi: "<< catAI << endl;
   cout << "grid: " << grid << endl;
   cout << "mouseAI: "<< mouseAI << endl;
   cout << "blood: " << blood << endl;*/
}

void ClassTracker::addUnit(const Unit * unit)
{
   unitsArray.push_back(unit->sName);
}

void ClassTracker::removeUnit(const Unit * unit)
{
   unitsArray.find_and_remove_fast(unit->sName);
}
