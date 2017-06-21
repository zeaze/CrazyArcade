#include "MapScene.h"
#include <iostream>
#include <fstream>
#include "ui\CocosGUI.h"
#include "Animation.h"
#include "Constant.h"
#include "Animation.h"
#include "Role.h"
using namespace ui;
using namespace std;
int MapScene::Map[17][15];
int MapScene::bomb[17][15];
bool MapScene::isBombExplode[17][15];
int MapScene::mapOpenGl[1024][768];
string MapScene::mapName, MapScene::rolePictureName;
char* MapScene::RoleRunAction_;
map<int, bool> MapScene::director, MapScene::director2, MapScene::key;
int MapScene::lastBombX = -1, MapScene::lastBombY = -1;
void MapScene::initMap(string _mapName)
{
	mapName = _mapName; 
}

void MapScene::initRole(string _rolePictureName,string runActionPlistName,string runActionPngName,char* RoleRunAction)
{
	rolePictureName = _rolePictureName;
	RoleRunAction_ = RoleRunAction;
	SpriteFrameCache * frameCache = SpriteFrameCache::sharedSpriteFrameCache();
	frameCache->addSpriteFramesWithFile(runActionPlistName, runActionPngName);
	if (rolePictureName == "Role1.png") {
		Role::SetSpeed(role1Speed);
		Role::SetBombNum(role1BombNum);
		Role::SetPower(role1Power);
		Role::SetSpeedMax(role1SpeedMax);
		Role::SetBombNumMax(role1BombNumMax);
		Role::SetPowerMax(role1PowerMax);
		Role::SetReleaseBombNum(0);
	}
	if (rolePictureName == "Role2.png") {
		Role::SetSpeed(role2Speed);
		Role::SetBombNum(role2BombNum);
		Role::SetPower(role2Power);
		Role::SetSpeedMax(role2SpeedMax);
		Role::SetBombNumMax(role2BombNumMax);
		Role::SetPowerMax(role2PowerMax);
		Role::SetReleaseBombNum(0);
	}

	//改变Role的数值
}

void MapScene::initKey()
{
	key.clear();
	key[26] = false;
	key[27] = false;
	key[28] = false;
	key[29] = false;
}

void MapScene::initDirector()
{
	director.clear();
	director[26] = false;
	director[27] = false;
	director[28] = false;
	director[29] = false;
	director2.clear();
	director2[26] = false;
	director2[27] = false;
	director2[28] = false;
	director2[29] = false;
}
int MapScene::transformXIntoCoordinateOfMap(int x)
{
	x = x - coordinateX;
	if (x % unitSize < unitSize / 2)return x / unitSize;
	return x / unitSize + 1;
}

int MapScene::transformYIntoCoordinateOfMap(int y)
{
	y = y - coordinateY;
	if (y % unitSize < unitSize / 2)return y / unitSize;
	return y / unitSize + 1;
}

cocos2d::Scene * MapScene::createScene()
{
	return MapScene::create();
}

bool MapScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	srand((unsigned)time(NULL));
	this->removeAllChildren();
	initKey();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto bg = Sprite::create("GameScene_bg.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	bg->setScale(visibleSize.width / (bg->getContentSize()).width, visibleSize.height / (bg->getContentSize()).height);
	this->addChild(bg, -1);

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
	this->addChild(returnButton, 1);

	auto role = Sprite::create(rolePictureName);
	role->setAnchorPoint(Vec2(0, 0));
	role->setPosition(Vec2(coordinateX + unitSize * 4, coordinateY + unitSize * 4));
	role->setScale(unitSize / (role->getContentSize()).width, unitSize / (role->getContentSize()).height);
	role->setTag(roleTag);
	this->addChild(role, 100 - 4 - 4);

	int x = 0;
	ifstream in(mapName);
	for (int i = 0; i < 1024; i++)
		for (int j = 0; j < 768; j++)
			mapOpenGl[i][j] = 0;
	while (x<255)  //17*15
	{
		int i = x % 17, j = x / 17;
		bomb[i][j] = -1;
		x++;
		in >> Map[i][j];
		if (Map[i][j] == 1) {
			auto barrier = Sprite::create("Barrier.png");
			barrier->setAnchorPoint(Vec2(0, 0));
			barrier->setScale(unitSize / (barrier->getContentSize()).width, unitSize / (barrier->getContentSize()).height);
			barrier->setPosition(Vec2(coordinateX + i * unitSize, coordinateY + j * unitSize));
			barrier->setTag(i * 1000 + j * 10 + 1);
			updateMapOpenGL(coordinateX + i * unitSize, coordinateY + j * unitSize, 1);
			this->addChild(barrier, 100 - i - j);
		}
		else if (Map[i][j] == 2) {
			auto permanent = Sprite::create("Permanent.png");
			permanent->setAnchorPoint(Vec2(0, 0));
			permanent->setScale(unitSize / (permanent->getContentSize()).width, unitSize / (permanent->getContentSize()).width);
			permanent->setPosition(Vec2(coordinateX + i * unitSize, coordinateY + j * unitSize));
			permanent->setTag(i * 1000 + j * 10 + 2);
			updateMapOpenGL(coordinateX + i * unitSize, coordinateY + j * unitSize, 2);
			this->addChild(permanent, 100 - i - j);
		}
		auto bombExplode1 = Sprite::create("bombExplode1.png");
		bombExplode1->setAnchorPoint(Vec2(0, 0));
		bombExplode1->setScale(unitSize / (bombExplode1->getContentSize()).width, unitSize / (bombExplode1->getContentSize()).height);
		bombExplode1->setPosition(Vec2(coordinateX + i * unitSize, coordinateY + j * unitSize));
		bombExplode1->setTag(i * 10000 + j * 100 + 1);
		bombExplode1->setVisible(false);
		this->addChild(bombExplode1, 100 - i - j);
		auto bombExplode2 = Sprite::create("bombExplode2.png");
		bombExplode2->setAnchorPoint(Vec2(0, 0));
		bombExplode2->setScale(unitSize / (bombExplode2->getContentSize()).width, unitSize / (bombExplode2->getContentSize()).height);
		bombExplode2->setPosition(Vec2(coordinateX + i * unitSize, coordinateY + j * unitSize));
		bombExplode2->setTag(i * 10000 + j * 100 + 2);
		bombExplode2->setVisible(false);
		this->addChild(bombExplode2, 100 - i - j);
		auto bombExplode3 = Sprite::create("bombExplode3.png");
		bombExplode3->setAnchorPoint(Vec2(0, 0));
		bombExplode3->setScale(unitSize / (bombExplode3->getContentSize()).width, unitSize / (bombExplode3->getContentSize()).height);
		bombExplode3->setPosition(Vec2(coordinateX + i * unitSize, coordinateY + j * unitSize));
		bombExplode3->setTag(i * 10000 + j * 100 + 3);
		bombExplode3->setVisible(false);
		this->addChild(bombExplode3, 100 - i - j);
		auto bombExplode4 = Sprite::create("bombExplode4.png");
		bombExplode4->setAnchorPoint(Vec2(0, 0));
		bombExplode4->setScale(unitSize / (bombExplode4->getContentSize()).width, unitSize / (bombExplode4->getContentSize()).height);
		bombExplode4->setPosition(Vec2(coordinateX + i * unitSize, coordinateY + j * unitSize));
		bombExplode4->setTag(i * 10000 + j * 100 + 4);
		bombExplode4->setVisible(false);
		this->addChild(bombExplode4, 100 - i - j);

	}

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(MapScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(MapScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	scheduleUpdate();


	auto speed = Label::createWithSystemFont(StringUtils::format("speed:%d/%d",Role::GetSpeed(),Role::GetSpeedMax()), "Arial", 36);
	speed->setPosition(Vec2(visibleSize.width * 0.9, visibleSize.height * 0.77));
	speed->setScale(0.6);
	speed->setColor(Color3B::BLACK);
	speed->setTag(100001);
	this->addChild(speed, 1);

	auto power = Label::createWithSystemFont(StringUtils::format("power:%d/%d", Role::GetPower(), Role::GetPowerMax()), "Arial", 36);
	power->setPosition(Vec2(visibleSize.width * 0.9, visibleSize.height * 0.67));
	power->setScale(0.6);
	power->setColor(Color3B::BLACK);
	power->setTag(100002);
	this->addChild(power, 1);

	auto bombNum = Label::createWithSystemFont(StringUtils::format("bombNum:%d/%d", Role::GetBombNum(), Role::GetBombNumMax()), "Arial", 36);
	bombNum->setPosition(Vec2(visibleSize.width * 0.9, visibleSize.height * 0.57));
	bombNum->setScale(0.6);
	bombNum->setColor(Color3B::BLACK);
	bombNum->setTag(100003);
	this->addChild(bombNum, 1);

	return true;
}

void MapScene::update(float dt)
{
	auto role = ((Sprite*)this->getChildByTag(roleTag));
	role->setZOrder(100 - (role->getPosition().x / unitSize) - (role->getPosition().y / unitSize));
	int i = transformXIntoCoordinateOfMap(role->getPosition().x), j = transformYIntoCoordinateOfMap(role->getPosition().y);
	if (Map[i][j] != 3) {
		lastBombX = -1;
		lastBombY = -1;
	}
	if (Map[i][j] == -1) {
		Role::AddSpeed();
		((Label*)this->getChildByTag(100001))->setString(StringUtils::format("speed:%d/%d", Role::GetSpeed(), Role::GetSpeedMax()));
		this->removeChildByTag(i * 1000 + j * 10 - 1);
		Map[i][j] = 0;
		updateMapOpenGL(coordinateX + i*unitSize, coordinateY + unitSize*j, 0);
		
	}	
	if (Map[i][j] == -2) {
		Role::AddPower();
		((Label*)this->getChildByTag(100002))->setString(StringUtils::format("power:%d/%d", Role::GetPower(), Role::GetPowerMax()));
		this->removeChildByTag(i * 1000 + j * 10 - 2);
		Map[i][j] = 0;
		updateMapOpenGL(coordinateX + i*unitSize, coordinateY + unitSize*j, 0);
	}
	if (Map[i][j] == -3) {
		Role::AddBombNum();
		this->removeChildByTag(i * 1000 + j * 10 - 3);
		((Label*)this->getChildByTag(100003))->setString(StringUtils::format("bombNum:%d/%d", Role::GetBombNum(), Role::GetBombNumMax()));
		Map[i][j] = 0;
		updateMapOpenGL(coordinateX + i*unitSize, coordinateY + unitSize*j, 0);
	}	
	
	//Map[i][j] = -4;
	updateBomb();
	//Map[i][j] = 0;
	updateKey();
	updateAction1();
	updateAction2();
	
}

void MapScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	auto role = ((Sprite*)this->getChildByTag(roleTag));
	int x = role->getPosition().x, y = role->getPosition().y;
	int i = transformXIntoCoordinateOfMap(x), j = transformYIntoCoordinateOfMap(y);
	if ((int)keyCode == 26) {
		initKey();
		key[26] = true;
	}
	if ((int)keyCode == 27) {
		initKey();
		key[27] = true;
	}
	if ((int)keyCode == 28) {
		initKey();
		key[28] = true;
	}
	if ((int)keyCode == 29) {
		initKey();
		key[29] = true;
	}

	if ((int)keyCode == 59) {   
		if ((Role::GetBombNum()>Role::GetReleaseBombNum())&&(!this->getChildByTag(i * 1000 + j * 10 + 3))) {
			bomb[i][j] = bombExplosionTime;
			isBombExplode[i][j] = false;
			Map[i][j] = 3;
			updateMapOpenGL(coordinateX + i * unitSize, coordinateY + j * unitSize, 3);
			Role::AddReleaseBombNum();
			auto bomb = Sprite::create("Bomb.png");
			bomb->setScale(unitSize / (bomb->getContentSize()).width, unitSize / (bomb->getContentSize()).height);
			bomb->setPosition(Vec2(coordinateX + i * unitSize, coordinateY + j * unitSize));
			bomb->setAnchorPoint(Vec2(0, 0));
			bomb->setTag(i * 1000 + j * 10 + 3);
			//bomb->runAction(GameAction::createAnimate2());
			lastBombX = i;
			lastBombY = j;
			this->addChild(bomb, 100 - i - j);
		}
	}
}

void MapScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event)
{
	if((int)keyCode == 26 || (int)keyCode == 27 || (int)keyCode == 28 || (int)keyCode == 29)
	key[(int)keyCode] = false;
}

bool MapScene::collisionDetectionRight(int x, int y)
{
	int i = 0, j = unitSize - 1;
	if (transformXIntoCoordinateOfMap(x) == lastBombX && transformXIntoCoordinateOfMap(y) == lastBombY
		&& (mapOpenGl[x + unitSize + i][y + i] == 3 || mapOpenGl[x + unitSize + i][y + j] == 3)) return false;
	if (mapOpenGl[x + unitSize + i][y + i] > 0) return true;;
	if (mapOpenGl[x + unitSize + i][y + j] > 0) return true;;
	return false;
}

bool MapScene::collisionDetectionLeft(int x, int y)
{
	int i = 0, j = unitSize - 1;
	if (transformXIntoCoordinateOfMap(x) == lastBombX && transformXIntoCoordinateOfMap(y) == lastBombY
		&& (mapOpenGl[x - unitSize + j][y + j] == 3 || mapOpenGl[x - unitSize + j][y + i] == 3)) return false;
	if (mapOpenGl[x - unitSize + j][y + j] > 0) return true;;
	if (mapOpenGl[x - unitSize + j][y + i] > 0) return true;;
	return false;
}

bool MapScene::collisionDetectionAbove(int x, int y)
{
	int i = 0, j = unitSize - 1;
	if (transformXIntoCoordinateOfMap(x) == lastBombX && transformXIntoCoordinateOfMap(y) == lastBombY
		&& (mapOpenGl[x + i][y + unitSize + i] == 3 || mapOpenGl[x + j][y + unitSize + i] == 3)) return false;
	if (mapOpenGl[x + i][y + unitSize + i] > 0) return true;
	if (mapOpenGl[x + j][y + unitSize + i] > 0) return true;
	return false;
}

bool MapScene::collisionDetectionBelow(int x, int y)
{
	int i = 0, j = unitSize - 1;
	if (transformXIntoCoordinateOfMap(x) == lastBombX && transformXIntoCoordinateOfMap(y) == lastBombY
		&& (mapOpenGl[x + j][y - unitSize + j] == 3 || mapOpenGl[x + i][y - unitSize + j] == 3)) return false;
	if (mapOpenGl[x + j][y - unitSize + j] > 0) return true;
	if (mapOpenGl[x + i][y - unitSize + j] > 0) return true;
	return false;
}

void MapScene::updateAction1()
{
	auto role = ((Sprite*)this->getChildByTag(roleTag));
	if (director[27] && !role->getActionByTag(11)) {  //右
		auto move1 = RepeatForever::create(MoveBy::create(0.1, Point(Role::GetSpeed(), 0)));
		move1->setTag(11);
		role->runAction(move1);
	}
	if (director[26] && !role->getActionByTag(21)) {   //左
		auto move1 = RepeatForever::create(MoveBy::create(0.1, Point(-Role::GetSpeed(), 0)));
		move1->setTag(21);
		role->runAction(move1);
	}
	if (director[29] && !role->getActionByTag(31)) {  //下
		auto move1 = RepeatForever::create(MoveBy::create(0.1, Point(0, -Role::GetSpeed())));
		move1->setTag(31);
		role->runAction(move1);
	}
	if (director[28] && !role->getActionByTag(41)) {   //上
		auto move1 = RepeatForever::create(MoveBy::create(0.1, Point(0, Role::GetSpeed())));
		move1->setTag(41);
		role->runAction(move1);
	}
	if (!director[27]) role->stopActionByTag(11);
	if (!director[26]) role->stopActionByTag(21);
	if (!director[29]) role->stopActionByTag(31);
	if (!director[28]) role->stopActionByTag(41);
}

void MapScene::updateAction2()
{
	auto role = ((Sprite*)this->getChildByTag(roleTag));
	if (director2[27] && !role->getActionByTag(12)) {  //右
		auto move2 = GameAction::CreationRoleRunAction(Vec2(1, 0), RoleRunAction_, 7, 0.1f, -1);
		move2->setTag(12);
		role->runAction(move2);
	}
	if (director2[26] && !role->getActionByTag(22)) {   //左
		auto move2 = GameAction::CreationRoleRunAction(Vec2(-1, 0), RoleRunAction_, 7, 0.1f, -1);
		move2->setTag(22);
		role->runAction(move2);
	}
	if (director2[29] && !role->getActionByTag(32)) {  //下
		auto move2 = GameAction::CreationRoleRunAction(Vec2(0, -1), RoleRunAction_, 7, 0.1f, -1);
		move2->setTag(32);
		role->runAction(move2);
	}
	if (director2[28] && !role->getActionByTag(42)) {   //上
		auto move2 = GameAction::CreationRoleRunAction(Vec2(0, 1), RoleRunAction_, 7, 0.1f, -1);
		move2->setTag(42);
		role->runAction(move2);
	}
	if (!director2[27]) role->stopActionByTag(12);
	if (!director2[26]) role->stopActionByTag(22);
	if (!director2[29]) role->stopActionByTag(32);
	if (!director2[28]) role->stopActionByTag(42);
	if (!director2[26] && !director2[27] && !director2[28] && !director2[29]) role->setTexture(rolePictureName);
}

void MapScene::updateBomb()
{
	for (int i = 0; i < 17; i++)
		for (int j = 0; j < 15; j++) {
			bomb[i][j]--;
			if (bomb[i][j] == 30) {
				isBombExplode[i][j] = true;
				this->getChildByTag(i * 1000 + j * 10 + 3)->runAction(GameAction::createAnimate2());
				updateBombExplodeAction(i, j, Role::GetPower());
			}
			if (bomb[i][j] == 0) {
				this->removeChildByTag(i * 1000 + j * 10 + 3);
				Role::ReduceReleaseBombNum();
				//CCLOG("%d", Role::GetReleaseBombNum());
				updateMapOpenGL(coordinateX + i * unitSize, coordinateY + j * unitSize, 0);
				Map[i][j] = 0;
				updateBombExplode(i, j, Role::GetPower());
			}
		}
}

void MapScene::updateKey()
{
	auto role = ((Sprite*)this)->getChildByTag(roleTag);
	int i = role->getPosition().x, j = role->getPosition().y;
	int x = i - coordinateX, y = j - coordinateY;
	while (x - unitSize >= 0)x -= unitSize;
	while (y - unitSize >= 0)y -= unitSize;
	initDirector();
	if (key[27]) {  //右
		if (!collisionDetectionRight(i, j)) {  
			director[27] = true;
			director2[27] = true;

		}
		else {
			if (y < unitSize / 4 && y>0) {
				director[29] = true;
				director2[29] = true;

			}
			else if (y > unitSize / 4 * 3) {
				director[28] = true;
				director2[28] = true;
			}
			else director2[27] = true;
		}
	}

	if (key[26]) {   //左
		if (!collisionDetectionLeft(i, j)) {
			director[26] = true;
			director2[26] = true;
		}
		else {
			if (y < unitSize / 4 && y>0) {
				director[29] = true;
				director2[29] = true;
			}
			else if (y > unitSize / 4 * 3) {
				director[28] = true;
				director2[28] = true;
			}
			else director2[26] = true;
		}
	}
	
	if (key[29]) {  //下
		if (!collisionDetectionBelow(i, j)) {
			director[29] = true;
			director2[29] = true;
		}
		else {
			if (x < unitSize / 4 && x>0) {
				director[26] = true;
				director2[26] = true;
			}
			else if (x > unitSize / 4 * 3) {
				director[27] = true;
				director2[27] = true;
			}
			else director2[29] = true;
		}
	}
	
	if (key[28]) {   //上
		if (!collisionDetectionAbove(i, j)) {
			director[28] = true;
			director2[28] = true;
		}
		else {
			if (x < unitSize / 4 && x>0) {
				director[26] = true;
				director2[26] = true;
			}
			else if (x > unitSize / 4 * 3) {
				director[27] = true;
				director2[27] = true;
			}
			else director2[28] = true;
		}
	}
}

void MapScene::updateBombExplode(int x, int y, int power)
{
	int lenX = 0, len_X = 0, lenY = 0, len_Y = 0;
	while (Map[x + lenX + 1][y] <= 0 && lenX < power) lenX++;
	while (Map[x - len_X - 1][y] <= 0 && len_X < power) len_X++;
	while (Map[x][y + lenY + 1] <= 0 && lenY < power) lenY++;
	while (Map[x][y - len_Y - 1] <= 0 && len_Y < power) len_Y++;
		
	if (Map[x + lenX + 1][y] == 1 && lenX < power) {
		this->removeChildByTag((x + lenX + 1) * 1000 + y * 10 + 1);
		Map[x + lenX + 1][y] = 0;
		updateMapOpenGL(coordinateX + unitSize*(x + lenX + 1), coordinateY + unitSize*y, 0);
		releasetools(x + lenX + 1, y);
	}
	if (Map[x - len_X - 1][y] == 1 && len_X < power) {
		this->removeChildByTag((x - len_X - 1) * 1000 + y * 10 + 1);
		Map[x - len_X - 1][y] = 0;
		updateMapOpenGL(coordinateX + unitSize*(x - len_X - 1), coordinateY + unitSize*y, 0);
		releasetools(x - len_X - 1, y);
	}
	if (Map[x][y + lenY + 1] == 1 && lenY < power) {
		this->removeChildByTag(x * 1000 + (y + lenY + 1) * 10 + 1);
		Map[x][y + lenY + 1] = 0;
		updateMapOpenGL(coordinateX + unitSize*x, coordinateY + unitSize*(y + lenY + 1), 0);
		releasetools(x, y + lenY + 1);
	}
	if (Map[x][y - len_Y - 1] == 1 && len_Y < power) {
		this->removeChildByTag(x * 1000 + (y - len_Y - 1) * 10 + 1);
		Map[x][y - len_Y - 1] = 0;
		updateMapOpenGL(coordinateX + unitSize*x, coordinateY + unitSize*(y - len_Y - 1), 0);
		releasetools(x, y - len_Y - 1);
	}
	
	if (Map[x + lenX + 1][y] == 3 && lenX < power && !isBombExplode[x + lenX + 1][y]) {     //引爆炸弹
		bomb[x + lenX + 1][y] = 31;
	}
	if (Map[x - len_X - 1][y] == 3 && len_X < power && !isBombExplode[x - len_X - 1][y]){
		bomb[x - len_X - 1][y] = 31;
	}
	if (Map[x][y + lenY + 1] == 3 && lenY < power && !isBombExplode[x][y + lenY + 1]) {
		bomb[x][y + lenY + 1] = 31;
	}
	if (Map[x][y - len_Y - 1] == 3 && len_Y < power && !isBombExplode[x][y - len_Y - 1]) {
		bomb[x][y - len_Y - 1] = 31;
	}
	auto role = ((Sprite*)this->getChildByTag(roleTag));
	int i = transformXIntoCoordinateOfMap(role->getPosition().x), j = transformYIntoCoordinateOfMap(role->getPosition().y);
	if ((x == i&&y - len_Y <= j&&j <= y + lenY) || (x - len_X <= i&&i <= x + lenX&&y == j)) {
		//this->removeChildByTag(roleTag);
		this->unscheduleUpdate();

		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto bg = Sprite::create("DIE_bg.png");
		bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		bg->setScale(visibleSize.width / (bg->getContentSize()).width, visibleSize.height / (bg->getContentSize()).height);
		this->addChild(bg, 10000);
	
		auto reStartGame = Button::create("button.png");
		reStartGame->setTitleText("RESTART");
		reStartGame->setTitleFontSize(16);
		reStartGame->setScale(2);
		reStartGame->setTitleFontName("Marker Felt.ttf");
		reStartGame->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.5));
		reStartGame->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
			if (type == Widget::TouchEventType::ENDED) {
				Director::getInstance()->popScene();
			}
		});
		this->addChild(reStartGame,100000);
	}
}

void MapScene::updateBombExplodeAction(int x, int y, int power)
{
	int lenX = 0, len_X = 0, lenY = 0, len_Y = 0;
	while ((Map[x + lenX + 1][y] <= 0 || (Map[x + lenX + 1][y] == 3 && bomb[x + lenX + 1][y] <30)) && lenX < power) {
		lenX++;
		this->getChildByTag((x + lenX) * 10000 + y * 100 + 1)->stopAllActions();
		this->getChildByTag((x + lenX) * 10000 + y * 100 + 1)->setVisible(false);
		this->getChildByTag((x + lenX) * 10000 + y * 100 + 1)->runAction(Blink::create(0.5, 1));
	}
	while ((Map[x - len_X - 1][y] <= 0 || (Map[x - len_X - 1][y] == 3 && bomb[x - len_X - 1][y] <30)) && len_X < power) {
		len_X++;
		this->getChildByTag((x - len_X) * 10000 + y * 100 + 2)->stopAllActions();
		this->getChildByTag((x - len_X) * 10000 + y * 100 + 2)->setVisible(false);
		this->getChildByTag((x - len_X) * 10000 + y * 100 + 2)->runAction(Blink::create(0.5, 1));
	}
	while ((Map[x][y + lenY + 1] <= 0 || (Map[x][y + lenY + 1] == 3 && bomb[x][y + lenY + 1] <30)) && lenY < power) {
		lenY++;
		this->getChildByTag(x * 10000 + (y + lenY) * 100 + 3)->stopAllActions();
		this->getChildByTag(x * 10000 + (y + lenY) * 100 + 3)->setVisible(false);
		this->getChildByTag(x * 10000 + (y + lenY) * 100 + 3)->runAction(Blink::create(0.5, 1));
	}
	while ((Map[x][y - len_Y - 1] <= 0 || (Map[x][y - len_Y - 1] == 3 && bomb[x][y - len_Y - 1] <30)) && len_Y < power) {
		len_Y++;
		this->getChildByTag(x * 10000 + (y - len_Y) * 100 + 4)->stopAllActions();
		this->getChildByTag(x * 10000 + (y - len_Y) * 100 + 4)->setVisible(false);
		this->getChildByTag(x * 10000 + (y - len_Y) * 100 + 4)->runAction(Blink::create(0.5, 1));
	}
	if (Map[x + lenX + 1][y] == 1 && lenX < power) {     
		lenX++;
		this->getChildByTag((x + lenX) * 10000 + y * 100 + 1)->stopAllActions();
		this->getChildByTag((x + lenX) * 10000 + y * 100 + 1)->setVisible(false);
		this->getChildByTag((x + lenX) * 10000 + y * 100 + 1)->runAction(Blink::create(0.5, 1));
	}
	if (Map[x - len_X - 1][y] == 1 && len_X < power) {
		len_X++;
		this->getChildByTag((x - len_X) * 10000 + y * 100 + 2)->stopAllActions();
		this->getChildByTag((x - len_X) * 10000 + y * 100 + 2)->setVisible(false);
		this->getChildByTag((x - len_X) * 10000 + y * 100 + 2)->runAction(Blink::create(0.5, 1));
	}
	if (Map[x][y + lenY + 1] == 1 && lenY < power) {
		lenY++;
		this->getChildByTag(x * 10000 + (y + lenY) * 100 + 3)->stopAllActions();
		this->getChildByTag(x * 10000 + (y + lenY) * 100 + 3)->setVisible(false);
		this->getChildByTag(x * 10000 + (y + lenY) * 100 + 3)->runAction(Blink::create(0.5, 1));
	}
	if (Map[x][y - len_Y - 1] == 1 && len_Y < power) {
		len_Y++;
		this->getChildByTag(x * 10000 + (y - len_Y) * 100 + 4)->stopAllActions();
		this->getChildByTag(x * 10000 + (y - len_Y) * 100 + 4)->setVisible(false);
		this->getChildByTag(x * 10000 + (y - len_Y) * 100 + 4)->runAction(Blink::create(0.5, 1));
	}
}

void MapScene::updateMapOpenGL(int x, int y,int mark)
{
	for (int i = 0; i < unitSize; i++)
		for (int j = 0; j < unitSize; j++)
			mapOpenGl[x + i][y + j] = mark;
}

void MapScene::releasetools(int x, int y)
{
	int ran = rand() % 5;
	//CCLOG("ran=%d", ran);
	if (ran == 1) {
		auto tool = Sprite::create("speedTool.png");
		tool->setPosition(Vec2(coordinateX + x * unitSize, coordinateY + y * unitSize));
		tool->setTag(x * 1000 + y * 10 - 1);
		tool->setScale(unitSize / (tool->getContentSize()).width, unitSize / (tool->getContentSize()).height);
		tool->setAnchorPoint(Vec2(0, 0));
		this->addChild(tool);
		Map[x][y] = -1;
		updateMapOpenGL(coordinateX + x*unitSize, coordinateY + unitSize*y, -1);
	}
	if (ran == 2) {
		auto tool = Sprite::create("powerTool.png");
		tool->setPosition(Vec2(coordinateX + x * unitSize, coordinateY + y * unitSize));
		tool->setTag(x * 1000 + y * 10 - 2);
		tool->setScale(unitSize / (tool->getContentSize()).width, unitSize / (tool->getContentSize()).height);
		tool->setAnchorPoint(Vec2(0, 0));
		this->addChild(tool);
		Map[x][y] = -2;
		updateMapOpenGL(coordinateX + x*unitSize, coordinateY + unitSize*y, -2);
	}
	if (ran == 3) {
		auto tool = Sprite::create("bombTool.png");
		tool->setPosition(Vec2(coordinateX + x * unitSize, coordinateY + y * unitSize));
		tool->setTag(x * 1000 + y * 10 - 3);
		tool->setScale(unitSize / (tool->getContentSize()).width, unitSize / (tool->getContentSize()).height);
		tool->setAnchorPoint(Vec2(0, 0));
		this->addChild(tool);
		Map[x][y] = -3;
		updateMapOpenGL(coordinateX + x*unitSize, coordinateY + unitSize*y, -3);
	}


}

MapScene::MapScene()
{
}

MapScene::~MapScene()
{
}
