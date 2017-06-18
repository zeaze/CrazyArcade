#include <HelpScene.h>
#include <HelloWorldScene.h>
#include "ui\CocosGUI.h"
#include <iostream>
#include <fstream>
USING_NS_CC;
using namespace ui;

cocos2d::Scene * HelpScene::createScene()
{
	return HelpScene::create();
}
bool HelpScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("HelpScene_bg.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	bg->setScale(visibleSize.width / (bg->getContentSize()).width, visibleSize.height / (bg->getContentSize()).height);
	this->addChild(bg, -1);

	auto returnButton = Button::create("button.png");
	returnButton->setScale(1);
	returnButton->setTitleText("RETURN");
	returnButton->setTitleFontSize(16);
	returnButton->setTitleFontName("Marker Felt.ttf");
	returnButton->setPosition(Vec2(visibleSize.width*0.9, visibleSize.height*0.1));
	returnButton->addTouchEventListener(CC_CALLBACK_2(HelpScene::touchReturnEvent, this));
	this->addChild(returnButton, 1);

	return true;
}

void HelpScene::touchReturnEvent(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) 
	{
			Director::getInstance()->pushScene(HelloWorld::createScene());
			return;
	}

}

HelpScene::HelpScene()
{

}
HelpScene::~HelpScene()
{

}