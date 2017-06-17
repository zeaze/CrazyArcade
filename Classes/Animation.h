#ifndef _ANIMATION_H_
#define _ANIMATION_H_
#include <cocos2d.h>
#include <vector>
#include <string>
using namespace cocos2d;
using namespace std;
USING_NS_CC;
class GameAction
{
public:
	static Action *CreationRoleRunAction(Vec2 direction,const char* name, int Num, float delay, unsigned int Loops);
	static Animate* createAnimate2();
};

#endif
