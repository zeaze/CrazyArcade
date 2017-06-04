#ifndef __Page_Select_Scene_H__
#define __Page_Select_Scene_H__
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include <string>
#include <iostream>
USING_NS_CC;
using namespace ui;
using namespace std;

class PageSelectScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void touchRole1Event(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void touchRole2Event(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void touchMap1Event(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void touchMap2Event(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void touchStartGameEvent(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	CREATE_FUNC(PageSelectScene);
	PageSelectScene();
	~PageSelectScene();
};
#endif