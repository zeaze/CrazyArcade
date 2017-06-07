#include "Animation.h"


CCAnimation * GameAction::CreationRoleRunAction(Vec2 direction,const char *name, int Num, float delay, unsigned int Loops) {
	CCSpriteFrameCache * cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	Vector<SpriteFrame*> framesArray;
	CCSpriteFrame * frame = NULL;
	int k = 0;
	if (direction == Vec2(0, 1))  k = 0;
	if (direction == Vec2(0, -1)) k = 6;
	if (direction == Vec2(-1, 0)) k = 12;
	if (direction == Vec2(1, 0))  k = 18;
	for (int i = 1; i<Num; i++) {
		frame = cache->spriteFrameByName(CCString::createWithFormat("%s%d.png", name, k+i)->getCString());
		if (frame == NULL) 
		{
			break;
		}
		framesArray.pushBack(frame);
	}

	CCAnimation * animation = CCAnimation::createWithSpriteFrames(framesArray);
	animation->setLoops(Loops);
	animation->setRestoreOriginalFrame(true); 
	animation->setDelayPerUnit(delay);

	return animation;
}
