#include "MakeMap.h"
#include "MapScene.h"
#include <iostream>
#include <fstream>
#include "Constant.h"
USING_NS_CC;

string MakeMap::rolePictureName;
cocos2d::Scene * MakeMap::createScene()
{
	return MakeMap::create();
}

void MakeMap::initRole(string _rolePictureName)
{
	rolePictureName = _rolePictureName;
}

bool MakeMap::init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto bg = Sprite::create("PageSelectScene_bg.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	bg->setScale(visibleSize.width / (bg->getContentSize()).width, visibleSize.height / (bg->getContentSize()).height);
	this->addChild(bg, -1);

	mark = 0;
	for (int i = 1; i < 16; i++)
		for (int j = 1; j < 14; j++)
			if (!(i == 4 & j == 4)) {
				map[i][j] = 0;
				makeNone(i, j);
			}
	map[4][4] = 0;
	for (int i = 0; i < 17; i++) {
		map[i][0] = 2;
		map[i][14] = 2;
		makeSpritePermanent(i, 0);
		makeSpritePermanent(i, 14);
	}
	for (int i = 0; i < 15; i++) {
		map[0][i] = 2;
		map[16][i] = 2;
		makeSpritePermanent(0, i);
		makeSpritePermanent(16, i);
	}
	auto role = Sprite::create(rolePictureName);
	role->setAnchorPoint(Vec2(0, 0));
	role->setPosition(Vec2(coordinateX + unitSize * 4, coordinateY + unitSize * 4));
	role->setScale(unitSize / (role->getContentSize()).width, unitSize / (role->getContentSize()).height);
	role->setTag(roleTag);
	this->addChild(role, 100 - 4 - 4);

	auto NoneSelect = Button::create("None.png");
	NoneSelect->setAnchorPoint(Vec2(0, 0));
	NoneSelect->setScale(unitSize / (NoneSelect->getContentSize()).width, unitSize / (NoneSelect->getContentSize()).width);
	NoneSelect->setPosition(Vec2(visibleSize.width * 0.8, visibleSize.height * 0.8));
	NoneSelect->setTag(1);
	NoneSelect->addTouchEventListener(CC_CALLBACK_2(MakeMap::touchNoneSelectEvent, this));
	this->addChild(NoneSelect);

	auto BarrierSelect = Button::create("Barrier.png");
	BarrierSelect->setAnchorPoint(Vec2(0, 0));
	BarrierSelect->setScale(unitSize / (BarrierSelect->getContentSize()).width, unitSize / (BarrierSelect->getContentSize()).width);
	BarrierSelect->setPosition(Vec2(visibleSize.width * 0.8, visibleSize.height * 0.7));
	BarrierSelect->setTag(2);
	BarrierSelect->addTouchEventListener(CC_CALLBACK_2(MakeMap::touchBarrierSelectEvent, this));
	this->addChild(BarrierSelect);

	auto PermanentSelect = Button::create("Permanent.png");
	PermanentSelect->setAnchorPoint(Vec2(0, 0));
	PermanentSelect->setScale(unitSize / (PermanentSelect->getContentSize()).width, unitSize / (PermanentSelect->getContentSize()).height);
	PermanentSelect->setPosition(Vec2(visibleSize.width * 0.8, visibleSize.height * 0.6));
	PermanentSelect->setTag(3);
	PermanentSelect->addTouchEventListener(CC_CALLBACK_2(MakeMap::touchPermanentSelectEvent, this));
	this->addChild(PermanentSelect);

	auto startGame = Button::create("button.png");
	startGame->setTitleText("START");
	startGame->setTitleFontSize(16);
	startGame->setTitleFontName("Marker Felt.ttf");
	startGame->setPosition(Vec2(visibleSize.width*0.9, visibleSize.height*0.2));
	startGame->addTouchEventListener(CC_CALLBACK_2(MakeMap::touchStartGameEvent, this));
	this->addChild(startGame);

	auto returnButton = Button::create("button.png");
	returnButton->setScale(1);
	returnButton->setTitleText("RETURN");
	returnButton->setTitleFontSize(16);
	returnButton->setTitleFontName("Marker Felt.ttf");
	returnButton->setPosition(Vec2(visibleSize.width*0.9, visibleSize.height*0.1));
	returnButton->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			Director::getInstance()->popScene();
		}
	});
	this->addChild(returnButton);

	return true;
}

void MakeMap::makeSpritePermanent(int i, int j)
{
	this->removeChildByTag(i * 100 + j);
	auto permanent = Sprite::create("Permanent.png");
	permanent->setAnchorPoint(Vec2(0, 0));
	permanent->setScale(unitSize / (permanent->getContentSize()).width, unitSize / (permanent->getContentSize()).height);
	permanent->setPosition(Vec2(coordinateX + i * unitSize, coordinateY + j * unitSize));
	permanent->setTag(i * 100 + j);
	this->addChild(permanent, 100 - i - j);
}

void MakeMap::makeNone(int i, int j)
{
	this->removeChildByTag(i * 100 + j);
	auto None = Button::create("None.png");
	None->setAnchorPoint(Vec2(0, 0));
	None->setScale(unitSize / (None->getContentSize()).width, unitSize / (None->getContentSize()).height);
	None->setPosition(Vec2(coordinateX + i * unitSize, coordinateY + j * unitSize));
	None->setTag(i * 100 + j);
	None->addTouchEventListener(CC_CALLBACK_2(MakeMap::touchMapEvent, this));
	this->addChild(None, 100 - i - j);
}

void MakeMap::touchMapEvent(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		auto target =(Button*)(pSender);
		if (mark == 0) {
			target->loadTextures("None.png","None.png");
			target->setScale(unitSize / (target->getContentSize()).width, unitSize / (target->getContentSize()).height);
			map[target->getTag() / 100][target->getTag() % 100] = 0;
		}
		if (mark == 1) {
			target->loadTextures("Barrier.png", "Barrier.png");
			target->setScale(unitSize / (target->getContentSize()).width, unitSize / (target->getContentSize()).height);
			map[target->getTag() / 100][target->getTag() % 100] = 1;
		}
		if (mark == 2) {
			target->loadTextures("Permanent.png", "Permanent.png");
			target->setScale(unitSize / (target->getContentSize()).width, unitSize / (target->getContentSize()).height);
			map[target->getTag() / 100][target->getTag() % 100] = 2;
		}
	}
}

void MakeMap::touchNoneSelectEvent(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		mark = 0;
	}
}

void MakeMap::touchBarrierSelectEvent(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		mark = 1;
	}
}

void MakeMap::touchPermanentSelectEvent(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		mark = 2;
	}
}

void MakeMap::touchStartGameEvent(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		fstream out("map3.txt");
		for (int j = 0; j < 15; j++) {
			for (int i = 0; i < 17; i++) {
				out << map[i][j] << ' ';
			}
			out << endl;
		}
		auto mapScene = MapScene::createScene();
		Director::getInstance()->pushScene(mapScene);
	}
}

MakeMap::MakeMap()
{
}

MakeMap::~MakeMap()
{
}
