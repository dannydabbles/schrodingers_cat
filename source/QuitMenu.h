//
//
//
//   Project : Schrödinger's cat
//   File Name : QuitMenu.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_QUITMENU_H)
#define _QUITMENU_H

#include "UserInterface.h"

class QuitMenu : public UserInterface
{
public:
    QuitMenu(CIwSVec2 i2Position);
private:
    void quit();
};

#endif  //_QUITMENU_H
