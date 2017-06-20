#ifndef __Make_Map_H__
#define __Make_Map_H__
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include <string>
#include <iostream>
USING_NS_CC;
using namespace ui;
using namespace std;

class MakeMap : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	static void initRole(string _rolePictureName);
	virtual bool init();
	void makeSpritePermanent(int i, int j);
	void makeNone(int i, int j);
	void touchMapEvent(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void touchNoneSelectEvent(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void touchBarrierSelectEvent(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void touchPermanentSelectEvent(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void touchStartGameEvent(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type);
	CREATE_FUNC(MakeMap);
	MakeMap();
	~MakeMap();
private:
	int map[17][15];
	int mark;
	static string rolePictureName;
};
#endif