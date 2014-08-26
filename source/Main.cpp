//
//
//
//   Project : Schrödinger's cat
//   File Name : Main.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


/*
#include "TimerTest.h"
#include <CompilerOutputter.h>
#include <extensions/TestFactoryRegistry.h>
#include <ui/text/TestRunner.h>
#include <TestResult.h>
//#include <JUnitTestResultCollector.h>
//#include <JUnitXmlOutputter.h>
#include <stdexcept>
*/



#include <iostream>
#include <string>
#include <utility>
#include <ctime>
#include <cmath>
#include <stdlib.h>
#include "s3e.h"
#include "Iw2D.h"
#include "Game.h"
#include "GameState.h"
#include "PlayerProfile.h"
#include "Memory.h"
//#include "TimerTest.h"

//--------------------------------------------------------------------------
// Main global function
//--------------------------------------------------------------------------

//using namespace CppUnit;

S3E_MAIN_DECL void IwMain()
{
   IW_CALLSTACK("IwMain");

#ifdef EXAMPLE_DEBUG_ONLY
   // Test for Debug only examples
#endif
   /*
   TestResult controller;
   JUnitTestResultCollector result;
   controller.addListener(&result);

   CppUnit::TextUi::TestRunner runner;
   runner.addTest( TestFactoryRegistry::getRegistry().makeTest() );
   runner.run(controller);

   // important stuff happens next
   ofstream xmlFileOut("cpptestresults.xml");

   xmlFileOut.close();

   TimerTestCase t= TimerTestCase();
   t.setUp();
   */
    cout << " befiore anything" << endl;
    s3eDeviceYield(0);
   Iw2DInit();
    cout << "first yeild" << endl;
    s3eDeviceYield(0);
   IwResManagerInit();
    s3eDeviceYield(0);
   SoundManager::Init();
    s3eDeviceYield(0);
   FontManager::Init();
    s3eDeviceYield(0);
   ImageManager::Init();
    s3eDeviceYield(0);

   PlayerProfile::setHash();

   /*IwMemBucketCreate(MAPMANAGER1, "BOX", 0xFFF * 0x800); 
   IwMemBucketCreate(MAP, "BOX'S MAP", 0xFFF * 0x008);
   IwMemBucketCreate(BOX, "MAP INSERTION", 0xFFF);
   IwMemBucketCreate(GRID, "PARTICLE", 0x8A8 * 0x080);
   IwMemBucketCreate(GRID1, "Grid1", 0x888 * 0x800);
   IwMemBucketCreate(UNIT, "Unit", 0x800 * 0x800);*/

    cout << "anything" << endl;

   Game Kitty = Game();
   Kitty.Init();
   uint64 oldTime = 0;
   uint64 newTime = 0;
   uint64 time = 0;
   bool flagTime = false;

   cout << "fuck this shit" << endl;

   while(true)
   {
      s3eDeviceYield(0);
      s3eKeyboardUpdate();
      oldTime = newTime;
      newTime = s3eTimerGetMs();
      time = (newTime - oldTime) + 1;
      SoundManager::update(time);
      Kitty.Update(time);

      if(s3eDeviceCheckQuitRequest())
      {
         break;
      }
      //Clear the screen
      Iw2DSurfaceClear( 0xffffffff );

      Kitty.Draw();

      //Present the rendered surface to the screen
      Iw2DSurfaceShow();
      //t.testUpdateGameLoop();
      //JUnitXmlOutputter xmlOut(&result, xmlFileOut);
      //xmlOut.write();
   }
   Kitty.ShutDown();

   SoundManager::ShutDown();
   ImageManager::ShutDown();
   FontManager::ShutDown();
   IwResManagerTerminate();
   Iw2DTerminate();
}
