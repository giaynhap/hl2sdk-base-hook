#pragma once
#ifndef  INC_KILLMARK
#define INC_KILLMARK 1

#include <stdafx.h>
 
class KillMark
{
public:
	KillMark();
	~KillMark();
	void prepare();
	void  Render();
	void startKillmark(bool isHeadShot,int weaponType, bool revengeKill);
	void revFromDeathMessage(int uid, bool isHeadShot, int weaponType, bool revengeKill=false);

	image_t killMarks[10];
	image_t killEffect[6];

	float m_startTime = 0.0;
	int killIndexImg = 0;
	int scoreKill = 0;
	bool isShow = false;


};

extern KillMark *g_Killmark;
#endif // ! INC_KILLMARK