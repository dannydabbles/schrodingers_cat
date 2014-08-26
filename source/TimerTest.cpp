/*
 *  untitled.cpp
 *  SyzEG
 *
 *  Created by Hosh Tachmuradov on 3/13/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
//#pragma once
#include "TimerTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION( TimerTestCase );

//void ExampleTestCase::example()
//{
//	CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.0, 1.1, 0.05 );
//	CPPUNIT_ASSERT( 1 == 0 );
//	CPPUNIT_ASSERT( 1 == 1 );
//}
//

void TimerTestCase::setUp()
{
	this->testTimer = s3eTimerGetMs();
}

void TimerTestCase::testUpdateGameLoop()
{
	//testTimer->update();
	
	int expectedGameLoop = -1;
	
	//int gameLoop = testTimer->getGameLoops();
	
	CPPUNIT_ASSERT( testTimer >= expectedGameLoop );
}
/*
void TimerTestCase::testUpdateSec()
{	
	int expectedSec = 1;
	
	for (int i =0; i < 60; ++i) {
		testTimer->update();
	}
	
	int gameSec = testTimer->getSec();
	
	testTimer->reset();
	
	CPPUNIT_ASSERT( expectedSec == gameSec );
}

void TimerTestCase::testResetGameLoop()
{
	testTimer->update();
	
	testTimer->reset();
	
	int expectedGameLoop = 0;
	
	int gameLoop = testTimer->getGameLoops();
	
	testTimer->reset();
	
	CPPUNIT_ASSERT( expectedGameLoop == gameLoop );
}

void TimerTestCase::testResetSec()
{
	int expectedSec = 0;
	
	for (int i =0; i < 60; ++i) {
		testTimer->update();
	}
	
	testTimer->reset();
	
	int gameLoop = testTimer->getGameLoops();
	
	testTimer->reset();
	
	CPPUNIT_ASSERT( expectedSec == gameLoop );
}

*/