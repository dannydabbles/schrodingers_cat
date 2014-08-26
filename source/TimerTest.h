/*
 *  TimerTest.h
 *  SyzEG
 *
 *  Created by Hosh Tachmuradov on 3/13/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#if !defined(_TIMERTEST_H)
#define _TIMERTEST_H
#include <extensions/HelperMacros.h>
#include <s3eTimer.h>

#include <iostream>
#include <string>
#include <utility>
#include <ctime>
#include <cmath>
#include <stdlib.h>
#include "s3e.h"
#include "Iw2D.h"

/* 
 * A test case that is designed to produce
 * example errors and failures
 *
 */

class TimerTestCase : public CPPUNIT_NS::TestFixture
{
public:
	CPPUNIT_TEST_SUITE( TimerTestCase );

	CPPUNIT_TEST( testUpdateGameLoop );
	
	CPPUNIT_TEST_SUITE_END();
	

	uint64 testTimer;
public:
	void setUp();
	
	void testUpdateGameLoop();
	void testUpdateSec();
	void testResetGameLoop();
	void testResetSec();
};

#endif

