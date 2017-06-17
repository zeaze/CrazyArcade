#ifndef __Map_Scene_H__
#define __Map_Scene_H__
#include "cocos2d.h"
#include <string>
#include <map>
USING_NS_CC;
using namespace std;

class MapScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	static void initMap(string _mapName);
	static void initRole(string _rolePictureName, string runActionPlistName, string runActionPngName, char* RoleRunAction);
	static void initKey();
	static void initDirector();
	static int transformXIntoCoordinateOfMap(int x);
	static int transformYIntoCoordinateOfMap(int y);
	virtual bool init();
	virtual void update(float dt);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);
	bool collisionDetectionRight(int x, int y);
	bool collisionDetectionLeft(int x, int y);
	bool collisionDetectionAbove(int x, int y);
	bool collisionDetectionBelow(int x, int y);
	void updateAction1();
	void updateAction2();
	void updateBomb();
	void updateKey();
	void updateBombExplode(int x, int y, int power);
	void updateBombExplodeAction(int x, int y, int power);
	static void updateMapOpenGL(int x, int y, int mark);
	void releasetools(int x, int y);
	CREATE_FUNC(MapScene);
	MapScene();
	~MapScene();
private:
	static string mapName, rolePictureName;
	static char* RoleRunAction_;
	static int Map[17][15];
	static int bomb[17][15];
	static int mapOpenGl[1024][768];
	static map<int, bool> director, director2, key;
	static int lastBombX, lastBombY;
};
#endif