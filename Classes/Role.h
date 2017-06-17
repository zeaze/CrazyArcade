#ifndef __Role_H__
#define __Role_H__
#include "cocos2d.h"
#include <string>
USING_NS_CC;
using namespace std;

class Role
{
public:
	static int GetSpeed() { return speed; }
	static int GetBombNum() { return bombNum; }
	static int GetPower() { return power; }
	static int GetSpeedMax() { return speedMax; }
	static int GetBombNumMax() { return bombNumMax; }
	static int GetPowerMax() { return powerMax; }
	static int GetReleaseBombNum() { return releaseBombNum; }
	static string GetRoleName() { return roleName; }
	static void SetSpeed(int _speed) { speed = _speed; }
	static void SetBombNum(int _bombNum) { bombNum = _bombNum; }
	static void SetPower(int _power) { power = _power; }
	static void SetSpeedMax(int _speedMax) { speedMax = _speedMax; }
	static void SetBombNumMax(int _bombNumMax) { bombNumMax = _bombNumMax; }
	static void SetPowerMax(int _powerMax) { powerMax = _powerMax; }
	static void SetReleaseBombNum(int _releaseBombNum) { releaseBombNum= _releaseBombNum; }
	static void SetRoleName(string _roleName) { roleName = _roleName; }
	static void AddSpeed() { if (speed < speedMax)speed++; }
	static void AddBombNum() { if (bombNum < bombNumMax)bombNum++; }
	static void AddPower() { if (power < powerMax)power++; }
	static void AddReleaseBombNum() { releaseBombNum++; }
	static void ReduceReleaseBombNum() { releaseBombNum--; }
	Role();
	~Role();
private:
	static int speed, bombNum, power, speedMax, bombNumMax, powerMax, releaseBombNum;
	static string roleName;
};
#endif