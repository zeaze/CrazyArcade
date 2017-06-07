#ifndef _ANIMATION_H_
#define _ANIMATION_H_
#include <cocos2d.h>
#include <vector>
using namespace cocos2d;
using namespace std;
class GameAction
{
public:
	static CCAnimation * CreationRoleRunAction(Vec2 direction,const char * name, int iNum, float delay, unsigned int iLoops);

};

#endif
