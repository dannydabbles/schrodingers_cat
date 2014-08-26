//
//
//
//   Project : Schrödinger's cat
//   File Name : QuitMenu.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "QuitMenu.h"

QuitMenu::QuitMenu(CIwSVec2 i2Position): UserInterface() 
{
   IW_CALLSTACK("QuitMenu::QuitMenu");

   this->i2Position = i2Position;

   ClassTracker::addUnit(this);
}

void QuitMenu::quit() 
{
   IW_CALLSTACK("QuitMenu::Quit");

}
