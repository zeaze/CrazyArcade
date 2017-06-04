#include "PageSelectScene.h"
#include "ui\CocosGUI.h"
USING_NS_CC;
using namespace ui;

cocos2d::Scene * PageSelectScene::createScene()
{
	return PageSelectScene::create();
}

bool PageSelectScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("PageSelectScene_bg.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	bg->setScale(visibleSize.width / (bg->getContentSize()).width, visibleSize.height / (bg->getContentSize()).height);
	this->addChild(bg, -1);

	auto label1 = Label::createWithSystemFont("Role Select", "Arial", 36);
	label1->setPosition(Vec2(visibleSize.width * 0.1, visibleSize.height * 0.77));
	this->addChild(label1, 1);

	auto role1Picture = Sprite::create("Role1.png");
	role1Picture->setPosition(Vec2(visibleSize.width * 0.3, visibleSize.height * 0.8));
	role1Picture->setTag(11);
	role1Picture->setScale(2);
	this->addChild(role1Picture, 1);
	auto role1 = Button::create("button.png");
	role1->setScale(1);
	role1->setTitleText("OK");
	role1->setTitleFontSize(16);
	role1->setTitleFontName("Marker Felt.ttf");
	role1->setPosition(Vec2(visibleSize.width*0.3, visibleSize.height*0.68));
	role1->addTouchEventListener(CC_CALLBACK_2(PageSelectScene::touchRole1Event, this));
	role1->setTag(12);
	this->addChild(role1, 1);

	auto role2Picture = Sprite::create("Role2.png");
	role2Picture->setPosition(Vec2(visibleSize.width * 0.45, visibleSize.height * 0.8));
	role2Picture->setScale(2);
	role2Picture->setTag(13);
	this->addChild(role2Picture, 0.8);
	auto role2 = Button::create("button.png");
	role2->setScale(1);
	role2->setTitleText("OK");
	role2->setTitleFontSize(16);
	role2->setTitleFontName("Marker Felt.ttf");
	role2->setPosition(Vec2(visibleSize.width*0.45, visibleSize.height*0.68));
	role2->addTouchEventListener(CC_CALLBACK_2(PageSelectScene::touchRole2Event, this));
	role2->setTag(14);
	this->addChild(role2, 1);

	auto label2 = Label::createWithSystemFont("Map Select", "Arial", 36);
	label2->setPosition(Vec2(visibleSize.width * 0.1, visibleSize.height * 0.48));
	label2->setVisible(false);
	label2->setTag(21);
	this->addChild(label2, 1);
	
	auto map1Picture = Sprite::create("map1.png");
	map1Picture->setPosition(Vec2(visibleSize.width * 0.3, visibleSize.height * 0.5));
	map1Picture->setScale(0.23);
	map1Picture->setVisible(false);
	map1Picture->setTag(22);
	this->addChild(map1Picture, 1);
	auto map1 = Button::create("button.png");
	map1->setScale(1);
	map1->setTitleText("OK");
	map1->setTitleFontSize(16);
	map1->setTitleFontName("Marker Felt.ttf");
	map1->setPosition(Vec2(visibleSize.width*0.3, visibleSize.height*0.38));
	map1->addTouchEventListener(CC_CALLBACK_2(PageSelectScene::touchMap1Event, this));
	map1->setVisible(false);
	map1->setTag(23);
	this->addChild(map1, 1);

	auto map2Picture = Sprite::create("map2.png");
	map2Picture->setPosition(Vec2(visibleSize.width * 0.45, visibleSize.height * 0.5));
	map2Picture->setScale(0.23);
	map2Picture->setVisible(false);
	map2Picture->setTag(24);
	this->addChild(map2Picture, 1);
	auto map2 = Button::create("button.png");
	map2->setScale(1);
	map2->setTitleText("OK");
	map2->setTitleFontSize(16);
	map2->setTitleFontName("Marker Felt.ttf");
	map2->setPosition(Vec2(visibleSize.width*0.45, visibleSize.height*0.38));
	map2->addTouchEventListener(CC_CALLBACK_2(PageSelectScene::touchMap2Event, this));
	map2->setVisible(false);
	map2->setTag(25);
	this->addChild(map2, 1);

	auto startGame = Button::create("button.png");
	startGame->setScale(2);
	startGame->setTitleText("START");
	startGame->setTitleFontSize(16);
	startGame->setTitleFontName("Marker Felt.ttf");
	startGame->setPosition(Vec2(visibleSize.width*0.78, visibleSize.height*0.5));
	startGame->addTouchEventListener(CC_CALLBACK_2(PageSelectScene::touchStartGameEvent, this));
	startGame->setTag(31);
	startGame->setVisible(false);
	this->addChild(startGame, 1);

	return true;
}

void PageSelectScene::touchRole1Event(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
{
	this->getChildByTag(21)->setVisible(true);
	this->getChildByTag(22)->setVisible(true);
	this->getChildByTag(23)->setVisible(true);
	this->getChildByTag(24)->setVisible(true);
	this->getChildByTag(25)->setVisible(true);
	this->getChildByTag(13)->setVisible(false);
	this->getChildByTag(14)->setVisible(false);

}

void PageSelectScene::touchRole2Event(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
{
	this->getChildByTag(21)->setVisible(true);
	this->getChildByTag(22)->setVisible(true);
	this->getChildByTag(23)->setVisible(true);
	this->getChildByTag(24)->setVisible(true);
	this->getChildByTag(25)->setVisible(true);
	this->getChildByTag(11)->setVisible(false);
	this->getChildByTag(12)->setVisible(false);

}

void PageSelectScene::touchMap1Event(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
{
	this->getChildByTag(24)->setVisible(false);
	this->getChildByTag(25)->setVisible(false);
	this->getChildByTag(31)->setVisible(true);

}

void PageSelectScene::touchMap2Event(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
{
	this->getChildByTag(22)->setVisible(false);
	this->getChildByTag(23)->setVisible(false);
	this->getChildByTag(31)->setVisible(true);

}

void PageSelectScene::touchStartGameEvent(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
{
	CCLOG("tan270");
}

PageSelectScene::PageSelectScene()
{
}

PageSelectScene::~PageSelectScene()
{
}
