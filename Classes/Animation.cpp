#include "Animation.h"


Action *GameAction::CreationRoleRunAction(Vec2 direction, const char* name, int Num, float delay, unsigned int Loops) {
	CCSpriteFrameCache * cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	Vector<SpriteFrame*> framesArray;
	CCSpriteFrame * frame = NULL;
	int k = 0;
	if (direction == Vec2(0, 1))  k = 0;
	if (direction == Vec2(0, -1)) k = 6;
	if (direction == Vec2(-1, 0)) k = 12;
	if (direction == Vec2(1, 0))  k = 18;
	for (int i = 1; i<Num; i++) {
		frame = cache->spriteFrameByName(CCString::createWithFormat("%s%d.png", name, k + i)->getCString());
		if (frame == NULL) {
			break;
		}
		framesArray.pushBack(frame);
	}

	CCAnimation * animation = CCAnimation::createWithSpriteFrames(framesArray);
	animation->setLoops(Loops);
	animation->setRestoreOriginalFrame(true);
	animation->setDelayPerUnit(delay);

	return Animate::create(animation);
}

Animate* GameAction::createAnimate2()
{
	SpriteFrameCache* frameCache2 = SpriteFrameCache::getInstance();
	frameCache2->addSpriteFramesWithFile("popo.plist", "popo.png");
	int iFrameNum = 7;
	SpriteFrame* frame2 = NULL;
	Vector<SpriteFrame*>frameVec2;
	for (int i = 0; i <iFrameNum; i++) {
		frame2 = frameCache2->getSpriteFrameByName(StringUtils::format("popo%d.png", i));
		frameVec2.pushBack(frame2);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameVec2);
	animation->setLoops(1);
	animation->setDelayPerUnit(0.1f);
	Animate* action = Animate::create(animation);

	return action;
}
