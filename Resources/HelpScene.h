#ifndef _HELPSCENE_H_
#define _HELPSCENE_H_
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include <string>
#include <iostream>
USING_NS_CC;
using namespace ui;
using namespace std;

class HelpScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void touchReturnEvent(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	CREATE_FUNC(HelpScene);
	HelpScene();
	~HelpScene();
};


#endif // !_HELPSCENE_H_

